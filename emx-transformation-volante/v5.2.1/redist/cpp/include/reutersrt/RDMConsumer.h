#ifndef __RDM_CONSUMER_H__
#define __RDM_CONSUMER_H__

// Application
#ifdef WIN32
	#include "MessageLoop.h"
#else
	#include "PollMessageLoop.h"
#endif

#include "Transform.h"
/**
	\class RDMCoonsumer RDMCoonsumer.h 
	\brief
	Main driver for application 

	Main driver for application. Manages initialization and cleanup of RFA constructs
    (Sessions, Logging, Eventqueues, etc) and handles all of the domain managers. It
    also receives callbacks from the LoginManager, DirectoryManager and DictionaryManager
    to expadite market data domain requests.

*/

#include "StatManager.h"
#include "LoginManager.h"
#include "RDMDict.h"

// RFA common package
#include "Common/QualityOfService.h"
#include "Common/Data.h"

// RFA session package
#include "SessionLayer/Session.h"
#include "SessionLayer/OMMConsumer.h"
#include "SessionLayer/OMMConnectionIntSpec.h"

//Logger package
#include "Logger/AppLoggerMonitor.h"
#include "Logger/AppLoggerInterestSpec.h"
#include "Logger/AppLogger.h"
#include "Logger/LoggerNotifyEvent.h"

// RFA message, data and RDM packages
#include "Message/RespMsg.h"
#include "Data/MapEntry.h"
#include "RDM/RDM.h"

#include <new>

/// Forward decls
class DirectoryManager;
class DictionaryManager;
class ConsumerDomainManager;

#include "ReutersDll.h"


class ReutersMessageHandler;
class REUTERS_EXPORT RDMConsumer : public rfa::common::Client
{
public:
	///@name Constructors
	//@{
	/// Constructor
	RDMConsumer(const rfa::common::RFA_String&  appName, const rfa::common::RFA_String&  customRFAConfigFile, const rfa::common::RFA_String&  customAppConfigFile);

	/// Destructor, does what destructors always do
	~RDMConsumer();
	//@}

	///@name Manager callbacks
	//@{
	/// Indicate if Login was succesful or a force logoff has occured
	void processLogin(bool success);

	// processDirectory
	void processDirectory(RespStatus::StreamState state);

	/// Indicates when requeried dicationaries are complete, 
	///   either downloaded or file based
	void processDictionariesComplete();
	//@}

	///@name Logging and connection event processing
	//@{
	///
	//process connection events - inherited for rfa::common::Client
	void processEvent(const rfa::common::Event & event );
	//@}


	///@name Accesors
	//@{
	/// 
	rfa::common::EventQueue* getAppEventQueue() const;
	///
	const rfa::sessionLayer::Session&	getAppSession() const;
	///
	const rfa::sessionLayer::OMMConnectionIntSpec& getAppOMMConnectionIntSpec() const;
	///
	rfa::sessionLayer::OMMConsumer&	getAppOMMConsumer() const;

	StatManager& getStatManager() const;

	AppConfig&	getAppConfig() const;

	//RDMFieldDict& getRDMFieldDict() const;

	void setLoggedIn(bool bVal);

	bool	getIsLoggedIn() const;
	//@}

	///@name Utils
	//@{
	/// Initialization
	bool init();
	void cleanup();

	bool initConfig();
	void cleanupConfig();

	bool initConsumer();
	void cleanupConsumer();

	bool initDomainManagers();
	void cleanupDomainManagers();

	bool initLogger();
	void cleanupLogger();

	bool initQueue();
	void cleanupQueue();

