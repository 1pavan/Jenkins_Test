#ifndef __ABSTRACTMESSAGEFLOW_H__
#define __ABSTRACTMESSAGEFLOW_H__
#include "MessageFlow.h"
#include "LoggingConstants.h"
#include "IInvokable.h"
#include "CustomClassSupport.h"
/*
*  AbstractMessageFlow.java
*
*  © Copyright 2001-2004 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/
VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT AbstractMessageFlow : public IMessageFlow {
protected:
	LookupContext lcxt;
	OutputPortList outputPorts;
	ExceptionHandler* exceptionHandler;
protected:
	//ObjectPtrMap<ObjectRef> lookupCache;
	SmallStringMap lookupCache;
	//Logger log;
private:
	vstring messageFlowName;
	bool traceEnabled;
	TransformContext* transformContext;

protected:
	AbstractMessageFlow(const vstring& messageFlowName);
	~AbstractMessageFlow() {
	}
	void addOutputPort(const vstring& name, const vstring& protocol, const vstring& outputDevice);
	TransformContext& getTransformContext() {
		return *transformContext;
	}
public:
	OutputPortList getOutputPorts();

public:
	void init();

private:
	void onStartMesageFlow(TransformContext& transformContext, ExceptionHandler* exceptionHandler);
	void onEndMesageFlow();

public:
	class MessageFlowLifeCycle {
		AbstractMessageFlow* mf;
	public:
		MessageFlowLifeCycle(AbstractMessageFlow* mf, TransformContext& cxt, ExceptionHandler* exceptionHandler) {
			this->mf = mf;
			mf->onStartMesageFlow(cxt, exceptionHandler);
		}
		~MessageFlowLifeCycle() {
			mf->onEndMesageFlow();
		}
	};
	Result<ObjectList> run2(const ObjectList& processArgs, TransformContext& cxt);
	friend class MessageFlowLifeCycle;

protected:
	virtual ObjectList run0(const ObjectList& processArgs, TransformContext& cxt) = 0;
	virtual DataObjectVal run0(const DataObjectVal& processArgs, TransformContext& cxt) = 0;

protected:
	virtual AbstractDataObject* getVariables() = 0;
	TransformContext* getDefaultTransformContext() {
		return transformContext;
	}
public:
	ObjectList run(const ObjectList& processArgs, TransformContext& cxt);

	ObjectList run(InputSource& input, TransformContext& cxt);

	Result<DataObjectVal> run2(const DataObjectVal& input, TransformContext& cxt);

	DataObjectVal run(const DataObjectVal& input, TransformContext& cxt);

private:
	//DataObjectVal prepareOutput(const ObjectList& outputArray);

private:
	//ObjectList prepareInput(const DataObjectVal& input);

protected:
	void ensureVariableNotNull(int index);

	template <class T>
		void handleExceptionResult(Result<T> result){
			if (result.hasException()) {
				throw TransformException(result.getExceptions());
			}
		}
		void handleExceptionResult(ExceptionList&  exceptions);

		void handleException(Exception& e);

		void onException(TransformException& e);

public:
	ExceptionHandler* getExceptionHandler() {
		return exceptionHandler;
	}

	void setExceptionHandler(ExceptionHandler* exceptionHandler) {
		this->exceptionHandler = exceptionHandler;
	}

	Message lookupMessage(const vstring& name);

	ExternalMessage lookupExternalMessage(const vstring& name);
	InternalMessage lookupInternalMessage(const vstring& name);

	MessageMapping lookupMessageMapping(const vstring& name);

	MessageFlow lookupMessageFlow(const vstring& name);


	OutputProtocol lookupOutputProtocol(const vstring& name);

	void trace(const vstring& str) {
		//log.trace(str);
	}

	void activityEnteredTrace(const vstring& activityName, const vstring& label);
	void activityEnteredTrace(const char* activityName, const char* label);

	DeviceInfo createDeviceInfo(const vstring& deviceName, TransformContext& cxt);
	void sendToDevice(const vstring& protocolName, const vstring& deviceName, const Binary& rawOut, TransformContext& cxt);
protected:
	Object* invokeCustomExternalClass(const vstring& className, const ObjectList& args, TransformContext& cxt)  {
			IInvokable* invokable = customExternalClassSupport.getCustomObject(className);
			return invokable->run(args, cxt);
	}
private:
	CustomClassSupport<IInvokable> customExternalClassSupport;
};

VOLANTE_NAMESPACE_END

#endif //__ABSTRACTMESSAGEFLOW_H__
