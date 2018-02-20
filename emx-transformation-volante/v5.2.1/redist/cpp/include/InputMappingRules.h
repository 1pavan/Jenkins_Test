#ifndef __INPUTMAPPINGRULES_H__
#define __INPUTMAPPINGRULES_H__
#include "DataObject.h"
#include "TransformContext.h"
#include "ExternalObject.h"
#include "MappingRules.h"
#include "IInputMapping.h"
#include "IExternalMapping.h"
#include "CustomClassSupport.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  InputMappingRules.h
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




class VOLANTE_EXPORT InputMappingRules : public MappingRules {
public:
	InputMappingRules() {
	}
	//protected final DisposableCache $disposableCache = new DisposableCache();
	void mapFields(ExternalObject* inputObj, NormalizedObject* normalizedObj, TransformContext& cxt);
protected:
	virtual void mapFields0(ExternalObject* inputObj, NormalizedObject* normalizedObj, TransformContext& cxt) = 0;

private:
	IInputMapping* getCustomMappingClass();
protected:
	vstring customMappingClassName;
private:
	SmartPtr<IInputMapping> customMapping;

};

class VOLANTE_EXPORT ExternalToExternalMappingRules : public MappingRules {
public:
	void mapFields(ExternalObject* inputObj, ExternalObject* outputObj, TransformContext& cxt);
protected:
	virtual void mapHeaderFields0(ExternalObject* inputObj, DataObject* outputObject, TransformContext& cxt) =0;
	virtual void mapDataFields0(ExternalObject* inputObj, DataObject* outputObject, TransformContext& cxt) =0;
	virtual void mapTrailerFields0(ExternalObject* inputObj, DataObject* outputObject, TransformContext& cxt) =0;
private:
	IExternalMapping* getCustomMappingClass();
protected:
	vstring customMappingClassName;
private:
	SmartPtr<IExternalMapping> customMapping;
};


VOLANTE_NAMESPACE_END

#endif //__INPUTMAPPINGRULES_H__

