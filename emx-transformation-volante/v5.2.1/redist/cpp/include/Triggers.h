#ifndef __TRIGGERS_H__
#define __TRIGGERS_H__
/*
*  Triggers.cpp
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


#include "DataObject.h"
#include "TransformContext.h"
#include "UserClassManager.h"
#include "ITrigger.h"
#include "AbstractTriggerContext.h"
#include "TriggerContextImpl.h"
#include "BusinessTransactionWrapper.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT Triggers {
	BusinessTransaction bt;
public:
	Triggers(BusinessTransaction bt);
	BusinessTransaction getBusinessTransaction();
	virtual Object* invokeTrigger(Properties& props);
	void onNewMessage(NormalizedObject* inputObj, TransformContext& cxt);
	virtual void onNewMessage0(NormalizedObject* inputObj, TransformContext& cxt)  = 0;
	virtual void onBatchStart(TransformContext& tcxt) = 0;
	virtual void onBatchEnd(TransformContext& tcxt) = 0;
protected:
	ITrigger* getTriggerObject(AbstractTriggerContext& triggerInfo);
private:
	ITrigger* createTriggerInstance(const vstring& triggerClass);
};

VOLANTE_NAMESPACE_END

#endif //__TRIGGERS_H__

