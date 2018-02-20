#ifndef __MD_H__
#define __MD_H__
////////////////////////////////////////////////
// PLATFORM DEPENDENT DECLARATIONS
////////////////////////////////////////////////

///////////////////////////////////////////////
// Designer Type    |  Machine Dependent
///////////////////////////////////////////////
//  Integer            int
//  Long               dlong
//  Character          char
//  Float              float
//  Double             double
//  Boolean            bool
//  String             vstring
//  Date               DateTime
///////////////////////////////////////////////

// NOTE:
// Platform specfic implementations, if any, should be 
// placed in md.cpp

///////////////////////////////////////////////////////////////////////////////
// String Optimization 
// Define VOLANTE_USE_STD_STRING to use std::string instead of volante's custom string 
// Default is to use volante's string
///////////////////////////////////////////////////////////////////////////////

//#define VOLANTE_USE_STD_STRING

///////////////////////////////////////////////////////////////////////////////


#define VOLANTE_USE_BIG_TYPES

//#define VOLANTE_THREAD_SAFE

#define REF_COUNT_TYPE int
#define SAFE_INC(val) ++val
#define SAFE_DEC(val) --val

//Comment out this line to use default namespace
#define VOLANTE_NAMESPACE volante

#if defined(VOLANTE_NAMESPACE)
#define VOLANTE_NAMESPACE_BEGIN namespace  VOLANTE_NAMESPACE {
#define VOLANTE_NAMESPACE_END  }
#define USING_VOLANTE  using namespace VOLANTE_NAMESPACE;
#else 
#define VOLANTE_NAMESPACE 
#define VOLANTE_NAMESPACE_BEGIN
#define VOLANTE_NAMESPACE_END
#define USING_VOLANTE
#endif

#define PLATFORM_EXPORT 
#define PLATFORM_IMPORT 
#define VOLANTE_EXPORT

// OS/Machine specific Starts

///////////////////////////////////////////////////////////////////////////////
// HP-UX 
///////////////////////////////////////////////////////////////////////////////
#if defined(_HPUX_SOURCE) ||  defined(HPUX_SOURCE)

#include <sys/types.h>  // for size_t and ssize_t
#include <limits.h>  // for MAX of size_t and ssize_t
#ifdef _HP_NAMESPACE_STD 
#else
#define std
#define VOLANTE_USE_OLD_STREAMS
#endif

typedef long long dlong;
typedef unsigned long long udlong;
#define LONG_LITERAL(literal) literal ## L

int stricmp(const char* const str1, const char* const  str2);
int strnicmp(const char* const str1, const char* const  str2, const unsigned int count);
#define V_POSIX_THREAD


///////////////////////////////////////////////////////////////////////////////
// TANDEM 
///////////////////////////////////////////////////////////////////////////////
#elif defined (__TANDEM)

#include <sys/types.h>  // for size_t and ssize_t
#include <limits.h>  // for MAX of size_t and ssize_t

// unsigned long is not supported!!
typedef long long dlong;
typedef long long udlong;
#define LONG_LITERAL(literal) literal ## lL

int stricmp(const char* const str1, const char* const  str2);
int strnicmp(const char* const str1, const char* const  str2, const unsigned int count);
#define V_POSIX_THREAD

///////////////////////////////////////////////////////////////////////////////
// LINUX_GCC 
///////////////////////////////////////////////////////////////////////////////
#elif defined (__GNUC__)

typedef long long dlong;
typedef unsigned long long udlong;
#define LONG_LITERAL(literal) literal ## ll

int stricmp(const char* const str1, const char* const  str2);
int strnicmp(const char* const str1, const char* const  str2, const unsigned int count);
inline bool isdigit(char c) {
	return c >= '0' && c <='9';
}
#define V_POSIX_THREAD
//char toupper(const char toUpper);

//char tolower(const char toLower);


///////////////////////////////////////////////////////////////////////////////
// SOLARIS 5.10
///////////////////////////////////////////////////////////////////////////////
#elif defined (__SOLARIS510)

#include <sys/types.h>  // for size_t and ssize_t
#include <sys/time.h>  // for size_t and ssize_t
#include <exception.h>  // for size_t and ssize_t
#include <limits.h>  // for MAX of size_t and ssize_t
#include <typeinfo.h>  // may not be needed here?
//#define VOLANTE_USE_OLD_STREAMS // enable to use OLD stream headers

typedef long long dlong;
typedef unsigned long long udlong;
#define LONG_LITERAL(literal) literal ## L
//#define LONG_LITERAL(literal) literal ## ll // LINUX variant

int stricmp(const char* const str1, const char* const  str2);
int strnicmp(const char* const str1, const char* const  str2, const unsigned int count);
#define V_POSIX_THREAD


///////////////////////////////////////////////////////////////////////////////
// MICROSOFT SPECIFIC 
///////////////////////////////////////////////////////////////////////////////
#elif defined(_MSC_VER)

typedef __int64 dlong;
typedef unsigned __int64 udlong;
#define LONG_LITERAL(literal) literal ## L
#undef PLATFORM_EXPORT
#undef PLATFORM_IMPORT
#define PLATFORM_EXPORT __declspec( dllexport )
#define PLATFORM_IMPORT __declspec( dllimport )
#undef VOLANTE_EXPORT
#pragma warning(disable: 4251)  // using non-exported as public in exported
#ifdef TRANSFORM_PROJECT
#define VOLANTE_EXPORT PLATFORM_EXPORT
#else
#define VOLANTE_EXPORT PLATFORM_IMPORT
#endif //TRANSFORM_PROJECT

#ifdef VOLANTE_THREAD_SAFE
#undef SAFE_INC
#undef SAFE_DEC
#undef REF_COUNT_TYPE
#include <windows.h>
#define REF_COUNT_TYPE volatile LONG
#define SAFE_INC(val) InterlockedIncrement(&val) 
#define SAFE_DEC(val) InterlockedDecrement(&val) 
#endif //VOLANTE_THREAD_SAFE


///////////////////////////////////////////////////////////////////////////////
// Borland SPECIFIC 
///////////////////////////////////////////////////////////////////////////////
#elif defined(__BORLANDC__)

typedef __int64 dlong;
typedef unsigned __int64 udlong;
#define LONG_LITERAL(literal) literal ## L

#define __USING_CNAME__


///////////////////////////////////////////////////////////////////////////////
// MAINFRAME IBM Z/OS (TODO) 
///////////////////////////////////////////////////////////////////////////////
#elif defined (__IBM__ZOS)

typedef long long dlong;
typedef unsigned long long udlong;
#define LONG_LITERAL(literal) literal ## ll

int stricmp(const char* const str1, const char* const  str2);
int strnicmp(const char* const str1, const char* const  str2, const unsigned int count);
inline bool isdigit(char c) {
	return c >= '0' && c <='9';
}
// Z/OS does not seem to support posix threads fully
// Lets us use a dummy implementation for threads
//#define V_POSIX_THREAD


#else 

#error Unrecognized platform/compiler

#endif


#endif //__MD_H__
