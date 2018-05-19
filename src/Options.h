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
		ADDRESS  = 3,
		PORT     = 4,
		METHOD   = 5,
		PASSWORD = 6,
		OBFSOPTS = 7,
		DELAY    = 8,
		LOST     = 9
	};

public:
	list<SurgeUrl> surgeUrls;
	list<int>      printFormat = {DELAY,LOST,GROUP,NAME};
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
