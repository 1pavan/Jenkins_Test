#ifndef __SESSION_LAYER_THREADED_EXAMPLE__TIMER__H__
#define __SESSION_LAYER_THREADED_EXAMPLE__TIMER__H__

#include <list>


#define  Timer_MinimumInterval 10

// A timer class; SessionClient is a derived class of CTimer and implements
// the main loop for driving the timers
// Publisher, StatManager, and Terminator classes implement CTimerClient interface
//

class CTimerClient
{
public:
	CTimerClient();
	~CTimerClient();

	virtual void processTimer(void* pClosure) = 0;


private:
// Declared, but not implemented to prevent default behavior generated by compiler
	CTimerClient( const CTimerClient & );
	CTimerClient & operator=( const CTimerClient & );
};

class CTimer 
{
public:
	CTimer();

	~CTimer();
	void	addTimerClient( CTimerClient &timerClient, long millisec, bool repeating, void* pClosure = 0  );
	void	dropTimerClient( CTimerClient &timerClient );

	long	nextTimer() const;
	void    processExpiredTimers();

private:
#ifndef WIN32
public:
#endif
	struct  CTime
	{
		long				 _sec;
		long				 _millisec;
		void				 set( long millisec );
		static CTime	 getCurrentTime();
		bool				 operator <= ( const CTime &two );
		long				 operator - ( const CTime &two );
	private:
		CTime &				 setCurrentTime();
	};


	struct  CTimerCallback
	{
		CTimerClient	*_pTimerClient;
		CTime		 _expirationTime;
		long			 _millisec;
		bool			 _repeating;
		void*			 _pClosure;
	};

	typedef std::list<CTimerCallback *>	_TimerCallbacks;
	_TimerCallbacks					_timerCallbacks;

	void  addTimerCallback( CTimerCallback *pCTimerCallback );

private:
// Declared, but not implemented to prevent default behavior generated by compiler
	CTimer( const CTimer & );
	CTimer & operator=( const CTimer & );
};


#endif // __SESSION_LAYER_THREADED_EXAMPLE__TIMER__H__
