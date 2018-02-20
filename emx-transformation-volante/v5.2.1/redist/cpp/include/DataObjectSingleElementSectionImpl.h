#ifndef __DATAOBJECTSINGLEELEMENTSECTIONIMPL_H__
#define __DATAOBJECTSINGLEELEMENTSECTIONIMPL_H__
/*
*  DataObjectSingleElementSectionImpl.java
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

class VOLANTE_EXPORT DataObjectSingleElementSectionImpl : public  AbstractDataObjectSection {
public:
	DataObjectSingleElementSectionImpl(const DataObjectSingleElementSectionImpl& copy, DataObject* newParent);
	void copy(const DataObjectSingleElementSectionImpl& right, DataObject* newParent);

	DataObjectSingleElementSectionImpl() {
		this->element = NULL;
	}
	~DataObjectSingleElementSectionImpl() {
		//delete element;
	}

	int getElementIndex(DataObject* elm) const;

	bool removeElement(int index) ;
	void addElement(DataObject* elm);
	int getElementCount() const {
		return element.get() != NULL ? 1 : 0;
	}
	DataObject* getElement(int index)  const;

	void clear();
	void removeLastElement();
	DataObjectSection* clone() const;

private:
	DataObjectVal element;
};

VOLANTE_NAMESPACE_END

#endif //__DATAOBJECTSINGLEELEMENTSECTIONIMPL_H__
