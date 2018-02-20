#ifndef __COMMANPROCESSORCONTEXT_H__
#define __COMMANPROCESSORCONTEXT_H__
#include "cp.h"
/*
*  CommandProcessorContext.cpp
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
VOLANTE_NAMESPACE_BEGIN

class Handler;
class VOLANTE_CP_EXPORT CommandProcessorContext {
public:
	virtual Handler* getHandler(const vstring& name) = 0;
};

VOLANTE_NAMESPACE_END

#endif //__COMMANPROCESSORCONTEXT_H__
