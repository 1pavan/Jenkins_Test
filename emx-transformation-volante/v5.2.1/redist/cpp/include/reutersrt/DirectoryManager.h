#ifndef __DirectoryManager_h
#define __DirectoryManager_h

//Common Package
#include "Common/RFA_Vector.h"
#include "Common/RFA_String.h"

//Data Package
#include "Data/MapEntry.h"
#include "Data/FilterEntry.h"
#include "Data/ElementListReadIterator.h"
#include "Data/ArrayReadIterator.h"

//Message Package
#include "Message/RespMsg.h"
#include "Message/ReqMsg.h"

//Application
#include "RDMConsumer.h"


/**
	\class ServiceEntry DirectoryManager.h 
	\brief
	
	ServiceEntry decode and stores the state, load and other information 
	contained in an RDM Directory an a per service basis. A list of ServiceEntry
	is held by the DirectoryManager.
*/

class ServiceEntry 
{
public:
		// Constructor
	ServiceEntry();

		// Destructor
	~ServiceEntry();

		// Clears all information stored by this object
	void clear();

		// Returns the serviceName for this Directory entry
	rfa::common::RFA_String& getServiceName();

		// Returns an RFA_Vector of capability enums for this service
	const rfa::common::RFA_Vector<rfa::common::UInt8>& getCapabilities() const;

		// Returns an RFA_Vector of capability enums for this service
	const rfa::common::RFA_Vector<rfa::common::RFA_String>& getUsedDictionaries() const;

		// Returns true if this service is accepting requests
	bool getAcceptingRequests() const;

		// Returns true if this service is up
	bool getServiceState() const;
	
		// Decodes and stores service data for a single service
	void decodeServiceData(const rfa::data::MapEntry& serviceData);

		// Prints data for a single service to stdout
	void dumpServiceEntry(rfa::common::UInt32 responseFilter);

private:
		//Utility and decoding methods
	void decodeServiceInfoData(const rfa::data::FilterEntry&);
	void decodeServiceStateData(const rfa::data::FilterEntry&);
	void decodeServiceGroupData(const rfa::data::FilterEntry&);
	void decodeServiceLoadData(const rfa::data::FilterEntry&);
	void decodeServiceDataData(const rfa::data::FilterEntry&);
	void decodeServiceLinkData(const rfa::data::FilterEntry&);

	void setCapabilities(const rfa::data::Array& array);
	void setProvidedDictionaries(const rfa::data::Array& array);
	void setUsedDictionaries(const rfa::data::Array& array);
	void setQos(const rfa::data::Array& array);

// Member Data
	rfa::common::RFA_String			 _serviceName;
	rfa::common::UInt8				 _mapEntryAction;

	//Info
	rfa::common::RFA_String			_name;
	rfa::common::RFA_String			_vendor;
	rfa::common::UInt32				_isSource;
	rfa::common::RFA_Vector<rfa::common::UInt8>	_capabilities;
	rfa::common::RFA_Vector<rfa::common::RFA_String>			_usedDictionaries;
	rfa::common::RFA_Vector<rfa::common::RFA_String>			_providedDictionaries;
	rfa::common::RFA_Vector<rfa::common::QualityOfServiceInfo> _qos;
	rfa::common::UInt32				_supportsQosRange;
	rfa::common::RFA_String			_itemList;
	rfa::common::UInt32				_supportsOutOfBandSnapshots;


	//State
	rfa::common::UInt32				_serviceState;
	rfa::common::UInt32				_acceptingRequests;
	rfa::common::RespStatus			_stateStatus;

	//Group
	rfa::common::Buffer				_groupId;
	rfa::common::Buffer				_mergeToGroup;
	rfa::common::RespStatus			_groupStatus;

	//Load
	rfa::common::UInt32				_openLimit;
	rfa::common::UInt32				_openWindow;
	rfa::common::UInt32				_loadFactor;

