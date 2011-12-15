/**
 * © 2011 by David Roden
 */

//! \file Main.hpp
//! \brief %Main class.

#ifndef __TP_MAIN__
#define __TP_MAIN__

#include <sys/time.h>
#include "CopierListener.hpp"
#include "Formatter.hpp"

/**
 * \brief %Main tp class.
 */
class Main: public CopierListener {

public:
	/**
	 * \brief Creates a new main class.
	 *
	 * \param argc Number of command-line arguments
	 * \param argv The command-line arguments
	 */
	Main(int argc, char** argv);

	/**
	 * \brief Destructor.
	 */
	~Main();

public:
	/**
	 * \brief Runs the main class.
	 *
	 * \return The exit code
	 */
	int run();

public:
	/**
	 * \brief Called by Copier to notify of progress.
	 *
	 * \param copier The copier that made the progress
	 */
	void copierProgress(Copier* copier);

private:
	/** The start time. */
	struct timeval startTime;

	/** The last time progress was made. */
	struct timeval lastTime;

	/** The formatter. */
	Formatter* formatter;

};

#endif
