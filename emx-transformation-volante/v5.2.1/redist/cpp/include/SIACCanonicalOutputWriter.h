#ifndef __SIACCanonicalOUTPUTWRITER_H__
#define __SIACCanonicalOUTPUTWRITER_H__
#include "TransformContext.h"
#include "Exceptions.h"
#include "DataObject.h"
#include "SIACCanonicalType.h"
#include "OutputWriter.h"
#include "SIACCanonicalException.h"

/*
*  SIACCanonical.h
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

#define  CFT_EndInstance_TAG    26999
#define  CFT_EndInstance_TAG_STR    "26999"
#define  CFT_EndGroup_TAG 		26000
#define  CFT_EndGroup_TAG_STR  	"26000"
#define  GROUP_START_STR			 "{"
#define  GROUP_END_STR			 "}"
#define  GROUP_INSTANCE_STR			 " "

class VOLANTE_EXPORT SIACCanonicalOutputWriter : public AbstractSimpleOutputWriter {
protected:
	char delimiter;
	bool checksum;
	vstringbuffer message;
public:
	SIACCanonicalOutputWriter() {
		this->checksum = true;
		delimiter = '\01';
		message.reserve(1000);
	}
	void setChecksum(bool checksum) {
		this->checksum = checksum;
	}
	virtual void writeHeader(DataObject* obj, TransformContext& cxt) = 0;
	virtual void writeData(DataObject* obj, TransformContext& cxt)=0;
	virtual void writeTrailer(DataObject* obj, TransformContext& cxt)=0;

	unsigned int generateCheckSum(const char* buffer, unsigned int  length);

	void initMessage();
	vstring endMessage();
protected:    
	vstring scratchBuffer;

private:    
	vstring tempStr;
	void appendField0(const char* fldName, const vstring& value) {
		message.append(fldName).operator += ('=').append(value).operator += (delimiter);
	}
	void writeCheckSumIndicator();
	void writeBodyLength();
	void writeCheckSum();
protected:
	void appendField(const char* fldName, const char* value) {
		size_t length = strlen(value);
		if( length> 0) {
			message.append(fldName).operator += ('=').append(value, length).operator += (delimiter);
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

  void appendBeginGroup(const char* fldName) {
			appendField0(fldName, GROUP_START_STR);
  }
  void appendEndGroup() {
			appendField0(CFT_EndGroup_TAG_STR, GROUP_END_STR);
  }
  void appendEndGroupInstance() {
			appendField0(CFT_EndInstance_TAG_STR, GROUP_INSTANCE_STR);
  }

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


#endif //__SIACCanonicalOUTPUTWRITER_H__
