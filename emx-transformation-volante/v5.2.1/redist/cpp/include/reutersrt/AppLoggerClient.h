#ifndef _RFA_EXAMPLE_AppLoggerClient_h
#define _RFA_EXAMPLE_AppLoggerClient_h

#include "Common/Client.h"

class rfa::common::Event;

using namespace rfa::common;

// **************** AppLoggerClient ************************

/**
 This client is implemented in order to receive log
 notifications from RFA ApplicationLogger
 */

class AppLoggerClient : public Client
{
public:
	AppLoggerClient();
	virtual ~AppLoggerClient();

	// handles all logger related events 
	virtual void processEvent( const Event & event );

private:
	AppLoggerClient(const AppLoggerClient&);
	AppLoggerClient& operator=(const AppLoggerClient&);
};

#endif
