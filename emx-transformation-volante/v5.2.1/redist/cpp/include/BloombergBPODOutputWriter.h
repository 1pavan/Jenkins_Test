#ifndef __BLOOMBERGBPODOUTPUTWRITER_H__
#define __BLOOMBERGBPODOUTPUTWRITER_H__
#include "TransformContext.h"
#include "DataObject.h"
#include "OutputWriter.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  BloombergOutputWriter.h
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
class BloombergBPODOutputWriter : public AbstractSimpleOutputWriter {
protected:
public:
	BloombergBPODOutputWriter() {
	}

	virtual void writeHeader(DataObject* obj, TransformContext& cxt) = 0;

	virtual void writeData(DataObject* obj, TransformContext& cxt)=0;

	virtual void writeTrailer(DataObject* obj, TransformContext& cxt)=0;

	void initMessage() {
	}
	vstring endMessage() {
		return "";
	}

private:    
private:    
	void requiredFieldMissing(AbstractDataObject* object, int index, int tag) {
	}
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





#endif //__BLOOMBERGBPODOUTPUTWRITER_H__
