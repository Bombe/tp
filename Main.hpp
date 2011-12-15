
#ifndef __TP_MAIN__
#define __TP_MAIN__

#include <sys/time.h>
#include "CopierListener.hpp"
#include "Formatter.hpp"

class Main: public CopierListener {

public:
	Main(int argc, char** argv);
	~Main();

public:
	int run();

public:
	void copierProgress(Copier* copier);

private:
	struct timeval startTime;
	struct timeval lastTime;
	Formatter* formatter;
};

#endif
