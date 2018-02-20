/*
	RDMProvider

	Initializes and shuts down RFA session, logger, event queue and dictionary.
	
	Creates SmallProvServer which creates the OMMProvider.

	Calls CMessageLoop to dispatch events.


*/
#ifndef RDMProvider_h
#define RDMProvider_h
#include "ReutersDll.h"

#include "IncludeReuters.h"
#include "reutersrt/ConfigDb.h"

class AppLoggerClient;
class ProviderMessageLoop;
class OMMFileFieldEnumDict;
class SmallProvServer;
class CTimer;
class VolanteOMMProvider;
class REUTERS_EXPORT RDMProvider
{
public:

    RDMProvider(const rfa::common::RFA_String&  rfaConfigFile, const rfa::common::RFA_String&  appConfigFile);

	virtual ~RDMProvider();

	int init();
	void run();

	void haltApplication();

	void cleanup();
	VolanteOMMProvider* getVolanteOMMProvider() {
		return volanteProvider;
	}

protected:

	bool  initConfig();
	bool  initQueue();
	bool  initLogger();
	bool  initProvider();
	bool  initDictionary();

	rfa::common::EventQueue * _eventQueue;
	rfa::sessionLayer::Session * _session;
  ConfigDb* _AppConfigDb;
  ConfigDb* _RFAConfigDb;
	ProviderMessageLoop* _messageLoop;
	
	OMMFileFieldEnumDict* _pDict;

	rfa::logger::ApplicationLogger *_logger;
	rfa::logger::AppLoggerMonitor *_loggerMonitor;
	rfa::common::Handle* _loggerHandle;
	AppLoggerClient *_loggerClient;

	//SmallProvServer* _provServer;
	VolanteOMMProvider* volanteProvider;
	CTimer* _timer;

   RFA_String _rfaConfigFile;
   RFA_String _appConfigFile;
   RFA_String _sessionName;
   RFA_String _serviceName;
};

#endif
