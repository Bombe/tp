
#ifndef __TP_COPIER_LISTENER__
#define __TP_COPIER_LISTENER__

class CopierListener;
#include "Copier.hpp"

class CopierListener {

public:
	virtual ~CopierListener();
	
	virtual void copierProgress(Copier* copier);

};

#endif
