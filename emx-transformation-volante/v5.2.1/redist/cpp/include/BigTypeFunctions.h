#ifndef __BIGTYPEFUNCTIONS_H__
#define __BIGTYPEFUNCTIONS_H__
/*
*
*  © Copyright 2001-2004 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT  BigTypeFunctions {
public:    
	static bool greater(const BigInteger&v1, const BigInteger&v2) {
		return v1 > v2;
	}

	static bool less(const BigInteger&v1, const BigInteger&v2) {
		return v1 < v2;
	}

	static bool equal(const BigInteger&v1, const BigInteger&v2) {
		return v1 == v2;
	}

	static bool notEqual(const BigInteger&v1, const BigInteger&v2) {
		return !equal(v1, v2);
	}

	static BigInteger plus(const BigInteger&v1, const BigInteger&v2) {
		return v1 + v2;
	}

	static BigInteger minus(const BigInteger&v1, const BigInteger&v2) {
		return v1 - v2;
	}

	static BigInteger multiply(const BigInteger&v1, const BigInteger&v2) {
		return v1 * v2;
	}
	static BigInteger divide(const BigInteger&v1, const BigInteger&v2) {
		return v1 /v2 ;
	}

	static BigInteger divideInteger(const BigInteger&v1, const BigInteger&v2) {
		return v1 /v2 ;
	}

	static BigInteger remainder(const BigInteger&v1, const BigInteger&v2) {
		return v1 % v2;
	}
	///////////////////////////////////
	//Big Decimal 

	static bool greater(const BigDecimal&v1, const BigDecimal&v2) {
		return v1 > v2;
	}

	static bool less(const BigDecimal&v1, const BigDecimal&v2) {
		return v1 < v2;
	}

	static bool equal(const BigDecimal&v1, const BigDecimal&v2) {
		return v1 == v2;
	}

	static bool notEqual(const BigDecimal& v1, const BigDecimal&v2) {
		return !equal(v1, v2);
	}
	static  BigDecimal plus(const BigDecimal&v1, const BigDecimal&v2) {
		return v1 + v2;
	}

	static  BigDecimal minus(const BigDecimal&v1, const BigDecimal&v2) {
		return v1 - v2;
	}

	static  BigDecimal multiply(const BigDecimal&v1, const BigDecimal&v2) {
		return v1 * v2;
	}

	static  BigDecimal divide(const BigDecimal&v1, const BigDecimal&v2) {
		return v1/ v2;
	}
	static BigDecimal remainder(const BigDecimal& v1, const BigDecimal& v2) {
		return v1 % v2;
	}
};

VOLANTE_NAMESPACE_END

#endif //__BIGTYPEFUNCTIONS_H__

