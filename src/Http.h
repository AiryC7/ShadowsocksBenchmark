#pragma once

#include <string>
#include <sstream>
#include <cstdint>
#include <cstddef>
#include <curl/curl.h>

#include "Exception.h"

using std::string;
using std::stringstream;

class Http {
public:
	static string  text(string const &url, int timeout = 30,string const &proxy = string(), string const &dns = string());
	static int64_t ping(string const &url,int timeout = 2,string const &proxy = string(), string const &dns = string());

private:
	class CurlGlobalHandle;
};

class Http::CurlGlobalHandle {
public:
	CurlGlobalHandle(void) noexcept;
	~CurlGlobalHandle(void) noexcept;

private:
	static CurlGlobalHandle handle;
};