	//Data
	rfa::common::UInt32				_type;
	rfa::common::Buffer				_data;

	//Link
	rfa::common::UInt32				_linkType;
	rfa::common::UInt32				_linkStatus;
	rfa::common::UInt32				_linkCode;
	rfa::common::RFA_String			_linkText;


	rfa::data::ElementListReadIterator	_elReadIter;
	rfa::data::ArrayReadIterator		_arrayReadIter;
};


/**
	\class DirectoryManager DirectoryManager.h 
	\brief
	
	DirectorManager is resposible RDM Directory request/responses on a per service 
    basis, as well decoding and caching RDM Directory messages. It provides an interface to 
    query Directory information. The DirectoryManager informs the 
	RDMConsumer when it has succesfully processed 
	directory infromation for the configured service.

*/
class DirectoryManager : public rfa::common::Client
{
public:
		// Constructor
	DirectoryManager(AppConfig& appConfig, RDMConsumer& parentConsumer);

		// Destructor
	~DirectoryManager();

//Request/Response methods
		// Sends a SrvDir request for the configured service
	void sendRequest();

		// Closed a Directory request
	void closeRequest();

// Cache state queries
		// indicates caches are available for query
	bool isAvailable() const { return _isAvailable; }

		// returns true if service exists for this source
	bool serviceExists(const rfa::common::RFA_String& serviceName);


// Service Info
		// Prerequisite: serviceExists(serviceName) == true
		// returns list of model types supported
	const RFA_Vector<UInt8>& getCapabilitiesInfo(const rfa::common::RFA_String& serviceName);

		// Prerequisite: serviceExists(serviceName) == true
		// returns list of dictionaries used
	const RFA_Vector<RFA_String>& getDictionaryUsedInfo(const rfa::common::RFA_String& serviceName);

// Service State
		// Prerequisite: serviceExists(serviceName) == true
		// returns state of service (true = up, false = down)
	bool getServiceState(const rfa::common::RFA_String& serviceName);

		// Prerequisite: serviceExists(serviceName) == true
		// returns state of accepting requests(true = yes, false = no)
	bool getAcceptingRequestsState(const rfa::common::RFA_String& serviceName);


private:
// Msg processing
	void processEvent(const rfa::common::Event & event);
	void processRespMsg(const rfa::message::RespMsg& respMsg);
	void processRefreshMsg(const rfa::message::RespMsg& respMsg);
	void processStatusMsg(const rfa::message::RespMsg& respMsg);
	void processUpdateMsg(const rfa::message::RespMsg& respMsg);
	void processRespStatus(const rfa::common::RespStatus& respStatus);

//Utility and decoding methods
	ServiceEntry* getServiceEntry(const RFA_String& serviceName);
	void removeServiceEntry(const RFA_String& serviceName);

	void decodePayload(const rfa::common::Data& data);
	void cleanup();
	void clear();
	void dumpCache();


private:
// members
	//subscription
	AppConfig&								_appConfig;			// access to application configuration
	RDMConsumer&							_parentConsumer;	// access to 'parent' consumer, needed to retrieve Session, Queue info amd noticiations
	rfa::sessionLayer::OMMItemIntSpec		_ommItemIntSpec;
	rfa::common::Handle*					_handle;
 
	rfa::common::UInt32						_responseFilter;

	//cache availability
	bool									_isAvailable;
	
	rfa::common::RespStatus::StreamState	_msgStreamState;
	rfa::common::UInt8						_msgStatusCode;
	rfa::common::RFA_String					_msgStatusText;

	rfa::message::ReqMsg					_reqMsg;
	rfa::message::AttribInfo				_attribInfo;

	// read iterators - they are reused by decodeService***() and cacheArray***() methods
	ElementListReadIterator	_elReadIter;
	ArrayReadIterator		_arrayReadIter;

	rfa::common::RFA_Vector<ServiceEntry*>  _serviceEntryList;
};
#endif
