/*
 * © 2011 by David Roden
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	void* buffer;
	size_t bufferSize = 65536;
	size_t bytesRead;

	/* allocate buffer. */
	buffer = malloc(bufferSize);

	while ((bytesRead = fread(buffer, bufferSize, 1, stdin)) > 0) {
	}

	return 0;
}

