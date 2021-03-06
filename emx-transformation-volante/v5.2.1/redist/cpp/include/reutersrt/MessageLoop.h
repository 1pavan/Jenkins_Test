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


#if !defined(RFA_MESSAGELOOP_H)
#define RFA_MESSAGELOOP_H

#if !defined( WIN32 ) && !defined( _WIN32 )
#error Supported on Win32 build only
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "windows.h"

#include <cassert>


#include "Common/DispatchableNotificationClient.h"


class rfa::common::Dispatchable;

#define WinMsg_RFA_MessageLoop_DataMessage WM_USER
#define	WinMsg_RFA_MessageLoop_WindowClass "WinMsg_RFA_MessageLoop_WindowClass"
#define	WinMsg_RFA_MessageLoop_WindowName "WinMsg_RFA_MessageLoop_HiddenWindow"

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
	It represents a concrete Windows Message loop version of RFA_MessageLoop.
	Windows Message Queue mechanisms are employed for dispatching incoming
	RFA events. 
 */
class WinMsg_RFA_MessageLoop : public RFA_MessageLoop
{
public:
	WinMsg_RFA_MessageLoop();
	virtual ~WinMsg_RFA_MessageLoop();

	virtual void	init( rfa::common::Dispatchable & disp );
	virtual void	run( void );
	virtual void	cleanup( void );
	virtual void	notify( rfa::common::Dispatchable & eventSource,
		                    void* closure );

protected:

	static BOOL WINAPI CtrlHandler( DWORD CtrlType );
	static LRESULT CALLBACK WindowProc(  HWND hwnd,  UINT uMsg, WPARAM wParam,  LPARAM lParam );
  
	static  long	_instanceCount;
	static  HWND	_hWnd;
	static	ATOM	_WndClass;
	static	DWORD	_threadId;
	static	long	_msgCount;

private:
	WinMsg_RFA_MessageLoop(const WinMsg_RFA_MessageLoop&);
	WinMsg_RFA_MessageLoop& operator=(const WinMsg_RFA_MessageLoop&);
};

#endif // !defined(RFA_MESSAGELOOP_H)
