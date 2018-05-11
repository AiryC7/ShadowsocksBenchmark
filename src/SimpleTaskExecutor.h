#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include <list>

using std::function;
using std::thread;
using std::mutex;
using std::list;

template<class Container,class Element>
class SimpleTaskExecutor {
public:
	SimpleTaskExecutor(Container &c,function<void (Element e)> f);

public:
	void exec(int threads = 1);

private:
	void threadRun(void);

private:
	typename Container::iterator iter;
	typename Container::iterator iterEnd;
	function<void (Element)> run;

private:
	mutex lock;
};

template<class Container,class Element>
SimpleTaskExecutor<Container,Element>::SimpleTaskExecutor(Container &c,function<void (Element e)> f) {
	iter = c.begin();
	iterEnd = c.end();
	run = f;
}

template<class Container,class Element>
void SimpleTaskExecutor<Container,Element>::exec(int threads) {
	threads = threads > 1 ? threads : 1;

	list<thread> threadList;

	for ( int i = 1 ; i < threads ; i++ )
		threadList.push_back(thread(std::bind(&SimpleTaskExecutor<Container,Element>::threadRun,this)));

	threadRun(); //Current thread

	for ( thread &t : threadList )
		t.join();
}

template<class Container,class Element>
void SimpleTaskExecutor<Container,Element>::threadRun(void) {
	while ( true ) {
		lock.lock();

		if ( iter == iterEnd ) {
			lock.unlock();
			break;
		}

		Element e = *iter++;

		lock.unlock();

		run(e);
	}
}

