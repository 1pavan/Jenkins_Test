/*****************************************************************************
*                                                                            *
* Module  CFtypes.h                                                          *
*                                                                            *
* Date     Item Release  Author Descriptions                                 *
* -------- ---- -------- ------ ------------                                 *
* 12/08/04      03.10.02 Z.P    Initial version of CF type classes           *
*                                                                            *
*****************************************************************************/
#ifndef CF_types
#define CF_types

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
//#include <iostream.h>
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


#ifdef _IBM_BUILD
#include <inttype.h>
#else
#include <CSinttypes.h>
#endif

typedef struct {
	struct tm dtFields;
	int       subSeconds;
	cs_int32_t  precision;
} TS_Fields;

#ifdef __cplusplus
#include <CFException.h>
#include <CFSP.h>

#define CF_TS_SECOND_PRE	1
#define CF_TS_MILLS_PRE		1000
#define CF_TS_MICRO_PRE		1000000
#define CF_TS_NANO_PRE		1000000000
#define CF_TS_DEFAULT_PRE 	CF_TS_MILLS_PRE
#define CF_TS_STRING_SIZE	28
#define CF_MAX_DECIMAL_PREC	9

class CF_Timestamp
{
public:
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Timestamp()
		:lInt64(0) , lStatus(0), lUTCtime(false), lString((char*)0)  {ltm.precision=CF_TS_DEFAULT_PRE;};

// string ctor will throw an exception if format check failed.

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Timestamp(const char* pStrTime,bool pUTCtime=false)
		:lStatus(0), lUTCtime(pUTCtime), lString((char*)0) { set(pStrTime); };
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Timestamp(const char* pStrTime,int pStrLen,bool pUTCtime=false)
		:lStatus(0), lUTCtime(pUTCtime), lString((char*)0) { set(pStrTime,pStrLen); };

//  pSeconds is the number of seconds since Jan. 01, 00:00:00, 1970 
//  ctor will throw an exception if pSeconds is negative.

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Timestamp(cs_int32_t pIntTime,bool pUTCtime=false)
		:lStatus(0), lUTCtime(pUTCtime), lString((char*)0) { set(pIntTime); };

//  pMilliSec is the number of milliseconds since Jan. 01, 00:00:00, 1970 
//  ctor will throw an exception if pMilliSec  is negative or
//  represents a date later than January 18, 19:14:07, 2038.

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Timestamp(cs_int64_t pIntTime,bool pUTCtime=false)
		:lStatus(0), lUTCtime(pUTCtime), lString((char*)0) { set(pIntTime); };

//  pMilliSec is the number of sub-seconds since Jan. 01, 00:00:00, 1970,  
//  ctor will throw an exception if pSubSec is negative or
//  represents a date later than January 18, 19:14:07, 2038.

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Timestamp(cs_int64_t pIntTime,unsigned precision,bool pUTCtime=false)
		:lStatus(0), lUTCtime(pUTCtime), lString((char*)0) { set(pIntTime,precision); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(cs_int32_t  pIntTime) throw (CFException&);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(cs_int32_t  pIntTime, bool UTCflag) {set(pIntTime); lUTCtime=UTCflag;};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(cs_int64_t  pIntTime) throw (CFException&);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(cs_int64_t  pIntTime, bool UTCflag) {set(pIntTime); lUTCtime=UTCflag;};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(cs_int64_t  pIntTime, unsigned precision) throw (CFException&);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(cs_int64_t  pIntTime, unsigned precision, bool UTCflag) {set(pIntTime); lUTCtime=UTCflag;};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(const char*  strVal);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(const char*  strVal, bool UTCflag) {set(strVal); lUTCtime=UTCflag;};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(const char*  strVal,int len) throw (CFException&);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(const char*  strVal,int len, bool UTCflag) {set(strVal,len); lUTCtime=UTCflag;};

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	bool isUTCTimestamp() { return(lUTCtime); }
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	char*       getString();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int64_t  getTime();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int32_t  getSeconds(){ return(getTSField(CF_TSS_FIELD_SEC));};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int         getSubSec(){ return(getTSField(CF_TSS_FIELD_SUBSEC));};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int         getMinutes(){ return(getTSField(CF_TSS_FIELD_MIN));};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int         getHours(){ return(getTSField(CF_TSS_FIELD_HOUR));};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int         getDay(){ return(getTSField(CF_TSS_FIELD_DAY));};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int         getMonth(){ return(getTSField(CF_TSS_FIELD_MON));};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int         getTotalDays(){ return(getTSField(CF_TSS_FIELD_YDAY));};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int         getYear(){ return(getTSField(CF_TSS_FIELD_YEAR));};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int32_t  getPrecision();

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   CF_Timestamp& operator=( const CF_Timestamp& x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   bool operator==( const CF_Timestamp& x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   bool operator!=( const CF_Timestamp& x) { return(!(*this==x)); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   bool operator<( const CF_Timestamp& x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   bool operator>( const CF_Timestamp& x) { return(!((*this==x) || (*this<x))); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	~CF_Timestamp() {if (lString) delete [] lString; };

private:

enum	Timestamp_Status
{
 	CF_TS_STRING_READY			= 0x1,
 	CF_TS_INT_READY				= 0x2,
 	CF_TS_TSS_READY				= 0x3
};

enum	Timestamp_Fields
{
 	CF_TSS_FIELD_SUBSEC,
 	CF_TSS_FIELD_SEC,
 	CF_TSS_FIELD_MIN,
 	CF_TSS_FIELD_HOUR,
 	CF_TSS_FIELD_DAY,
 	CF_TSS_FIELD_MON,
 	CF_TSS_FIELD_YEAR,
 	CF_TSS_FIELD_YDAY
};

	void 		setTSS(int mask);
	int         getTSField(int fieldId);

	char*		lString;
	cs_uint8_t	lStatus;
	cs_int64_t	lInt64;
	TS_Fields	ltm;
	bool		lUTCtime;
};

// string tor will throw exception if non digit char is found.
//
class CF_Decimal
{
enum	Decimal_Status
{
 	CF_DECIMAL_STRING_READY		= 0x1,
 	CF_DECIMAL_DENOM_READY		= 0x2,
	CF_DECIMAL_DOUBLE_READY		= 0x4
};

public:
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Decimal()
		: lNumerator(0) , lPrecision(2), lStatus(CF_DECIMAL_DENOM_READY), lStrLen(0) {};

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Decimal(double dValue, cs_int32_t pPrecision=2)
		: lDval(dValue), lPrecision((pPrecision>CF_MAX_DECIMAL_PREC?CF_MAX_DECIMAL_PREC:pPrecision)), lStatus(CF_DECIMAL_DOUBLE_READY), lStrLen(0) {};

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Decimal(cs_int64_t  numerator,cs_int32_t pPrecision=2)
		: lNumerator(numerator), lPrecision((pPrecision>CF_MAX_DECIMAL_PREC?CF_MAX_DECIMAL_PREC:pPrecision)), lStatus(CF_DECIMAL_DENOM_READY), lStrLen(0) {};

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Decimal(const char*  strVal) :lStrLen(0) { setString(strVal,strlen(strVal)); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Decimal(const char*  strVal, int sLen) :lStrLen(0) { setString(strVal,sLen); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(double dValue);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(double dValue, cs_int32_t pPrecision);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(cs_int64_t  numerator);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(cs_int64_t  numerator, cs_int32_t pPrecision);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(char*  strVal);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void set(char*  strVal,cs_int32_t len);
	//void set(char*  strVal,int len);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void changePrecision(cs_int32_t newPrecision);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int64_t  getNumerator();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int32_t getDenominator();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int64_t  getWhole();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int32_t getFraction();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int32_t getPrecision();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	char* getString();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	double getDouble();

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   CF_Decimal& operator=( const CF_Decimal& x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   bool operator==( const CF_Decimal& x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   bool operator!=( const CF_Decimal& x) { return(!(*this==x)); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   bool operator<( const CF_Decimal& x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   bool operator>( const CF_Decimal& x) { return(!((*this==x) || (*this<x))); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   CF_Decimal& operator+( CF_Decimal& x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   CF_Decimal& operator+( const double x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   CF_Decimal& operator-( const CF_Decimal& x);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
   CF_Decimal& operator-( const double x) { return(*this+(-x)); };



#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	~CF_Decimal();// {if (lStatus&CF_DECIMAL_STRING_READY) delete [] lString; };

private:

	void StringToNum();
	void DoubleToString();
	void NumToDouble();
	void setPrecision();
	void setString(const char*,int) throw (CFException&);
	cs_uint64_t	lNumerator;
	cs_int32_t	lPrecision;
	char*		lString;
	short		lStrLen;
	cs_uint8_t	lStatus;
	double		lDval;

};

typedef CF_Decimal CF_Price;
typedef CFSPtr<CF_Price> CF_Price_Ptr;
typedef CFSPtr<CF_Decimal> CF_Decimal_Ptr;
typedef CFSPtr<CF_Timestamp> CF_Timestamp_Ptr;
typedef CFSPtr<char*> CF_String_Ptr;

class CF_TagData
{
public:
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_TagData()
		:  lTypeMap(0),lStrLen(0)  {};

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void setInt8(cs_int8_t x) { lInt8 = x; };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void setInt16(cs_int16_t x) { lInt16 = x; };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void setInt32(cs_int32_t x) { lInt32 = x; };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void setInt64(cs_int64_t x) { lInt64 = x; };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Decimal_Ptr& getDecimal();

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Price_Ptr& getPrice();

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Timestamp_Ptr& getTimestamp();

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void setString(const char* strVal);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void setData(const char* strVal, int dataLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	const char* getString() { return(lString); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	const char* getData() { return(lString); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int getDataLen() { return(lDataLen); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int8_t getInt8() { return(lInt8); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_uint8_t getUint8() { return((cs_uint8_t)lInt8); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int16_t getInt16() { return(lInt16); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_uint16_t getUint16() { return((cs_uint16_t)lInt16); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int32_t getInt32() { return(lInt32); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_uint32_t getUint32() { return((cs_uint32_t)lInt32); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_int64_t getInt64() { return(lInt64); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	cs_uint64_t getUint64() { return((cs_uint64_t)lInt64); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void setTagType(int tType) { currentType = tType; };
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int tagType() { return(currentType); };

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	~CF_TagData();

private:

	enum	Decimal_Status
	{
 		CF_STRING_READY			= 0x1,
 		CF_DECIMAL_READY		= 0x2,
		CF_TIMESTAMP_READY		= 0x4
	};

	short currentType;
	cs_int8_t lInt8;
	cs_int16_t lInt16;
	cs_int32_t lInt32;
	cs_int64_t lInt64;
	CF_Decimal_Ptr lDecimal;
	CF_Timestamp_Ptr lTimestamp;
	char *lString;
	short lStrLen;
	int lDataLen;

	cs_uint32_t	lTypeMap;

};
#endif
#endif /* CF_types */
