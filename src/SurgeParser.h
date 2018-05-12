#pragma once

#include <list>
#include <string>
#include <sstream>
#include <regex>

#include "Exception.h"
#include "Proxy.h"
#include "DnsLookup.h"

using std::regex;
using std::list;
using std::string;
using std::stringstream;

class SurgeParser {
public:
	static void parse(string const &input,list<ProxyPtr> &output,string const &group = "");
};
