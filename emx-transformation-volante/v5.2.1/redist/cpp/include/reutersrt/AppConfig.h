#ifndef __APPCONFIG__
#define __APPCONFIG__

/**
	\class AppConfig AppConfig.h 
	\brief
	Config storage Class for RDMConsumer example app

	AppConfig is a storage class for RDMConsumer's configuration
	variables. It utilizes RFA's config package to retrieve string,
	numeric, and boolean data from Windows registry or via config
	file and stores them in class member variables for easy access. 
	Its main function is to load config from registry 
	(Windows: HKEY_LOCAL_MACHINE\\SOFTWARE\\Reuters\\RFA\\RDMConsumer) 
	or "./RDMConsumer.cfg" (Unix/Linux). See included sample 
	config file for config structure.

*/

// stl 
#include <iostream>

// rfa config package
#include "Config/ConfigDatabase.h"
#include "Config/StagingConfigDatabase.h"
#include "Config/ConfigTree.h"


class AppConfig
{
public:
	///@name Constructors
	//@{	
	/// Constructor, takes the path and file name of config file. If an empty 
	///		string is passed in the default is to load config from 
	///		registry or flat file See included sample 
	///		config file for config structure.
	AppConfig(rfa::common::RFA_String&  customRFAConfigFile,rfa::common::RFA_String&  customAppConfigFile);

	/// Desructor
	~AppConfig(void);
	//@}

	///@name Accessors
	//@{
	/// Returns username
	const rfa::common::RFA_String& getUserName() const;

	/// Returns app Id
	const rfa::common::RFA_String& getApplicationId() const;

	/// Returns postion (usually ip address)
	const rfa::common::RFA_String& getPosition() const;

	/// Returns service name
	const rfa::common::RFA_String& getServiceName() const;

	/// Returns if true if displayStats config is true, false implies market data will be displayed
	bool getDisplayStats() const;

	bool getLoadLocalDicts() const;

	const rfa::common::RFA_String& getFidDictLocation() const;

	const rfa::common::RFA_String& getEnumDictLocation() const;

	bool getMsgModelDefaultDisplay() const;

	rfa::common::UInt8 getMsgModelRequestType() const;

	const rfa::common::RFA_String& getSessionName() const;

	const rfa::config::StringList* getItemList() const;

	rfa::common::UInt32 getDirectoryReqFilter() const;

	bool useEventQueue() const;
	//@}

private:
	///@name Internal Utilities
	//@{
	///
	void initConfig(bool bUseCustomConfigFile);
	void populateLocalConfig(const rfa::config::ConfigTree *pTree);
	void displayConfigTree(const rfa::config::ConfigTree *pStagingTree);
	void loadSymbolsFromFile(const rfa::common::RFA_String& filename);
#ifdef WIN32
	void loadFromRegistry(rfa::config::StagingConfigDatabase *pRFASDB, rfa::config::StagingConfigDatabase *pAPPSDB);
#endif
	void loadFromFlatFile(rfa::config::StagingConfigDatabase *pRFASDB, rfa::config::StagingConfigDatabase *pAPPSDB);
	//@}


private:
/// Class Members
	rfa::common::RFA_String		_RDMConsumerConfigFile; // Stores path and file name of config file for application
	rfa::common::RFA_String		_RFAConfigFile;					// Stores path and file name of config file for RFA

	/// Application Config variables
		//msg and session
	rfa::common::UInt8		_msgModelRequestType;   // (defualt = marketPrice) RDM msg type, see RDM.h for enumerations 
	bool					_msgModelDefaultDisplay;	// (default = true ) true = domain specific decoding, false = generic decoding
	const rfa::config::StringList*	_itemList;		// (default = RTRSY.O) Comma seperated RIC List
	rfa::common::RFA_String _symbolFile;
	rfa::common::RFA_String	_session;	// (Required, no default) Specifies config node for session parameters 
	rfa::common::RFA_String	_service;	// (Required, no default) Service name for request

		//stats
	bool					_trackStats;		// (default = true ) true = record msg stats, false = turn off recording of msg stats
	bool					_displayStats;				// ( default = false ) true = displays stats to screen every time interval, preempts item display, false = don't display
	long					_displayStatInterval;		// ( default = 5 ) in secs, display stats at specified interval


		//dicts
	bool						_loadLocalDicts;   // ( default = false ) defaults to download, uses _fidDictLocation and _enumDictLocation for paths
	rfa::common::RFA_String		_fidDictLocation;  // ( default = none ) location of local fid dictionary
	rfa::common::RFA_String		_enumDictLocation; // ( default = none )location of local enum dictionary

		//misc
	long				_runTime;		// ( default = -1 ) run time of app in secs, -1 specifies infinite run time, at of specified run time app closes items, cleans up and exits
	long					_eventQueueFlag;  

		//login
	rfa::common::RFA_String			_userName;  // (default = 'localhost') userName for Login
	rfa::common::RFA_String			_position;  // (default = 'user') position for Login
	rfa::common::RFA_String			_appId;		// (default = RDMConsumer ) appId for Login

		//Directory
	rfa::common::UInt32				_directoryReqFilter; // (default = SERVICE_INFO_FILTER | SERVICE_STATE_FILTER )

	rfa::config::ConfigDatabase						*_pRFAConfigDb;
	rfa::config::ConfigDatabase						*_pAppConfigDb;

	bool _useEventQueue;  // (default = true)  used to avoid thread context switch between SessionLayer and application

};

inline const rfa::common::RFA_String& AppConfig::getUserName() const
{ return _userName;}

inline const rfa::common::RFA_String& AppConfig::getPosition() const
{ return _position;}

inline const rfa::common::RFA_String& AppConfig::getApplicationId() const
{ return _appId;}

inline const rfa::common::RFA_String& AppConfig::getServiceName() const
{ return _service;}

inline bool AppConfig::getDisplayStats() const
{ return _displayStats; }

inline bool AppConfig::getLoadLocalDicts() const
{ return _loadLocalDicts; }

inline const rfa::common::RFA_String& AppConfig::getFidDictLocation() const
{ return _fidDictLocation; }

inline const rfa::common::RFA_String& AppConfig::getEnumDictLocation() const
{ return _enumDictLocation; }

inline	bool AppConfig::getMsgModelDefaultDisplay() const
{ return _msgModelDefaultDisplay; }

inline	rfa::common::UInt8 AppConfig::getMsgModelRequestType() const
{ return _msgModelRequestType; }

inline 	const rfa::common::RFA_String& AppConfig::getSessionName() const
{ return _session; }

inline 	const rfa::config::StringList* AppConfig::getItemList() const
{ return _itemList; }

inline rfa::common::UInt32 AppConfig::getDirectoryReqFilter() const
{ return _directoryReqFilter; }

inline bool AppConfig::useEventQueue() const
{ return _useEventQueue; }

#endif
