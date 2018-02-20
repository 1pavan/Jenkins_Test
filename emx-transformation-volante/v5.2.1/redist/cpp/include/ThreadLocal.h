#ifndef __THREADLOCAL_H__
#define __THREADLOCAL_H__
#include "cp.h"

#if defined(V_POSIX_THREAD)
	#include <pthread.h>
#endif 

/**
 * Thread Local class
 *
 *  Usage:
 *     // instance or static variable
 *    ThreadLocal myLocal;
 *   
 *   // muti threaded method
 *   void myMethod() {
 *		void* myObj = myLocal.get()
 *      if(myObj == NULL) {
 *			myObj = new ...
 *			myLocal.set(myObj);
 *		}
 *		// use 'myObj' here
 *	 }
 *
 */
VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT ThreadLocal {
public:
	ThreadLocal();
	~ThreadLocal();
	void* get() const;
	bool set(void* value);
private:
#ifdef _WIN32
    unsigned long m_key;
#else 
#ifdef V_POSIX_THREAD
    pthread_key_t m_key;
#endif
#endif
};

VOLANTE_NAMESPACE_END


#endif //__THREADLOCAL_H__
