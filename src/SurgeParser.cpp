#include "SurgeParser.h"

static const regex PATTERN_PROXY_SHADOWSOCKS = regex("^(.+)=\\s*custom,([0-9a-zA-Z\\.:\\-]+),([0-9]+),([a-zA-Z0-9\\-]+),(\\S+),.+module\\s*$");
static const regex PATTERN_PROXY_SHADOWSOCKS_SIMPLE_OBFS = regex("^(.+)=\\s*custom,([0-9a-zA-Z\\.:\\-]+),([0-9]+),([a-zA-Z0-9\\-]+),(\\S+),.+module,(obfs=.+)\\s*$");

static string trim(string const &str) {
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first) {
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

static string replace(string const &str,char o,char n) {
	string result = str;
	size_t pos;
	while (( pos = result.find(o)) != string::npos )
		result[pos] = n;
	return result;
}

void SurgeParser::parse(const string &input, list<ProxyPtr> &output,string const &group) {
	stringstream stream(input);
	string line;
	bool inProxyBlock = false;

	while ( std::getline(stream,line) ) {
		line = trim(line);
		if ( line.empty() )
			continue;

		if ( line[0] == '[' && line[line.length()-1] == ']' )
			inProxyBlock = (line == "[Proxy]");

		if ( inProxyBlock ) {
			std::smatch result;
			if ( std::regex_match(line,result,PATTERN_PROXY_SHADOWSOCKS_SIMPLE_OBFS) ) {
				ProxyPtr proxy = Proxy::create();

				proxy->type          = Proxy::PROXY_SHADOWSOCKS_SIMPLE_OBFS;
				proxy->group         = group;
				proxy->name          = trim(result[1]);
				proxy->host          = trim(result[2]);
				proxy->address       = DnsLookup::lookup(proxy->host);
				proxy->port          = trim(result[3]);
				proxy->method        = trim(result[4]);
				proxy->password      = trim(result[5]);
				proxy->plugin_option = trim(replace(result[6],',',';'));

				output.push_back(proxy);
			} else if ( std::regex_match(line,result,PATTERN_PROXY_SHADOWSOCKS) ) {
				ProxyPtr proxy = Proxy::create();

				proxy->type          = Proxy::PROXY_SHADOWSOCKS;
				proxy->group         = group;
				proxy->name          = trim(result[1]);
				proxy->host          = trim(result[2]);
				proxy->address       = DnsLookup::lookup(proxy->host);
				proxy->port          = trim(result[3]);
				proxy->method        = trim(result[4]);
				proxy->password      = trim(result[5]);

				output.push_back(proxy);
			}
		}
	}
}
