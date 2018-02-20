#ifndef __ABSTRACTDATAOBJECTSECTION_H__
#define __ABSTRACTDATAOBJECTSECTION_H__
#include "DataObjectBase.h"
/*
*  AbstractDataObjectSection.h
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

class VOLANTE_EXPORT AbstractDataObjectSection :  public DataObjectSection {
protected:
public:
	AbstractDataObjectSection();
	AbstractDataObjectSection(DataObject* parent, const vstring& sectionName, int minOccurs, int maxOccurs);
	void initialize(DataObject* parent, const vstring& sectionName, int minOccurs, int maxOccurs);
	void reset();

	DataObject* getParent() const;

	vstring getSectionName() const;

	DataObject* createElement() ;

	vstring getName() const;

	vstring getQualifiedName() const ;

	DataObject* getRootDataObject() const;

	void assertConstraints() const ;

	int getMinOccurs() const {
		return minOccurs;
	}
	int getMaxOccurs() const {
		return maxOccurs;
	}
	vstring toXMLString() const;
	vstring toXMLString(int indent) const ;
	vstring toXMLString(const vstring& sectionElementXMLName, int indent) const ;
	bool isEmpty()const ;
protected:
	void throwElementIndexOutOfBounds(int index, int size) const;

private:
	int minOccurs;
	int maxOccurs;
	DataObject* parent;
	vstring sectionName;
};
VOLANTE_NAMESPACE_END

#endif //__ABSTRACTDATAOBJECTSECTION_H__


