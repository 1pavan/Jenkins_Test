#ifndef __LOGFACTORY_H__
#define __LOGFACTORY_H__
#include "Object.h"

VOLANTE_NAMESPACE_BEGIN

enum V_LOG_LEVEL {
	V_LOG_DISCARD_ALL = 0,
	V_LOG_INHERIT_LEVEL = 0,
	V_LOG_ERROR = 1,
	V_LOG_WARN = 2,
	V_LOG_INFO = 3,
	V_LOG_TRACE = 4,
	V_LOG_DEBUG = 5
};
class VOLANTE_EXPORT ILogger : public ObjectRef {
public:
	virtual vstring getCategoryName() = 0;
	virtual void info(const vstring&  str) = 0;
	virtual void info(const char* str) = 0;
	virtual void debug(const char* str) = 0;
	virtual void debug(const vstring&  str) = 0;
	virtual void warn(const char* str) = 0;
	virtual void warn(const vstring&  str) = 0;
	virtual void error(const char* str) = 0;
	virtual void error(const vstring&  str) = 0;
	virtual void setLogLevel(V_LOG_LEVEL level) = 0;
	virtual bool isLevelEnabled(V_LOG_LEVEL callLevel) = 0;
};
template class VOLANTE_EXPORT SmartPtr<ILogger>;

class VOLANTE_EXPORT Logger : public SmartPtr<ILogger> {
public:
	Logger()  {
	}
	Logger(ILogger* logger) : SmartPtr<ILogger>(logger) {
	}
	void info(const vstring&  str) {
		obj->info(str);
	}
	void info(const char* str) {
		obj->info(str);
	}
	void trace(const vstring&  str) {
		obj->debug(str);
	}
	void debug(const char* str) {
		obj->debug(str);
	}
	void debug(const vstring&  str) {
		obj->debug(str);
	}
	void warn(const char* str) {
		obj->warn(str);
	}
	void warn(const vstring&  str) {
		obj->warn(str);
	}

	void error(const char* str) {
		obj->error(str);
	}
	void error(const vstring&  str) {
		obj->error(str);
	}
	void setLogLevel(V_LOG_LEVEL level) {
		obj->setLogLevel(level);
	}
	vstring getCategoryName() {
		return obj->getCategoryName();
	}
	bool isLevelEnabled(V_LOG_LEVEL callLevel) {
		return obj->isLevelEnabled(callLevel);
	}

};

class VOLANTE_EXPORT LogFactory {
public:
	static Logger getLog(const vstring& category);
	static Logger getLog(const char* category);
	static Logger getRoot();
};

/*
class LoggingEvent {
public:
	LoggingEvent(ILogger* category, const vstring& message);
private:
	ILogger* category;
	vstring message;
	DateTime timeStamp;
};
class Appender {
	virtual void write(LoggingEvent e) = 0;
};
*/


VOLANTE_NAMESPACE_END

#endif //__LOGFACTORY_H__
