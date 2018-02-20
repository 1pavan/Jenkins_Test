#ifndef __FUNCTIONDEFS_H__
#define __FUNCTIONDEFS_H__

#include "Object.h"
#include "TransformContext.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FunctionDefs {
protected:
	static Object* invokeCustomExternalClass(const vstring& className, ObjectList& args, TransformContext* cxt);
	static CustomClassSupport<IInvokable> customExternalClassSupport;
};

VOLANTE_NAMESPACE_END



#endif //__FUNCTIONDEFS_H__
