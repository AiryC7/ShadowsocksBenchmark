#include "Benchmark.h"

void Benchmark::benchmark(list<ProxyPtr> &input,list<BenchmarkResult> &output,int threads,int pingCount) {
	std::atomic_int port(BENCHMARK_PORT_BEGIN);
	std::mutex mutex;

	SimpleTaskExecutor<list<ProxyPtr>,ProxyPtr>(input,[&](ProxyPtr p) {
		int currentPort = port++;
		Process process = Process::startSsLocal(*p,std::to_string(currentPort));
		BenchmarkResult result;
		int delayTotal = 0;

		result.proxy = p;
		result.count = pingCount;
		result.lost = 0;
		process.sleep(1000);

		for ( int i = 0 ; i < pingCount ; i++ ) {
			try {
				delayTotal += Http::ping(BENCHMARK_URL,BENCHMARK_TIMEOUT,std::string("socks5h://127.0.0.1:") + std::to_string(currentPort), BENCHMARK_DNS);
			} catch (Exception &e) {
				result.lost += 1;
			}
		}
		
		result.delay = delayTotal == 0 ? -1 : delayTotal / ( pingCount - result.lost );

		process.kill();
		process.waitFor();

		mutex.lock();
		output.push_back(result);
		mutex.unlock();
	}).exec(threads);

	output.sort([](BenchmarkResult const &p1,BenchmarkResult const &p2)->bool{
		return (unsigned)p1.delay < (unsigned)p2.delay;
	});
}
