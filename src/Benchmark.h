#pragma once

#include "Proxy.h"
#include "Process.h"
#include "Http.h"
#include "Exception.h"
#include "SimpleTaskExecutor.h"

#include <list>
#include <mutex>
#include <atomic>
#include <string>

using std::list;

#define BENCHMARK_URL        "https://www.google.com/generate_204"
#define BENCHMARK_DNS        "8.8.8.8"
#define BENCHMARK_TIMEOUT    2
#define BENCHMARK_PORT_BEGIN 23333

class Benchmark {
public:
	class BenchmarkResult;

public:
	static void benchmark(list<ProxyPtr> &input,list<BenchmarkResult> &output,int threads = 12 ,int pingCount = 12);
};

class Benchmark::BenchmarkResult {
public:
	ProxyPtr proxy;
	int      delay;
	int      count;
	int      lost;
};
