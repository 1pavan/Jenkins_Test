#ifndef __OUTPUTHANDLER_H__
#define __OUTPUTHANDLER_H__
/*
* OutputHandler.h
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
#include "Object.h"
#include "Transform.h"
#include "Handler.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT OutputHandler : public Handler {
	vstring deviceName;
public:


	OutputHandler();

	virtual OutputDevice* createDevice(DeviceInfo& info) = 0;

	void init(Properties& props, CommandProcessorContext& cxt) ;

	void start() ;
	void stop();
private:
	LookupContext getLookupContext();
};

VOLANTE_NAMESPACE_END

#endif //__OUTPUTHANDLER_H__

