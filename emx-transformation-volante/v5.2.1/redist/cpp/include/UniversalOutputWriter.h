#ifndef __UNIVERSALOUTPUTWRITER_H__
#define __UNIVERSALOUTPUTWRITER_H__
#include "Transform.h"
#include <stack>
#include "MathUtil.h"
#include "FileInputSource.h"
#include "UniversalOutputRecord.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  UniversalOutputWriter.java
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
class VOLANTE_EXPORT UniversalOutputWriter : public AbstractSimpleOutputWriter {

	vstringbuffer message;

protected:
	UniversalOutputWriter();
	void initMessage();
	vstring endMessage();
	void appendMessage(const char* bytes, int length);
	void handleException(TransformException& e, UniversalOutputRecord* out, AbstractDataObject* obj);

	void assertLength(int value, int min, int max) ;
	// onlyone should be false if a filler is present
	// returns true if a filler has to be written
	bool ensureChoice(AbstractDataObject* obj, bool onlyone) ;
	void requiredFieldMissing(AbstractDataObject* obj, int index);
protected:
};
VOLANTE_NAMESPACE_END

#endif //__UNIVERSALOUTPUTWRITER_H__