	void run();
	//@}
	void setAppName(const char* appName) {
		this->appName = appName;
	}
	const char* getAppName() {
		return this->appName.c_str();
	}
public:
	ConsumerDomainManager* openItem(const vstring& service, int msgModelRequestType, volante::StringList& items,  ReutersMessageHandler* reutersMessageHandler, void* handler );
	void closeItem(const vstring& service, int msgModelRequestType, volante::StringList& items, ReutersMessageHandler* reutersMessageHandler, void* handler);
	ConsumerDomainManager* findDomainManager(const vstring& service, int msgModelRequestType);
private:
// utils
	void openItems();

//Class members
	AppConfig*			_pAppConfig;
	rfa::common::RFA_String		_RDMConsumerConfigFile; // Stores path and file name of config file for application
	rfa::common::RFA_String		_RFAConfigFile;					// Stores path and file name of config file for RFA



	//Managers
	StatManager*				_pStatManager;
	LoginManager*				_pLoginManager;
	DirectoryManager*			_pDirManager;
	DictionaryManager*			_pDictManager;
	typedef vector<ConsumerDomainManager*>		ConsumerDomainManagers;
	ConsumerDomainManagers consumerDomainManagers;
	//Session and queues
	rfa::common::EventQueue*					_pEventQueue;
	rfa::sessionLayer::Session*					_pSession;
	rfa::sessionLayer::OMMConnectionIntSpec		_connectionIntSpec;
	rfa::common::Handle *						_pOMMConnectionIntSpecHandle;
	rfa::sessionLayer::OMMConsumer*				_pOMMConsumer;

	//RFA logging
	rfa::logger::ApplicationLogger*		_pLogger;
	rfa::logger::AppLoggerMonitor *		_pLoggerMonitor;
	rfa::common::Handle*				_pLoggerHandle;

	rfa::common::RFA_String appName;
	bool _bLoggedIn;
	bool ready;

	//Msg Loops
#ifdef WIN32
	WinMsg_RFA_MessageLoop _msgLoop;
#else
	Poll_MessageLoop _msgLoop;
#endif

};

inline rfa::common::EventQueue* RDMConsumer::getAppEventQueue() const
{ 
	if (_pAppConfig->useEventQueue())
		return _pEventQueue;
	else
		return 0;
}

inline const rfa::sessionLayer::Session&	RDMConsumer::getAppSession() const
{ 
	return *_pSession;
}

inline const rfa::sessionLayer::OMMConnectionIntSpec& RDMConsumer::getAppOMMConnectionIntSpec() const
{ 
	return _connectionIntSpec;
}

inline rfa::sessionLayer::OMMConsumer&	RDMConsumer::getAppOMMConsumer() const
{ 
	return *_pOMMConsumer;
}

inline StatManager&	RDMConsumer::getStatManager() const
{ 
	return *_pStatManager;
}

inline AppConfig& RDMConsumer::getAppConfig() const 
{
	return *_pAppConfig;
}


//***** Static misc. util functions *****
static rfa::common::RFA_String msgModelTypeToString(rfa::common::UInt8 msgType)
{
	switch (msgType)
	{
		case rfa::rdm::MMT_MARKET_PRICE:
			return "MarketPrice";
		case rfa::rdm::MMT_MARKET_BY_ORDER:
			return "MarketByOrder";
		case rfa::rdm::MMT_MARKET_BY_PRICE:
			return "MarketByPrice";
		case rfa::rdm::MMT_MARKET_MAKER:
			return "MarketMaker";
		case rfa::rdm::MMT_SYMBOL_LIST:
			return "SymbolList";
		case rfa::rdm::MMT_RANKED_SYMBOL_LIST:
			return "RankedSymbolList";
		case rfa::rdm::MMT_HISTORY:
			return "History";
		case rfa::rdm::MMT_LOGIN:
			return "Login";
		case rfa::rdm::MMT_DIRECTORY:
			return "Directory";
		case rfa::rdm::MMT_DICTIONARY:
			return "Dictionary";
		default:
			{
				cout<<endl<<"WARNING: msgModelTypeToString() - invalid value passed in"<<endl;
				return "ERROR";
			}
	}
}



