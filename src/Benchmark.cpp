#include "Benchmark.h"

void Benchmark::benchmark(list<ProxyPtr> &input,list<BenchmarkResult> &output,int threads) {
	std::atomic_int port(BENCHMARK_PORT_BEGIN);
	std::mutex mutex;

	SimpleTaskExecutor<list<ProxyPtr>,ProxyPtr>(input,[&](ProxyPtr p) {
		int currentPort = port++;
		Process process = Process::startSsLocal(*p,std::to_string(currentPort));
		BenchmarkResult result;

		result.proxy = p;
		process.sleep(1000);

		try {
			result.delay = Http::ping(BENCHMARK_URL,BENCHMARK_TIMEOUT,std::string("socks5h://127.0.0.1:") + std::to_string(currentPort), BENCHMARK_DNS);
		} catch (Exception &e) {
			result.delay = -1;
		}

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
