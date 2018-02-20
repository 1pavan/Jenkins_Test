/*
** Copyright (c) 2007 Tervela Inc,   All rights reserved.
*/

/***********************************************************************
*
* FILE NAME
*      tvaSecurityContext.h
*
* DESCRIPTION
*      Security context support header file
*
***********************************************************************/

#ifndef _TVASECURITYCONTEXT_H_
#define _TVASECURITYCONTEXT_H_

/* includes */
#include "tvaTypes.h"
#include "tvaErrors.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* TVA_PASSWORD_SECURITY_CONTEXT -- Password security context	*/
#define TVA_PASSWORD_SECURITY_CONTEXT "PWD"

/* typedefs */

/* General type definitions */

typedef struct tvaSecurityContext
{
    TVA_STRING passwordContext;
    unsigned char securityContextString[17];
}TVA_SECURITY_CONTEXT;

/* methods */

/* ---------------------------------------------------------------------*/
/* tvaSetSecurityContextString -- This function sets the security 	*/
/*                                context string for the password.	*/
/* ---------------------------------------------------------------------*/

TVA_EXPORTED TVA_STATUS tvaSetSecurityContextString(
        TVA_SECURITY_CONTEXT* securityContext, 
        TVA_STRING password);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_TVASECURITYCONTEXT_H_*/