static rfa::common::RFA_String msgRespTypeToString(rfa::common::UInt32 respType)
{
	switch (respType)
	{
		case rfa::message::RespMsg::RefreshEnum:
			return "Refresh";
		case rfa::message::RespMsg::StatusEnum:
			return "Status";
		case rfa::message::RespMsg::UpdateEnum:
			return "Update";
		default:
			{
				cout<<endl<<"WARNING: msgRespTypeToString() - invalid value passed in"<<endl;
				return "ERROR";
			}
	}
}
static rfa::common::RFA_String statusCodeToString(rfa::common::UInt8 statusCode)
{
	switch (statusCode)
	{
		case rfa::common::RespStatus::NoneEnum:
			return "None";
		case rfa::common::RespStatus::NotFoundEnum:
			return "NotFound";
		case rfa::common::RespStatus::TimeoutEnum:
			return "Timeout";
		case rfa::common::RespStatus::NotAuthorizedEnum:
			return "NotAuthorized";
		case rfa::common::RespStatus::InvalidArgumentEnum:
			return "InvalidArgument";
		case rfa::common::RespStatus::UsageErrorEnum:
			return "UsageError";
		case rfa::common::RespStatus::PreemptedEnum:
			return "Preempted";
		case rfa::common::RespStatus::JustInTimeFilteringStartedEnum:
			return "JustInTimeFilteringStarted";
        case rfa::common::RespStatus::TickByTickResumedEnum:
            return "TickByTickResumed";
        case rfa::common::RespStatus::FailoverStartedEnum:
            return "FailoverStarted";
        case rfa::common::RespStatus::FailoverCompletedEnum:
            return "FailoverCompleted";
        case rfa::common::RespStatus::GapDetectedEnum:
            return "GapDetected";
		case rfa::common::RespStatus::NoResourcesEnum:
            return "NoResources";
		case rfa::common::RespStatus::TooManyItemsEnum:
            return "TooManyItems";
		case rfa::common::RespStatus::AlreadyOpenEnum:
            return "AlreadyOpen";
		case rfa::common::RespStatus::SourceUnknownEnum:
            return "SourceUnknown";
		default:
			{
				cout<<endl<<"WARNING: statusCodeToString() - invalid value passed in"<<endl;
				return "ERROR";
			}
	}
}


static rfa::common::RFA_String qosRateToString(long qosRate)
{
	if( qosRate == rfa::common::QualityOfService::tickByTick )
		return "TickByTick";
	else if( qosRate == rfa::common::QualityOfService::justInTimeFilteredRate )
		return "JustInTimeFilteredRate";
	else if( qosRate == rfa::common::QualityOfService::unspecifiedRate )
		return "UnspecifiedRate";
	else
	{
		return "Numeric Rate";
	}
}
static rfa::common::RFA_String qosTimelinessToString(long qosTimeliness)
{
	if( qosTimeliness == rfa::common::QualityOfService::realTime )
		return "RealTime";
	else if( qosTimeliness == rfa::common::QualityOfService::unspecifiedTimeliness )
		return "UnspecifiedTimeliness";
	else if( qosTimeliness == rfa::common::QualityOfService::unspecifiedDelayedTimeliness )
		return "UnspecifiedDelayedTimeliness";
	else
	{
		return "Numeric Timeliness";
	}
}

static rfa::common::RFA_String dataStateToString(rfa::common::RespStatus::DataState dataState)
{
	switch (dataState)
	{
		case rfa::common::RespStatus::OkEnum:
			return "Ok";
		case rfa::common::RespStatus::SuspectEnum:
			return "Suspect";
		case rfa::common::RespStatus::UnspecifiedEnum:
			return "Unspecified";
		default:
			{
				cout<<endl<<"WARNING: dataStateToString() - invalid value passed in"<<endl;
				return "ERROR";
			}
	}
}


