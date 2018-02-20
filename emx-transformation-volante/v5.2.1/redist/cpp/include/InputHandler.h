#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__
/*
*  InputHandler.h
*
*  © Copyright 2001-2003 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/

/** 
 * Class that runs as part of the command processor, which is responsible for 
 * sending input to transform runtime. 
 *
 * @see com.tplus.transform.runtime.external.Handler
 */
#include "cp.h"
#include "Handler.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT InputHandler : public  Handler {
public:
protected:
	Properties* contextProperties;

public:
	InputHandler();
	void init(Properties& props, CommandProcessorContext& cxt);
protected:

	void setContextProperties(TransformContext& tcxt);
	virtual void processInput(InputSource& source, TransformContext& tcxt, const vstring& inputFormatName);
private:

private:
	vstring lastInputFormatName;
	InputFormat lastInputFormat;
	LookupContext lcxt;
	typedef ObjectMap<InputFormat> InputFormatMap;
	InputFormatMap inputFormats;
};

VOLANTE_NAMESPACE_END

#endif //__INPUTHANDLER_H__


