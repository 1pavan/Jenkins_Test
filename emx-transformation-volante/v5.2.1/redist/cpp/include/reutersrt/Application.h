#ifndef __Application__H__
#define __Application__H__

#include <iostream>

/**
	\class Application Application.h 
	\brief
	Basic application runtime implementation.

*/
#include "ReutersDll.h"
#include "Common/Context.h"

class RDMConsumer;

class REUTERS_EXPORT Application  
{
public:
	Application();
	virtual ~Application();
	
	void run();
	bool init(const rfa::common::RFA_String& appName, const rfa::common::RFA_String& customRFAConfigfile, const rfa::common::RFA_String&  customAPPConfigfile);
	void cleanup();
	void displayUsage();
	RDMConsumer* getRDMConsumer() {
		return _rdmConsumer;
	}
protected:
	void setupConfigDb();

private:	
	RDMConsumer*			_rdmConsumer;
};

#endif
