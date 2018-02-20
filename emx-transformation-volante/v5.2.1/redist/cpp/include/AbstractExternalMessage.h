#ifndef __ABSTRACTEXTERNALMESSAGE_H__
#define __ABSTRACTEXTERNALMESSAGE_H__
#include "Message.h"
#include "ExceptionHandler.h"
#include "ExternalObject.h"
#include "InputParser.h"
#include "FieldsValidationRules.h"
#include "OutputWriter.h"
#include "AbstractMessage.h"
#include "ExternalMessage.h"
#include "GenericExternalObject.h"

VOLANTE_NAMESPACE_BEGIN


class VOLANTE_EXPORT AbstractExternalMessage : public IExternalMessage {
public:
	DataObjectVal createObject();
	DataObjectVal parse(const Binary& source, TransformContext& cxt) ;
	DataObjectVal parse(InputSource& source, TransformContext& cxt) ;
	DataObjectVal parse(const RawMessage& source, TransformContext& cxt) ;

	void validate(const DataObjectVal& obj, TransformContext& cxt);
	void validate(const vstring& name, const DataObjectVal& obj, TransformContext& cxt);

	Binary serialize(const DataObjectVal& obj, TransformContext& cxt);
	RawMessage serializeMessage(const DataObjectVal& obj, TransformContext& cxt);
	Result<RawMessage> serializeMessage2(const DataObjectVal& obj, TransformContext& cxt);
	RawMessage serializeMessage(const DataObjectVal& obj, ExceptionHandler* exceptionHandler, TransformContext& cxt);

	Result<DataObjectVal> parse2(const Binary& source, TransformContext& cxt);
	Result<DataObjectVal> parse2(InputSource& source, TransformContext& cxt);

	Result<DataObjectVal> validate2(const DataObjectVal& obj,  TransformContext& cxt);
	Result<DataObjectVal> validate2(const vstring& name, const DataObjectVal& obj,  TransformContext& cxt);

	Result<Binary> serialize2(const DataObjectVal& obj, TransformContext& cxt);
protected:
	AbstractExternalMessage(const vstring& messageName);
	DataObjectVal parse(const Binary& source, ExceptionHandler* handler, TransformContext& cxt);
	void validate(const DataObjectVal& obj, ExceptionHandler* handler, TransformContext& cxt);
	void validate(const vstring& name, const DataObjectVal& obj, ExceptionHandler* exceptionHandler, TransformContext& cxt);
	Binary serialize(const DataObjectVal& obj, ExceptionHandler* handler, TransformContext& cxt);
  void methodEnteredTrace(const vstring& methodName);
  void methodEnteredTrace(const char* methodName);
	void addValidator(const vstring& name, FieldsValidationRules* validator) {
		validators.insert(ValidationMap::value_type(name, validator));
	}
	FieldsValidationRules* getValidatorByName(const vstring& name);

protected:
	virtual ExternalObjectVal createExternalObject()  = 0 ;
	virtual InputParser& getInputParser() = 0;
	//virtual FieldsValidationRules& getValidator() = 0;
	virtual SimpleOutputWriter& getWriter() = 0;
private:
	LookupContext lcxt;
	vstring messageName;
	typedef std::map<vstring, FieldsValidationRules*> ValidationMap;
	ValidationMap validators;
protected:
	FieldsValidationRules* defaultValidator;
	//Logger log;

};

VOLANTE_NAMESPACE_END


#endif //__ABSTRACTEXTERNALMESSAGE_H__
