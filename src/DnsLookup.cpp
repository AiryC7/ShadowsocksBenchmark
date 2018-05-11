#include "DnsLookup.h"

string DnsLookup::lookup(string const &host) {
	struct addrinfo *answer = nullptr;
	char buffer[INET6_ADDRSTRLEN];

	if ( getaddrinfo(host.c_str(), nullptr, nullptr, &answer) || answer == nullptr ) {
		freeaddrinfo(answer);
		throw Exception("Lookup dns for " + host + " failure. ");
	}

	inet_ntop(answer->ai_family,&(((struct sockaddr_in *)(answer->ai_addr))->sin_addr),buffer,INET6_ADDRSTRLEN);

	freeaddrinfo(answer);

	return buffer;
}
