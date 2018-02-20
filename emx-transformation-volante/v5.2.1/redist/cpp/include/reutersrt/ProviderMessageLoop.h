#ifndef __PROVIDERMESSAGELOOP_H__
#define __PROVIDERMESSAGELOOP_H__
//
//|---------------------------------------------------------------
//|                Copyright (C) 2001 Reuters,                  --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//

// MessageLoop.h: interface for the related MessageLoop class.
//
//////////////////////////////////////////////////////////////////////



namespace rfa {
	namespace common {
		class EventQueue;
	}
}


#include "Timer.h"

class ProviderMessageLoop
{
public:
	ProviderMessageLoop();
	~ProviderMessageLoop();

	void	run(rfa::common::EventQueue  *pEQueue, CTimer* timer);
	
	inline void terminate() { _isActive = false; }

	void	setTimerClient(CTimerClient& timerClient);

private:
	ProviderMessageLoop(const ProviderMessageLoop&);
	ProviderMessageLoop& operator=(const ProviderMessageLoop&);

	bool _isActive;
	CTimerClient*	_timerClient;
};




#endif //__PROVIDERMESSAGELOOP_H__
