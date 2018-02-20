#ifndef __STATMANAGER__
#define __STATMANAGER__


/**
	\class StatManager StatManager.h 
	\brief
	Msg statictics keeper for item clients 

	This class provides operators to track the number of request, 
	update, refresh, status, and close message send or received by 
   	the application. Currently not fully implemented.

*/

#include "AppConfig.h"

class StatManager
{
public:

	///@name Constructors
	//@{	
	/// Constructor, takes access to application configuration
	StatManager();

	/// Destructor
	~StatManager();
	//@}

	///@name Display accessors
	//@{
	/// Print display header (TODO - show example format)
	void printHeader();

	/// Print current total statics
	void printTotalStats();
	//@}

	///@name stat operators
	//@{
	///
	void incrementRefresh() { _totalRefresh++; _refresh++; };

	///
	void incrementRequest() { _totalRequest++; _request++; };

	///
	void incrementUpdate() { _totalUpdate++; _update++; };

	///
	void incrementStatus() { _totalStatus++; _status++; };

	///
	void incrementClose() { _totalClose++; _close++; };
	//@}

	/// TODO HANDLE TIMER EVENT!!!!
	/// processTimerEvent();

private:

	///@name Private Utility
	//@{
	/// Print stats since last interval
	void printStats();

	///
	void clearIntervalStats() { _request = _update = _refresh = _status = _close = 0; };
	//@}

/// Class Members
		//interval stats
	int _request;
	int	_update;
	int	_refresh;
	int	_status;
	int	_close;

		//total stats
	int	_totalRefresh;
	int	_totalUpdate;
	int	_totalRequest;
	int	_totalStatus;
	int	_totalClose;

	int	_iteration;
	int	_interval;
	
	//AppConfig&		_appConfig;
};

#endif

