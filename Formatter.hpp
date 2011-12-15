/*
 * © 2011 by David Roden
 */

#ifndef __TP_FORMATTER__
#define __TP_FORMATTER__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <string>

class Formatter {

public:
	Formatter(std::vector<std::string> units);
	~Formatter();

	char* format(const char* format, double number);

private:
	std::vector<std::string> units;
	char* outputBuffer;

};

#endif
