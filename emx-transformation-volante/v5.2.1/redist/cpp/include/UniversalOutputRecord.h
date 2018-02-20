#ifndef __UniversalOutputRecord_H__
#define __UniversalOutputRecord_H__
#include "Transform.h"
#include <stack>
#include "MathUtil.h"
#include "ByteBuffer.h"
#include "FileInputSource.h"
#include "UniversalRecord.h"
#include "UniversalFieldParser.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  UniversalOutputRecord*.java
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

class VOLANTE_EXPORT UniversalOutputRecord : public UniversalRecord {
#define SPACE_CHAR			' '
	int trailingFieldMarker;
	int lastDelimiterPosition;
	int trailingDelimiterMarker;
	ByteBuffer buffer;
	UniversalOutputRecord* encosingWriter;
	int terminator;
public:
	UniversalOutputRecord();
	vstring toString() const;
public:
	UniversalOutputRecord(UniversalOutputRecord* encosingWriter, const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter) ;
	void init(UniversalOutputRecord* encosingWriter);
	bool isEmpty();

public:
	int getRecordLength() {
		return buffer.length() - getSequenceStartIndex();
	}
protected:
	int getSequencePosition() {
		return buffer.length();
	}

public:
	void endSequence();
	void endAll();
	void endChoice();
	void addSequence(UniversalOutputRecord* sub);
	void endSection0();
public:
	UniversalOutputRecord* getEnclosingRecord() {
		return encosingWriter;
	}

public: UniversalOutputRecord* writeDelimitedRecord(const vstring& delimiter, bool ignoreTrailingFields, bool ignoreTrailingDelimiter);
public:
	const char* getBytes(int& length);

	void onWriteNullSequence();
	void onWriteSequence();
	void onWriteField();
	void onWriteSection();

