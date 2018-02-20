/*****************************************************************************
*                                                                            *
* Module  CFSP.h                                                             *
*                                                                            *
* Date     Item Release  Author Descriptions                                 *
* -------- ---- -------- ------ ------------                                 *
* 12/08/04      03.10.02 Z.P    Initial version of CFSPtr class              *
*                                                                            *
*****************************************************************************/
#ifndef CFSP_H
#define CFSP_H

template <class X> class CFSPtr
{
public:
#ifndef _IBM_BUILD
    explicit 
#endif
	CFSPtr(X* p = 0)
        : itsCounter(0) {if (p) itsCounter = new counter(p);}
    ~CFSPtr() {release();}
    CFSPtr(const CFSPtr<X>& r) throw() {acquire(r.itsCounter);}
    CFSPtr<X>& operator=( CFSPtr<X>& r)
    {
        if (this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }
	CFSPtr<X>& operator=( X* r)
	{
    	if (itsCounter == 0)
        	itsCounter = new counter(r);
       	else
       	{
       		if (itsCounter->ptr != r)
			   {
               if (--itsCounter->count == 0)
                   delete itsCounter->ptr;
               itsCounter->ptr = r;
               itsCounter->count = 1;
        	   }
       	}
		return *this;
	}

#ifndef _IBM_BUILD
#endif
    X& operator*()  throw()
	{
       createifneeded();
       return *itsCounter->ptr;
    }
    X* operator->() throw()   
    {
       createifneeded();
       return itsCounter->ptr;
    }
    X* get()        const throw()   {return itsCounter ? itsCounter->ptr : 0;}
    bool unique()   const throw()
        {return (itsCounter ? itsCounter->count == 1 : true);}

private:

	struct counter
	{
		counter(X* p = 0, unsigned c = 1) : ptr(p), count(c) {}
	X*          ptr;
        unsigned    count;
    }* itsCounter;

    void acquire(counter* c) throw()
    {
        itsCounter = c;
        if (c) ++c->count;
    }

    inline        
    void createifneeded()
    {
       if (itsCounter == 0)
       {
          X* pl = new X;
          itsCounter = new counter(pl); 
       }
    }

    void release()
    {
        if (itsCounter) {
            if (--itsCounter->count == 0) {
                delete itsCounter->ptr;
                delete itsCounter;
            }
            itsCounter = 0;
        }
    }
};

#endif // CFSP_H