static rfa::common::RFA_String streamStateToString(rfa::common::RespStatus::StreamState streamState)
{
	switch (streamState)
	{
		case rfa::common::RespStatus::UnspecifiedStreamStateEnum:
			return "UnspecifiedStreamState";
		case rfa::common::RespStatus::OpenEnum:
			return "Open";
		case rfa::common::RespStatus::NonStreamingEnum:
			return "NonStreaming";
		case rfa::common::RespStatus::ClosedRecoverEnum:
			return "ClosedRecoverable";
		case rfa::common::RespStatus::ClosedEnum:
			return "Closed";
		case rfa::common::RespStatus::RedirectedEnum:
			return "Redirected";
		default:
			{
				cout<<endl<<"WARNING: streamStateToString() - invalid value passed in"<<endl;
				return "ERROR";
			}
	}
}

static rfa::common::RFA_String msgNameTypeToString(rfa::common::UInt8 type)
{
	switch(type)
	{
	case rfa::rdm::INSTRUMENT_NAME_UNSPECIFIED:
		return "INSTRUMENT_NAME_UNSPECIFIED";
	case rfa::rdm::INSTRUMENT_NAME_RIC:
		return "INSTRUMENT_NAME_RIC";
	case rfa::rdm::INSTRUMENT_NAME_MAX_RESERVED:
		return "INSTRUMENT_NAME_MAX_RESERVED";
	default:
		{
			cout<<endl<<"WARNING: msgNameTypeToString() - invalid value passed in"<<endl;
				return "ERROR";
		}
	}
}

static rfa::common::RFA_String msgUpdateRespTypeNumToStr(rfa::common::UInt8 type)
{
	switch(type)
	{
	case rfa::rdm::INSTRUMENT_UPDATE_UNSPECIFIED:
		return "INSTRUMENT_UPDATE_UNSPECIFIED";
	case rfa::rdm::INSTRUMENT_UPDATE_QUOTE:
		return "INSTRUMENT_UPDATE_QUOTE";
	case rfa::rdm::INSTRUMENT_UPDATE_TRADE:
		return "INSTRUMENT_UPDATE_TRADE";
	case rfa::rdm::INSTRUMENT_UPDATE_NEWS_ALERT:
		return "INSTRUMENT_UPDATE_NEWS_ALERT";
	case rfa::rdm::INSTRUMENT_UPDATE_VOLUME_ALERT:
		return "INSTRUMENT_UPDATE_VOLUME_ALERT";
	case rfa::rdm::INSTRUMENT_UPDATE_ORDER_INDICATION:
		return "INSTRUMENT_UPDATE_ORDER_INDICATION";
	case rfa::rdm::INSTRUMENT_UPDATE_CLOSING_RUN:
		return "INSTRUMENT_UPDATE_CLOSING_RUN";
	case rfa::rdm::INSTRUMENT_UPDATE_CORRECTION:
		return "INSTRUMENT_UPDATE_CORRECTION";
	case rfa::rdm::INSTRUMENT_UPDATE_MARKET_DIGEST:
		return "INSTRUMENT_UPDATE_MARKET_DIGEST";
	case rfa::rdm::INSTRUMENT_UPDATE_QUOTES_TRADE:
		return "INSTRUMENT_UPDATE_QUOTES_TRADE";
	case rfa::rdm::INSTRUMENT_UPDATE_MULTIPLE:
		return "INSTRUMENT_UPDATE_MULTIPLE";
	default:
		{
			cout<<endl<<"WARNING: msgUpdateRespTypeNumToStr() - invalid value passed in"<<endl;
			return "ERROR";
		}
	}
}

static rfa::common::RFA_String msgRefreshRespTypeNumToStr(rfa::common::UInt8 type)
{
	switch(type)
	{
	case rfa::rdm::REFRESH_SOLICITED:
		return "REFRESH_SOLICITED";
	case rfa::rdm::REFRESH_UNSOLICITED:
		return "REFRESH_SOLICITED";
	default:
		{
			cout<<endl<<"WARNING: msgRefreshRespTypeNumToStr() - invalid value passed in"<<endl;
			return "ERROR";
		}
	}
}

