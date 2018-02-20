#ifndef __THREAD_H__
#define __THREAD_H__

#include "cp.h"

VOLANTE_NAMESPACE_BEGIN
typedef void* THREADHANDLE;


class VOLANTE_CP_EXPORT Thread {
	enum STATUS {
		NOT_STARTED,
			RUNNING,
			COMPLETED
	};
private:
	void exited();
	THREADHANDLE handle;
	int threadId;
	bool autoDelete;
	STATUS status;
private:
	vstring getThreadIdString();
public: 
	void runThread();
	
public:
	// Public API
	Thread(bool autoDelete = false);
	~Thread();
	
	/*
	* Should be overridden. Should not be called directly. Call start instead.
	*/
	virtual void run() = 0;
	/**
	*  Starts the new thread.
	*/
	void start();
	vstring toString();
	
	/**
	*  Returns the id of this thread
	*/
	int getThreadId();
	
	/**
	*  Returns true if the thread is started and is still running.
	*/
	bool isAlive();
	
	/**
	*  Makes the current thread wait for this thread to complete.
	*/
	void join();
	
	/**
	*  sleeps for specified milli seconds.
	*/
	static void sleep(int millis);
	
	/**
	*  Yields control to other threads.
	*/
	static void yield();
	
	/**
	*  Returns the id of the current thread
	*/
	static int getCurrentThreadId();
};

VOLANTE_NAMESPACE_END

#endif //__THREAD_H__

