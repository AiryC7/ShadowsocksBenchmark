#include "Options.h"

static const char *optionsString = "t:p:h";

static void parse_print_format(char *arg,list<int> &out) {
	out.clear();

	char *p = strtok(arg,",");
	do {
		if      ( strcmp(p,"GROUP") == 0 )
			out.push_back(Options::GROUP);
		else if ( strcmp(p,"NAME") == 0 )
			out.push_back(Options::NAME);
		else if ( strcmp(p,"HOST") == 0 )
			out.push_back(Options::HOST);
		else if ( strcmp(p,"ADDRESS") == 0 )
			out.push_back(Options::ADDRESS);
		else if ( strcmp(p,"PORT") == 0 )
			out.push_back(Options::PORT);
		else if ( strcmp(p,"METHOD") == 0 )
			out.push_back(Options::METHOD);
		else if ( strcmp(p,"PASSWORD") == 0 )
			out.push_back(Options::PASSWORD);
		else if ( strcmp(p,"OBFSOPTS") == 0 )
			out.push_back(Options::OBFSOPTS);
		else if ( strcmp(p,"DELAY") == 0 )
			out.push_back(Options::DELAY);
		else throw Exception(string("Unsupported print format ") + p);
	} while (( p = strtok(nullptr,",")) != nullptr );
}

static void parse_surge_url(char *arg,list<Options::SurgeUrl> &out) {
	char *p = strchr(arg,'#');
	Options::SurgeUrl result;

	if ( p ) {
		*p++ = 0;
		result.group = arg;
		result.url   = p;
	} else {
		result.url   = arg;
	}

	out.push_back(result);
}

Options Options::parse(int argc,char **argv) {
	int opt;
	Options result;

	while (( opt = getopt(argc,argv,optionsString)) > 0 ) {
		switch ( opt ) {
		case 't' :
			result.threads = atoi(optarg);
			break;
		case 'p' :
			parse_print_format(optarg,result.printFormat);
			break;
		case 'h' :
			printHelp();
			exit(1);
			break;
		default :
			printHelp();
			throw Exception(string("Unsupported option ") + argv[optind]);
		}
	}

	for (; optind < argc ; optind++ ) {
		parse_surge_url(argv[optind],result.surgeUrls);
	}

	return result;
}

void Options::printHelp(ostream &stream) {
	stream << "Usage: ss_bm [-t <count>] [-p <ITEM1,ITEM2...>] <Group#SurgeURL>..." << std::endl;
	stream << "A tool to benchmark shadowsocks hosts. Download hosts list from Surge configure url." << std::endl << std::endl;
	stream << "Options:" << std::endl;
	stream << "    " << "-p" << "  " << "Output list. [GROUP,NAME,HOST,PORT,PASSWORD,METHOD,OBFSOPTS,DELAY]" << std::endl;
	stream << "    " << "-t" << "  " << "Test threads." << std::endl << std::endl;
	stream << "Example:" << std::endl;
	stream << "    " << "ss_bm \"Self#https://my.cloud.org/fskwidnjfjsownbrhculame?is_ss=1\"" << std::endl;
	stream << "    " << "ss_bm -t 10 -p DELAY,GROUP,HOST \"Self#https://my.cloud.org/fskwidnjfjsownbrhculame?is_ss=1\"" << std::endl;
}

