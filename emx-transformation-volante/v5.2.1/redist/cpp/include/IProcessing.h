#ifndef __IPROCESSING_H__
#define __IPROCESSING_H__

#include "ICustomClass.h"
VOLANTE_NAMESPACE_BEGIN

/*
*  IProcessing.h
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
 * Interface for external classes to process (manipulate) the Normalized object.
 * The implementing method can access and modify the fields of the  Normalized object
 * This same interface is used for both pre and post processing.
 *
 * <p>The implementing class,  
 * <ul>
 *     <li> should be public
 *     <li> should have a public default constructor
 *     <li> should be made available to the generated JAR at runtime (by specifying in the manifest classpath)
 *     <li> should be stateless. The class should not maintain call specific data.
 * </ul>
 *
 * As many instances of the implementing class will be created as required. The class 
 * should not expect all calls to be made to one particular instance. 
 *
 */
class VOLANTE_EXPORT IProcessing : public ICustomClass {
public:
    /** 
     * Processes (access/modify) the normalized object. 
     * The implementing method can access and modify the fields of the Normalized object.
     *
     * @param obj The object that should be processed.
     *
     * @see DataObject#getField
     * @see DataObject#setField
     *
     * @exception ValidationException if a field was found to be invalid
     * and it affects further processing.
     */ 
    virtual void process(DataObject* obj) = 0;
};

VOLANTE_NAMESPACE_END

#endif //__IPROCESSING_H__

