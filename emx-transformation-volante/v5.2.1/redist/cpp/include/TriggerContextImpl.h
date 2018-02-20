#ifndef __TRIGGERCONTEXTIMPL_H__
#define __TRIGGERCONTEXTIMPL_H__
/*
*  TriggerContextImpl.h
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

#include "LookupContextFactory.h" 
#include "AbstractTriggerContext.h" 

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT TriggerContextImpl : public  AbstractTriggerContext {
	LookupContext cxt;
public:
	TriggerContextImpl() {
	}
private:
	LookupContext getLookupContext() {
		if(cxt.isNull()) {
			cxt = LookupContextFactory::getLookupContext();
		}
		return cxt;
	}
public:

	Message lookupMessage(const vstring& name) {
		return getLookupContext()->lookupMessage(name);
	}
	InternalMessage lookupInternalMessage(const vstring& name) {
		return getLookupContext()->lookupInternalMessage(name);
	}

	ExternalMessage lookupExternalMessage( const vstring& name)  {
		return getLookupContext()->lookupExternalMessage(name);
	}
	MessageFlow lookupMessageFlow( const vstring& name)  {
		return getLookupContext()->lookupMessageFlow(name);
	}
	MessageMapping lookupMessageMapping( const vstring& name)  {
		return getLookupContext()->lookupMessageMapping(name);
	}
	NormalizedObjectMappingFormat lookupNormalizedObjectMappingFormat( const vstring& name)  {
		return getLookupContext()->lookupNormalizedObjectMappingFormat(name);
	}
	OutputFormat lookupOutputFormat(const vstring& name)  {
		return getLookupContext()->lookupOutputFormat(name);
	}
	InputFormat lookupInputFormat(const vstring& name)  {
		return getLookupContext()->lookupInputFormat(name);
	}
	Object* lookupComponent(const vstring& name) {
		return getLookupContext()->lookupComponent(name);
	}
	BusinessTransaction lookupBusinessTransaction(const vstring& name)  {
		return getLookupContext()->lookupBusinessTransaction(name);
	}
	IOutputProtocol* lookupOutputProtocol(const vstring& name) {
		return getLookupContext()->lookupOutputProtocol(name);
	}
	/*
	public BatchContext createBatchContext() throws javax.naming.NamingException {
	return getLookupContext().createBatchContext();
	}
	public void destroyBatchContext(BatchContext bc) throws TransformException,java.rmi.RemoteException,javax.naming.NamingException {
	getLookupContext().destroyBatchContext(bc);
	}
	public com.tplus.transform.util.sql.connection.ConnectionPool lookupDataSourceconst vstring& name) throws TransformException,java.rmi.RemoteException,javax.naming.NamingException {
	return getLookupContext().lookupDataSource(name);
	}
	public PersistenceManager lookupPersistenceManagerconst vstring& name) throws NamingException {
	return getLookupContext().lookupPersistenceManager(name);
	}*/

	StringList getExternalMessages()  {
		return getLookupContext()->getExternalMessages();
	}
	StringList getMessageMappings()  {
		return getLookupContext()->getMessageMappings();
	}
	StringList getMessageFlows()  {
		return getLookupContext()->getMessageFlows();
	}
	StringList getMessages() {
		return getLookupContext()->getMessages();
	}

	StringList getInternalMessages()  {
		return getLookupContext()->getInternalMessages();
	}
	StringList getInputFormats()  {
		return getLookupContext()->getInputFormats();
	}
	StringList getOutputFormats()  {
		return getLookupContext()->getOutputFormats();
	}
	StringList getNormalizedObjectMappings()  {
		return getLookupContext()->getNormalizedObjectMappings();
	}

	void bind(const vstring& name, Object* obj)  {
		getLookupContext()->bind(name, obj);
	}
	void rebind(const vstring& name, Object* obj)  {
		getLookupContext()->rebind(name, obj);
	}
	Object* lookup(const vstring& name) {
		return getLookupContext()->lookup(name);
	}
	void unbind(const vstring& name)  {
		getLookupContext()->unbind(name);
	}
};
VOLANTE_NAMESPACE_END

#endif //__TRIGGERCONTEXTIMPL_H__

