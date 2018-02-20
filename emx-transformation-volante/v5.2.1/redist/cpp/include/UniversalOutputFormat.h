#ifndef __UNIVERSALOUTPUTFORMAT_H__
#define __UNIVERSALOUTPUTFORMAT_H__
#include "Transform.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  UniversalOutputFormat.java
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
class VOLANTE_EXPORT UniversalOutputFormat : public AbstractOutputFormat {
protected:
	vstring getFormatSuffix() {
		return "asc";
	}
};
VOLANTE_NAMESPACE_END

#endif //__UNIVERSALOUTPUTFORMAT_H__
