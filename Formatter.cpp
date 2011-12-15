
#include "Formatter.hpp"

Formatter::Formatter(std::vector<std::string> units) {
	this->outputBuffer = (char*) malloc(128);
	if (!this->outputBuffer) {
		/* TODO - signal error. */
	}
	this->units = units;
}

Formatter::~Formatter() {
	free(this->outputBuffer);
}

char* Formatter::format(const char* format, double number) {
	size_t unit = 0;
	double reducedNumber = number;
	while ((reducedNumber >= 1024) && (unit < this->units.size() - 1)) {
		++unit;
		reducedNumber /= 1024;
	}
	snprintf(this->outputBuffer, 128, format, reducedNumber, this->units[unit].c_str());
	return this->outputBuffer;
}
