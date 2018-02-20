#ifndef __MUTEX_H__
#define __MUTEX_H__
#include "cp.h"

#if defined(V_POSIX_THREAD)
	#include <pthread.h>
#endif 

/**
 * Non reentrant mutex. Use it in conjunction with the Lock class.
 *
 *  Usage:
 *     // instance variable
 *    Mutex myMutex;
 *
 *   void myMethod() {
 *		Lock lock(mutex);
 *		// do your stuff here
 *	 }
 *
 */

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT Mutex {
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
private:
#ifdef _WIN32
	void* m_mutex;
#elif defined(V_POSIX_THREAD)
	pthread_mutex_t m_mutex;
#endif 
};


class VOLANTE_CP_EXPORT Lock {
public:
	Lock(Mutex& mutex) : mutex(mutex) {
		mutex.lock();
	}
	~Lock() {
		mutex.unlock();
	}
private:
	Mutex& mutex;
};

VOLANTE_NAMESPACE_END

#endif //__MUTEX_H__
