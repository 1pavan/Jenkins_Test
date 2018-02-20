#ifndef __LOOKUPCONTEXT_H__
#define __LOOKUPCONTEXT_H__

/*
*  LookupContext.cpp
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

#include "Object.h"
#include "InternalMessage.h"
#include "ExternalMessage.h"
#include "InputFormat.h"
#include "OutputFormat.h"
#include "NormalizedObjectMappingFormat.h"
#include "OutputProtocol.h"
#include "MessageMapping.h"
#include "MessageFlow.h"

VOLANTE_NAMESPACE_BEGIN

/** 
* The LookupContext provides access to other components executing in the runtime environment.
* 
*  Using the LookupContext you can 
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

class VOLANTE_EXPORT ILookupContext : public ObjectRef {
public:
	//typedef std::vector<vstring> StringList;
	/**
	*  Look up a component that is running as part of this application. 
	*  In case of EJB this method can be used to lookup other application
	*  specific beans or generated beans such as another BusinessTransaction.
	*  @throws NamingException if the property is not specified during design
	*/
	virtual Object* lookupComponent(const vstring& name) = 0;
	/**
	*  Look up a NormalizedObject Mapper ( maps one NO to another)
	*/
	virtual NormalizedObjectMappingFormat lookupNormalizedObjectMappingFormat(const vstring& name) = 0;

	/**
	* Look up a message. The message can be {@link IInternalMessage} or an {@link IExternalMessage}.
	* The message should have been defined using the Designer and deployed or made available in the
	* current context (by linking to it).
	*
	* @param name lookup name of the message
	* @return the message processor object.
	* @throws NamingException thrown if such a message object does not exist or could not be instantiated.
	* @see #lookupExternalMessage(String)
	* @see #lookupInternalMessage(String)
	*/
	virtual Message lookupMessage(const vstring& name) = 0;
	/**
	* Look up a external message.
	* The message should have been defined using the Designer and deployed or made available in the
	* current context.
	*
	* @param name lookup name of the external message
	* @return the external message object.
	* @throws NamingException thrown if such a message object does not exist or could not be instantiated.
	* @see #lookupMessage(String)
	* @see #lookupInternalMessage(String)
	*/
	virtual ExternalMessage lookupExternalMessage(const vstring& name) = 0;


	/**
	* Look up a internal message.
	* The message should have been defined using the Designer and deployed or made available in the
	* current context.
	*
	* @param name lookup name of the internal message
	* @return the internal message object.
	* @throws NamingException thrown if such a message object does not exist or could not be instantiated.
	* @see #lookupMessage(String)
	* @see #lookupExternalMessage(String)
	*/
	virtual InternalMessage lookupInternalMessage(const vstring& name) = 0;


	/**
	* Look up a message mapping.
	* The message mapping should have been defined using the Designer and deployed or made available in the
	* current context.
	*
	* @param name lookup name of the message mapping
	* @return the message mapping object.
	* @throws NamingException thrown if such a message flow object does not exist or could not be instantiated.
	* @see #lookupMessage(String)
	* @see #lookupMessageFlow(String)
	*/
	virtual MessageMapping lookupMessageMapping(const vstring& name) = 0;

	/**
	* Look up a message flow.
	* The message flow should have been defined using the Designer and deployed or made available in the
	* current context.
	*
	* @param name lookup name of the message flow
	* @return the message flow object.
	* @throws NamingException thrown if such a message flow object does not exist or could not be instantiated.
	* @see #lookupMessage(String)
	* @see #lookupMessageMapping(String)
	*/
	virtual MessageFlow lookupMessageFlow(const vstring& name) = 0;

	/**
	*  Look up a Business Transaction
	*  @deprecated use lookupInternalMessage
	*/
	virtual BusinessTransaction lookupBusinessTransaction(const vstring& name) = 0;

	/**
	*  Look up an Input format 
	*  @deprecated
	*/
	virtual InputFormat lookupInputFormat(const vstring& name) = 0;
	/**
	*  Look up an Output format 
	*  @deprecated
	*/
	virtual OutputFormat lookupOutputFormat(const vstring& name) = 0;
	virtual IOutputProtocol* lookupOutputProtocol(const vstring& name) = 0;


	/**
	* Returns the names of messages deployed in this runtime environment
	* @return names of messages deployed in this runtime environment
	* @throws NamingException NamingException while preparing the list
	*/
	virtual StringList getMessages() = 0;
	/**
	* Returns the names of external messages deployed in this runtime environment
	* @return names of external messages deployed in this runtime environment
	* @throws NamingException NamingException while preparing the list
	*/
	virtual StringList getExternalMessages() = 0;
	/**
	* Returns the names of internal messages deployed in this runtime environment
	* @return names of internal messages deployed in this runtime environment
	* @throws NamingException NamingException while preparing the list
	*/
	virtual StringList getInternalMessages() = 0;

	/**
	* Returns the names of message mapping deployed in this runtime environment
	* @return names of message flows deployed in this runtime environment
	* @throws NamingException NamingException while preparing the list
	*/
	virtual StringList getMessageMappings() = 0;
	/**
	* Returns the names of message flows deployed in this runtime environment
	* @return names of message flows deployed in this runtime environment
	* @throws NamingException NamingException while preparing the list
	*/
	virtual StringList getMessageFlows() = 0;
	virtual StringList getInputFormats() = 0;
	virtual StringList getOutputFormats() = 0;
	virtual StringList getNormalizedObjectMappings() = 0;
	virtual void bind(const vstring& name, Object* obj) = 0;
	virtual void rebind(const vstring& name, Object* obj) = 0;
	virtual Object* lookup(const vstring& name) = 0;
	virtual void unbind(const vstring& name) = 0;
};
typedef SmartPtr<ILookupContext> LookupContext;

VOLANTE_NAMESPACE_END

#endif //__LOOKUPCONTEXT_H__

