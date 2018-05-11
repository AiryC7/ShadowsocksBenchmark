#pragma once

#include <string>
#include <memory>

using std::string;
using std::wstring;

class Proxy {
public:
	string group;
	string name;
	string host;
	string port;
	string method;
	string password;

public:
	int type;
	string plugin_option;

public:
	enum {
		PROXY_SHADOWSOCKS,
		PROXY_SHADOWSOCKS_SIMPLE_OBFS
	};

public:
	inline static std::shared_ptr<Proxy> create(void);
};

typedef std::shared_ptr<Proxy> ProxyPtr;

std::shared_ptr<Proxy> Proxy::create(void) {
	return std::make_shared<Proxy>();
}
