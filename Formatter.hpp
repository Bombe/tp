/*
 * © 2011 by David Roden
 */

//! \file Formatter.hpp
//! \brief Formats a number according to given units.

#ifndef __TP_FORMATTER__
#define __TP_FORMATTER__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <string>

/**
 * \brief Formats a number according to given units.
 *
 * Only units with a quanitity of 1 or larger may be given, and it is
 * assumed that each unit is 1024 times the amount of the previous unit.
 * This makes this class optimal for formatting numbers of bytes into
 * SI units, such as converting 246261 to 240 KiB.
 */
class Formatter {

public:
	/**
	 * \brief Creates a new formatter for the given units.
	 *
	 * The first unit has to have the quantity 1, each following unit
	 * must have 1024 times the quantity of the previous unit.
	 *
	 * \param units The units
	 */
	Formatter(std::vector<std::string> units);

	/**
	 * \brief Destructor.
	 */
	~Formatter();

	/**
	 * \brief Formats the given number using the given format.
	 *
	 * The format is used for an \ref snprintf call, with the first argument
	 * being the reduced number and the second argument being the correct
	 * unit.
	 *
	 * The returned buffer is allocated by this class and must not be freed
	 * nor used otherwise by the calling class. The next call to this method
	 * will destroy the content of the buffer.
	 *
	 * \param format The format for \ref snprintf
	 * \param number The number to format
	 */
	char* format(const char* format, double number);

private:
	/** The units. */
	std::vector<std::string> units;

	/** The output buffer. */
	char* outputBuffer;

};

#endif
