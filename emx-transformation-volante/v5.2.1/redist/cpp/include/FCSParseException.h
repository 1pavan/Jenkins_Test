#ifndef __FCSPARSEEXCEPTION_H__
#define __FCSPARSEEXCEPTION_H__
#include "TransformException.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FCSParseException : public TransformException {
public:
	FCSParseException(const vstring& message) : TransformException(message){

	}
	virtual Object* clone() const {
		return new FCSParseException(*this);
	}

	void setLocation(int line, int column);
	void setFailedLine(const vstring& failedLine);
private:
	vstring failedLine;

};
VOLANTE_NAMESPACE_END

#endif //__FCSPARSEEXCEPTION_H__
