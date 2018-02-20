#ifndef __BIGDECIMAL_H__
#define __BIGDECIMAL_H__


VOLANTE_NAMESPACE_BEGIN

#include "m_apm.h"

class VOLANTE_EXPORT  BigDecimal {
public:
	explicit BigDecimal() : val(0) {
	}
	explicit BigDecimal(int value) : val(value) {
	}
	explicit BigDecimal(dlong value);
	explicit BigDecimal(float value) : val(value) {
	}
	explicit BigDecimal(double value) : val(value) {
	}

	explicit BigDecimal(const char* value) : val(value) {
	}

	explicit BigDecimal(const vstring& value) : val(value.c_str()) {
	}

	BigDecimal(const BigInteger& value);

	friend VOLANTE_EXPORT BigDecimal operator + (const BigDecimal &a,const BigDecimal &b);
	friend VOLANTE_EXPORT BigDecimal operator - (const BigDecimal &a,const BigDecimal &b);

	friend VOLANTE_EXPORT BigDecimal operator * (const BigDecimal &a,const BigDecimal &b);

	friend VOLANTE_EXPORT BigDecimal operator / (const BigDecimal &a,const BigDecimal &b);

	friend VOLANTE_EXPORT BigDecimal operator % (const BigDecimal &a,const BigDecimal &b);
	bool operator==(const BigDecimal &m) const;
	bool operator!=(const BigDecimal &m) const;
	bool operator < (const BigDecimal &m) const;
	bool operator <= (const BigDecimal &m) const;
	bool operator > (const BigDecimal &m) const;
	bool operator >= (const BigDecimal &m) const;

	int toInt() const;
	dlong toLong() const;
	double toDouble() const;
	float toFloat() const;

	const char* toString(char* out) const;
	vstring toString() const;
	int sign() const {
		return val.sign();
	}


private:
	BigDecimal(const MAPM& val) : val(val) {
	}
	::MAPM val;
};
VOLANTE_EXPORT BigDecimal operator + (const BigDecimal &a,const BigDecimal &b);
VOLANTE_EXPORT BigDecimal operator - (const BigDecimal &a,const BigDecimal &b);
VOLANTE_EXPORT BigDecimal operator * (const BigDecimal &a,const BigDecimal &b);
VOLANTE_EXPORT BigDecimal operator / (const BigDecimal &a,const BigDecimal &b);
VOLANTE_EXPORT BigDecimal operator % (const BigDecimal &a,const BigDecimal &b);

VOLANTE_NAMESPACE_END

#endif //__BIGDECIMAL_H__
