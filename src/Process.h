#pragma once

#include "Proxy.h"
#include "Exception.h"
#include "DnsLookup.h"

#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <resolv.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

using std::string;

class Process {
public:
	Process(pid_t pid);

public:
	int  waitFor(void);
	void sleep(int milliseconds);
	void kill(int signal = SIGTERM);

private:
	pid_t pid;

public:
	static Process startSsLocal(Proxy const &proxy,string const &localPort = "1080",string const &localAddress = "127.0.0.1");
};
