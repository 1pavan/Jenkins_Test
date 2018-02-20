#ifndef __ABSTRACTOUTPUTFORMAT_H__
#define __ABSTRACTOUTPUTFORMAT_H__

#include "OutputFormat.h"
#include "ExternalObject.h"
#include "OutputMappingRules.h"
#include "FieldsValidationRules.h"
#include "OutputWriter.h"
#include "LookupContextFactory.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  AbstractOutputFormat.h
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
class VOLANTE_EXPORT AbstractOutputFormat : public IOutputFormat {
protected:
	LookupContext lcxt;
public: 
	AbstractOutputFormat();
	void setOutputDevice(OutputDevice* device);
	void write(NormalizedObject* no, TransformContext& tcxt);
protected:
    virtual DataObject* createRecordData();
    virtual DataObject* createHeader();
    virtual DataObject* createTrailer();
    virtual void mapData(NormalizedObject* no, DataObject* recordData, TransformContext& cxt);
    virtual void mapHeader(NormalizedObject* no, DataObject* header, TransformContext& cxt);
    virtual void mapTrailer(NormalizedObject* no, DataObject* recordData, DataObject* trailer, TransformContext& cxt);
	virtual OutputWriter* getOutputWriter()  = 0;
	SimpleOutputWriter* getSimpleOutputWriter();
	vstring writeOutput(ExternalObject& output, TransformContext& cxt);
private:
	OutputDevice* device;
};
VOLANTE_NAMESPACE_END

#endif //__ABSTRACTOUTPUTFORMAT_H__


