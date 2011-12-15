
#include "Copier.hpp"
#include <algorithm>

Copier::Copier(FILE* input, FILE* output) {
	this->input = input;
	this->output = output;
	this->copied = 0;
}

Copier::~Copier() {
	/* nothing here. */
	this->copierListeners.clear();
}

void Copier::addCopierListener(CopierListener* copierListener) {
	this->copierListeners.push_back(copierListener);
}

void Copier::start() {
	void* buffer;
	size_t bufferSize = 65536;
	size_t bytesRead;
	size_t bytesWritten;

	/* allocate buffer. */
	buffer = malloc(bufferSize); /* TODO - check for error. */

	while (!feof(this->input)) {
		bytesRead = fread(buffer, 1, bufferSize, this->input);
		bytesWritten = fwrite(buffer, 1, bytesRead, this->output);
		if ((bytesRead == 0) || (bytesRead != bytesWritten)) {
			/* some error occured. */
			break;
		}
		this->copied += (uint64_t) bytesRead;
		for (std::vector<CopierListener*>::iterator copierListeners = this->copierListeners.begin(); copierListeners != this->copierListeners.end(); (*copierListeners)->copierProgress(this), ++copierListeners);
	}
}

uint64_t Copier::getCopied() {
	return this->copied;
}
