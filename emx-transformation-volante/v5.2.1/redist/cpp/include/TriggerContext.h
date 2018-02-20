#ifndef __TRIGGERCONTEXT_H__
#define __TRIGGERCONTEXT_H__
/*
*  TriggerContext.h
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
#include "LookupContext.h"

VOLANTE_NAMESPACE_BEGIN

/** 
* The TriggerContext provides the trigger classes access to the runtime environment.
* 
*  Using the TriggerContext a trigger can
*
*  <ul>
*  <li> access other generated components, such as a output format, business transaction etc.
*  <li> access application specific components. For instance, application specific bean if 
*        it is running under EJB environment.
*  <li> access properties defined during design time.
*  </ul>
*
* Note that all the lookup methods are defined in the base interface 
* <code>LookupContext<code>.
*
* @see LookupContext
* @see ITrigger
* @see ITrigger#setContext
*/
class VOLANTE_EXPORT TriggerContext : public ILookupContext {
public:
	typedef std::map<vstring, vstring> StringMap;
public:

	/**
	*  Returns the value of specified property. The properties are name-value pairs specified
	*  during design time. You can avoid hardcoding application specific values in the 
	*  trigger class using design time properties. 
	*  @throws NamingException if the property is not specified during design time.
	*  @return the value of the property (never null)
	*/
	virtual vstring getProperty(const vstring&  name) const = 0;


	virtual bool getProperty(const vstring&  name, vstring& value)const = 0;
	virtual const StringMap& getProperties()const = 0;

	/**
	*  Returns the BusinessTransaction as part of which the trigger is executing.
	*  @return the triggers' BusinessTransaction
	*/
	virtual BusinessTransaction getBusinessTransaction() const = 0;


	/**
	*  Returns the a unique name for the associated trigger
	*  @return unique name for the trigger
	*/
	virtual vstring getIdentity() const = 0;

};
VOLANTE_NAMESPACE_END

#endif //__TRIGGERCONTEXT_H__

