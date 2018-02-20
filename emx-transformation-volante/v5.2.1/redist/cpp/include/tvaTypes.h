/*
** Copyright (c) 2007 Tervela Inc,   All rights reserved.
*/

/***********************************************************************
*
* FILE NAME
*      tvaTypes.h
*
* DESCRIPTION
*      Type definitions for common types 
*
***********************************************************************/

#ifndef _TVATYPES_H_
#define _TVATYPES_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* General macros */

#define TVA_TRUE    (1)
#define TVA_FALSE   (0)

#ifndef TVA_EXPORTED
# ifdef WIN32
#  define TVA_EXPORTED      __declspec(dllexport)
# else
#  define TVA_EXPORTED
# endif
#endif

/* Type definitions */

typedef char                TVA_BOOLEAN;
typedef char                TVA_INT8;
typedef short               TVA_INT16;
typedef int                 TVA_INT32;
typedef long long           TVA_INT64;
typedef unsigned char       TVA_UINT8;
typedef unsigned short      TVA_UINT16;
typedef unsigned int        TVA_UINT32;
typedef unsigned long long  TVA_UINT64;
typedef float               TVA_FLOAT;
typedef double              TVA_DOUBLE;
typedef char*               TVA_STRING;

typedef struct date
{
    TVA_UINT64 timeInMicroSecs;
} TVA_DATE;

/* Field Types */

typedef enum tvaFieldType
{
    FIELD_TYPE_INTEGER = 1,
    FIELD_TYPE_LONG,
    FIELD_TYPE_BYTE,
    FIELD_TYPE_SHORT,
    FIELD_TYPE_DEFINEDNUMERIC,
    FIELD_TYPE_FLOAT,
    FIELD_TYPE_DOUBLE,
    FIELD_TYPE_BOOLEAN,
    FIELD_TYPE_DATETIME,
    FIELD_TYPE_STRING,
    FIELD_TYPE_BYTEARRAY = 12,
    FIELD_TYPE_EMBEDDED_MESSAGE,
    FIELD_TYPE_EMBEDDED_ELEMENT_ARRAY
} TVA_FIELD_TYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_TVATYPES_H_*/
