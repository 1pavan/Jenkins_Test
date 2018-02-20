#ifndef __BUSINESSTRANSACTIONWRAPPER_H__
#define __BUSINESSTRANSACTIONWRAPPER_H__
#include "InternalMessage.h"

VOLANTE_NAMESPACE_BEGIN
/**
*  For internal use only
*/ 
class VOLANTE_EXPORT  BusinessTransactionWrapper : public IBusinessTransaction {
	IBusinessTransaction* bt;
public:
	BusinessTransactionWrapper(IBusinessTransaction* bt) {
		this->bt = bt;
	}
	virtual DataObject* createNormalizedObject()  {
		return bt->createNormalizedObject();
	}
	virtual void handleNormalizedObject(NormalizedObject* obj, TransformContext& tcxt) {
		bt->handleNormalizedObject(obj, tcxt);
	}
	DataObjectVal createObject() {
		return bt->createObject();
	}
	DataObjectVal parse(InputSource& source, TransformContext& cxt) {
		return bt->parse(source, cxt);
	}

	Result<DataObjectVal> parse2(InputSource& source, TransformContext& cxt) {
		return bt->parse2(source, cxt);
	}
	DataObjectVal parse(const Binary& source, TransformContext& cxt) {
		return bt->parse(source, cxt);
	}
	DataObjectVal parse(const RawMessage& source, TransformContext& cxt) {
		return bt->parse(source, cxt);
	}

	Result<DataObjectVal> parse2(const Binary& source, TransformContext& cxt) {
		return bt->parse2(source, cxt);
	}


	void validate(const DataObjectVal& obj, TransformContext& cxt) {
		bt->validate(obj, cxt);
	}
	void validate(const vstring& name, const DataObjectVal& obj, TransformContext& cxt) {
		bt->validate(name, obj, cxt);
	}


	Result<DataObjectVal> validate2(const DataObjectVal& obj, TransformContext& cxt) {
		return bt->validate2(obj, cxt);
	}
	Result<DataObjectVal> validate2(const vstring& name, const DataObjectVal& obj, TransformContext& cxt) {
		return bt->validate2(name, obj, cxt);
	}

	Binary serialize(const DataObjectVal& obj, TransformContext& cxt) {
		return bt->serialize(obj, cxt);
	}


	Result<Binary> serialize2(const DataObjectVal& obj, TransformContext& cxt) {
		return bt->serialize2(obj,  cxt);
	}

	RawMessage serializeMessage(const DataObjectVal& obj, TransformContext& cxt) {
		return bt->serializeMessage(obj,  cxt);
	}
	Result<RawMessage> serializeMessage2(const DataObjectVal& obj, TransformContext& cxt) {
		return bt->serializeMessage2(obj,  cxt);
	}

	DataObjectVal preprocess(const DataObjectVal& nobj, TransformContext& cxt) {
		return bt->preprocess(nobj,  cxt);
	}
	Result<DataObjectVal> preprocess2(const DataObjectVal& nobj, TransformContext& cxt) {
		return bt->preprocess2(nobj,  cxt);
	}
	DataObjectVal postprocess(const DataObjectVal& nobj, TransformContext& cxt) {
		return bt->postprocess(nobj,  cxt);
	}
	Result<DataObjectVal> postprocess2(const DataObjectVal& nobj, TransformContext& cxt) {
		return bt->postprocess2(nobj,  cxt);
	}
	Result<DataObjectVal> process2(const vstring& name, const DataObjectVal& nobj, TransformContext& cxt) {
		return bt->process2(name, nobj,  cxt);
	}
	DataObjectVal process(const vstring& name, const DataObjectVal& obj, TransformContext& cxt) {
		return bt->process(name, obj,  cxt);
	}

};
VOLANTE_NAMESPACE_END




#endif //__BUSINESSTRANSACTIONWRAPPER_H__
