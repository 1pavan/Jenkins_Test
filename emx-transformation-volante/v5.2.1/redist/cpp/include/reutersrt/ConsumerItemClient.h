#ifndef _RFA_ConsClient_h_
#define _RFA_ConsClient_h_

#include "ConsumerItem.h"
#include "Common/Client.h"
#include "Message/RespMsg.h"

/**
	\class ConsumerItemClient ConsumerItemClient.h
	\brief
		
	Base class for Clients of ConsumerItems. Provides an interface
	for basic message process. Is easily extended to handle different
    Reuters Domain Models (RDM) or user defined domain model (via 
    Open Message Models (OMM) semantics)
*/


class ConsumerItemClient : public rfa::common::Client
{
public:
	ConsumerItemClient() {};
	virtual ~ConsumerItemClient(){};

	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void processEvent(const rfa::common::Event & event) = 0;
	virtual void processStatusRespMsg(const rfa::message::RespMsg & respMsg, ConsumerItem & cacheItem)= 0;
	virtual void processRefreshRespMsg(const rfa::message::RespMsg & respMsg, ConsumerItem & cacheItem)= 0;
	virtual void processUpdateRespMsg(const rfa::message::RespMsg & respMsg, ConsumerItem & cacheItem)= 0;
};

#endif
