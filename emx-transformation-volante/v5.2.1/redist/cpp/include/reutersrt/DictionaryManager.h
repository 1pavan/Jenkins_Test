#ifndef __RDM_DictionaryManager_H__
#define __RDM_DictionaryManager_H__

/**
	\class DictionaryManager DictionaryManager.h 
	\brief
	Manages the requesting/loading, decoding and caching of field and enumeration 
	data dictionaries. It has an interface that allow access to individual
    field and enum definitions


*/

#include "RDMDict.h"
#include "RDMConsumer.h"
#include "AppConfig.h"

#include "Common/Client.h"
#include "Common/Handle.h"

#include "Message/RespMsg.h"
#include "Message/ReqMsg.h"

class RDMNetworkDictionaryDecoder;

class DictionaryManager : public rfa::common::Client
{
public:
	DictionaryManager( AppConfig& appConfig, RDMConsumer& parentConsumer, const RFA_String& dictName1, const RFA_String& dictName2 );
	~DictionaryManager();

//Access
	RDMFieldDict& getFieldDict(); //- use to gain access to version, etc
	RDMEnumDict& getEnumDict(); //- see above
	const RDMFieldDef& getFieldDef(rfa::common::Int16 fieldId); // access to FeildDefs without having to retrieve dict
	const RDMEnumDef& getEnumDef(rfa::common::Int16 fieldId); // access to EnumDefs without having to retrieve dict
	bool isAvailable(); // are the dicts complete and available to be queried?

//Msg related
	void sendRequest();

private:
	void init();
	void cleanup();
	void clear();

// Msg processing
	void processEvent(const rfa::common::Event & event);
	void processRefreshMsg(const rfa::message::RespMsg& data);
	void processStatusMsg(const rfa::message::RespMsg& data);
	void closeRequest();

//Data Members
	RDMFieldDict		_fieldDict;
	rfa::common::RFA_String			_networkDictName1;
	rfa::common::RFA_String			_networkDictName2;
	bool				_isAvailable;
	bool				_loadFromNetwork;

	//subscription
	RDMNetworkDictionaryDecoder *			_netDictionaryDecoder;
	AppConfig&								_appConfig;
	RDMConsumer&							_parentConsumer;	//access to 'parent' consumer, needed to retrieve Session, Queue info amd noticiations
	rfa::sessionLayer::OMMItemIntSpec		_ommItemIntSpec;
	rfa::common::Handle*					_dictHandle1;
	rfa::common::Handle*					_dictHandle2;
	rfa::message::ReqMsg					_reqMsg;
	rfa::message::AttribInfo				_attribInfo;

};

#endif

