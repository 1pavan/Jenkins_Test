#ifndef __ABSTRACTVALIDATIONRULES_H__
#define __ABSTRACTVALIDATIONRULES_H__
#include "DataObject.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "IFieldValidation.h"
#include "IInvokable.h"
#include "CustomClassSupport.h"
#include "ActivityUtils.h"


VOLANTE_NAMESPACE_BEGIN



class VOLANTE_EXPORT AbstractValidationRules {
	TransformContext* transformContext;
public:
	AbstractValidationRules() {
		transformContext = NULL;
	}
protected:
	void throwFieldInvalid(const vstring& validationName, const vstring& fieldName)  {
		THROW_EXCEPTION(FieldValidationException("Validation '" + validationName + "' failed. Field '" + fieldName + "' is not valid", fieldName));
	}


	void throwFieldInvalid(const vstring& validationMessage, const vstring& validationName, const vstring& errorCode, const vstring& severity, bool cascadable, DataObject* object, int index) ;
	void throwFieldInvalid(const vstring& validationName, const vstring& errorCode, const vstring& severity, bool cascadable, DataObject* object, int index);
protected:
	bool customValidation(const vstring& customClass, const Object* value, const vstring& fldName, DataObject* obj);
	CustomClassSupport<IFieldValidation> fieldValidationSupport;
private:
	void throwFieldInvalid(FieldValidationException& ex, const vstring& validationMessage, const vstring& validationName, const vstring& errorCode, const vstring& severity, bool cascadable, DataObject* object, int index);
	void throwFieldInvalid(FieldValidationException& ex, const vstring& validationName, const vstring& errorCode, const vstring& severity, bool cascadable, DataObject* object, int index);
protected:
	Object* invokeCustomExternalClass(const vstring& className, const ObjectList& args, TransformContext& cxt)  {
		IInvokable* invokable = customExternalClassSupport.getCustomObject(className);
		return invokable->run(args, cxt);
	}
protected:
	TransformContext& getTransformContext() {
		return *transformContext;
	}
public:
	void setup(TransformContext& cxt) {
		this->transformContext = &cxt;
	}
	void teardown() {
		this->transformContext = NULL;
	}

private:
	CustomClassSupport<IInvokable> customExternalClassSupport;

};



class VOLANTE_EXPORT ValidationRules : public AbstractValidationRules {
public:
	ValidationRules();
	void validate(NormalizedObject* nObj, TransformContext& cxt);

	virtual void validate0(NormalizedObject* nObj) = 0;
	void setExceptionHandler(ExceptionHandler* exceptionHandler) {
		this->exceptionHandler = exceptionHandler;
	}
private:
	ExceptionHandler*  exceptionHandler;
};

VOLANTE_NAMESPACE_END



#endif //__ABSTRACTVALIDATIONRULES_H__
