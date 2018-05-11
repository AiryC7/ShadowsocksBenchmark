#include "src/Benchmark.h"
#include "src/SurgeParser.h"
#include "src/Http.h"
#include "src/Options.h"
#include "src/Formatter.h"

using namespace std;

int main(int argc,char **argv) {
	try {
		Options options = Options::parse(argc,argv);
		list<ProxyPtr> proxies;
		list<Benchmark::BenchmarkResult> results;

		for ( Options::SurgeUrl const &url : options.surgeUrls ) {
			string data = Http::text(url.url);
			SurgeParser::parse(data,proxies,url.group);
		}

		Benchmark::benchmark(proxies,results,options.threads);

		Formatter::format(results,options.printFormat);
	} catch ( Exception &e ) {
		cout << "Exception: " << e.what() << endl;
	}

	return 0;
}
