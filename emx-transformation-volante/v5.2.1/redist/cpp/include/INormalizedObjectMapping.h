#ifndef __INORMALIZEDOBJECTMAPPING_H__
#define __INORMALIZEDOBJECTMAPPING_H__

#include "ICustomClass.h"
VOLANTE_NAMESPACE_BEGIN

/*
*  INormalizedObjectMapping.h
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
 * Interface for external classes to map one normalized object(source) to 
 * another Normalized object(destination).
 * The implementing method can access the fields in the source normalized object 
 * and update the fields in the destination Normalized object.
 *
 * <p>The implementing class  
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
class VOLANTE_EXPORT INormalizedObjectMapping : public ICustomClass {
public:
	virtual void map(NormalizedObject* sourceNormalizedObject, NormalizedObject* destinationNormalizedObject, TransformContext& cxt) = 0 ;
};

VOLANTE_NAMESPACE_END

#endif //__INORMALIZEDOBJECTMAPPING_H__
