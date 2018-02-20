#ifndef __TRANSFORMEXCEPTION_H__
#define __TRANSFORMEXCEPTION_H__
#include "Exceptions.h"
#include "ExceptionDataObject.h"
VOLANTE_NAMESPACE_BEGIN
class VOLANTE_EXPORT TransformException : public Exception, public ExceptionDataObject {
public:
	TransformException(ExceptionList& e);
	TransformException(const ExceptionDataObject& e);

	TransformException(const vstring& message) : Exception(message) {
		setMessage(message);
		initFields();
	}

	TransformException(const vstring& message, Exception* detail) : Exception(message, detail) {
		setMessage(message);
		initFields();
	}
private:
	void initFields() {
		setErrorCode(vstringliteral(""));
		setSeverity(getEXCEPTION_SEVERITY_FATAL());
		setCascadable(true);
	}
public:
	TransformException(const TransformException& transformException);
	TransformException& operator = (const TransformException& transformException);
public:
	virtual Object* clone() const {
		return new TransformException(*this);
	}
	virtual void  addAll(const TransformException* toAdd){
		addAll(*toAdd);
	}
	virtual void  addAll(const TransformException& toAdd);

	const vstring& getMessage() const {
		return ExceptionDataObject::getMessage();
	}
	virtual void setMessage(const vstring& value) {
		Exception::setMessage(value);
		ExceptionDataObject::setMessage(value);
	}
	vstring toString() const {
		return toXMLString();
	}
	void addRef() {
		ExceptionDataObject::addRef();
	}
	void releaseRef() {
		ExceptionDataObject::releaseRef();
	}

	vstring toXMLString() const {
		return ExceptionDataObject::toXMLString();
	}
	vstring toXMLString(int indent)  const {
		return ExceptionDataObject::toXMLString(indent);
	}
	vstring toXMLString(bool includeDataRecord);
	void getExceptionsAsList(ExceptionList& exceptionList);
  void setInternalCode(const vstring& internalCode) {
		setContextProperty(ExceptionObject::getINTERNAL_CODE(), internalCode);
  }

private:
	vstring indentStr(int val);
	vstring tagStart(const vstring& tag);
	vstring tagEnd(const vstring& tag);
	vstring tagValue(int indent, const vstring& tag, const vstring& value);

private:
};



class VOLANTE_EXPORT UnhandledMessageException : public TransformException {
public:
	UnhandledMessageException(const vstring& message) : TransformException(message){

	}
	virtual Object* clone() const {
		return new UnhandledMessageException(*this);
	}
};

class VOLANTE_EXPORT UnrecognizedMessageException : public UnhandledMessageException {
public:
	UnrecognizedMessageException(const vstring& message) : UnhandledMessageException(message){

	}
	virtual Object* clone() const {
		return new UnrecognizedMessageException(*this);
	}
};

class VOLANTE_EXPORT TransformRuntimeException : public TransformException {
public:
	TransformRuntimeException(const vstring& message) : TransformException(message){

	}
	virtual Object* clone() const {
		return new TransformRuntimeException(*this);
	}
};

class VOLANTE_EXPORT TransformNullValueException : public TransformRuntimeException {
public:
	TransformNullValueException(const vstring& message) : TransformRuntimeException(message){

	}
	virtual Object* clone() const {
		return new TransformNullValueException(*this);
	}
};

class VOLANTE_EXPORT FieldNotFoundException : public TransformException{
public:
	FieldNotFoundException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const {
		return new FieldNotFoundException(*this);
	}
};
class VOLANTE_EXPORT FieldTypeMismatchException : public TransformException{
public:
	FieldTypeMismatchException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const {
		return new FieldTypeMismatchException(*this);
	}
};
class VOLANTE_EXPORT FieldNullException : public TransformException{
public:
	FieldNullException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const {
		return new FieldNullException(*this);
	}
};
class VOLANTE_EXPORT FieldParsingException : public TransformException{
public:
	FieldParsingException(const vstring& message) : TransformException(message){
	}
	FieldParsingException(const vstring& message, const vstring& fieldName) : TransformException(message){
	}
	virtual Object* clone() const{
		return new FieldParsingException(*this);
	}
};

class VOLANTE_EXPORT FieldValidationException : public TransformException{
public:
	FieldValidationException(const vstring& message, const vstring& fieldName) : TransformException(message) {
		setFFieldName(fieldName);
	}
	virtual Object* clone() const{
		return new FieldValidationException(*this);
	}
};
class VOLANTE_EXPORT NamingException : public TransformException {
public:
	NamingException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const{
		return new NamingException(*this);
	}
};
class VOLANTE_EXPORT SectionConstraintException : public TransformException{
public:
	SectionConstraintException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const {
		return new SectionConstraintException(*this);
	}
};

VOLANTE_NAMESPACE_END

#endif //__TRANSFORMEXCEPTION_H__
