#ifndef __SIACCANONICALSIACOUTPUTWRITER_H__
#define __SIACCANONICALSIACOUTPUTWRITER_H__
#include "TransformContext.h"
#include "Exceptions.h"
#include "DataObject.h"
#include "SIACCanonicalType.h"
#include "OutputWriter.h"
#include "SIACCanonicalException.h"
#include "SIACWriterWrapper.h"

/*
*  SIACCanonicalSIACOutputWriter.h
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

class SIACCanonicalSIACOutputWriter : public AbstractSimpleOutputWriter {
	//Class not exported, completely inlined - Bug 1145 
protected:
	bool checksum;
	SIACWriterWrapper siacWrapper;
	vstring scratchBuffer;
public:
	SIACCanonicalSIACOutputWriter() {
		this->checksum = true;
	}
	void setChecksum(bool checksum) {
		this->checksum = checksum;
		siacWrapper.setChecksum(checksum);
	}
	virtual void writeHeader(DataObject* obj, TransformContext& cxt) = 0;
	virtual void writeData(DataObject* obj, TransformContext& cxt)=0;
	virtual void writeTrailer(DataObject* obj, TransformContext& cxt)=0;

	void initMessage() {
		siacWrapper.initMessage();
	}
	vstring endMessage() {
		return siacWrapper.endMessage();
	}
	void requiredFieldMissing(AbstractDataObject* object, int index, int tag) {
		vstring fldName = object->getFieldName(index);
		THROW_EXCEPTION(SIACCanonicalWriterException (fldName + " is a mandatory field. Tag '" + fldName + "[" + intToString(tag) + "]" + "' cannot be null."));
	}

public:
};


VOLANTE_NAMESPACE_END




#endif //__SIACCANONICALSIACOUTPUTWRITER_H__

