// PollMessageLoop.h: interface for the related MessageLoop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(RFA_EAP2_STTICKER_MESSAGELOOP_H)
#define RFA_EAP2_STTICKER_MESSAGELOOP_H


#include "Common/DispatchableNotificationClient.h"

#include <unistd.h>


class rfa::common::Dispatchable;

/**
	The idea of RFA_MessageLoop is to create an abstract user interface 
	that can be used to integrate the RFA event distribution logic into 
	an existing event dispatching mechanism
 */
class RFA_MessageLoop  : public rfa::common::DispatchableNotificationClient
{
public:
	RFA_MessageLoop();
	virtual ~RFA_MessageLoop();

	virtual void	init( rfa::common::Dispatchable & disp ) = 0;
	virtual void	run( void ) = 0;
	virtual void	cleanup( void ) = 0;
	virtual void	notify( rfa::common::Dispatchable & eventSource,
		                    void* closure ) = 0;

protected:
	static rfa::common::Dispatchable	*_pDisp;

private:
	RFA_MessageLoop(const RFA_MessageLoop&);
	RFA_MessageLoop& operator=(const RFA_MessageLoop&);
};

/**
	It represents a concrete Polling Message loop version of RFA_MessageLoop.
 */
class Poll_MessageLoop : public RFA_MessageLoop
{
public:
	Poll_MessageLoop();
	virtual ~Poll_MessageLoop();

	virtual void	init( rfa::common::Dispatchable & disp );
	virtual void	run( void );
	virtual void	cleanup( void );
	virtual void	notify( rfa::common::Dispatchable & eventSource,
		                    void* closure );

protected:

	static void handleIt( );
  
	static  long	_instanceCount;
	static	long	_msgCount;

private:
	Poll_MessageLoop(const Poll_MessageLoop&);
	Poll_MessageLoop& operator=(const Poll_MessageLoop&);


	struct pollfd		*_pollFds;
	int					_pollMaxIdx;
	int                 _pipe[2];
	int                 _infoOnPipe:1;
	bool		    _isCleanup; 

};

#endif // !defined(RFA_EAP2_STTICKER_MESSAGELOOP_H)
