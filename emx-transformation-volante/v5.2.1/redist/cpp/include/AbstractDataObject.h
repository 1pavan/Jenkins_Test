#ifndef __ABSTRACTDATAOBJECT_H__
#define __ABSTRACTDATAOBJECT_H__
#include "DataObjectBase.h"
#include "BitFieldFlag.h"
/*
*  AbstractDataObject.h
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

VOLANTE_NAMESPACE_BEGIN
//#define USE_BIT_FLAGS


class VOLANTE_EXPORT AbstractDataObject : public DataObjectBase {
protected :
	AbstractDataObject(DataObjectMetaInfo* metaInfo, BIT_FIELD_TYPE* bitFields, DataObjectSection* parentSection = NULL);
	AbstractDataObject(const AbstractDataObject& copyFrom, BIT_FIELD_TYPE* bitFields, DataObjectSection* parentSection = NULL);
private: AbstractDataObject(const AbstractDataObject& copyFrom){
				 }
public:
	DataObjectMetaInfo* getMetaInfo() const  {
		return metaInfo;
	}
public:
	~AbstractDataObject();
	int getFieldCount() const ;
	int getFieldIndex(const vstring& fieldName) const;
	const vstring& getFieldName(int index) const;
	const vstring& getFieldType(int index) const;
	const vstring& getFieldType(const vstring& fieldName) const;

	vstring getQualifiedName(int index) const;

	vstring toString() const;
	Object* getField(const vstring& fieldName) const;

	Object* getField(int index) const;
	bool getField(int index, Object& valueObject)  const;
	void setField(int index, const Object& value);
	void setField(const vstring& fieldName, const Object* value) ;
	void setField(const vstring& fieldName, const Object& value) ;
	void setField(int index, const Object* value);

	/* 
	*	Derived class must override this method and perform initialization(bring the obj to clean state)
	*  after call the super classes' method.
	* The derived class constructor must all call this method
	*/
	virtual void reset();
protected :
	virtual void setField0(int index, const Object* value);

	virtual Object* getField0(int index)  const;
	virtual Object* getField0(int index, Object* value)  const;

	void setAllFieldsToNull();

	void throwNullValueException(int index) const;
public:

	bool isNullValue(int index) const {
		return V_IS_NULL_VALUE(index);
	}
	bool isNull(int index) const;
	bool isNull(const vstring& fieldName) const;
	bool isNotNull(int index) const {
		return V_IS_NOT_NULL_VALUE(index);
	}
	inline void setNullValue(int index)  {
		V_SET_NULL_VALUE(index);
	}
	void setNotNull(int index)  {
		V_SET_NOT_NULL_VALUE(index);
	}

	inline void ensureNotNull(int index)  const {
		if(isNullValue(index)) {
			throwNullValueException(index);
		}
	}
	void assertNotNull(int index) const;
	void setNull(int index)   {
		setNullValue(index);
	}
	void setNull(int index, bool bl);
	void setNull(const vstring& fieldName)  {
		DataObjectBase::setNull(fieldName);
	}

	DataObjectSection* getParentSection() const;
	void setParentSection(DataObjectSection* parentSection);

	DataObject* getRootDataObject() const;

public:
	bool isEmpty() const;


public:
	virtual DataObject* createSectionElement(const vstring& sectionName, DataObjectSection* sec) const;
protected:
	DataObjectSection* parentSection;
	// If a field is non-null the flag will be set	
	V_DECLARE_NULL_FLAG_REF_FIELD(nonNullFields)
	DataObjectMetaInfo* metaInfo;
};

VOLANTE_NAMESPACE_END

#endif //__ABSTRACTDATAOBJECT_H__


