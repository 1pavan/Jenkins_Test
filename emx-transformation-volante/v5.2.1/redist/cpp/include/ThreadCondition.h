#ifndef __THREADCONDITION_H__
#define __THREADCONDITION_H__
#include "Transform.h"
#include "cp.h"

#ifdef _WIN32
  #define HAS_WINTHREADS
#elif defined(V_POSIX_THREAD)
  #define HAS_PTHREADS
#endif

#include "Mutex.h"

#if defined(HAS_PTHREADS)
#   include <pthread.h>
#endif

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT ThreadConditionImpl {
    friend class condition;

public:
    ThreadConditionImpl();
    ~ThreadConditionImpl();

    void notify_one();
    void notify_all();

#if (defined(HAS_WINTHREADS))
    void enter_wait();
    void do_wait();
    void* m_gate;
    void* m_queue;
    void* m_mutex;
    unsigned m_gone;  // # threads that timed out and never made it to m_queue
    unsigned long m_blocked; // # threads blocked on the condition
    unsigned m_waiting; // # threads no longer waiting for the condition but
                        // still waiting to be removed from m_queue
#elif defined(HAS_PTHREADS)
    void do_wait(pthread_mutex_t* pmutex);
    //bool do_timed_wait(const xtime& xt, pthread_mutex_t* pmutex);
    pthread_cond_t m_condition;
#endif
};


class VOLANTE_CP_EXPORT ThreadCondition 
{
public:
    ThreadCondition();
    ~ThreadCondition();

    void notify_one();
    void notify_all();

    void wait(Mutex& mutex);
private:
    ThreadConditionImpl m_impl;
    void do_wait(Mutex& mutex);

};

VOLANTE_NAMESPACE_END

#endif //__THREADCONDITION_H__
