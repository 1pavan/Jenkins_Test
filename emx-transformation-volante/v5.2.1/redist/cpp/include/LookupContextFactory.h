#ifndef __LOOKUPCONTEXTFACTORY_H__
#define __LOOKUPCONTEXTFACTORY_H__


/*
*  LookupContextFactory.h
*
*  © Copyright 2001-2006 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/
/** 
 * The LookupContext factory provides access to other components executing in the runtime environment.
 * 
 *  Using the LookupContextfactory you can 
 *
 *  <ul>
 *  <li> access other generated components, such as a output format, business transaction etc.
 *  <li> access application specific components. For instance, application specific bean if 
 *        it is running under EJB environment.
 *  </ul>
 *
 *
 * @see TriggerContext
 */

#include "LookupContext.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT Cartridge {

};




class VOLANTE_EXPORT LookupContextFactory {
public:
	static LookupContext getLookupContext() {
		return getLookupContextFactory().createLookupContext();
	}
	static LookupContextFactory& getLookupContextFactory();

	LookupContext createLookupContext();
private:
};

VOLANTE_NAMESPACE_END

#endif //__LOOKUPCONTEXTFACTORY_H__

