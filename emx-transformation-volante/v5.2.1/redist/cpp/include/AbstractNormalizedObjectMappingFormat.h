#ifndef __ABSTRACTNORMALIZEDOBJECTMAPPINGFORMAT_H__
#define __ABSTRACTNORMALIZEDOBJECTMAPPINGFORMAT_H__
/*
*  AbstractNormalizedObjectMappingFormat.h
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

#include "Transform.h"

class VOLANTE_EXPORT AbstractNormalizedObjectMappingFormat : public INormalizedObjectMappingFormat {

private:
	LookupContext lcxt;
	vstring sourceInternalMessageName;
	vstring destinationInternalMessageName;


protected:
	LookupContext getLookupContext();
	AbstractNormalizedObjectMappingFormat(const vstring& sourceInternalMessageName, const vstring& destinationInternalMessageName) : sourceInternalMessageName (sourceInternalMessageName), destinationInternalMessageName (destinationInternalMessageName) {
	}

public:

	virtual NormalizedObject* map(NormalizedObject* sourceNormalizedObject, TransformContext& tcxt)  = 0;
	NormalizedObject** map(NormalizedObject** sourceNormalizedObject, int length, TransformContext& tcxt);
	vstring getDestinationMessageName() {
		return destinationInternalMessageName;
	}
	vstring getSourceMessageName()  {
		return sourceInternalMessageName;		
	}

};

VOLANTE_NAMESPACE_END

#endif //__ABSTRACTNORMALIZEDOBJECTMAPPINGFORMAT_H__
