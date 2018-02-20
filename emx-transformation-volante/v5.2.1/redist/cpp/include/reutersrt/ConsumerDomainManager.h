#ifndef _RFA_DomainManager_h_
#define _RFA_DomainManager_h_

/**
	\class ConsumerDomainManager ConsumerDomainManager.h 
	\brief
	Parent class for market data Domain Managers 
	This class provides management of request/response 
	for a all domains. It acts as a container for concrete 
    a ConsuemrItemClient and a ConsumerCache. It is easily 
    extented to handle specific RDMs or user defined OMMs.
	Managers only provide functionality to subscribe to a
	single service. This class also provides generic open(),
	close() and closeAll() methods that all specific domain 
	managers can use.
*/


#include <string>
#include "ConsumerCache.h"
#include "RDMConsumer.h"
#include "Message/ReqMsg.h"

#include "ReutersDll.h"

class REUTERS_EXPORT ConsumerDomainManager
{
protected:
	ConsumerDomainManager(RDMConsumer& parentConsumer, 
		int messageModelType, 
		const RFA_String& serviceName, 
		rfa::common::Client* client);
		
public:
	virtual ~ConsumerDomainManager();

	virtual void init() = 0;
	virtual void cleanup() = 0;

	void setConsumerCache(ConsumerCache* cache) {_consumerCache = cache ;}

	void open(const rfa::common::RFA_String & name, ReutersMessageHandler* reutersMessageHandler, void* handler);
	void close(const rfa::common::RFA_String & name);
	void closeAll();
	int getMessageModelType() {
		return _messageModelType;
	}
	const RFA_String& getServiceName() {
		return _serviceName;
	}
	Client* getClient() {
		return _client;
	}
protected:

	RDMConsumer&						_parentConsumer;	//access to 'parent' consumer, needed to retrieve Session, Queue info amd notifiations

	rfa::message::ReqMsg				_reqMsg;
	rfa::message::AttribInfo			_attribInfo;
	rfa::sessionLayer::OMMItemIntSpec	_ommItemIntSpec;
	Client*								_client;
	ConsumerCache*						_consumerCache;
	int									_messageModelType;
	const RFA_String					_serviceName;
};

#endif
