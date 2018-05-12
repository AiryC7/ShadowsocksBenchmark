#include "Formatter.h"


static std::function<void (Benchmark::BenchmarkResult &r,ostream &stream)> print[9] = {
//print[0]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(12) << r.proxy->group << " ";
	},

//print[1]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(40) << r.proxy->name << " ";
	},

//print[2]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(12) << r.proxy->host << " ";
	},

	//print[2]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(16) << r.proxy->host << " ";
	},

//print[3]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(5) << r.proxy->port << " ";
	},

//print[4]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(10) << r.proxy->method << " ";
	},

//print[5]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(10) << r.proxy->password << " ";
	},

//print[6]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(24) << r.proxy->plugin_option << " ";
	},

//print[7]
	[](Benchmark::BenchmarkResult &r,ostream &stream)->void{
		stream << std::setiosflags(std::ios::left) << std::setw(8) << (r.delay > 0 ? std::to_string(r.delay) + "ms" : "timeout") << " ";
	}
};

void Formatter::format(list<Benchmark::BenchmarkResult> &data, list<int> &format, std::ostream &stream) {
	for ( Benchmark::BenchmarkResult &r : data ) {
		for ( int f : format ) {
			print[f](r,stream);
		}
		stream << std::endl;
	}
}
