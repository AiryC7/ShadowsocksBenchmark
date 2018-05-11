#pragma once

#include "Exception.h"

#include <string>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>

using std::string;

class DnsLookup {
public:
	static string lookup(string const &host);
};
