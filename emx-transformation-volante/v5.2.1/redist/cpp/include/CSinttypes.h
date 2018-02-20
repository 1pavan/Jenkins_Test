/******************************************************************************
*                                                                             *
*   CSinttypes.h                                                              *
*                                                                             *
******************************************************************************/
/* DATE       VERSION    ITEM  AUTHOR    DESCRIPTION
 * -------    --------   ----  -------   ----------------------------------------------------------
 * 04/17/06   03.70.02         JH        Remove cs_timespec definitions.
 *
 */

#ifndef CSINTTYPESH
#define CSINTTYPESH

typedef char					cs_int8_t;
typedef unsigned char			cs_uint8_t;
typedef short					cs_int16_t;
typedef unsigned short			cs_uint16_t;

typedef long					cs_int32_t;
typedef unsigned long			cs_uint32_t;

#if defined(_NT_BUILD)
typedef	__int64					cs_int64_t;
typedef	unsigned __int64		cs_uint64_t;

typedef unsigned int              cs_time_t;

#define CS_INT8_MIN				_I8_MIN
#define CS_INT8_MAX				_I8_MAX
#define CS_UINT8_MAX			_UI8_MAX

#define CS_INT16_MIN			_I16_MIN
#define CS_INT16_MAX			_I16_MAX
#define CS_UINT16_MAX			_UI16_MAX

#define CS_INT32_MIN			_I32_MIN
#define CS_INT32_MAX			_I32_MAX
#define CS_UINT32_MAX			_UI32_MAX

#define CS_INT64_MIN			_I64_MIN
#define CS_INT64_MAX			_I64_MAX
#define CS_UINT64_MAX			_UI64_MAX

#else 

#include  <limits.h>
#if !defined (__TANDEM) || defined(_OSS_TARGET)
#include  <stdio.h>
#endif

#define CS_INT8_MIN               SCHAR_MIN
#define CS_INT8_MAX               SCHAR_MAX
#define CS_UINT8_MAX              UCHAR_MAX

#define CS_INT16_MIN              SHRT_MIN
#define CS_INT16_MAX              SHRT_MAX
#define CS_UINT16_MAX             USHRT_MAX

#define CS_INT32_MIN              INT_MIN
#define CS_INT32_MAX              INT_MAX
#define CS_UINT32_MAX             UINT_MAX

#define CS_MSG_DELIMITER          2120113790  /* Value is equal to 
                                                 CS_MSG_DELIMITER_PATTERN */

#define CS_MSG_DELIMITER_PATTERN  "~^^~"        

typedef unsigned int              cs_time_t;


#ifdef __LP64__

#define	CS_INT64_MIN			  LONG_MIN;
#define	CS_INT64_MAX			  LONG_MAX;
#define	CS_UINT64_MAX			  ULONG_MAX;

typedef	long        		  	  cs_int64_t;
typedef	unsigned long        	  cs_uint64_t;

#else

typedef	long long        		  cs_int64_t;

#ifdef __TANDEM

typedef	long long                 cs_uint64_t;

#define	CS_INT64_MIN			  LLONG_MIN
#define	CS_INT64_MAX			  LLONG_MAX
#define	CS_UINT64_MAX			  LLONG_MIN

#else

typedef	unsigned long long        cs_uint64_t;

#ifdef _IBM_BUILD
#define	CS_INT64_MIN			  LONGLONG_MIN
#define	CS_INT64_MAX			  LONGLONG_MAX
#define	CS_UINT64_MAX			  ULONGLONG_MAX
#else
#define	CS_INT64_MIN			  LONG_LONG_MIN
#define	CS_INT64_MAX			  LONG_LONG_MAX
#define	CS_UINT64_MAX			  ULONG_LONG_MAX
#endif

#endif

#endif

#endif
#endif /*CSINTTYPESH*/
