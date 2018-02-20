#ifndef __PROCESSINGRULES_H__
#define __PROCESSINGRULES_H__
#include "DataObject.h"
#include "TransformContext.h"
#include "IFieldValidation.h"
#include "IFieldProcessing.h"
#include "IProcessing.h"
#include "CustomClassSupport.h"
#include "AbstractValidationRules.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  ProcessingRules.h
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
class VOLANTE_EXPORT ProcessingRules : public AbstractValidationRules {
public:
	ProcessingRules();
	void process(NormalizedObject* inputObj, TransformContext& cxt);
	virtual void process0(NormalizedObject* inputObj, TransformContext& cxt);

	void preprocess(NormalizedObject* nObj, TransformContext& cxt) ;
	void postprocess(NormalizedObject* nObj, TransformContext& cxt);
	void validate(NormalizedObject* nObj, TransformContext& cxt);
	void checkNotNull(NormalizedObject* nObj, TransformContext& cxt);
	void setExceptionHandler(ExceptionHandler* exceptionHandler) {
		this->exceptionHandler = exceptionHandler;
	}

protected:
	virtual void preprocess(NormalizedObject* nObj) ;
	virtual void postprocess(NormalizedObject* nObj);
	virtual void validate(NormalizedObject* nObj);
	virtual void checkNotNull(NormalizedObject* nObj);
	Object* customFieldProcessing(const vstring& customClass, const vstring& fldName, NormalizedObject* obj);

protected:
	//bool customValidation(const vstring& customClass, Object* value, const vstring& fldName, NormalizedObject* obj);
	//CustomClassSupport<IFieldValidation> fieldValidationSupport;
	CustomClassSupport<IFieldProcessing> fieldProcessingSupport;
	ExceptionHandler*  exceptionHandler;
	typedef std::auto_ptr<IProcessing> Processing;
};



class VOLANTE_EXPORT BusinessProcessingRules : public AbstractValidationRules {
public:
	BusinessProcessingRules();
	void process(NormalizedObject* inputObj, TransformContext& cxt);
	virtual void process0(NormalizedObject* inputObj, TransformContext& cxt);
	void setExceptionHandler(ExceptionHandler* exceptionHandler) {
		this->exceptionHandler = exceptionHandler;
	}

protected:
	virtual void process(NormalizedObject* nObj) ;
	Object* customFieldProcessing(const vstring& customClass, const vstring& fldName, NormalizedObject* obj);

protected:
	CustomClassSupport<IFieldProcessing> fieldProcessingSupport;
	ExceptionHandler*  exceptionHandler;
	typedef std::auto_ptr<IProcessing> Processing;
};

VOLANTE_NAMESPACE_END

#endif //__PROCESSINGRULES_H__

