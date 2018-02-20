#ifndef __NORMALIZEDOBJECTVALIDATIONRULES_H__
#define __NORMALIZEDOBJECTVALIDATIONRULES_H__

VOLANTE_NAMESPACE_BEGIN

/*
*  NormalizedObjectValidationRules.h
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
class VOLANTE_EXPORT NormalizedObjectValidationRules {
public:
	void validate(NormalizedObject* obj) {
       validate0(obj);
    }
protected:
	virtual void validate0(NormalizedObject* obj) = 0;
protected:
	bool customValidation(const vstring& customClass, Object* value, const vstring& fldName, DataObject* obj);
	CustomClassSupport<IFieldValidation> fieldValidationSupport;

	void throwFieldInvalid(const vstring& validationName, const vstring& fieldName)  {
        THROW_EXCEPTION(FieldValidationException("Validation '" + validationName + "' failed. Field '" + fieldName + "' is not valid", fieldName));
	}
};

VOLANTE_NAMESPACE_END

#endif //__NORMALIZEDOBJECTVALIDATIONRULES_H__
