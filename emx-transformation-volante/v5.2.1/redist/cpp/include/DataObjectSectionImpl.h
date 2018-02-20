#ifndef __DATAOBJECTSECTIONIMPL_H__
#define __DATAOBJECTSECTIONIMPL_H__
#include "AbstractDataObjectSection.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  DataObjectSectionImpl.h
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
* Generic object that encapsulates a data structure. Fields of the data 
* structure can be accessed by name or by index. The index parameter is the 
* 0 based index of field as defined in the transform designer.
* The class also provides metainfo about the data structure. The names
* of the fields can be obtained using the method getFieldName(index).
*
* <pre>
*    for(int i =0; i< obj.getFieldCount(); ++i) {
*     	
*	  }
* </pre>
* 
* The interface provides two ways of accessing the fields, by index and by name.
* Access by index is faster than access by name. In case of repeated access of a field,
* you can convert the fieldname to its index and then access it based on index. 
*
* A concrete implementation of the interface may provide a way to directly access the
* the field. For instance getFirstName() instead of getField("FirstName"). If it is 
* acceptable it is always efficient to cast to the appropriate type and use
* the field directly.
*
* @see DataObject
*/
class VOLANTE_EXPORT DataObjectSectionImpl : public AbstractDataObjectSection {
public:
	typedef std::vector<DataObjectVal> ElementList;
	DataObjectSectionImpl() {
	}
	DataObjectSectionImpl(const DataObjectSectionImpl& right, DataObject* newParent = NULL);
	void copy(const DataObjectSectionImpl& right, DataObject* newParent = NULL);
	~DataObjectSectionImpl();
	DataObject* getElement(int index) const;
	int getElementIndex(DataObject* elm) const;
	bool removeElement(int index);
	void addElement(DataObject* elm) {
		addElement(elm, true);
	}
	void clear();
	void removeLastElement();
	DataObjectSection* clone() const;

protected:
	void deleteAll();

	void addElement(DataObject* elm, bool checkParent);
	int getElementCount() const{
		return (int)elements.size();
	}
	vstring toString() const;
	ElementList elements;
};
VOLANTE_NAMESPACE_END

#endif //__DATAOBJECTSECTIONIMPL_H__

