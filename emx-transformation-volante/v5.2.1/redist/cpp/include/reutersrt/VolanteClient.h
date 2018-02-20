#ifndef __RDM_VolanteClient_H__
#define __RDM_VolanteClient_H__

/**
	\class VolanteClient VolanteClient.h 
	\brief
	Handles and displays market data items of all domain types, either RDM or user defined.
    It displays all relevent message and data information and should be used
    either for diagnostic purposes for for handling domain models that do not
    currently have a specific implementation written for them (like MarketPrice
    and MarketByOrder have in this application)

*/

#include "RDMConsumer.h"
#include "ConsumerItem.h"
#include "ConsumerItemClient.h"

#include "StatManager.h"
#include "Common/Event.h"
#include "Message/RespMsg.h"

#include "Common/Data.h"
#include "Data/FieldList.h"
#include "Data/FieldEntry.h"
#include "Data/FieldListReadIterator.h"

#include "Data/ElementList.h"
#include "Data/ElementEntry.h"

#include "Data/Array.h"
#include "Data/ArrayEntry.h"

#include "Data/FilterList.h"
#include "Data/FilterEntry.h"

#include "Data/Map.h"
#include "Data/MapEntry.h"
#include "Data/MapReadIterator.h"

#include "Data/Series.h"
#include "Data/SeriesEntry.h"

#include "Data/Vector.h"
#include "Data/VectorEntry.h"


class ReutersMessageHandler {
public:
	virtual bool process(const rfa::message::RespMsg& respMsg,  void * handler) =0;};

class VolanteClient : public ConsumerItemClient
{
public:
	VolanteClient(RDMConsumer& consumer, int messageModelType);
	~VolanteClient();

		//inherited from ConsumerItemClient
	virtual void init() ;
	virtual void cleanup();

	void processEvent(const rfa::common::Event & event);
	void processStatusRespMsg(const rfa::message::RespMsg & respMsg, ConsumerItem & cacheItem);
	void processRefreshRespMsg(const rfa::message::RespMsg & respMsg, ConsumerItem & cacheItem);
	void processUpdateRespMsg(const rfa::message::RespMsg & respMsg, ConsumerItem & cacheItem);
	void processCloseRespMsg(const rfa::message::RespMsg & respMsg, ConsumerItem & cacheItem);

private:
	void displayServiceAndItemName(const rfa::message::RespMsg & respMsg, ConsumerItem & cacheItem);
	void displayMsgInfo(const rfa::message::RespMsg & respMsg);
	void displayMsgAttribInfo(const rfa::message::AttribInfo & info);
	void displayMsgManifest(const rfa::message::Manifest & info);
	void displayMsgRespStatus(const rfa::common::RespStatus & status);
	void displayMsgQOSInfo(const rfa::common::QualityOfService & info);



	/// Currently were are only showing how to 'generically' decode Map, FieldList an DataBuffer
	/// since the supported RDM Msg Domain types only use these. Generic decoding for 
	/// other data types will be implemented in later releases
	/// For an examples of how to decode Series, Array, ElementList and FilterList see
	/// the DirectoryManager or DictioanryManager(and RDMDicts)
	/*
	void decodeData(const rfa::common::Data& data);
	void decodeFieldList(const rfa::data::FieldList& input);
	void decodeFieldEntry(const rfa::data::FieldEntry& input);
	void decodeMap(const rfa::data::Map& input);
	void decodeMapEntry(const rfa::data::MapEntry& input);
	void decodeDataBuffer(const rfa::data::DataBuffer& dataBuffer);*/


	void encodeIndents();
	/*
	void addHandler(ReutersMessageHandler* reutersMessageHandler, void* handler) {
		handlers.push_back(HandlerPair(reutersMessageHandler, handler));
	}
	void removeHandler(ReutersMessageHandler* reutersMessageHandler, void* handler) {
			for(Handlers::iterator it = handlers.begin(); it != handlers.end(); ++it) {
				HandlerPair handlerPair = *it;
				if(reutersMessageHandler == handlerPair.first && 	handler == handlerPair.second) {
					it =  handlers.erase(it);
				}
			}
	}*/
private:
		RDMConsumer&		_parentConsumer;	//access to 'parent' consumer, needed to retrieve Session, Queue info amd noticiations
		StatManager&		_stats;				// store a reference for ease of use
		int messgeModelType;
		bool			_display;
		int				m_indents;
		//typedef std::pair<ReutersMessageHandler*, void*> HandlerPair;
		//typedef std::vector<HandlerPair> Handlers;
		//Handlers handlers;
		//ReutersMessageHandler* reutersMessageHandler;
		//void* handler;
};

#endif

