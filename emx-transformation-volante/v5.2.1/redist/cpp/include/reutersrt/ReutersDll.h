#ifndef __REUTERSDLL_H__
#define __REUTERSDLL_H__
#define REUTERS_EXPORT
#ifdef _MSC_VER
#undef REUTERS_EXPORT
#ifdef REUTERS_PROJECT
#define  REUTERS_EXPORT _declspec(dllexport)
#else
#define  REUTERS_EXPORT _declspec(dllimport)
#endif
#endif

#endif //__REUTERSDLL_H__
