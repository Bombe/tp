
#ifndef __TP_COPIER__
#define __TP_COPIER__

#include <stdio.h>
#include <stdint.h>
#include <vector>

class Copier;
#include "CopierListener.hpp"

class Copier {

public:
	Copier(FILE* input, FILE* output);
	~Copier();

	void addCopierListener(CopierListener* copierListener);

	void start();

	uint64_t getCopied();

private:
	FILE* input;
	FILE* output;
	uint64_t copied;
	std::vector<CopierListener*> copierListeners;

};

#endif

