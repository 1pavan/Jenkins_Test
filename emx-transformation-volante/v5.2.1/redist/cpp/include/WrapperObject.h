#ifndef __WRAPPEROBJECT_H__
#define __WRAPPEROBJECT_H__

#include "DateTime.h"
#include "BigInteger.h"
#include "BigDecimal.h"
#include "Binary.h"
#include "DesignerTypes.h"

VOLANTE_NAMESPACE_BEGIN
/**
*  An object wrapper for C++ primitive types.
*
*  <table border="1">
*  <thead><tr><td>Designer Type</td><td>C++ Type</td><td>Wrapper Object</td></tr></thead>
*  <tr><td>BigDecimal</td><td>{@link BigDecimal}</td><td>{@link BigDecimalObject}</td></tr>
*  <tr><td>BigInteger</td><td>{@link BigInteger}</td><td>{@link BigIntegerObject}</td></tr>
*  <tr><td>Binary</td>    <td>{@link Binary}</td>    <td>{@link BinaryObject}</td></tr>
*  <tr><td>Boolean</td>    <td>bool</td>    <td>{@link BoolObject}</td></tr>
*  <tr><td>Character</dt>    <td>char</td>    <td>{@link CharObject}</td></tr>
*  <tr><td>DateOnly</td>   <td>{@link DateTime}</td><td>{@link DateObject}</td></tr>
*  <tr><td>DateTime</td>   <td>{@link DateTime}</td><td>{@link DateObject}</td></tr>
*  <tr><td>Double</td>   <td>double</td><td>{@link DoubleObject}</td></tr>
*  <tr><td>Float</td>   <td>float</td><td>{@link FloatObject}</td></tr>
*  <tr><td>ISODate</td>   <td>{@link ISODateTime}</td><td>{@link ISODateObject}</td></tr>
*  <tr><td>ISODateTime</td><td>{@link ISODateTime}</td><td>{@link ISODateObject}</td></tr>
*  <tr><td>ISOTime</td><td>{@link ISODateTime}</td><td>{@link ISODateObject}</td></tr>
*  <tr><td>Integer</td><td>int</td><td>{@link IntObject}</td></tr>
*  <tr><td>Long</td><td>{@link dlong}</td><td>{@link LongObject}</td></tr>
*  <tr><td>String</td><td>{@link vstring}</td><td>{@link StringObject}</td></tr>
*  <tr><td>TimeOnly</td>   <td>{@link DateTime}</td><td>{@link DateObject}</td></tr>
*  </table>
*/
class VOLANTE_EXPORT WrapperObject : public Object {
};

class VOLANTE_EXPORT NumberObject : public WrapperObject {
public:
 	virtual int getInt() const =0  ;
	virtual dlong getLong()const =0  ;
	virtual double getDouble() const= 0  ;
	virtual float getFloat() const = 0  ;
	int intValue() const {
		return getInt();
	}
	dlong longValue()const {
		return getLong();
	}
	double doubleValue() const {
		return getDouble();
	}
	float floatValue() const {
		return getFloat();
	}

};
///////////////////////////////////////////////////////////////////////////////

/**
* The IntObject class wraps a value of the primitive type <code>int</code>
* in an object. An object of type <code>IntObject</code> contains a
* single field whose type is <code>int</code>.
*/
class VOLANTE_EXPORT IntObject : public NumberObject {
public:
	IntObject() {
		val = 0;
	}
	IntObject(int val);
	int getValue() const {
		return val;
	}
	int getInt() const ;
	dlong getLong() const ;
	double getDouble() const ;
	float getFloat()const;

	void setInt(int value);
	void setLong(dlong value);
	void setDouble(double value);
	void setFloat(float value);
	void setObject(const Object* obj) {
		val = obj->getInt();
	}

	vstring toString() const ;
	virtual Object* clone() const;
	const vstring& getObjectType() const {
		return DesignerTypes::INT_TYPE;
	}
private:
	int val;
};
///////////////////////////////////////////////////////////////////////////////

/**
* The LongObject class wraps a value of the primitive type <code>long (int64)</code>
* in an object. An object of type <code>LongObject</code> contains a
* single field whose type is <code>dlong</code>.
*/
class VOLANTE_EXPORT LongObject : public NumberObject{
public:
	LongObject() {
		val = 0;
	}
	LongObject(dlong val);
	dlong getValue() const {
		return val;
	}
	int getInt()const ;
	dlong getLong()const ;
	double getDouble()const ;
	float getFloat()const ;
	void setInt(int value);
	void setLong(dlong value);
	void setDouble(double value);
	void setFloat(float value);
	void setObject(const Object* obj) {
		val = obj->getLong();
	}

	vstring toString() const;
	Object* clone() const;
	const vstring& getObjectType() const {
		return DesignerTypes::LONG_TYPE;
	}
private:
	dlong val;
};
///////////////////////////////////////////////////////////////////////////////

