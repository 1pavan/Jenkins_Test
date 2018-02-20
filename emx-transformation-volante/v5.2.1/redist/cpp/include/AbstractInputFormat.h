#ifndef __ABSTRACTINPUTFORMAT_H__
#define __ABSTRACTINPUTFORMAT_H__
#include "InputFormat.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT AbstractInputFormat : public IInputFormat {
	LookupContext lcxt;
	BusinessTransaction bt;
	DataObjectVal cachedNormalizedObject;
public :
	AbstractInputFormat(const vstring& btName);
	~AbstractInputFormat();
	void processInput(InputSource& source, TransformContext& tcxt);
	NormalizedObject* handleInput(InputSource& is, TransformContext& cxt);
protected:
	virtual void handleInput0(InputSource& is, NormalizedObject* toNObj, TransformContext& cxt) = 0;
	virtual AbstractDataObject* createNormalizedObject() =0;
};
VOLANTE_NAMESPACE_END

#endif //__ABSTRACTINPUTFORMAT_H__

