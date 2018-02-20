#ifndef __FILEINPUTHANDLER_H__
#define __FILEINPUTHANDLER_H__
/*
*  FileInputHandler.h
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
#include "cp.h"
#include "Transform.h"
#include "InputHandler.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT FileInputHandler : public InputHandler {
public:
	static vstring INPUT_DIRECTORY;
	static int SLEEP_TIME;
protected:
	vstring inputDir;
	vstring inputFormatName;
	vstring outputFormatName;
	vstring outputDeviceName;
	vstring processedDir;
	vstring specifiedInputDir;
public:
	bool stopFlag;
public:
	FileInputHandler();
	void init(Properties& props, CommandProcessorContext& cxt);

public:
	void start();

public:
	void stop();

	void processInputDirectory();
	void writeError(const vstring& sourceFile, TransformException* e);

	protected:
		virtual void processFile(const vstring& fileName, TransformContext& tcxt) ;
		virtual void processFile(InputSource& source, TransformContext& tcxt);


};
VOLANTE_NAMESPACE_END

#endif //__FILEINPUTHANDLER_H__

