#ifndef __BITFIELDFLAG_H__
#define __BITFIELDFLAG_H__
/*
*  BitFieldFlag.h
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
//#define USE_BIT_FLAGS

#ifdef USE_BIT_FLAGS
typedef unsigned long BIT_FIELD_TYPE ;
const int V_INT_BIT_LENGTH = sizeof(BIT_FIELD_TYPE) * 8;
#define V_BIT_ARRAY_SIZE(nFields) (nFields + V_INT_BIT_LENGTH  -1)/V_INT_BIT_LENGTH
#define v_bitshift(by)  ((BIT_FIELD_TYPE)1 << by)

// External macros
#define V_DECLARE_NULL_FLAG_FIELD(nullFieldVar, nFields)  BIT_FIELD_TYPE nullFieldVar[ V_BIT_ARRAY_SIZE(nFields) ];
#define V_DECLARE_NULL_FLAG_REF_FIELD(nonNullFieldsVar)  BIT_FIELD_TYPE* nonNullFieldsVar;
#define V_IS_NULL_VALUE(index) ((nonNullFields[index/V_INT_BIT_LENGTH ] & (v_bitshift(index%V_INT_BIT_LENGTH ))) == 0)
#define V_IS_NOT_NULL_VALUE(index) (nonNullFields[index/V_INT_BIT_LENGTH ] & (v_bitshift(index%V_INT_BIT_LENGTH ))) != 0
#define V_SET_NULL_VALUE(index) nonNullFields[index/V_INT_BIT_LENGTH ] &= ~(v_bitshift(index%V_INT_BIT_LENGTH))
#define V_SET_NOT_NULL_VALUE(index) nonNullFields[index/V_INT_BIT_LENGTH ] |= (v_bitshift(index%V_INT_BIT_LENGTH))
#define V_SET_ALL_NULL(nFields)  	\
	int bitLength = (nFields + V_INT_BIT_LENGTH  -1)/V_INT_BIT_LENGTH ; \
	for(int i =0; i<bitLength;++i) { \
		nonNullFields[i]= (BIT_FIELD_TYPE)0; \
	}

#else 
typedef bool BIT_FIELD_TYPE;

// External macros
#define V_DECLARE_NULL_FLAG_FIELD(nullFieldVar, nFields)  BIT_FIELD_TYPE nullFieldVar[nFields]
#define V_DECLARE_NULL_FLAG_REF_FIELD(nonNullFieldsVar)  BIT_FIELD_TYPE* nonNullFieldsVar;
#define V_IS_NULL_VALUE(index) (!nonNullFields[index])
#define V_IS_NOT_NULL_VALUE(index) (nonNullFields[index])
#define V_SET_NULL_VALUE(index) nonNullFields[index] = false
#define V_SET_NOT_NULL_VALUE(index) nonNullFields[index]=true
#define V_SET_ALL_NULL(nFields)  	\
	for(int i =0; i<nFields;++i) { \
		nonNullFields[i]= false; \
	}
#endif


VOLANTE_NAMESPACE_END





#endif //__BITFIELDFLAG_H__
