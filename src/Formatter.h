#pragma once

#include "Benchmark.h"
#include "Options.h"

#include <iostream>
#include <iomanip>
#include <list>
#include <functional>
#include <string>

using std::wostream;
using std::string;
using std::wstring;

class Formatter {
public:
	static void format(list<Benchmark::BenchmarkResult> &data,list<int> &format,ostream &stream = std::cout);
};
