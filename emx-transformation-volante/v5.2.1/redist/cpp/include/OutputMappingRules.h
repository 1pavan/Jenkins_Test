#ifndef __OUTPUTMAPPINGRULES_H__
#define __OUTPUTMAPPINGRULES_H__
#include "DataObject.h"
#include "TransformContext.h"
#include "MappingRules.h"
#include "IOutputMapping.h"
#include "CustomClassSupport.h"


VOLANTE_NAMESPACE_BEGIN

/*
*  OutputMappingRules.h
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
class VOLANTE_EXPORT OutputMappingRules : public MappingRules {
public:
    void mapFields(NormalizedObject* normalizedObj, ExternalObject* externalObject , TransformContext& cxt) {
        mapHeaderFields(normalizedObj, externalObject->getHeader(), cxt);
        mapDataFields(normalizedObj, externalObject->getData(), cxt);
        mapTrailerFields(normalizedObj, externalObject->getData(), externalObject->getTrailer(), cxt);
    }

	void mapHeaderFields(NormalizedObject* normalizedObj, DataObject* header, TransformContext& cxt);
	void mapDataFields(NormalizedObject* normalizedObj, DataObject* data, TransformContext& cxt);
	void mapTrailerFields(NormalizedObject* normalizedObj, DataObject* data, DataObject* trailer, TransformContext& cxt);


   virtual void mapHeaderFields0(NormalizedObject* normalizedObj, DataObject* header, TransformContext& cxt);
	virtual void mapDataFields0(NormalizedObject* normalizedObj, DataObject* data, TransformContext& cxt) = 0;
	virtual void mapTrailerFields0(NormalizedObject* normalizedObj, DataObject* trailer, TransformContext& cxt);
private:
	IOutputMapping* getCustomMappingClass() ;
protected:
	vstring customMappingClassName;
private:
	SmartPtr<IOutputMapping> customMapping;
};

VOLANTE_NAMESPACE_END

#endif //__OUTPUTMAPPINGRULES_H__

