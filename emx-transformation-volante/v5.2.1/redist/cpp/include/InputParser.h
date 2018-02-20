#ifndef __INPUTPARSER_H__
#define __INPUTPARSER_H__
#include "Object.h"
#include "DataObject.h"
#include "TransformContext.h"
#include "InputSource.h"
#include "ExternalObject.h"
#include "ExceptionHandler.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT InputParser : public Object {
private:
	ExceptionHandler* exceptionHandler;
public:
	InputParser();
	virtual ExternalObject* parse(InputSource& input, TransformContext& cxt);
	virtual void parse(ExternalObject* externalObject, InputSource& input, TransformContext& cxt);
	virtual ExternalObject* parseData(const Binary& input, TransformContext& cxt) = 0;
	virtual void parseData(ExternalObject* externalObject, const Binary& input, TransformContext& cxt) = 0;
	void setExceptionHandler(ExceptionHandler* exceptionHandler) {
		this->exceptionHandler = exceptionHandler;
	}
	void ensureNotNull0(const vstring& value, DataObject* object, int index, TransformContext& cxt);
protected:
	bool isNull(const vstring& value)  {
		if(value.length() == 0) {
			return true;
		}
		return false;
	}
	inline void ensureNotNull(const vstring& value, DataObject* object, int index, TransformContext& cxt) {
		if(value.length() == 0) {
			ensureNotNull0(value, object, index, cxt);
		}
	}
};
VOLANTE_NAMESPACE_END

#endif //__INPUTPARSER_H__
