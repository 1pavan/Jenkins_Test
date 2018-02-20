#ifndef __DATAOBJECTBASE_H__
#define __DATAOBJECTBASE_H__
#include "DataObject.h"
#include "DataObjectCollection.h"
#include "DataObjectSection.h"
#include "DataObjectMetaInfo.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  DataObjectBase.h
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
class VOLANTE_EXPORT DataObjectBase : public DataObject {
protected:
public:

	DataObjectSection* getSection(const vstring& secName)  const;

	DataObjectSection* getSection(int index)  const;

	ObjectVal getFieldVal(const vstring& fieldName)  const;
	ObjectVal getFieldVal(int index)  const;
	ObjectVal getFieldCheckNullVal(int index) const;
	Object* getField(const vstring& fieldName)  const;
	bool getField(const vstring& fieldName, Object& valueObject)  const;
	void setField(int index, const Object& value);
	void setField(const vstring& fieldName, const Object& value);
	void setField(const vstring& fieldName, const Object* value);

	bool isNull(const vstring& fieldName) const;
	void setNull(const vstring& fieldName);
	virtual void setNull(int index)  = 0;
	virtual const vstring& getFieldType(int index) const = 0;
	const vstring& getFieldType(const vstring& fieldName) const;

	virtual vstring getRootXMLTag() const ;

	virtual vstring toXMLString() const;
	virtual vstring toXMLString(int indent) const;

	void setField(const vstring& fieldName, const vstring& value) {
			setField(fieldName, StringObject(value)); 
	}
	void setField(int fieldIndex, const vstring& value) {
			setField(fieldIndex, StringObject(value)); 
	}
	bool getField(int fieldIndex, vstring& value) {
		  StringObject wrapper;
			if(getField(fieldIndex, wrapper)) { 
				value = wrapper.getString();
				return true;
			}
			return false;
	}


	const vstring& getMangledName(const vstring& fieldName) const ;
	const vstring& getMangledName(int fieldIndex) const ;
	virtual vstring toString() const;

	virtual Object* getField(int index) const  = 0;
	virtual bool getField(int index, Object& valueObject)  const = 0;
	virtual void setField(int index, const Object* value) = 0;
	virtual int getFieldIndex(const vstring& fieldName) const  = 0;
	virtual const vstring& getFieldName(int index) const = 0;
	virtual int getFieldCount() const = 0;
	virtual bool isNull(int index) const  = 0;
	Object* getFieldCheckNull(int index) const;
	virtual DataObject* createSectionElement(const vstring& sectionName, DataObjectSection* sec) const;
	void read(std::istream& in);
	void write(std::ostream& out) const;
	static void copy(const DataObject* src, DataObject* dest);
protected:
	virtual vstring toXMLStringImpl(int indent) const ;

};


VOLANTE_NAMESPACE_END

#endif //__DATAOBJECTBASE_H__

