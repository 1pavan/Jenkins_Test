#ifndef __SIACCANONICALEXCEPTION_H__
#define __SIACCANONICALEXCEPTION_H__

#include "TransformException.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT SIACCanonicalParsingException : public TransformException {
public:
	SIACCanonicalParsingException(const TransformException& copyFrom) : TransformException(copyFrom) {
	}
	SIACCanonicalParsingException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const{
		return new SIACCanonicalParsingException(*this);
	}
};


class VOLANTE_EXPORT SIACCanonicalWriterException : public TransformException{
public:
	SIACCanonicalWriterException(const TransformException& copyFrom) : TransformException(copyFrom) {
	}
	SIACCanonicalWriterException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const{
		return new SIACCanonicalWriterException(*this);
	}
};
VOLANTE_NAMESPACE_END

#endif //__SIACCANONICALEXCEPTION_H__


