/*
 * © 2011 by David Roden
 */

/// \file tp.c
/// \brief Main method and formatting functions.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

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

/**
 * \brief Reduces the given number until it is smaller than 1024.
 *
 * The number is divided by 1024 until it is smaller than 1024. This is used in
 * conjunction with #getFormattedUnit(double) to create a formatted value like
 * “145.2 KiB" for a number like 145217.
 *
 * \param number The number to format \return The formatted number, smaller
 * than 1000
 */
double getFormattedNumber(double number) {
	double currentNumber = number;
	while (currentNumber >= 1024) {
		currentNumber /= 1024;
	}
	return currentNumber;
}

/**
 * \brief Returns the unit for the formatted number.
 *
 * This method should be used in conjunction with getFormattedNumber(double).
 * It returns the number of reductions that have been performed on a number,
 * converted as units of bytes (KiB, MiB, etc.).
 *
 * \param number The number to get the unit for
 * \return The unit for the formatted number
 */
char* getFormattedUnit(double number) {
	static char* units[] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB"};
	int unit = 0;
	double currentNumber = number;
	while (currentNumber >= 1024) {
		currentNumber /= 1024;
		++unit;
	}
	return units[unit];
}

/**
 * \brief Main method of tp.
 *
 * The command-line is currently ignored.
 *
 * \param argc The number of parameters
 * \param argv The command-line parameters
 * \return The exit code
 */
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

