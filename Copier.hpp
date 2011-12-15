/**
 * © 2011 by David Roden
 */

//! \file Copier.hpp
//! \brief Simple class that copies data from one FILE to another.

#ifndef __TP_COPIER__
#define __TP_COPIER__

#include <stdio.h>
#include <stdint.h>
#include <vector>

class Copier;
#include "CopierListener.hpp"

/**
 * \brief Class that copies data from one FILE to another.
 *
 * Every time a block of data has been copied from the input to the output,
 * an arbitrary number of optional \ref CopierListener "CopierListeners" are notified
 * (using CopierListener::copierProgress()).
 */
class Copier {

public:
	/**
	 * \brief Creates a new copier.
	 *
	 * \param input The input file
	 * \param output The output file
	 */
	Copier(FILE* input, FILE* output);

	/**
	 * \brief Destructor.
	 */
	~Copier();

	/**
	 * \brief Adds a CopierListener to this Copier.
	 *
	 * The given CopierListener is added to a list of registered CopierListeners.
	 *
	 * \param copierListener The copier listener to add
	 */
	void addCopierListener(CopierListener* copierListener);

	/**
	 * \brief Starts this Copier.
	 */
	void start();

	/**
	 * \brief Returns the number of bytes that have been copied.
	 */
	uint64_t getCopied();

private:
	/** The input file. */
	FILE* input;

	/** The output file. */
	FILE* output;

	/** The number of copied bytes. */
	uint64_t copied;

	/** The listeners. */
	std::vector<CopierListener*> copierListeners;

};

#endif

