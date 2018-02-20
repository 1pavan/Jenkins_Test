#ifndef __ITRIGGER_H__
#define __ITRIGGER_H__


/*
*  ITrigger.h
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
 * Interface for external classes to process the Normalized object.
 * The implementing class is called when either a new message arrives 
 * or at a preconfigured time (or time interval). 
 * Before the trigger method is called the runtime calls the trigger's <code>setContext</code> method.
 * The TriggerContext allows the implementing class to access the runtime environment.
 *
 * <p>The implementing class,  
 * <ul>
 *     <li> should be public
 *     <li> should have public default constructor
 *     <li> should be made available to the generated JAR at runtime (by specifying in the manifest classpath)
 *     <li> should be stateless. The class should not maintain call specific data.
 * </ul>
 *
 * As many instances of the implementing class will be created as required. The class 
 * should not expect all calls to be made to one particular instance. 
 *
 */
#include "Object.h"
#include "DataObject.h"
#include "ICustomClass.h"
#include "TransformContext.h"
#define NAME_PROPERTY "name"

VOLANTE_NAMESPACE_BEGIN
class TriggerContext;

class VOLANTE_EXPORT ITrigger : public ICustomClass {
    
    /**
     * Called when a new message arrives. The trigger can process the message
     * by applying application specific business logic.
     *
     * @param obj the normalized object 
     * @param tcxt A context object that provides access to the context in which the transformation occurs.
     *             
     * @throws TransformException if business logic cannot be applied on the normalized object.
     *         A exception throw by the trigger is treated as a fatal error for the object and
     *         further processing of the normalized object is terminated.
     * 
     */
public:
	virtual void onNewMessage(NormalizedObject* obj, TransformContext& tcxt) = 0;
    
    /**
     * Sets the context in which the trigger executes. Typically,
     * the trigger class would save the context in an instance field for later use.
     * The TriggerContext allows the implementing class to access the runtime environment.
     * @param tcxt A context object that provides access to the context in which the trigger 
     *             executes.  
     */
    virtual void setContext(TriggerContext* tcxt) = 0;

	/**
     *  Informs the trigger that a batch is about to start. The information
     *  about the batch is in the TransformContext object. The trigger
     *  typically notifies the output format associated with the batch that 
     *  the batch is about to start.
     * @param tcxt A context object that provides access to the context in which the transformation occurs
     */
	virtual void onBatchStart(TransformContext& tcxt) = 0;
	/**
     *  Informs the trigger a batch has ended. The information
     *  about the batch is in the TransformContext object. The trigger
     *  in turn notifies the output format associated with the batch
     *  that the batch has ended.
     * @param tcxt A context object that provides access to the context in which the transformation occurs
     */
	virtual void onBatchEnd(TransformContext& tcxt) = 0;

	/**
     *  Execute this trigger. This method is called by the business transaction 
     *  when an external client calls its invokeTrigger method with the name
     *  property set to this trigger's name. This method is applicable only for
     *  on demand triggers. This is a convienient method for an external
     *  client to trigger some application specific action.
     *
     *  @see com.tplus.transform.runtime.BusinessTransaction#invokeTrigger
     */
	virtual Object* execute(Properties& props) = 0;

};

VOLANTE_NAMESPACE_END

#endif //__ITRIGGER_H__

