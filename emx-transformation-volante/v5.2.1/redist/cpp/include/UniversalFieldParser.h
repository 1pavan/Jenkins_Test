#ifndef __UniversalFieldParser_H__
#define __UniversalFieldParser_H__
#include "Transform.h"

/*
*  UniversalFieldParser.java
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

class VOLANTE_EXPORT UniversalFieldParser {
    
public:
	static bool parseBoolean(const vstring& str, const vstring& trueValue, const vstring& falseValue);
    
private:
	static vstring fixDecimal(const vstring& str, char decimalDigit);
    
public:
	static float parseFloat(const vstring& str, char decimalDigit);
    
    static double parseDouble(const vstring& str, char decimalDigit);
    
    static float parseFloat(const vstring& str, int numberDigits, int decimalDigits, char decimalDigit) ;
    
    static double parseDouble(const vstring& str, int numberDigits, int decimalDigits, char decimalDigit) ;
    
    static double parseImpliedDouble(const vstring& str, int numberDigits, int decimalDigits) ;
    
    static vstring formatbool(bool value, const vstring& trueValue, const vstring& falseValue);
};

VOLANTE_NAMESPACE_END

#endif //__UniversalFieldParser_H__

