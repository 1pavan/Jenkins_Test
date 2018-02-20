#ifndef __FIXOUTPUTWRITER_H__
#define __FIXOUTPUTWRITER_H__
#include "TransformContext.h"
#include "DataObject.h"
#include "FIXType.h"
#include "OutputWriter.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  FIXOutputWriter.h
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
class VOLANTE_EXPORT FIXOutputWriter : public AbstractSimpleOutputWriter {
protected:
	char delimiter;
	bool checksum;
	vstringbuffer message;
	vstring scratchBuffer;
public:
	FIXOutputWriter() {
		this->checksum = true;
		delimiter = '\01';
	}
	void setChecksum(bool checksum) {
		this->checksum = checksum;
	}

	virtual void writeHeader(DataObject* obj, TransformContext& cxt) = 0;

	virtual void writeData(DataObject* obj, TransformContext& cxt)=0;

	virtual void writeTrailer(DataObject* obj, TransformContext& cxt)=0;

	void initMessage();
	vstring endMessage();

private:    
	unsigned int generateCheckSum(const char* buffer, unsigned int  length);
	void writeBodyLength();
	void writeCheckSum();
private:    

	vstring tempStr;
	void appendField0(const char* fldName, const vstring& value) {
		message.append(fldName).operator += ('=').append(value).operator += (delimiter);
	}
protected:
	void appendField(const char* fldName, const char* value) {
		if(strlen(value) > 0) {
			message.append(fldName).operator += ('=').append(value).operator += (delimiter);
		}
	}
	void appendField(const char* fldName, const vstring& value) {
		if(value.length() > 0) {
			appendField0(fldName, value);
		}
	}
	void appendField(const char* fldName, int value) {
		intToString(value, tempStr);
		appendField0(fldName, tempStr);
	}
	void appendField(const char* fldName, dlong value) {
		dlongToString(value, tempStr);
		appendField0(fldName, tempStr);
	}

	void appendField(const char* fldName, float value) {
		floatToString(value, tempStr);
		appendField0(fldName, tempStr);
	}

	void appendField(const char* fldName, double value) {
		doubleToString(value, tempStr);
		appendField0(fldName, tempStr);
	}
	void appendField(const char* fldName, bool value) {
		boolToString(value, tempStr);
		appendField0(fldName, tempStr);
	}

	void appendField(const char* fldName, char value) {
		charToString(value, tempStr);
		appendField0(fldName, tempStr);
	}
	/*
	void appendField(const char* fldName, const DateTime& value, vstringbuffer& buffer, vstring format) {
	vstring formattedDate = Parsing::formatDate(value, format);
	appendField(fldName, formattedDate, buffer);
	}*/

	void requiredFieldMissing(AbstractDataObject* object, int index, int tag);
public:
	Object* writeBodyStart()  {
		return NULL;
	}

	Object* writeBodyEnd()  {
		return NULL;
	}

	Object* writeBatchStart() {
		return NULL;
	}

	Object* writeBatchEnd() {
		return NULL;
	}
};

VOLANTE_NAMESPACE_END

#endif //__FIXOUTPUTWRITER_H__

