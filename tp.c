/*
 * © 2011 by David Roden
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

uint64_t getTimeDifference(struct timeval* firstTimestamp, struct timeval* secondTimestamp) {
	return (secondTimestamp->tv_sec * 1000000 + secondTimestamp->tv_usec) - (firstTimestamp->tv_sec * 1000000 + firstTimestamp->tv_usec);
}

double getFormattedNumber(double number) {
	double currentNumber = number;
	while (currentNumber >= 1000) {
		currentNumber /= 1000;
	}
	return currentNumber;
}

char* getFormattedUnit(double number) {
	static char* units[] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB"};
	int unit = 0;
	double currentNumber = number;
	while (currentNumber >= 1000) {
		currentNumber /= 1000;
		++unit;
	}
	return units[unit];
}

int main(int argc, char** argv) {
	
	void* buffer;
	size_t bufferSize = 65536;
	size_t bytesRead;
	size_t bytesWritten;
	uint64_t movedTotal = 0;
	uint64_t movedLast = 0;
	struct timeval startTimestamp, lastTimestamp, timestamp;
	uint64_t sinceStart, sinceLast;
	double throughput;

	/* allocate buffer. */
	buffer = malloc(bufferSize); /* TODO - check for error. */

	gettimeofday(&startTimestamp, NULL); /* TODO - check for error. */
	lastTimestamp = startTimestamp;

	while (!feof(stdin)) {
		bytesRead = fread(buffer, 1, bufferSize, stdin);
		bytesWritten = fwrite(buffer, 1, bytesRead, stdout);
		if ((bytesRead == 0) || (bytesRead != bytesWritten)) {
			/* some error occured. */
			break;
		}
		movedTotal += (uint64_t) bytesRead;
		movedLast += (uint64_t) bytesRead;
		gettimeofday(&timestamp, NULL); /* TODO - check for error. */
		sinceLast = getTimeDifference(&lastTimestamp, &timestamp);
		if (sinceLast > 500000) {
			sinceStart = getTimeDifference(&startTimestamp, &timestamp);
			throughput = (movedTotal / (sinceStart / 1000000.0));
			fprintf(stderr, "%llu bytes total, %llu seconds, %.1f %s/s%c[K\r", movedTotal, sinceStart / 1000000, getFormattedNumber(throughput), getFormattedUnit(throughput), 27);
			lastTimestamp = timestamp;
			movedLast = 0;
		}
	}
	fprintf(stderr, "\n");

	return 0;
}

