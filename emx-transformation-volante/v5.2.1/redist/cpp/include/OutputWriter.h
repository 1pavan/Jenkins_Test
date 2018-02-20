#ifndef __OUTPUTWRITER_H__
#define __OUTPUTWRITER_H__

#include "ByteArrayInputSource.h"
VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT OutputWriter {
public:
	virtual ~OutputWriter() {
	}
};


class VOLANTE_EXPORT SimpleOutputWriter : public OutputWriter {
public:
	virtual vstring write(ExternalObject& outputObject, ExceptionHandler* exceptionHandler, TransformContext& cxt) {
		this->exceptionHandler = exceptionHandler;
		return writeExternal(outputObject, cxt);
	}
	virtual RawMessage writeMessage(ExternalObject& outputObject, ExceptionHandler* exceptionHandler, TransformContext& cxt) {
		this->exceptionHandler = exceptionHandler;
		return writeExternalMessage(outputObject, cxt);
	}
	virtual vstring writeExternal(ExternalObject& outputObject, TransformContext& cxt) = 0;
	virtual RawMessage writeExternalMessage(ExternalObject& outputObject, TransformContext& cxt)  {
			vstring mes = writeExternal(outputObject, cxt);
			return RawMessage(new StringInputSource(mes));
	}
private:
	ExceptionHandler* exceptionHandler;
};

class VOLANTE_EXPORT AbstractSimpleOutputWriter : public SimpleOutputWriter {
public:
	vstring writeExternal(ExternalObject& outputObject, TransformContext& cxt) {
		initMessage();
		writeHeader(outputObject.getHeader(), cxt);
		writeData(outputObject.getData(), cxt);
		writeTrailer(outputObject.getTrailer(), cxt);
		return endMessage();
	}
	virtual void writeHeader(DataObject* obj, TransformContext& cxt) = 0;
	virtual void writeData(DataObject* obj, TransformContext& cxt)=0;
	virtual void writeTrailer(DataObject* obj, TransformContext& cxt)=0;
	virtual void initMessage() = 0;
	virtual vstring endMessage() = 0;

};

VOLANTE_NAMESPACE_END

#endif //__OUTPUTWRITER_H__

