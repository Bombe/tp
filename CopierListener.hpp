/**
 * © 2011 by David Roden
 */

//! \file CopierListener.hpp
//! \brief Interface for objects that want to be notified on Copier events.

#ifndef __TP_COPIER_LISTENER__
#define __TP_COPIER_LISTENER__

class CopierListener;
#include "Copier.hpp"

/**
 * \brief Interface for objects that want to be notified on Copier events.
 */
class CopierListener {

public:
	/**
	 * \brief Destructor.
	 */
	virtual ~CopierListener();
	
	/**
	 * \brief Notifies a listener that progress has been made by the given Copier.
	 *
	 * \param copier The Copier that made the progress
	 */
	virtual void copierProgress(Copier* copier);

};

#endif
