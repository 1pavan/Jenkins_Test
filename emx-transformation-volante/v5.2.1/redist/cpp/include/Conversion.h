#ifndef __CONVERSION_H__
#define __CONVERSION_H__
///////////////////////////////////////////////////////////////////////////////
VOLANTE_NAMESPACE_BEGIN

vstring VOLANTE_EXPORT charToString(char value);
void VOLANTE_EXPORT charToString(char value, vstring& str);
int VOLANTE_EXPORT charToString(char value, char* buffer);

vstring VOLANTE_EXPORT intToString(int value);
void VOLANTE_EXPORT intToString(int value, char* buffer);
void VOLANTE_EXPORT intToString(int value, vstring& str);

vstring VOLANTE_EXPORT dlongToString(dlong value);
void VOLANTE_EXPORT dlongToString(dlong value, vstring& str);
void VOLANTE_EXPORT dlongToString(dlong value, char* buffer);

vstring VOLANTE_EXPORT udlongToString(udlong value);
void VOLANTE_EXPORT udlongToString(udlong value, vstring& str);
void VOLANTE_EXPORT udlongToString(udlong value, char* buffer);

vstring VOLANTE_EXPORT floatToString(float value);
void VOLANTE_EXPORT floatToString(float value, vstring& str);
void VOLANTE_EXPORT floatToString(float value, char* buffer);

vstring VOLANTE_EXPORT doubleToString(double value);
void VOLANTE_EXPORT doubleToString(double value, vstring& str);
void VOLANTE_EXPORT doubleToString(double value, char* buffer);

void VOLANTE_EXPORT boolToString(bool value, vstring& str);
vstring VOLANTE_EXPORT boolToString(bool value);
int VOLANTE_EXPORT boolToString(bool value, char* buffer);


vstring VOLANTE_EXPORT bigIntegerToString(const BigInteger& value);
void VOLANTE_EXPORT bigIntegerToString(const BigInteger& value, vstring& str);
vstring VOLANTE_EXPORT bigDecimalToString(const BigDecimal& value);
void VOLANTE_EXPORT bigDecimalToString(const BigDecimal& value, vstring& str) ;

vstring VOLANTE_EXPORT binaryToString(const Binary& value);
vstring VOLANTE_EXPORT dateTimeToString(const DateTime& value);

///////////////////////////////////////////////////////////////////////////////
bool isIdentifierStart(char c);
bool isIdentifierPart(char c);
///////////////////////////////////////////////////////////////////////////////
void VOLANTE_EXPORT v_itoa(int val, char *buf);
void VOLANTE_EXPORT v_ltoa(dlong val, char *buf);

int VOLANTE_EXPORT v_atoi(const char *nptr, const char *eptr);
dlong VOLANTE_EXPORT v_atol(const char *nptr, const char *eptr);

inline int v_atoi(const vstring& str)  {
	return v_atoi(str.data(), str.data() + str.length());
}
inline int v_atoi(const vstring& str, int start, int length)  {
	return v_atoi(str.data() + start, str.data() + length);
}

inline dlong v_atol(const vstring& str)  {
	return v_atol(str.data(), str.data() + str.length());
}

///////////////////////////////////////////////////////////////////////////////

inline void intToString(int value, char* buffer) {
	v_itoa(value, buffer);
}

inline vstring intToString(int value) {
#ifdef VOLANTE_USE_STD_STRING
	char buffer[25];
	intToString(value, buffer);
	return buffer;
#else 
	vstring str;
	str.assign(value);
	return str;
#endif
}

inline void intToString(int value, vstring& str) {
#ifdef VOLANTE_USE_STD_STRING
	str = intToString(value);
#else 
	str.assign(value);
#endif
}

inline void doubleToString(double value, vstring& str) {
#ifdef VOLANTE_USE_STD_STRING
	str = doubleToString(value);
#else 
	str.assign(value);
#endif
}
inline void charToString(char value, vstring& str) {
#ifdef VOLANTE_USE_STD_STRING
	str = charToString(value);
#else 
	str.assign(value);
#endif
}
//////////////////////////////////////////////////

inline vstring valueToString(int val) {
	return intToString(val);
}
inline vstring valueToString(dlong val) {
	return dlongToString(val);
}
inline vstring valueToString(float val) {
	return floatToString(val);
}
inline vstring valueToString(double val) {
	return doubleToString(val);
}
inline vstring valueToString(const vstring& val) {
	return val;
}

inline vstring valueToString(const DateTime& val) {
	return dateTimeToString(val);
}
inline vstring valueToString(const Binary& val) {
	return binaryToString(val);
}
inline vstring valueToString(const BigInteger& val) {
	return bigIntegerToString(val);
}
inline vstring valueToString(const BigDecimal& val) {
	return bigDecimalToString(val);
}

inline vstring valueToString(char val) {
	return charToString(val);
}

VOLANTE_NAMESPACE_END

#endif //__CONVERSION_H__
