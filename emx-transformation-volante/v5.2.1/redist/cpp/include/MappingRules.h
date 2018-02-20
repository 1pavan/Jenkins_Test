#ifndef __MAPPINGRULES_H__
#define __MAPPINGRULES_H__
#include "IInvokable.h"
#include "CustomClassSupport.h"
#include "ActivityUtils.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT MappingRules {
public:
	MappingRules() {
		transformContext = NULL;
	}
	void setup(TransformContext& cxt) {
		this->transformContext = &cxt;
	}
	void teardown() {
		this->transformContext = NULL;
	}
protected:
	Object* invokeCustomExternalClass(const vstring& className, const ObjectList& args, TransformContext& cxt)  {
			IInvokable* invokable = customExternalClassSupport.getCustomObject(className);
			return invokable->run(args, cxt);
	}
	TransformContext& getTransformContext() {
		return *transformContext;
	}
private:
	CustomClassSupport<IInvokable> customExternalClassSupport;
	TransformContext* transformContext;
};


VOLANTE_NAMESPACE_END

#endif //__MAPPINGRULES_H__

