#ifndef __UNIVERSALINPUTPARSER_H__
#define __UNIVERSALINPUTPARSER_H__
#include "Transform.h"
#include <stack>
#include "UniversalInputRecord.h"
#include "MathUtil.h"
#include "FileInputSource.h"
VOLANTE_NAMESPACE_BEGIN

/*
*  UniversalInputParser.java
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
class VOLANTE_EXPORT UniversalInputParser : public InputParser {

	ObjectRefPool<UniversalInputRecord> universalInputRecordPool;
protected:
	UniversalInputParser();
	void assertConstraints(AbstractDataObject* object, int index) ;
	void assertLength(int value, int min, int max) ;
	void assertNotNull(AbstractDataObject* object, int index);
	void assertFieldNew(AbstractDataObject* object, int index) ;
	void checkFillerValue(const vstring& actualValue, const vstring& expectedValue) ;
	void missingChoice(AbstractDataObject* object);
	UniversalInputRecord* createInputRecord(const Binary& bytes) {
		UniversalInputRecord* record = universalInputRecordPool.create();
		record->init(bytes);
		return record;
	}

	UniversalInputRecord* getDelimitedRecord(UniversalInputRecord* parent, const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter) {
		UniversalInputRecord* child = universalInputRecordPool.create();
		//UniversalInputRecord* child = new UniversalInputRecord();
		parent->getDelimitedRecord(child, delimiter, ignoreTrailingFields, ignoreTrailingDelimiter);
		return child;
	}


	bool checkNull(const vstring& value)  {
		return value.length() == 0;
	}
	void handleException(TransformException& e, UniversalInputRecord* record, AbstractDataObject* obj);
protected:
};

VOLANTE_NAMESPACE_END

#endif //__UNIVERSALINPUTPARSER_H__
