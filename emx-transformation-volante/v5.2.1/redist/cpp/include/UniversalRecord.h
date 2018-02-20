#ifndef __FIXEDLENGTHRECORD_H__
#define __FIXEDLENGTHRECORD_H__
#include "Transform.h"
#include <stack>

VOLANTE_NAMESPACE_BEGIN

/*
*  FixedLengthRecord.java
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

const short SEQUENCE_TYPE = 1;
const short CHOICE_TYPE = 2;
const short ALL_TYPE = 3;
class VOLANTE_EXPORT SequenceInfo {
public:
	void init(short sectionType, short currentFieldIndex, int sequenceStartIndex)	 {
		this->sectionType = sectionType;
		this->currentFieldIndex = currentFieldIndex;
		this->sequenceStartIndex = sequenceStartIndex;
	}
	void onField() {
		if(sectionType == SEQUENCE_TYPE) {
			++currentFieldIndex;
		}
	}
private:
	int sequenceStartIndex;
	short sectionType;
	short currentFieldIndex;
	friend class UniversalRecord;
};

class VOLANTE_EXPORT UniversalRecord : public ObjectRef {
	typedef ArrayList<SequenceInfo> Stack;
private:
	Stack fieldIndexStack;
	bool isTrailingFieldVal;
	bool ignoreTrailingFields;
	vstring delimiter;
	SequenceInfo sequenceInfo;
protected:
	~UniversalRecord() {}
public:
	bool ignoreTrailingDelimiter;
	UniversalRecord(const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter);
	void init(const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter);
	virtual int getSequencePosition() = 0;
	void reset() {
		fieldIndexStack.clear();
		delimiter = EMPTY_STRING;
		this->ignoreTrailingFields = false;
		this->ignoreTrailingDelimiter = false;
		this->isTrailingFieldVal=false;
	}
	virtual SequenceInfo createSequenceState() {
		return SequenceInfo();
	}
	void startSequence()  {
		startSection(SEQUENCE_TYPE);
	}
	void endSequence() {
		endSection(SEQUENCE_TYPE);
	}
	void startChoice()  {
		startSection(CHOICE_TYPE);
	}
	void endChoice() {
		endSection(CHOICE_TYPE);
	}
	void startAll()  {
		startSection(ALL_TYPE);
	}
	void endAll()  {
		endSection(ALL_TYPE);
	}
	void startSection(short sectionType);
	void endSection(short sectionType);
	bool isSequenceCompleted() {
		return fieldIndexStack.size()== 0;
	}
	bool isLastSequence() {
		return fieldIndexStack.size()== 1;
	}

	int getCurrentFieldIndex() {
		return sequenceInfo.currentFieldIndex;
	}
	void setCurrentFieldIndex(int index) {
		sequenceInfo.currentFieldIndex = index;
	}

	int getSequenceStartIndex() {
		return sequenceInfo.sequenceStartIndex;
	}
	void startTrailingFields() {
		isTrailingFieldVal = true;
	}
	bool isTrailingField() {
		return isTrailingFieldVal;
	}
	const vstring& getDelimiter() {
		return delimiter;
	}
	void onField() {
		sequenceInfo.onField();
	}
	void requiredFieldMissing(AbstractDataObject* obj, int index) ;

	// Packed Decimal support
	static int INT_POWERS_OF_10[];
	static dlong LONG_POWERS_OF_10[];
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MIN_UNSIGNED_INT1_VALUE			(int)0
#define MAX_UNSIGNED_INT1_VALUE			(int)0xFF
#define MIN_UNSIGNED_INT2_VALUE			(int)0
#define MAX_UNSIGNED_INT2_VALUE			(int)0xFFFF
#define MIN_UNSIGNED_INT4_VALUE			(int)0
#define MAX_UNSIGNED_INT4_VALUE			LONG_LITERAL(0xFFFFFFFF)
#define MIN_UNSIGNED_INT8_VALUE			LONG_LITERAL(0)
	//static long MAX_UNSIGNED_INT8_VALUE = 0xFFFFFFFFFFFFFFFFL; // wrong

#define MIN_INT1_VALUE		(int)-128
#define MAX_INT1_VALUE		(int)0x7F
#define MIN_INT2_VALUE		(int)-32768
#define MAX_INT2_VALUE		(int)0x7FFF
#define MIN_INT4_VALUE		(int)0x80000000
#define MAX_INT4_VALUE		(int)0x7fffffff
#define MIN_INT8_VALUE		LONG_LITERAL(0x8000000000000000)
#define MAX_INT8_VALUE		LONG_LITERAL(0x7fffffffffffffff)

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DOT_DECIMAL_POINT		'.'
#define COMMA_DECIMAL_POINT		','
#define NO_DECIMAL_POINT 		(char)0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	static float intBitsToFloat(int value) {
		return *((float*)(&value));
	}
	static int floatToIntBits(float value) {
		return *((int*)(&value));
	}
	static double longBitsToDouble(dlong value) {
		return *((double*)(&value));
	}
	static dlong doubleToLongBits(double value) {
		return *((dlong*)(&value));
	}

	static vstringliteral EMPTY_STRING;
};

VOLANTE_NAMESPACE_END

#endif //__FIXEDLENGTHRECORD_H__
