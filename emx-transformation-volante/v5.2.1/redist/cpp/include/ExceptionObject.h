#ifndef __EXCEPTIONOBJECT_H__
#define __EXCEPTIONOBJECT_H__

#include "DataObject.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT ExceptionObject  {
public :
	static vstring getERROR_PHASE();
	static vstring getERROR_TYPE();
	static vstring getERROR_TYPE_PARSING();
	static vstring getERROR_TYPE_REQUIRED();
	static vstring getERROR_TYPE_VALIDATION();
	static vstring getERROR_TYPE_MAPPING();
	static vstring getERROR_TYPE_PROCESSING();
	static vstring getERROR_TYPE_OUTPUT();
	static vstring getERROR_FIELD();
	static vstring getINPUT_PHASE();
	static vstring getOUTPUT_PHASE();
	static vstring getINTERNAL_MESSAGE_PHASE();
	static vstring getEXCEPTION_SEVERITY_FATAL();
	static vstring getEXCEPTION_SEVERITY_ERROR();
	static vstring getEXCEPTION_SEVERITY_WARN();
	static vstring getLINE();
	static vstring getCOLUMN();
	static vstring getINDEX();
	static vstring getINTERNAL_CODE();

private:
	static vstring ERROR_PHASE;
	static vstring ERROR_TYPE;
	static vstring ERROR_TYPE_PARSING;
	static vstring ERROR_TYPE_REQUIRED;
	static vstring ERROR_TYPE_VALIDATION;
	static vstring ERROR_TYPE_MAPPING;
	static vstring ERROR_TYPE_PROCESSING;
	static vstring ERROR_TYPE_OUTPUT;
	static vstring ERROR_FIELD;
	static vstring INPUT_PHASE;
	static vstring OUTPUT_PHASE;
	static vstring INTERNAL_MESSAGE_PHASE;
	static vstring EXCEPTION_SEVERITY_FATAL;
	static vstring EXCEPTION_SEVERITY_ERROR;
	static vstring EXCEPTION_SEVERITY_WARN;
	static vstring LINE;
	static vstring COLUMN;
	static vstring INDEX;
	static vstring INTERNAL_CODE;
public:
	enum ExceptionSeverity {
		NON_FATAL=0,
		FATAL=1
	};

public:
	virtual ~ExceptionObject() {
	}
	virtual const vstring& getMessage() const =0;

};

class ExceptionDataObject;


VOLANTE_NAMESPACE_END


#endif //__EXCEPTIONOBJECT_H__
