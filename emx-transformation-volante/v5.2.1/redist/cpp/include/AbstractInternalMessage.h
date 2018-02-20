#ifndef __AbstractInternalMessage_H__
#define __AbstractInternalMessage_H__
#include "InternalMessage.h"
#include "ProcessingRules.h"
#include "AbstractValidationRules.h"
//#include "BusinessProcessingRules.h"
#include "Triggers.h"
//#include "LogFactory.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT AbstractInternalMessage : public IInternalMessage {
public:
	AbstractInternalMessage(const vstring& messageName);
	virtual ~AbstractInternalMessage();

	DataObjectVal createObject();
	DataObjectVal parse(InputSource& source, TransformContext& cxt);
	DataObjectVal parse(const RawMessage& source, TransformContext& cxt);
	DataObjectVal parse(const Binary& source, TransformContext& cxt) ;

	Result<DataObjectVal> parse2(InputSource& source, TransformContext& cxt);
	Result<DataObjectVal> parse2(const Binary& source, TransformContext& cxt);
	void validate(const vstring& name, const DataObjectVal& obj, TransformContext& cxt);
	//void validate(const DataObjectVal& obj, ExceptionHandler* exceptionHandler, TransformContext& cxt);
	void validate(const DataObjectVal& obj, TransformContext& cxt);

	Result<DataObjectVal> validate2(const DataObjectVal& obj, TransformContext& cxt);
	Result<DataObjectVal> validate2(const vstring& name, const DataObjectVal& obj, TransformContext& cxt);

	Binary serialize(const DataObjectVal& obj, TransformContext& cxt);

	void serialize(const DataObjectVal& obj, OutputDevice& outputDevice, TransformContext& cxt);

	Result<Binary> serialize2(const DataObjectVal& obj, TransformContext& cxt);

	void handleNormalizedObject(NormalizedObject* obj, TransformContext& tcxt);


	RawMessage serializeMessage(const DataObjectVal& obj, TransformContext& cxt);
	Result<RawMessage> serializeMessage2(const DataObjectVal& obj, TransformContext& cxt);

	DataObjectVal preprocess(const DataObjectVal& nobj, TransformContext& cxt);
	Result<DataObjectVal> preprocess2(const DataObjectVal& nobj, TransformContext& cxt);
	void preprocess(const DataObjectVal& obj, ExceptionHandler* exceptionHandler, TransformContext& cxt);

	DataObjectVal postprocess(const DataObjectVal& nobj, TransformContext& cxt);
	Result<DataObjectVal> postprocess2(const DataObjectVal& nobj, TransformContext& cxt);
	void postprocess(const DataObjectVal& obj, ExceptionHandler* exceptionHandler, TransformContext& cxt);
	DataObjectVal process(const vstring& name, const DataObjectVal& obj, TransformContext& cxt);
	Result<DataObjectVal> process2(const vstring& name, const DataObjectVal& nobj, TransformContext& cxt);

	virtual Triggers* getTriggers() {
		return NULL;
	}
protected:
	void validate(const vstring& name, const DataObjectVal& obj, ExceptionHandler* exceptionHandler, TransformContext& cxt);
	void addValidator(const vstring& name, ValidationRules* validator) {
		validators.insert(ValidationMap::value_type(name, validator));
	}
	void addProcessing(const vstring& name, BusinessProcessingRules* businessProcessingRules) {
		processingMap.insert(BusinessProcessingRulesMap::value_type(name, businessProcessingRules));
	}
private:
	void processAll(NormalizedObject* inputObj, TransformContext& cxt);
	bool processingRuleExists(const vstring& name);
	ValidationRules* getValidatorByName(const vstring& name);
	BusinessProcessingRules* getProcessingRuleByName(const vstring& name);
	void process(const vstring& name, const DataObjectVal& obj, ExceptionHandler* exceptionHandler, TransformContext& cxt);

private:
	vstring messageName;
	typedef std::map<vstring, ValidationRules*> ValidationMap;
	ValidationMap validators;
	typedef std::map<vstring, BusinessProcessingRules*> BusinessProcessingRulesMap;
	BusinessProcessingRulesMap processingMap;
protected:
	ValidationRules* defaultValidator;


	//Logger log;
	static vstring PREPROCESSING_NODE_NAME;
	static vstring POSTPROCESSING_NODE_NAME;
};

VOLANTE_NAMESPACE_END

#endif //__AbstractInternalMessage_H__


