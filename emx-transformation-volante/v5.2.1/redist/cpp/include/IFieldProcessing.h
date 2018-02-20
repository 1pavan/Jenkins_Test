#ifndef __IFIELDPROCESSING_H__
#define __IFIELDPROCESSING_H__

#include "ICustomClass.h"
VOLANTE_NAMESPACE_BEGIN
/*
*  IFieldProcessing.h
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
 * Interface for external classes to set the value of a field in Normalized object (internal message).
 * The implementing method should return the fields value (or NULL). This value will
 * be set as field's value by the runtime. The name of the implementing class is typically
 * set as field processing class for one of the fields in the NormalizedObject. This 
 * interface applies to both pre and post processing.
 *
 * <p>The implementing class,  
 * <ul>
 *     <li> should have public default constructor
 *     <li> should be made available during linking as an external library 
 *     <li> should be stateless. The class should not maintain call specific data.
 *     <li> since you specify the name the class in the Designer you need to call REGISTER_CLASS(validationclass)
 *          at the end of your class declaration (in CPP file) to make it available 
 *          to the runtime (for dynamic creation).
 * </ul>
 *
 * As many instances of the implementing class will be created as required. The class 
 * should not expect all calls to be made to one particular instance. 
 *
  *  <pre>
 *   class MyProcessing : public IFieldProcessing {
 *		Object* processField(const vstring& fldName, DataObject* obj) {
 *          // do your processing here
 *          // set the name of the field as its value
 *         return new StringObject(fldName);
 *      }
 *
 *   }
 *  </pre>
 *   REGISTER_CLASS(MyProcessing);
*/
class VOLANTE_EXPORT IFieldProcessing : public ICustomClass {
public:
    /** 
     * Returns the value of a field in the Normalized Object.
     * The implementing method should return the value of the 
     * field or a FieldValidationException in case of error. If the field's
     * value depends on other fields of the object, the processing class can use the
     * obj parameter to access those fields by name.
     *
     *  @param fldName Name of field whose value will be set.
     *  @param obj The object whose field is validated. The validator can use this parameter to 
     *         access other fields of the object. This object should be treated as immutable.
     *         Note that if the field is part of nested section, <code>obj</code> is 
     *         the DataObject that encapsulates the fields in that section (and not the 
     *         root DataObject).
     *
     *  @return Value of the field. If the field is of primitive type
     *   object returned should be an instance of the corresponding primitive wrapper class. 
     *
     *  @exception FieldValidationException if a field used during processing is not valid
     *   and it affects further processing.
     *
     *  @see DataObject
     *  @see NormalizedObject
     * 
     */
	virtual Object* processField(const vstring& fldName, DataObject* obj) = 0;
};

VOLANTE_NAMESPACE_END

#endif //__IFIELDPROCESSING_H__