static rfa::common::RFA_String dataTypeToStr(rfa::common::UInt8 type)
{
	switch(type)
	{
	case rfa::data::VectorEnum:
			return "Vector";
        case rfa::data::ElementListEnum:
			return "ElementList";
        case rfa::data::FieldListEnum:
			return "FieldList";
        case rfa::data::SeriesEnum:
			return "Series";
		case rfa::data::ArrayEnum:
			return "Array";
        case rfa::data::MapEnum:
			return "Map";
		case rfa::data::FilterListEnum:
			return "FilterList";
		case rfa::data::DataBufferEnum:
			return "DataBuffer";
		case rfa::data::DataBuffer::EnumerationEnum:
			return "DataBuffer::Enumeration";
		case rfa::data::DataBuffer::FloatEnum:
			return "DataBuffer::Float";
		case rfa::data::DataBuffer::DoubleEnum:
			return "DataBuffer::Double";
		case rfa::data::DataBuffer::Int32Enum:
			return "DataBuffer::Int32";
		case rfa::data::DataBuffer::UInt32Enum:
			return "DataBuffer::UInt32";
		case rfa::data::DataBuffer::Int64Enum:
			return "DataBuffer::Int64";
		case rfa::data::DataBuffer::UInt64Enum:
			return "DataBuffer::UInt64";
	    case rfa::data::DataBuffer::StringAsciiEnum:
			return "DataBuffer::StringAscii";
        case rfa::data::DataBuffer::StringUTF8Enum:
			return "DataBuffer::StringUTF8";
		case rfa::data::DataBuffer::StringRMTESEnum:
			return "DataBuffer::StringRMTES";
		case rfa::data::DataBuffer::TimeEnum:
			return "DataBuffer::Time";
		case rfa::data::DataBuffer::DateEnum:
			return "DataBuffer::Date";
		case rfa::data::DataBuffer::DateTimeEnum:
			return "DataBuffer::DataTime";
		case rfa::data::DataBuffer::QualityOfServiceInfoEnum:
			return "DataBuffer::QualityOfServiceInfo";
		case rfa::data::DataBuffer::Real32Enum:
			return "DataBuffer::Real32";
		case rfa::data::DataBuffer::Real64Enum:
			return "DataBuffer::Real64";
		case rfa::data::DataBuffer::BufferEnum:
			return "DataBuffer::Buffer";
		case rfa::data::DataBuffer::UnknownDataBufferEnum:
			return "DataBuffer::UnknownDataBuffer";
		default:
		{
			cout<<endl<<"WARNING: dataTypeToStr() - invalid value passed in"<<endl;
			return "ERROR";
		}
	} 
}

static rfa::common::RFA_String actionToString(rfa::common::UInt8 action)
{
	switch(action)
	{
	case rfa::data::MapEntry::Add:
		return "Add";
	case rfa::data::MapEntry::Update:
		return "Update";
	case rfa::data::MapEntry::Delete:
		return "Delete";
	default:
		{
			cout<<endl<<"WARNING: actionToString() - invalid value passed in"<<endl;
			return "ERROR";
		}
	}
}

static rfa::common::RFA_String dictionaryVerbosityTypeToString(rfa::common::UInt32 dictType)
{
	switch(dictType)
	{
	case rfa::rdm::DICTIONARY_INFO:
		return "DICTIONARY_INFO";
	case rfa::rdm::DICTIONARY_MINIMAL:
		return "DICTIONARY_MINIMAL";
	case rfa::rdm::DICTIONARY_NORMAL:
		return "DICTIONARY_NORMAL";
	case rfa::rdm::DICTIONARY_VERBOSE:
		return "DICTIONARY_VERBOSE";
	default:
		{
			cout<<endl<<"WARNING: dictionaryVerbosityTypeToString() - invalid value passed in"<<endl;
			return "ERROR";
		}
	}
}

#endif	//__RDM_CONSUMER_H__
