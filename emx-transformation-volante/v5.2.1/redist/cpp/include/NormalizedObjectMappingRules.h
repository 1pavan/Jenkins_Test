#ifndef __NORMALIZEDOBJECTMAPPINGRULES_H__
#define __NORMALIZEDOBJECTMAPPINGRULES_H__

#include "DataObject.h"
#include "TransformContext.h"
#include "MappingRules.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  NormalizedObjectMappingRules.h
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
class VOLANTE_EXPORT NormalizedObjectMappingRules : public MappingRules {
public:
	void mapFields(NormalizedObject* sourceNormalizedObject, NormalizedObject* destinationNormalizedObject, TransformContext& cxt);
protected:
	virtual void mapFields0(NormalizedObject* sourceNormalizedObject, NormalizedObject* destinationNormalizedObject, TransformContext& cxt) = 0;
private:
	INormalizedObjectMapping* getCustomMappingClass();

protected:
	vstring customMappingClassName;
private:
	SmartPtr<INormalizedObjectMapping> customMapping;
};

VOLANTE_NAMESPACE_END

#endif //__NORMALIZEDOBJECTMAPPINGRULES_H__
