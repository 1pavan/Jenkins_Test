#ifndef __IEXTERNALMAPPING_H__
#define __IEXTERNALMAPPING_H__

#include "ICustomClass.h"
VOLANTE_NAMESPACE_BEGIN

/*
*  IInputMapping.h
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
 * Interface for external classes to map the input object to the Normalized object.
 * The implementing method can access the fields in the input object and update the fields 
 * in the  Normalized object
 *
 * <p>The implementing class,  
 * <ul>
 *     <li> should be public
 *     <li> should have a public default constructor
 *     <li> should be made available during linking as an external library 
 *     <li> should be stateless. The class should not maintain call specific data.
 *     <li> since you specify the name the class in the Designer you need to call REGISTER_CLASS(mappingclass)
 *          at the end of your class declaration (in CPP file) to make it available 
 *          to the runtime (for dynamic creation).
 *     <li> should be stateless. The class should not maintain call specific data.
 * </ul>
 * </p>
 * As many instances of the implementing class will be created as required. The class 
 * should not expect all calls to be made to one particular instance. 
 *
 */
 class VOLANTE_EXPORT IExternalMapping : public ICustomClass {
 public:

    /** 
     * Maps the input object to normalized object. 
     * The implementing method can access the fields of the input object 
     * and modify the fields of the Normalized object.
     * 
     * Note that custom-mapping class is called after applying the mappings
     * specified in the designer.
     *
     *
     * @param input The input object that need to be mapped to the normalized object. This comprises header, data and trailer.
     * @param nf    The Normalized object.
     * @param cxt   The context in which transformation occurs.
     *
     * @see DataObject#getField
     * @see DataObject#setField
     *
     * @exception ValidationException if a field was found to be invalid and it affects further processing.
     */
    virtual void map(ExternalObject* input, ExternalObject* output, TransformContext& cxt) = 0;
};

VOLANTE_NAMESPACE_END




#endif //__IEXTERNALMAPPING_H__
