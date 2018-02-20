#ifndef __PARSING_H__
#define __PARSING_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT Parsing {
public:
	static vstring TRUE_VALUE;
	static vstring FALSE_VALUE;
	static vstring EMPTY;
	static DateTime parseDate(const vstring& arg, const vstring& pattern);
	static vstring formatDate(const DateTime& date, const vstring& pattern);
	static void formatDate(const DateTime& date, const vstring& pattern, vstring& out);

	static double parseDouble(const vstring& arg);

	static int parseInt(const vstring& arg) ;
	static dlong parseLong(const vstring& arg);
	static bool parseBool(const vstring& arg);

	static float parseFloat(const vstring& arg);
	static char parseChar(const vstring& arg);
	static BigInteger parseBigInteger(const vstring& arg);
	static BigDecimal parseBigDecimal(const vstring& arg);
	static Binary parseBinary(const vstring& arg);

	static vstring stringValue(StringObject* str);
	static DateTime dateValue(DateObject* date);
	static int intValue(NumberObject* number);
	static dlong longValue(NumberObject* number);
	static double doubleValue(NumberObject* number);
	static float floatValue(NumberObject* number);
	static char charValue(CharObject* charVal);
	static bool boolValue(BoolObject* boolVal);
	static BigInteger bigIntegerValue(BigIntegerObject* boolVal);
	static BigDecimal bigDecimalValue(BigDecimalObject* boolVal);
	static Binary binaryValue(BinaryObject* boolVal);



	static vstring stringValueWithNull(StringObject* str);
	static DateTime dateValueWithNull(DateObject* date);
	static int intValueWithNull(NumberObject* number);
	static dlong longValueWithNull(NumberObject* number);
	static double doubleValueWithNull(NumberObject* number);
	static float floatValueWithNull(NumberObject* number);
	static char charValueWithNull(CharObject* charVal);
	static bool boolValueWithNull(BoolObject* boolVal);
	static BigInteger bigIntegerValueWithNull(BigIntegerObject* bigVal);
	static BigDecimal bigDecimalValueWithNull(BigDecimalObject* bigVal);
	static Binary binaryValueWithNull(BinaryObject* boolVal);

	inline static bool isNumericalDigit(char c) {
		return c >= '0' && c <= '9';
	}

	static vstring intToString(int val)  {
		return VOLANTE_NAMESPACE::intToString(val);
	}
	static vstring longToString(dlong val)  {
		return VOLANTE_NAMESPACE::dlongToString(val);
	}
	static vstring doubleToString(double val)  {
		return VOLANTE_NAMESPACE::doubleToString(val);
	}
	static vstring floatToString(float val)  {
		return VOLANTE_NAMESPACE::floatToString(val);
	}
	static vstring boolToString(bool val)  {
		return val ? TRUE_VALUE : FALSE_VALUE;
	}
	static vstring charToString(char val)  {
		return VOLANTE_NAMESPACE::charToString(val);
	}
	static vstring dateToString(const DateTime& val)  {
		return val.toString(vstring("MMM dd, yyyy"));
	}
	static vstring stringToString(const vstring& val)  {
		return val;
	}
	static vstring bigIntegerToString(const BigInteger& val)  {
		return val.toString();
	}
	static vstring bigDecimalToString(const BigDecimal& val)  {
		return val.toString();
	}
	static vstring binaryToString(const Binary& val)  {
		return val.toString();
	}
	static vstring runtimeObjectToString(Object* obj, const vstring& type);
	static Object* toRuntimeObject(const vstring& value, const vstring& type);
	static vstring readUTF(std::istream& in);
	static void writeUTF(std::ostream& out, const vstring& str);
	static vstring binaryToBase64String(const Binary& binary);

	static Binary base64StringToBinary(const vstring& str);

	static vstring binaryToHexString(const Binary& binary);

	static Binary hexStringToBinary(const vstring& str);

	static Object* toBinaryTypeObject(Object* obj);
	static Object* toRawMessageTypeObject(Object* obj);
};

VOLANTE_NAMESPACE_END

#endif //__PARSING_H__

