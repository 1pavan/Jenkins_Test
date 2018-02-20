#ifndef __LOGINMANAGER__
#define __LOGINMANAGER__

/**
	\class LoginManager LoginManager.h 
	\brief
	LoginManager is resposible RDM Login request/responses and 
	decoding login messages.

*/

#include "Common/Client.h"
#include "SessionLayer/OMMItemIntSpec.h"
#include "AppConfig.h"
#include "Common/Handle.h"
#include "Message/ReqMsg.h"

//Foward declarations
class RDMConsumer;


class LoginManager : public rfa::common::Client
{
public:
	LoginManager(AppConfig& appConfig, RDMConsumer& parentConsumer);
	~LoginManager();

	// Send Login ReqMsg using application parameters
	void sendRequest();

	//process Login events - inherited for rfa::common::Client
	void processEvent(const rfa::common::Event & event );

	void closeRequest();

private:
	AppConfig&							_appConfig;
	RDMConsumer&						_parentConsumer;	//access to 'parent' consumer, needed to retrieve Session, Queue info amd noticiations

	rfa::sessionLayer::OMMItemIntSpec	_ommItemIntSpec;
	rfa::common::Handle*				_loginHandle;
	rfa::message::ReqMsg				_reqMsg;
	rfa::message::AttribInfo			_attribInfo;

};
#endif
