#pragma once

#include "Exception.h"

#include <list>
#include <string>
#include <iostream>
#include <getopt.h>
#include <cstring>

using std::list;
using std::string;
using std::ostream;

class Options {
public:
	class SurgeUrl;

public:
	enum {
		GROUP    = 0,
		NAME     = 1,
		HOST     = 2,
		PORT     = 3,
		METHOD   = 4,
		PASSWORD = 5,
		OBFSOPTS = 6,
		DELAY    = 7
	};

public:
	list<SurgeUrl> surgeUrls;
	list<int>      printFormat = {DELAY,GROUP,NAME};
	int threads                = 8;

public:
	static Options parse(int argc,char **argv);
	static void    printHelp(ostream &stream = std::cerr);
};

class Options::SurgeUrl {
public:
	string url;
	string group;
};
