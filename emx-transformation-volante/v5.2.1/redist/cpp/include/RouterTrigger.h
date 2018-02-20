#ifndef __ROUTERTRIGGER_H__
#define __ROUTERTRIGGER_H__


/*
*  RouterTrigger.h
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
 *  Added support for overriding output format specified in CP.
 */
#include "ITrigger.h"
#include "TriggerContext.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT AbstractTrigger : public ITrigger {
    
public:
	AbstractTrigger() {
        cxt = NULL;
    }
    
    void setContext(TriggerContext* cxt);
	Object* execute(Properties& props);
protected:
	TriggerContext* getTriggerContext() {
		return cxt;
	}
	TransformContext& getTransformContext(TransformContext& tcxt);

protected:
	OutputFormat getOutputFormat(vstring name);
protected:
    TriggerContext* cxt;
    TransformContextWrapper overridingContext;
	typedef ObjectMap<OutputFormat> OutputFormatMap;
    OutputFormatMap outputFormats;
};


class VOLANTE_EXPORT RouterTrigger : public AbstractTrigger {
public:
    
public:
	void onNewMessage(NormalizedObject* obj, TransformContext& tcxt);
    void onBatchStart(TransformContext& tcxt);
    void onBatchEnd(TransformContext& tcxt);
protected:
};


class VOLANTE_EXPORT InternalRouterTrigger : public AbstractTrigger {
    NormalizedObjectMappingFormat internaMessageMappingFormat;
    BusinessTransaction destinationInternalMessageFormat;
    vstring internalMsgMappingName;
public:    
    void setContext(TriggerContext* cxt);
    
    void onBatchStart(TransformContext& tcxt);
    
    void onNewMessage(NormalizedObject* obj, TransformContext& tcxt);
    
    void onBatchEnd(TransformContext& tcxt);
private:
    void initNormalizedObjectMappingFormat();
};

VOLANTE_NAMESPACE_END

#endif //__ROUTERTRIGGER_H__

