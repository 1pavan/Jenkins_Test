#ifndef __OBJECT_H__
#define __OBJECT_H__
#ifdef _MSC_VER
#pragma warning(disable: 4251)  // using non-exported as public in exported
#pragma warning( disable : 4786 )
#endif



#include "md.h"
#include <stdio.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#ifdef VOLANTE_USE_OLD_STREAMS
#include <iostream.h>
#include <fstream.h>
#else 
#include <iostream>
#include <fstream>
#endif

#include <typeinfo>

VOLANTE_NAMESPACE_BEGIN

//#define CHECK_THREAD_OWNER
#ifdef CHECK_THREAD_OWNER
class Object;
class VOLANTE_EXPORT SingleThreadAccess {
public:
	SingleThreadAccess() {
		ownerThread = getCurrentThread();
	}
	void* getCurrentThread();
	void checkThreadOwner();
	void checkThreadOwner(Object* obj);
private:
	void* ownerThread;
};
#endif

//typedef signed char vbyte;
typedef char vbyte;
VOLANTE_NAMESPACE_END

#ifdef VOLANTE_USE_STD_STRING
#include "vstring.h"
VOLANTE_NAMESPACE_BEGIN
typedef std::string		vstring;
typedef std::string		vstringbuffer;
typedef std::string		vstringliteral;
VOLANTE_NAMESPACE_END
#else 
#include "vstring.h"
VOLANTE_NAMESPACE_BEGIN
typedef vlstring		vstring;
typedef vlstringbuffer	vstringbuffer;
typedef vlstringliteral vstringliteral;
VOLANTE_NAMESPACE_END
#endif
#include "DesignerTypes.h"
#include "DateTime.h"
#include "BigInteger.h"
#include "BigDecimal.h"
#include "Binary.h"
#include "DesignerTypes.h"

VOLANTE_NAMESPACE_BEGIN


class BigInteger;
class BigDecimal;
class Binary;
class DateTime;
class RawMessage;
/** 
* Root of the class hierarchy. All the key classes in this library have this class 
* as its base class.
* @see ObjectRef
*/
class VOLANTE_EXPORT Object {
	static vstringliteral OBJECT_TYPE;
protected:
	Object() {
	}
	virtual ~Object() {
	}
public:
	/** Support for reference counting in derived class (ObjectRef) */

	virtual void addRef() {
		// Nothing to do here - we are not reference counted
	}
	virtual void releaseRef() {
		// Delete this object
		delete this;
	}
	/**
	* Returns a string representation of the object. In general, the 
	* <code>toString</code> method returns a string that 
	* "textually represents" this object.
	*/
	virtual vstring toString() const;

	/**
	* Creates and returns a copy of this object in the heap.  
	*/
	virtual Object* clone() const;
	virtual int getInt() const {
		unsupportedConversionException(DesignerTypes::INT_TYPE);
		return 0;
	}
	virtual void setInt(int value) {
		unsupportedConversionException(DesignerTypes::INT_TYPE);
	}
	virtual dlong getLong()const {
		unsupportedConversionException(DesignerTypes::LONG_TYPE);
		return 0;
	}
	virtual void setLong(dlong value) {
		unsupportedConversionException(DesignerTypes::LONG_TYPE);
	}
	virtual double getDouble() const {
		unsupportedConversionException(DesignerTypes::DOUBLE_TYPE);
		return 0;
	}
	virtual void setDouble(double value) {
		unsupportedConversionException(DesignerTypes::DOUBLE_TYPE);
	}
	virtual float getFloat() const {
		unsupportedConversionException(DesignerTypes::FLOAT_TYPE);
		return 0;
	}
	virtual void setFloat(float value) {
		unsupportedConversionException(DesignerTypes::FLOAT_TYPE);
	}
	virtual char getCharacter() const {
		unsupportedConversionException(DesignerTypes::CHAR_TYPE);
		return 0;
	}
	virtual void setCharacter(char value) {
		unsupportedConversionException(DesignerTypes::CHAR_TYPE);
	}
	virtual bool getBoolean() const {
		unsupportedConversionException(DesignerTypes::BOOLEAN_TYPE);
		return false;
	}
	virtual void setBoolean(bool value) {
		unsupportedConversionException(DesignerTypes::BOOLEAN_TYPE);
	}
	virtual BigInteger getBigInteger() const {
		unsupportedConversionException(DesignerTypes::BIG_INTEGER_TYPE);
		return BigInteger(0);
	}
	virtual void setBigInteger(const BigInteger& value) {
		unsupportedConversionException(DesignerTypes::BIG_INTEGER_TYPE);
	}
	virtual BigDecimal getBigDecimal() const {
		unsupportedConversionException(DesignerTypes::BIG_DECIMAL_TYPE);
		return BigDecimal(0);
	}
	virtual void setBigDecimal(const BigDecimal& value) {
		unsupportedConversionException(DesignerTypes::BIG_DECIMAL_TYPE);
	}
	virtual DateTime getDate() const {
		unsupportedConversionException(DesignerTypes::DATE_TIME_TYPE);
		return DateTime();
	}
	virtual void setDate(const DateTime& value) {
		unsupportedConversionException(DesignerTypes::DATE_TIME_TYPE);
	}
	virtual ISODateTime getISODate() const {
		unsupportedConversionException(DesignerTypes::ISO_DATE_TIME_TYPE);
		return DateTime();
	}
	virtual void setISODate(const ISODateTime& value) {
		unsupportedConversionException(DesignerTypes::ISO_DATE_TIME_TYPE);
	}
	virtual vstring getString() const {
		unsupportedConversionException(DesignerTypes::STRING_TYPE);
		return vstring();
	}
	virtual void setString(const vstring& value) {
		unsupportedConversionException(DesignerTypes::STRING_TYPE);
	}
	virtual Binary getBinary() const {
		unsupportedConversionException(DesignerTypes::BINARY_TYPE);
		return Binary();
	}
	virtual void setBinary(const Binary& value) {
		unsupportedConversionException(DesignerTypes::BINARY_TYPE);
	}
	virtual const RawMessage& getRawMessage() const {
		unsupportedConversionException(DesignerTypes::RAW_MESSAGE_TYPE);
		RawMessage* raw = NULL;
		return *raw;
	}
	virtual void setRawMessage(const RawMessage& value)  {
		unsupportedConversionException(DesignerTypes::RAW_MESSAGE_TYPE);
	}
	virtual const vstring& getObjectType() const {
		return OBJECT_TYPE;
	}
	void unsupportedConversionException(const vstring& destType) const;
	virtual void setObject(const Object* value) {
		unsupportedConversionException(value->getObjectType());
	}

};

#define CLONE_IMPL(className) \
	virtual Object* clone() const  {  \
	return new className(*this); \
	}


///////////////////////////////////////////////////////////////////////////////

VOLANTE_NAMESPACE_END

#include "Conversion.h"
#include "WrapperObject.h"

#include "ObjectRef.h"
#include "ObjectUtils.h"
#include "Class.h"
#include "Parsing.h"

#endif //__OBJECT_H__