	void onWriteNullField();
	void onWriteFillerField() ;
	void onWriteDelimiter() {
		lastDelimiterPosition = buffer.length();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Choice support

public:
	void padRecordToLength(int length);

private:
	void writeChoicePadding(int length);

	///////////////////////////////////////////////////////////////////////
	// ASCII FIXED

public:
	void appendASCIIField(const BigInteger& value, int width, bool lpad, char paddingChar);
	void appendASCIIField(int value, int width, bool lpad, char paddingChar);
	void appendASCIIField(dlong value, int width, bool lpad, char paddingChar);
	void appendASCIIField(float value, int numberDigits, int decimalDigits,  char decimalPoint, bool lpad, char paddingChar) ;
	void appendASCIIField(double value, int numberDigits, int decimalDigits, char decimalPoint, bool lpad, char paddingChar);
	void appendASCIIField(float value, int width, char decimalPoint, bool lpad, char paddingChar);

	void appendASCIIField(const BigDecimal& value, int width, int decimalDigits,char decimalPoint, bool lpad, char paddingChar) ;
	void appendASCIIFieldHex(const Binary& value, int width, bool lpad,char paddingChar);
	void appendASCIIFieldBase64(const Binary& value, int width, bool lpad,char paddingChar);


	void appendASCIIField(double value, int width, char decimalPoint, bool lpad, char paddingChar);
	void setTerminator(char terminator) {
		this->terminator = terminator;
	}
	void clearTerminator() {
		this->terminator = -1;
	}
	void appendASCIIField(bool value, int width, const vstring& trueValue, const vstring& falseValue, bool lpad, char paddingChar) ;

	void appendASCIIField(const vstring& value, int width, bool lpad, char paddingChar) ;

	void appendASCIIField(char value, int width, bool lpad,char paddingChar);

public:
	void appendASCIIField(const DateTime& value, int width, const vstring& format);

	void appendASCIINullField(int length);

	void appendFiller(int length);
	void appendFiller(const vstring& defValue);

	void appendTag(const vstring& tag) {
		buffer.append(tag);
	}
	//////////////////////////////////////////////////////////////////
	/// Length preceded fields
	int appendASCIIField(const vstring& value) ;

	int appendASCIIField(int value);

	int appendASCIIField(dlong value);

	int appendASCIIField(float value, int numberDigits, int decimalDigits, char decimalPoint) ;

	int appendASCIIField(double value, int numberDigits, int decimalDigits, char decimalPoint) ;

	int appendASCIIField(double value, char decimalPoint);

	int appendASCIIField(float value, char decimalPoint);

	int appendASCIIField(char value) {
		return appendASCIIField(charToString(value));
	}

	int appendASCIIField(bool value, const vstring& trueValue, const vstring& falseValue)  {
		return appendASCIIField(value ? trueValue : falseValue);
	}

	int appendASCIIField(const DateTime& value, const vstring& format);
	int appendBinaryField(const Binary& value);
	int appendASCIIFieldHex(const Binary& value);
	int appendASCIIFieldBase64(const Binary& value);

	//////////////////////////

	int getASCIIFieldLength(const vstring& value) {
		return (int)value.length();
	}

public: 
	int getASCIIFieldLength(int value) {
		vstring strValue = intToString(value);
		return getASCIIFieldLength(strValue);
	}

	int getASCIIFieldLength(dlong value) {
		vstring strValue = dlongToString(value);
		return getASCIIFieldLength(strValue);
	}

	int getASCIIFieldLength(float value, int numberDigits, int decimalDigits, char decimalPoint) ;

	int getASCIIFieldLength(double value, int numberDigits, int decimalDigits, char decimalPoint) ;

	int getASCIIFieldLength(double value, char decimalPoint);

	int getASCIIFieldLength(float value, char decimalPoint);

	int getASCIIFieldLength(char value) {
		return getASCIIFieldLength(charToString(value));
	}

	int getASCIIFieldLength(bool value, const vstring& trueValue, const vstring& falseValue)  {
		return getASCIIFieldLength(value ? trueValue : falseValue);
	}

	int getASCIIFieldLength(const DateTime& value, const vstring& format);

	int getBinaryFieldLength(const Binary& value);
	int getASCIIFieldLengthHex(const Binary& value);
	int getASCIIFieldLengthBase64(const Binary& value);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	static void appendChar0(int length, char c, ByteBuffer& buffer);

	static void appendFillerSpace(int length, ByteBuffer& buffer) {
		appendPaddingChar(length, SPACE_CHAR, buffer);
	}

	static void appendEmptyFieldSpace(int length, ByteBuffer& buffer) {
		appendPaddingChar(length, SPACE_CHAR, buffer);
	}

	static void appendPaddingChar(int length, char paddingChar, ByteBuffer& buffer) {
		if(length > 0) {
			appendChar0(length, paddingChar, buffer);
		}
	}
	static void appendPaddedLong(dlong value, bool negative, int width, bool lpad, char paddingChar, ByteBuffer& buffer) ;

	static void appendPaddedInt(int value, bool negative,int width,  bool lpad, char paddingChar, ByteBuffer& buffer);

	static void appendDoubleValue(double value, int numberDigits, int decimalDigits, char decimalPoint, bool lpad, char paddingChar, ByteBuffer& buffer);

	static void appendDoubleValue(double value, int width,  char decimalPoint, bool lpad, char paddingChar, ByteBuffer& buffer) ;
	/////////////
	static vstring getDoubleValue(double value, int numberDigits, int decimalDigits, char decimalPoint, bool lpad, char paddingChar);

	static void padLong(dlong value, bool negative, int width, bool lpad, char paddingChar, vstringbuffer& buffer) ;

	static void appendPaddingChar(int length, char paddingChar, vstringbuffer& buffer) {
		appendChar0(length, paddingChar, buffer);
	}

	void appendPaddedBigInt(const BigInteger& value, bool negative, int width,  bool lpad, char paddingChar, ByteBuffer& buffer);
	void appendBigDecimalValue(const BigDecimal& value, int width,  char decimalPoint, bool lpad, char paddingChar, ByteBuffer& buffer);

	static void appendChar0(int length, char c, vstringbuffer& buffer);
	/////////////////////    
	static void appendString(const vstring& value, int width, bool lpad, char paddingChar, int terminator, ByteBuffer& buffer) ;
	static void appendTerminator( ByteBuffer& buffer, int terminator);
public:	
	void appendSectionTag(const vstring& tag) {
		buffer.append(tag);
	}
	void appendSectionTag(const vstring& tag, const vstring& separator) {
		buffer.append(tag);
		buffer.append(separator);
	}
private:
	void appendDelimiter(const vstring& delimiter);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Delimited
public: 
	void appendDelimitedFieldHex(const Binary& value, const vstring&  delimiter);
	void appendDelimitedFieldBase64(const Binary&  value, const vstring& delimiter);

	void appendDelimitedFiller(const vstring& delimiter);
	void appendDelimitedFiller(const vstring& value, const vstring& delimiter);

	void appendDelimitedNullField(const vstring& delimiter);

	void appendDelimitedField(const vstring& value, const vstring& delimiter);
	void appendDelimitedField(const vstring& value, const vstring& delimiter, char quoteChar);

	void appendDelimitedField(int value, const vstring& delimiter);

	void appendDelimitedField(dlong value, const vstring& delimiter);
	void appendDelimitedField(float value, int numberDigits, int decimalDigits, char decimalPoint, const vstring& delimiter, char paddingChar) ;
	void appendDelimitedField(float value,  char decimalPoint, const vstring& delimiter);

	void appendDelimitedField(double value, int numberDigits, int decimalDigits, char decimalPoint, const vstring& delimiter, char paddingChar) ;
	void appendDelimitedField(double value,  char decimalPoint, const vstring& delimiter);

	void appendDelimitedField(char value, const vstring& delimiter);

	void appendDelimitedField(bool value, const vstring& delimiter, const vstring& trueValue, const vstring& falseValue) ;
	void appendDelimitedField(const BigDecimal& value, const vstring& delimiter) ;
	void appendDelimitedField(const BigInteger& value, const vstring& delimiter) ;

	void appendDelimitedField(const DateTime& value, const vstring& format, const vstring& delimiter);
	void appendDelimitedASCIIFieldHex(const Binary& value, const vstring&  delimiter);
	void appendDelimitedASCIIFieldASCII(const Binary&  value, const vstring&  delimiter);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Binary 

public:
	void writeBinaryInt(int length, int value,  bool signedValue, bool bigEndian) ;
	void assertRangeInt(int value, int start, int end) ;
	void assertRangeLong(dlong value, dlong start, dlong end);

	void writeBinaryLong(int length, dlong value,  bool signedValue, bool bigEndian) ;

	void writeBinaryBoolean(bool value) ;
	void writeBinaryBinary(const Binary& bytes);
	void writeBinaryBinary(const Binary& bytes, int length);

	void writeBinaryInt1(int value) ;

	void writeBinaryInt2(int value, bool bigEndian) ;

	void writeBinaryInt4(int value, bool bigEndian)  ;

	void writeBinaryInt8(dlong value, bool bigEndian)  ;
	void writeBinaryFloat(float value, bool bigEndian) ;

	void writeBinaryDouble(double value, bool bigEndian);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Packed Decimal

	void writePackedDecimalInt(int value, int ndigits);
	void writePackedDecimalLong(dlong value, int ndigits);
	void writePackedDecimalDouble(double value, int intDigits, int decimalDigits) ;

	void writePackedDecimalFloat(float value, int intDigits, int decimalDigits) ;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
VOLANTE_NAMESPACE_END

#endif //__UniversalOutputRecord_H__
