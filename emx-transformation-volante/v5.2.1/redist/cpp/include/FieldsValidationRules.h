#ifndef __FIELDSVALIDATIONRULES_H__
#define __FIELDSVALIDATIONRULES_H__
#include "DataObject.h"
#include "Exceptions.h"
#include "IFieldValidation.h"
#include "CustomClassSupport.h"
#include "AbstractValidationRules.h"


VOLANTE_NAMESPACE_BEGIN



class VOLANTE_EXPORT FieldsValidationRules : public AbstractValidationRules  {
public :
	void validateData(DataObject* header, DataObject* data, TransformContext& cxt);
	void validateHeader(DataObject*  header, TransformContext& cxt);
	void validateTrailer(DataObject* trailer, TransformContext& cxt);
	void setExceptionHandler(ExceptionHandler* exceptionHandler) {
		this->exceptionHandler = exceptionHandler;
	}

protected:
	virtual void validateData0(DataObject* header, DataObject* data) = 0;
	virtual void validateHeader0(DataObject*  header) = 0;
	virtual void validateTrailer0(DataObject* trailer) = 0;

protected:
	ExceptionHandler* exceptionHandler;
};

VOLANTE_NAMESPACE_END

#endif //__FIELDSVALIDATIONRULES_H__

