/*****************************************************************************
*                                                                            *
* Module  CFlatency.h                                                        *
*                                                                            *
* Date     Item Release  Author Descriptions                                 *
* -------- ---- -------- ------ ------------                                 *
* 06/20/05      04.00.01 Z.P    Initial version of CF latency class          *
*                                                                            *
*****************************************************************************/
#if ! defined( __TANDEM ) || defined( _OSS_TARGET )
#ifndef CF_latency
#define CF_latency

#ifdef __TANDEM
#if ! defined( _OSS_HOST )
#include <cftdm.h>
#endif
#endif
#ifdef __CSCLIB
#include <csclib.h>
#else
#include <limits.h>
#include <stdio.h>
#include <string.h>
#endif
#ifdef __cplusplus
#include <iostream>
#endif
#include <time.h>

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

//#include <cf.h>
#include <CSinttypes.h>
#include <CFtypes.h>
#include <CFlatencyDef.h>

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
extern const LatencyField  LatencyHeader[];

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
extern const LatencyField  LatencyArray[];

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
const char *getEmitterID();

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
//CS_BOOL
bool
getLatencySwitch();

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
short
getLatencyArrayPreFill();

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_AddLatencySendTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	cs_int64_t      sendTime,
	unsigned 		*rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_AddLatencySendTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	CF_Timestamp    sendTime,
	unsigned        *rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_AddLatencySendTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	unsigned        *rtnLen);

int
CF_UpdateLatencySendTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	cs_int64_t      sendTime,
	unsigned 		*rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_UpdateLatencySendTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	CF_Timestamp    sendTime,
	unsigned        *rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_AddLatencyRecvTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	cs_int64_t      recvTime,
	unsigned 		*rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_AddLatencyRecvTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	CF_Timestamp    recvTime,
	unsigned        *rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_AddLatencyRecvTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	unsigned        *rtnLen);

int
CF_UpdateLatencyRecvTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	cs_int64_t      recvTime,
	unsigned 		*rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_UpdateLatencyRecvTime(
	unsigned int    options,
	char*           msg,
	int             msgLen,
	int             bufSize,
	CF_Timestamp    recvTime,
	unsigned        *rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_UpdateLatencyEventTime(
	unsigned int    options,
	char*           buf,
	int             bufLen,
	int             bufSize,
	CF_Timestamp    eventTime,
	unsigned        *rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_UpdateLatencyEventTime(
	unsigned int    options,
	char*           buf,
	int             bufLen,
	int             bufSize,
	cs_int64_t      eventTime,
	unsigned        *rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_UpdateLatencyEventTime(
	unsigned int    options,
	char*           buf,
	int             bufLen,
	int             bufSize,
	cs_int64_t      eventTime,
	unsigned    	pPrecision,
	unsigned        *rtnLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_UpdateLatencyEventTime(
	unsigned int    options,
	char*           buf,
	int             bufLen,
	int             bufSize,
	char*           eventTime,
	unsigned        *rtnLen);




#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
class CF_Latency
{
public:	

	enum CSLatencyStatus
	{
		EVENT = 0,
		SEND,
		RECEIVE
	};
				
	CF_Latency();
	CF_Latency(CSLatencyFormat::FORMAT format);
	CF_Latency(const char *emitterId);
	CF_Latency(const char *blobBuf, int blobSize);
	CF_Latency(const char *emitterId, cs_int64_t eventTime);
	CF_Latency(const char *emitter, cs_int64_t eventTime, cs_int32_t pPrecision);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	~CF_Latency();

	void reset(const char *emitterId, cs_int64_t eventTime);
	void reset(const char *emitterId);
	char* getFormatedBlob();
	void printBlob();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	const char* getBlob(void);
	const int getBlobSize() { 
	//short t = ((short)arrayCount)*((short)CF_Latency::arraySize_);
	//t += CF_Latency::headerSize_;
	//return(CF_Latency::headerSize_+((short)arrayCount)*((short)CF_Latency::arraySize_)); 
	return(CF_Latency::headerSize_+arrayCount*CF_Latency::arraySize_); 
	};

	static short headerSize_;
	static cs_int8_t arraySize_;
	char *fBuf;
private:
	void buildBlob();
	void updateBlob();

	cs_int64_t	eventTime_;
	cs_int32_t	initialDelta;
	char emitterId_[7];
	char	*blob_;
	bool	blobReady_;
	cs_int8_t	format_;
	cs_int8_t	state;		
	cs_int8_t	arrayMax;		
	cs_int8_t	arrayCount;		
};

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetLatencyField(
	unsigned int    options,
	char*           buf,
	int             bufLen,
	CSLatencyField::FIELDINDEX	fieldNum,
	void            *fieldVal);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetLatencyArrayField(
	unsigned int    options,
	char*           buf,
	int             bufLen,
    int             idx,
	CSLatencyArrayField::FIELDINDEX	fieldNum,
	void            *fieldVal);

#endif
#endif /* cpp*/
