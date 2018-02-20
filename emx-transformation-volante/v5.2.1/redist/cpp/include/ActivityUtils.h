#ifndef __ACTIVITYUTILS_H__
#define __ACTIVITYUTILS_H__
#include "TransformContext.h"

VOLANTE_NAMESPACE_BEGIN
template <class T>
class ActivityExecutionScope {
	T* activity;
public:
	ActivityExecutionScope(T* activity, TransformContext& cxt) {
			this->activity = activity;
			activity->setup(cxt);
	}
	~ActivityExecutionScope() {
		activity->teardown();
	}
};

VOLANTE_NAMESPACE_END

#endif //__ACTIVITYUTILS_H__