/**
* The DoubleObject class wraps a value of the primitive type <code>double (double precision)</code>
* in an object. An object of type <code>DoubleObject</code> contains a
* single field whose type is <code>double</code>.
*/
class VOLANTE_EXPORT DoubleObject : public NumberObject{
public:
	DoubleObject() {
		val = 0;
	}
	DoubleObject(double val);
	double getValue() const {
		return val;
	}
	int getInt()const ;
	dlong getLong()const ;
	double getDouble()const ;
	float getFloat()const ;
	void setInt(int value);
	void setLong(dlong value);
	void setDouble(double value);
	void setFloat(float value);
	void setObject(const Object* obj) {
		val = obj->getDouble();
	}

	vstring toString() const;
	virtual Object* clone() const;
	const vstring& getObjectType() const {
		return DesignerTypes::DOUBLE_TYPE;
	}
private:
	double val;
};

///////////////////////////////////////////////////////////////////////////////
/**
* The FloatObject class wraps a value of the primitive type <code>float (single precision)</code>
* in an object. An object of type <code>FloatObject</code> contains a
* single field whose type is <code>float</code>.
*/
class VOLANTE_EXPORT FloatObject : public NumberObject{
public:
	FloatObject() {
		val = 0;
	}
	FloatObject(float val);
	float getValue() const {
		return val;
	}
	int getInt()const ;
	dlong getLong()const ;
	double getDouble()const ;
	float getFloat()const ;
	void setInt(int value);
	void setLong(dlong value);
	void setDouble(double value);
	void setFloat(float value);
	void setObject(const Object* obj) {
		val = obj->getFloat();
	}

	vstring toString() const;
	virtual Object* clone() const;
	const vstring& getObjectType() const {
		return DesignerTypes::FLOAT_TYPE;
	}
private:
	float val;
};
///////////////////////////////////////////////////////////////////////////////

/**
* Represents a string. The StringObject class wraps a value of the value type <code>vstring</code>
* in an object. 
* @see vstring
*/
class VOLANTE_EXPORT StringObject : public WrapperObject {
public:
	StringObject() {
	}
	StringObject(const vstring& value);
	const vstring& getValue() const;
	vstring getString() const {
			return value;
	}
	void setString(const vstring& value)  {
			this->value = value;
	}
	void setObject(const Object* obj) {
		value = obj->getString();
	}
	vstring toString() const;
	virtual Object* clone() const;
	const vstring& getObjectType() const {
		return DesignerTypes::STRING_TYPE;
	}
private:
	vstring value;
};
///////////////////////////////////////////////////////////////////////////////

/**
* The DateObject class wraps a value of the value type <code>DateTime</code>
* in an object. 
* @see DateTime
*/
class VOLANTE_EXPORT DateObject : public WrapperObject {
public:
	DateObject() {
	}
	DateObject(const DateTime& value);
	const DateTime& getValue() const ;
	vstring toString() const;
	virtual Object* clone() const;
	const vstring& getObjectType() const {
		return DesignerTypes::DATE_TIME_TYPE;
	}
	void setDate(const DateTime& value)  {
			this->value = value;
	}
	void setObject(const Object* obj) {
		value = obj->getDate();
	}

	DateTime getDate() const {
			return value;
	}
private:
	DateTime value;
};
///////////////////////////////////////////////////////////////////////////////
/**
* The DateObject class wraps a value of the value type <code>DateTime</code>
* in an object. 
* @see DateTime
*/
class VOLANTE_EXPORT ISODateObject : public WrapperObject {
public:
	ISODateObject() {
	}
	ISODateObject(const ISODateTime& value);
	const ISODateTime& getValue() const ;
	vstring toString() const;
	virtual Object* clone() const;
	virtual const vstring& getObjectType() const {
		return DesignerTypes::ISO_DATE_TIME_TYPE;
	}
	ISODateTime getISODate() const {
			return value;
	}
	void setObject(const Object* obj) {
		value = obj->getISODate();
	}
	void setISODate(const ISODateTime& value)  {
			this->value = value;
	}
private:
	ISODateTime value;
};
///////////////////////////////////////////////////////////////////////////////

/**
* The CharObject class wraps a value of the primitive type <code>char</code>
* in an object. An object of type <code>CharObject</code> contains a
* single field whose type is <code>char</code>.
*/
class VOLANTE_EXPORT CharObject : public WrapperObject {
public:
	CharObject() {
		value = 0;
	}
	CharObject(char value);
	char getValue() const {
		return value;
	}
	char charValue()const ;
	vstring toString() const;
	virtual Object* clone() const;
	const vstring& getObjectType() const {
		return DesignerTypes::CHAR_TYPE;
	}
	void setObject(const Object* obj) {
		value = obj->getCharacter();
	}
	char getCharacter() const {
			return value;
	}
	void setCharacter(char value)  {
			this->value = value;
	}

private:
	char value;
};
///////////////////////////////////////////////////////////////////////////////

