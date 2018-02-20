/*****************************************************************************
*                                                                            *
* Module  CFlatencyDef.h                                                     *
*                                                                            *
* Date     Item Release  Author Descriptions                                 *
* -------- ---- -------- ------ ------------                                 *
* 06/20/05      04.00.01 Z.P    Initial version of CF latency defines        *
*                                                                            *
*****************************************************************************/
#ifndef CFLATENCYDEF
#define CFLATENCYDEF
#include <tags.h>

#ifdef _NT_BUILD
#define DECLSPEC	1
#ifdef _NT_EXE_BUILD
#define	DECLSPEC_TOKEN	dllimport
#define	DECLSPEC_TOKEN2	dllimport
#endif
#ifdef _NT_LIB_BUILD
#define	DECLSPEC_TOKEN	dllexport
#define	DECLSPEC_TOKEN2	dllimport
#endif
#ifdef _NT_LIB2_BUILD
#define	DECLSPEC_TOKEN	dllimport
#define	DECLSPEC_TOKEN2	dllexport
#endif
#endif

typedef struct latency_field_def
{
	const   char    *fieldname;
	short           type;
	short           size;
	short           offset;
}   LatencyField;

#ifdef DECLSPEC
extern __declspec( DECLSPEC_TOKEN )
#endif
const short latencyHeaderFields;

class CSLatencyField
{
public:
enum FIELDINDEX
{
	HEADERSIZE = 0,
	ARRAYSIZE,
	ARRAYCOUNT,
	ARRAYUSED,
	STATUS,
	FORMAT,
	EMITTERID,
	EVENTTIME,
	SENDTIME,
	RECVTIME
};
};

class CSLatencyArrayField
{
public:
enum FIELDINDEX
{
	RECVTIME = 0,
	EMITTERID,
	SENDTIME
};
};

enum CSLatencyStatus
{
	EVENT = 0x0,
	SEND  = 0x1,
	RECEIVE = 0x2
};

class CSLatencyFormat
{
public:
enum FORMAT
{
	MILLSECOND = 1,
	MICROSECOND,
	NANOSECOND
};
};

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#else
const
#endif
LatencyField	CSLatencyBlob[];

#ifdef DECLSPEC
extern __declspec( DECLSPEC_TOKEN )
#endif
const short latencyArrayFields;

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#else
const
#endif
LatencyField	CSLatencyArray[];
#endif /* CFLATENCYDEF */
