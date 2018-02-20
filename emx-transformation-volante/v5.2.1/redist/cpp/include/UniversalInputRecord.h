#ifndef __UniversalInputRecord_H__
#define __UniversalInputRecord_H__
#include "Transform.h"
#include <stack>
#include "UniversalRecord.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  UniversalInputRecord.java
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
class VOLANTE_EXPORT UniversalInputRecord : public UniversalRecord {
	// Record range
	int startIndex;
	int endIndex;
	Binary input;
	vstring recordStr;
	const vbyte* bytes;
	// current parse state/position
	int currentIndex;
	int previousIndex;

	UniversalInputRecord* enclosingRecord;
protected:
	~UniversalInputRecord() {}
public:
	UniversalInputRecord();
	//UniversalInputRecord(const Binary& input);
	void init(const Binary& input);
	void reset();
private:
	//UniversalInputRecord(const Binary& input, const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter);    
	//UniversalInputRecord(const vstring& recordStr, const Binary& input, int startIndex, int length, const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter, UniversalInputRecord* enclosingRecord);
	void init(const vstring& recordStr, const Binary& input, int startIndex, int length, const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter, UniversalInputRecord* enclosingRecord);
	void init(const vstring& recordStr, const Binary& input, int startIndex, int length, UniversalInputRecord* enclosingRecord);
public:

	UniversalInputRecord* getEnclosingRecord() {
		return enclosingRecord;
	}
	int getSequencePosition() {
		return currentIndex;
	}

	void onReadField() {
		UniversalRecord::onField();
	}
	void onReadSection() {
		UniversalRecord::onField();
	}

	UniversalInputRecord* getDelimitedRecord(UniversalInputRecord* child, const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter);

	int getCurrentIndex() {
		return currentIndex;
	}

	int getPreviousIndex() {
		return previousIndex;
	}
	vstring getFixedString(int length) {
		onReadField();
		return getString(length);
	}
	vstring getFixedFiller(int length) {
		onReadField();
		return getString(length);
	}
	void skipFixedFiller(int length) {
		onReadField();
		skipString(length);
	}
	std::pair<int, int> getLineOffsetAt(int index);
private:
	vstring getTagString(int length);
	vstring getString(int length);
	void skipString(int length);
public:
	bool isNext(const vstring& str);
	bool isNext(const char* str);
	vstring peekString(int length) {
		return peekString(0, length);
	}
	vstring peekString(int start, int length);
	vstring peekRest();
	static vstring peekString(UniversalInputRecord* obj, int start, int length);
	static vstring peekString(UniversalInputRecord* obj, int length);
	static vstring peekRest(UniversalInputRecord* obj);
	static bool isNext(UniversalInputRecord* obj, const vstring& tag);


	static vstring terminateNullRight(const vstring& str) {
		return terminateRight(str, (char)0);
	}

	static vstring terminateRight(const vstring& str, char c);

	void skipFieldTag(const vstring&  tag);
	void skipFieldTag(const vstring&  tag, const vstring&  separator);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Section Field support
	void skipSectionTag(const vstring& tag);
	void skipSectionTag(const vstring& tag, const vstring& separator);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Choice support

	void skipChoicePadding(int length) {
		skip(length);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Delimited Field support

	vstring getDelimitedField(const vstring& delimiter) {
		return getDelimitedField(delimiter, (char)0);
	}
	vstring getDelimitedField(const vstring& delimiter, bool lastField) {
		return getDelimitedField(delimiter, (char)0, lastField);
	}

	vstring getDelimitedField(const vstring& delimiter, char quoteChar) {
		return getDelimitedField(delimiter, quoteChar, false);
	}
	vstring getDelimitedField(const vstring& delimiter, char quoteChar, bool lastField);
	vstring getDelimitedFiller(const vstring& delimiter) {
		return getDelimitedFiller(delimiter, (char)0, false);
	}
	vstring getDelimitedFiller(const vstring& delimiter, char quoteChar, bool lastField) {
		onReadField();
		return getDelimitedString(delimiter, quoteChar, lastField);
	}

private:
	vstring getDelimitedString(const vstring& delimiter, char quoteChar, bool lastField);
	int findDelimiter(const vstring& delimiter, char quoteChar, int fromIndex, int endIndex);
	bool hasQuote(const vstring& str, char quoteChar);
	vstring removeQuote(const vstring& str, char quoteChar);

public:
	friend class FastDecoder;
	friend class FastEncoder;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Binary support

	bool getBinaryBoolean();
	Binary getBinaryBinary(int length);

	int getBinaryInt(int length, bool signedValue, bool bigEndian);

	dlong getBinaryLong(int length, bool signedValue, bool bigEndian);

	int getBinaryInt1(bool bigEndian, bool signedValue);

	int getBinaryInt2(bool bigEndian, bool signedValue);
	// only signed is supported
	int getBinaryInt4(bool bigEndian);
	dlong getBinaryInt4Unsigned(bool bigEndian);

private:
	int getBinaryInt4Private(bool bigEndian);
	dlong getBinaryLong4Private(bool bigEndian);
public:
	// only signed is supported
	dlong getBinaryInt8(bool bigEndian);

	float getBinaryFloat(bool bigEndian);
	double getBinaryDouble(bool bigEndian);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	double getPackedDecimalDouble(int intDigits, int decimalDigits);
	float getPackedDecimalFloat(int intDigits, int decimalDigits);

	dlong getPackedDecimalLong(int ndigits);

	int getPackedDecimalInt(int ndigits);

private:
	static bool parseSign(int high);

	static int getHighPart(int packedByte) {
		return (packedByte & 0xf0) >> 4;
	}

	static int getLowPart(int packedByte) {
		return (packedByte & 0x0f);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public:
	void skip(int length) ;
	bool isEmpty() {
		return currentIndex ==  endIndex;
	}
	void assertMessageCompleted();
	void assertCompleted();
	void assertCompleted(const vstring& blockName);

	static vstring splitTagValue(const vstring& str, const vstring& tag);
	static vstring splitTagValue(const vstring& str, const vstring& tag, const vstring& separator);


	static vstring trimSpaces(const vstring& str) {
		return trimSpaces(str, true, true);
	}



	static vstring trimSpaces(const vstring& str, bool left, bool right);
private:
	void assertRemaining(int size) {
		if((endIndex - currentIndex) < size) {
			throwASCIITokenizeException("Not enough characters. Required " + intToString(size) + " , available " + intToString(endIndex - currentIndex));
		}
	}

protected:
	void throwASCIITokenizeException(const vstring& message);

};
VOLANTE_NAMESPACE_END

#endif //__UniversalInputRecord_H__
