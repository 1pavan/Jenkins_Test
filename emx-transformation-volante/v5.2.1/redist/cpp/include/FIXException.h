#ifndef __FIXEXCEPTION_H__
#define __FIXEXCEPTION_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FIXParsingException : public TransformException {
public:
	FIXParsingException(const TransformException& copyFrom) : TransformException(copyFrom) {
	}
	FIXParsingException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const{
		return new FIXParsingException(*this);
	}
};

class VOLANTE_EXPORT FIXWriterException : public TransformException{
public:
	FIXWriterException(const TransformException& copyFrom) : TransformException(copyFrom) {
	}
	FIXWriterException(const vstring& message) : TransformException(message){
	}
	virtual Object* clone() const{
		return new FIXWriterException(*this);
	}
};


VOLANTE_NAMESPACE_END


#endif //__FIXEXCEPTION_H__


