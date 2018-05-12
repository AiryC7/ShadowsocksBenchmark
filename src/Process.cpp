#include "Process.h"

Process Process::startSsLocal(Proxy const &proxy,string const &localPort,string const &localAddress) {
	if ( proxy.type != Proxy::PROXY_SHADOWSOCKS && proxy.type != Proxy::PROXY_SHADOWSOCKS_SIMPLE_OBFS )
		throw Exception("Invalid proxy type");

	int pid = fork();
	if ( pid > 0 ) { //parent
		return pid;
	} else if ( pid == 0 ) { //child
		int nullfd = open("/dev/null",O_RDWR);
		dup2(nullfd,STDOUT_FILENO);
		dup2(nullfd,STDERR_FILENO);
		dup2(nullfd,STDIN_FILENO);

		if ( proxy.type == Proxy::PROXY_SHADOWSOCKS ) {
			execlp("ss-local","ss-local",
				   "-s",proxy.address.c_str(),
			       "-p",proxy.port.c_str(),
			       "-m",proxy.method.c_str(),
			       "-k",proxy.password.c_str(),
			       "-l",localPort.c_str(),
				   "-b",localAddress.c_str() ,
				   nullptr);
		} else {
			execlp("ss-local","ss-local",
				   "-s",proxy.address.c_str(),
			       "-p",proxy.port.c_str(),
			       "-m",proxy.method.c_str(),
			       "-k",proxy.password.c_str(),
			       "-l",localPort.c_str(),
			       "-b",localAddress.c_str(),
			       "--plugin","obfs-local",
				   "--plugin-opts",proxy.plugin_option.c_str() ,
				   nullptr);
		}
		exit(-1);
	} else {
		throw Exception("Failure to fork()");
	}

	return 1;
}

Process::Process(pid_t pid) {
	this->pid = pid;
}

int Process::waitFor(void) {
	int result = 0;

	waitpid(pid,&result,0);

	return result;
}

void Process::sleep(int milliseconds) {
	usleep(1000 * milliseconds);
}

void Process::kill(int signal) {
	::kill(pid,signal);
}
