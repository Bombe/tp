
#include "Main.hpp"

#include <stdio.h>
#include <vector>
#include <string>

/**
 * \brief Returns the time difference between two timestamps.
 *
 * The difference is returned as microseconds.
 *
 * \param firstTimestamp The first timestamp
 * \param secondTimestamp The second timestamp
 * \return The difference between the two timestamps (in microseconds)
 */
uint64_t getTimeDifference(struct timeval* firstTimestamp, struct timeval* secondTimestamp) {
	return (secondTimestamp->tv_sec * 1000000 + secondTimestamp->tv_usec) - (firstTimestamp->tv_sec * 1000000 + firstTimestamp->tv_usec);
}

Main::Main(int argc, char** argv): CopierListener() {
	string units[] = { "B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB" };
	gettimeofday(&this->startTime, NULL);
	gettimeofday(&this->lastTime, NULL);
	this->formatter = new Formatter(std::vector<std::string>(units, units + sizeof(units) / sizeof(string)));
}

Main::~Main() {
	delete this->formatter;
}

void Main::copierProgress(Copier* copier) {
	struct timeval now;
	uint64_t timeSpent;
	uint64_t sinceStart;
	double throughput;

	gettimeofday(&now, NULL);
	timeSpent = getTimeDifference(&this->lastTime, &now);

	if (timeSpent > 500000) {
		sinceStart = getTimeDifference(&this->startTime, &now);
		throughput = (copier->getCopied() / (sinceStart / 1000000.0));
		fprintf(stderr, "%llu bytes total, %llu seconds, %s/s%c[K\r", copier->getCopied(), sinceStart / 1000000, this->formatter->format("%.1f %s", throughput), 27);
		this->lastTime = now;
	}
}

int Main::run() {
	Copier copier(stdin, stdout);

	copier.addCopierListener(this);
	copier.start();

	return 0;
}

int main(int argc, char** argv) {
	Main main(argc, argv);

	return main.run();
}

