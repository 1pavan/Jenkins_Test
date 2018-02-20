#ifndef __BIGINTEGER_H__
#define __BIGINTEGER_H__

#include "m_apm.h"

VOLANTE_NAMESPACE_BEGIN


class VOLANTE_EXPORT  BigInteger {
public:
	BigInteger() : val(0) {
	}
	explicit BigInteger(int value) : val(value) {
	}
	explicit BigInteger(dlong value);
	explicit BigInteger(udlong value);

	explicit BigInteger(const char* value) : val(value) {
	}
	explicit BigInteger(const vstring& value) : val(value.c_str()) {
	}

	friend VOLANTE_EXPORT BigInteger operator + (const BigInteger &a,const BigInteger &b);
	friend VOLANTE_EXPORT BigInteger operator - (const BigInteger &a,const BigInteger &b);

	friend VOLANTE_EXPORT BigInteger operator * (const BigInteger &a,const BigInteger &b);

	friend VOLANTE_EXPORT BigInteger operator / (const BigInteger &a,const BigInteger &b);
	friend VOLANTE_EXPORT BigInteger operator % (const BigInteger &a,const BigInteger &b);
	bool operator==(const BigInteger &m) const;
	bool operator!=(const BigInteger &m) const;
	bool operator < (const BigInteger &m) const;
	bool operator <= (const BigInteger &m) const;
	bool operator > (const BigInteger &m) const;
	bool operator >= (const BigInteger &m) const;

	int toInt() const;
	dlong toLong() const;
	udlong toULong() const;
	double toDouble() const;
	float toFloat() const;
	const char* toString(char* out) const;
	vstring toString() const;
	int sign() const {
		return val.sign();
	}
	BigInteger abs() const;
private:
	BigInteger(const MAPM& val) : val(val) {
	}
	::MAPM val;
	friend class BigDecimal;
};

VOLANTE_NAMESPACE_END

#endif //__BIGINTEGER_H__

