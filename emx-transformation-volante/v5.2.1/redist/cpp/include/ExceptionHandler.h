#ifndef __EXCEPTIONHANDLER_H__
#define __EXCEPTIONHANDLER_H__

#include "ExceptionObject.h"

VOLANTE_NAMESPACE_BEGIN


typedef VOLANTE_EXPORT std::vector<ExceptionDataObject*> ExceptionList;

//class VOLANTE_EXPORT ExceptionList : public std::vector<ExceptionDataObject*> {
//}; 

class VOLANTE_EXPORT ExceptionHandler : public Object {
public:
	virtual void onException(ExceptionDataObject* e) = 0;
	static ExceptionHandler* DRACONIAN_EXCEPTION_HANDLER;
};

class VOLANTE_EXPORT DraconianExceptionHandler : public ExceptionHandler  {
public:
	void onException(ExceptionDataObject* e);
};

class VOLANTE_EXPORT CascadingExceptionHandler : public ExceptionHandler  {
public:
	void onException(ExceptionDataObject* e);
	ExceptionList& getExceptions() {
		return exceptions;
	}
private:
	 ExceptionList exceptions;
};

VOLANTE_NAMESPACE_END

#endif //__EXCEPTIONHANDLER_H__
