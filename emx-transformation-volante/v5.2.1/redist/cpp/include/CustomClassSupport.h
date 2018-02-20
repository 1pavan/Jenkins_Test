#ifndef __CUSTOMCLASSSUPPORT_H__
#define __CUSTOMCLASSSUPPORT_H__
#include "UserClassManager.h"
#include "TransformException.h"

VOLANTE_NAMESPACE_BEGIN

template <class T>
class CustomClassSupport {
public:
	CustomClassSupport() {
	}
	static T* createInstance(const vstring& className)  {
		try {
			Object* obj = UserClassManager::createInstance(className);
			if(T* customObj = dynamic_cast<T*>(obj)) {
				return customObj;
			}
			else {
				obj->releaseRef();
				THROW_EXCEPTION(TransformException("Error creating custom class instance - " + className + " is not of expected type"));
			}
		}
		catch(ClassNotFoundException& e) {
			THROW_EXCEPTION(TransformException("Error creating custom class instance - " + className + "." + e.getMessage()));
		}
	}

	T* getCustomObject(const vstring&  className) {
		T* customObj= static_cast<T*>(customObjects.get(className));
		if(customObj == NULL) {
			customObj = createInstance(className);
			customObjects.put(className, customObj);
		}
		return customObj;
	}

	SmallStringMap customObjects;
};

VOLANTE_NAMESPACE_END

#endif //__CUSTOMCLASSSUPPORT_H__