/**
* The BoolObject class wraps a value of the primitive type <code>bool</code>
* in an object. An object of type <code>BoolObject</code> contains a
* single field whose type is <code>bool</code>.
*/
class VOLANTE_EXPORT BoolObject : public WrapperObject {
public:
	BoolObject() {
		value = false;
	}
	BoolObject(bool value);
	bool getValue() const {
		return value;
	}
	bool boolValue()const ;
	vstring toString() const;
	virtual Object* clone() const ;
	const vstring& getObjectType() const {
		return DesignerTypes::BOOLEAN_TYPE;
	}
	bool getBoolean() const {
			return value;
	}
	void setObject(const Object* obj) {
		value = obj->getBoolean();
	}
	void setBoolean(bool value)  {
			this->value = value;
	}

private:
	bool value;
};
///////////////////////////////////////////////////////////////////////////////


/**
* The BigIntegerObject class wraps a value of the primitive type <code>BigInteger</code>
* in an object. An object of type <code>BigIntegerObject</code> contains a
* single field whose type is <code>BigInteger</code>.
* @see BigInteger
*/
class VOLANTE_EXPORT BigIntegerObject : public WrapperObject {
public:
	BigIntegerObject() {
	}
	BigIntegerObject(const BigInteger& value);
	const BigInteger& getValue() const {
		return value;
	}
	const BigInteger& bigIntegerValue()const ;
	vstring toString() const;
	virtual Object* clone() const ;
	const vstring& getObjectType() const {
		return DesignerTypes::BIG_INTEGER_TYPE;
	}
	BigInteger getBigInteger() const {
			return value;
	}
	void setBigInteger(const BigInteger& value)  {
			this->value = value;
	}
	void setObject(const Object* obj) {
		value = obj->getBigInteger();
	}

private:
	BigInteger value;
};

///////////////////////////////////////////////////////////////////////////////


/**
* The BigDecimalObject class wraps a value of the primitive type <code>BigInteger</code>
* in an object. An object of type <code>BigDecimalObject</code> contains a
* single field whose type is <code>BigDecimal</code>.
* @see BigDecimal
*/
class VOLANTE_EXPORT BigDecimalObject : public WrapperObject {
public:
	BigDecimalObject() {
	}
	BigDecimalObject(const BigDecimal& value);
	const BigDecimal& getValue() const {
		return value;
	}
	const BigDecimal& bigDecimalValue()const ;
	vstring toString() const;
	virtual Object* clone() const ;
	const vstring& getObjectType() const {
		return DesignerTypes::BIG_DECIMAL_TYPE;
	}
	BigDecimal getBigDecimal() const {
			return value;
	}
	void setBigDecimal(const BigDecimal& value)  {
			this->value = value;
	}
	void setObject(const Object* obj) {
		value = obj->getBigDecimal();
	}

private:
	BigDecimal value;
};


/**
* The BinaryObject class wraps a value of the primitive type <code>Binary</code>
* in an object. An object of type <code>BinaryObject</code> contains a
* single field whose type is <code>Binary</code>.
* @see Binary
*/
class VOLANTE_EXPORT BinaryObject : public WrapperObject {
public:
	BinaryObject() {
	}
	BinaryObject(const Binary& value);
	const Binary& getValue() const {
		return value;
	}
	vstring toString() const;
	virtual Object* clone() const ;
	const vstring& getObjectType() const {
		return DesignerTypes::BINARY_TYPE;
	}
	Binary getBinary() const {
			return value;
	}
	void setBinary(const Binary& value)  {
			this->value = value;
	}
	void setObject(const Object* obj) {
		value = obj->getBinary();
	}

private:
	Binary value;
};

///////////////////////////////////////////////////////////////////////////////


class DataObjectSection;
/**
* The SectionObject acts as wrapper for DataObjectSection. 
* @see DataObject#getSection
*/
class VOLANTE_EXPORT SectionObject : public WrapperObject {
public:
	SectionObject() {
		section = NULL;
		own = false;
	}
	SectionObject(DataObjectSection& section);
	~SectionObject();
	SectionObject(const DataObjectSection& section);
	SectionObject(DataObjectSection* section, bool own = false);
	DataObjectSection* getSection() const ;
	void setSection(DataObjectSection* sec);
	void setSection(DataObjectSection& section);
	void setSection(const DataObjectSection& section);
	vstring toString() const;
	virtual Object* clone() const;
	const vstring& getObjectType() const {
		return DesignerTypes::SECTION_TYPE;
	}
	void setObject(const Object* obj);

private:
	DataObjectSection* section;
	bool own;
};

class VOLANTE_EXPORT Wrapper {
public:
	static Object* box(bool v) {
		return new BoolObject(v);
	}
	static Object* box(int v) {
		return new IntObject(v);
	}
	static Object* box(dlong v) {
		return new LongObject(v);
	}
	static Object* box(float v) {
		return new FloatObject(v);
	}
	static Object* box(double v) {
		return new DoubleObject(v);
	}
	static Object* box(const DateTime& v) {
		return new DateObject(v);
	}
};

VOLANTE_NAMESPACE_END
#endif //__WRAPPEROBJECT_H__
