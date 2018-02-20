#ifndef __ABSTRACTTRIGGERCONTEXT_H__
#define __ABSTRACTTRIGGERCONTEXT_H__
/*
*  AbstractTriggerContext.h
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
#include "TriggerContext.h"
#include "Exceptions.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT AbstractTriggerContext : public  TriggerContext {
private:
	StringMap properties;
	BusinessTransaction businessTransaction;
	vstring identity;
	vstring triggerClass;
	ITrigger* triggerObject;

public:
	AbstractTriggerContext();
	AbstractTriggerContext(BusinessTransaction businessTransaction, const vstring& triggerClass, const vstring& identity);
	~AbstractTriggerContext();
	void init(BusinessTransaction businessTransaction, const vstring& triggerClass, const vstring& identity);

    vstring getIdentity() const;
	vstring getTriggerClassName();
	void setTriggerObject(ITrigger* triggerObject);
	ITrigger* getTriggerObject();
	BusinessTransaction getBusinessTransaction() const;
	void addProperty(vstring name, vstring value);
	vstring getProperty(const vstring& name)const;
	bool getProperty(const vstring& name, vstring& value)const;
	const StringMap& getProperties()const;

};

VOLANTE_NAMESPACE_END

#endif //__ABSTRACTTRIGGERCONTEXT_H__

