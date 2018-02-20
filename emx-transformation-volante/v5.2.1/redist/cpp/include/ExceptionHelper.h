#ifndef __EXCEPTIONHELPER_H__
#define __EXCEPTIONHELPER_H__

#include "Object.h"
#include "Exceptions.h"
#include "ResourceBundle.h"
#include "MessageFormat.h"

VOLANTE_NAMESPACE_BEGIN

#define CREATE_EXCEPTION(classname, messageId, argList) \
	classname(MessageFormat::format(Resources::getProperty(#messageId ".message"), argList))

template<class E>
E createException(const vstring& id, const ObjectList& objList) {
	E e(MessageFormat::format(Resources::getProperty(id + ".message"), objList));
	e.setErrorCode(Resources::getProperty(id + ".code"));
	return e;
}

template<class E>
E createException(const vstring& id, const vstring& arg) {
	E e(MessageFormat::format(Resources::getProperty(id + ".message"), ObjectList(arg)));
	e.setErrorCode(Resources::getProperty(id + ".code"));
	return e;
}

template<class E>
E createException(const vstring& id) {
	E e(MessageFormat::format(Resources::getProperty(id + ".message"), ObjectList()));
	e.setErrorCode(Resources::getProperty(id + ".code"));
	return e;
}

#define THROW_EXCEPTION_FMT(className, id, arg) \
	THROW_EXCEPTION(createException<className>(id, arg));

#define THROW_EXCEPTION_FMT0(className, id) \
	THROW_EXCEPTION(createException<className>(id));


VOLANTE_NAMESPACE_END



#endif //__EXCEPTIONHELPER_H__
