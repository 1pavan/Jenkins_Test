#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include "ExceptionHandler.h"
#include "AbstractDataObject.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT ExceptionTrace {
public:
	ExceptionTrace() {
		line = 0;
	}
	bool isValid() {
		return line != 0;
	}
	void setFileName(const char* fileName) {
		this->fileName = fileName;
	}
	vstring getFileName() {
		return fileName;
	}
	void setLine(int line) {
		this->line = line;
	}
	int getLine() {
		return line;
	}
	vstring getTraceString() {
		vstring toRet;
		if(line != 0) {
			toRet = fileName + ":" + intToString(line) + ":" ;
		}
		return toRet;
	}
private:
	vstring fileName;
	int line;
};

class VOLANTE_EXPORT Exception : public virtual Object {
public:
	Exception(const vstring& message) {
		detail = NULL;
		setMessage(message);
	}
	Exception(const vstring& message, Exception* detail) {
		this->detail = detail;
		setMessage(message);
	}
	virtual ~Exception() {
		delete detail;
	}
	Exception& getThis() {
		return *this;
	}
	virtual const vstring& getMessage() const {
		return Message;
	}
	virtual void setMessage(const vstring& value) {
		this->Message = value;
	}
	virtual vstring toString() const {
		vstring toRet(typeid(*this).name());
		toRet = toRet + ":";
		toRet = toRet + const_cast<Exception*>(this)->getMessage();
		return toRet;
	}
	ExceptionTrace& getTrace() const {
		return exceptionTrace;
	}
	vstring getTraceString() const {
		return exceptionTrace.getTraceString();
	}
	void setDetail(Exception& e) {
		detail = dynamic_cast<Exception*>(e.clone()); 
	}
	Exception* getDetail() {
		return detail;
	}
	virtual Object* clone() const {
		return new Exception(*this);
	}

private:
	vstring Message;
	Exception* detail;
	mutable ExceptionTrace exceptionTrace;
};

class VOLANTE_EXPORT InternalError  : public Exception {
public:
	InternalError(const vstring& message)  : Exception(message){
	}
	virtual Object* clone() const {
		return new InternalError(*this);
	}
};

class VOLANTE_EXPORT IllegalArgumentException : public Exception {
public:
	IllegalArgumentException(const vstring& message) : Exception(message) {
	}
	virtual Object* clone() const {
		return new IllegalArgumentException(*this);
	}
};

class ClassCastException : public Exception {
public:
	ClassCastException(const vstring& message) : Exception(message){
	}
	virtual Object* clone() const{
		return new ClassCastException(*this);
	}
};


class VOLANTE_EXPORT ClassNotFoundException : public Exception {
public:
	ClassNotFoundException(const vstring& message) : Exception(message) {
	}
	virtual Object* clone() const{
		return new ClassNotFoundException(*this);
	}
};
template <class T>
inline T& add_exception_trace(const T& ex, const char* fileName, int line) {
	ExceptionTrace& trace = ex.getTrace();
	trace.setFileName(fileName);
	trace.setLine(line);
	return const_cast<T&>(ex);
}


#define THROW_EXCEPTION(ex) \
	throw add_exception_trace(ex, __FILE__, __LINE__);


template <class Target, class Source>
inline Target polymorphic_cast(Source* x)
{
    Target tmp = dynamic_cast<Target>(x);
    if ( tmp == 0 ) 
		if( x == 0) {
			THROW_EXCEPTION(ClassCastException("Cannot cast NULL to " + Class(typeid(Target)).getName()));
		}
		else {
			THROW_EXCEPTION(ClassCastException("Cannot cast " + Class(typeid(*x)).getName()  + "* to " + Class(typeid(Target)).getName()));
		}
    return tmp;
}

VOLANTE_NAMESPACE_END

#endif //__EXCEPTIONS_H__

