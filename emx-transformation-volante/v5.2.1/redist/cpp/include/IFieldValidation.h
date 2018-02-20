#ifndef __IFIELDVALIDATION_H__
#define __IFIELDVALIDATION_H__

#include "ICustomClass.h"
VOLANTE_NAMESPACE_BEGIN
/*
*  IFieldValidation.h
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
* Interface for external classes to validate a field of a Normalized object (internal message)
* or Input/Output Object (external message). The implementing class should check the value of the field and 
* return false if it is not valid.
* <p>The implementing class,  
* <ul>
*     <li> should have public default constructor
*     <li> should be made available during linking as an external library 
*     <li> should be stateless. The class should not maintain call specific data.
*     <li> since you specify the name the class in the Designer you need to call REGISTER_CLASS(validationclass)
*          at the end of your class declaration (in CPP file) to make it available 
*          to the runtime (for dynamic creation).
*
* </ul>
* <p>
* As many instances of the implementing class will be created as required. The class 
* should not expect all calls to be made to one particular instance. 
*
*  <pre>
*   class MyValidation : public IFieldValidation {
*      bool validate(const vstring& fldName, Object* value, DataObject* obj) {
*          // do your validation here
*         IntObject* intVal = polymorphic_cast<IntObject*>(value);
*         return intVal->intValue() > 10 &&  intVal->intValue() < 20;
*      }
*
*   }
*  </pre>
*   REGISTER_CLASS(MyValidation);
*
*/
class VOLANTE_EXPORT IFieldValidation : public ICustomClass {
public:
	/** 
	* Validates a field in the normalized object or input/output object. 
	* The implementing class should check the value and return false 
	* if the value is not valid. If the validation
	* depends on other fields of the object, the validating class can use the
	* <code>obj</code> parameter to access those fields by name.
	*
	*  @param fldName Name of field that should be validated
	*  @param value Value of the field that is validated. If the field is of primitive type
	*   value's type is the corresponding primitive wrapper class. 
	*  @param obj The object whose field is validated. The validator can use this parameter to 
	*        access other fields of the object. This object should be treated as immutable. 
	*         Note that if the field is part of nested section, <code>obj</code> is 
	*         the DataObject that encapsulates the fields in that section (and not the 
	*         root DataObject).
	*
	*  @returns false If the value is not valid.
	*  @throws FieldValidationException If the object is not in a proper state
	*
	*  @see DataObject
	* 
	*/
	virtual bool validate(const vstring& fldName, const Object* value, DataObject* obj) = 0;
};

VOLANTE_NAMESPACE_END

#endif //__IFIELDVALIDATION_H__

