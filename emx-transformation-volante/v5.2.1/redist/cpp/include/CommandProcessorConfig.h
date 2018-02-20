#ifndef __COMMANDPROCESSORCONFIG_H__
#define __COMMANDPROCESSORCONFIG_H__
#include "cp.h"
#include "Transform.h"
#include "LogFactory.h"
/*
*  CommandProcessorConfig.h
*
*  © Copyright 2001-2003 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/


VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT HandlerConfig : public  Object {
public:
	HandlerConfig(const vstring& name, const vstring& className);

	vstring getName();

	vstring  getHandlerClass();

	vstring toString() const;

	Object* newInstance();
	vstring name;
	vstring className;
};
class InputHandler;
class VOLANTE_CP_EXPORT InputHandlerConfig : public HandlerConfig {
public :    
	InputHandlerConfig(const vstring& name, const vstring& className);

	InputHandler* newInputHandler();
};
class OutputHandler;
class VOLANTE_CP_EXPORT OutputHandlerConfig : public HandlerConfig {
public:
	OutputHandlerConfig(const vstring& name, const vstring& className);

	OutputHandler* newOutputHandler();
};
class VOLANTE_CP_EXPORT DefConfig : public Object {
public:
	enum {
		NO_MATCH = 0,
		MODIFIED = 1,
		SAME = 2
	};

	DefConfig(const vstring& name, const vstring& handlerType);

	vstring getName();

	vstring getHandlerType();

	Properties& getProperties();
	void setProp(const vstring& name, const vstring& value);

	vstring toString() const;
	/*
	int compare(DefConfig toCompare) {
	if(name != toCompare.name) {
	return NO_MATCH;
	}
	if(handlerType == toCompare.handlerType) {
	if(props == toCompare.props) {
	return SAME;
	}
	}
	return MODIFIED;
	}*/
private:
	vstring name;
	vstring handlerType;
	Properties props;
};
class VOLANTE_CP_EXPORT InputDefConfig : public DefConfig {

public:
	InputDefConfig(const vstring& name, const vstring& handlerType);

	void setInputHandler(InputHandler* handler);

	InputHandler* getInputHandler();

	InputDefConfig* setProperty(const vstring& name, const vstring& value);
	Properties getContextProperties();
private:
	InputHandler* handler;
	Properties contextProps;
};

class VOLANTE_CP_EXPORT OutputDefConfig : public DefConfig {
public:
	OutputDefConfig(const vstring& name, const vstring& handlerType);

	void setOutputHandler(OutputHandler* handler);
	OutputDefConfig* setProperty(const vstring& name, const vstring& value);

	OutputHandler* getOutputHandler();
private:
	OutputHandler* handler;
};

typedef std::vector<InputDefConfig*> InputDefConfigs;
typedef std::vector<OutputDefConfig*> OutputDefConfigs;
class VOLANTE_CP_EXPORT CommandProcessorConfig {
	static Logger log;
	ObjectPtrMap<InputHandlerConfig> inputHandlers;
	ObjectPtrMap<OutputHandlerConfig> outputHandlers;
	ObjectPtrMap<InputDefConfig> inputDefs;
	ObjectPtrMap<OutputDefConfig> outputDefs;
public:
	void addInputHandler(InputHandlerConfig* handler);
	void addOutputHandler(OutputHandlerConfig* handler);

	void addInputDef(InputDefConfig* def) ;

	void addOutputDef(OutputDefConfig* def);

	InputDefConfigs getInputDefs();

	OutputDefConfigs getOutputDefs();

	OutputHandlerConfig* getOutputHandlerConfig(const vstring& name);

	InputHandlerConfig* getInputHandlerConfig(const vstring& name);
};

////////////////////////////////////////////////////////////////////
#define COMMAND_PROCESSOR_BEGIN  CommandProcessorConfig& getCommandProcessorConfig() { static CommandProcessorConfig cpconfig;


#define COMMAND_PROCESSOR_END	return cpconfig; }



#define INPUT_HANDLER(name, className) \
	USING_CLASS(className) \
	cpconfig.addInputHandler(new InputHandlerConfig(#name, #className));

#define OUTPUT_HANDLER(name, className) \
	USING_CLASS(className) \
	cpconfig.addOutputHandler(new OutputHandlerConfig(#name, #className));

#define INPUT_HANDLER_DEF_BEGIN(name, type) \
{										\
	InputDefConfig* def =new InputDefConfig(#name, #type);


#define INPUT_HANDLER_DEF_END cpconfig.addInputDef(def);  }										

#define OUTPUT_HANDLER_DEF_BEGIN(name, type) \
{										\
	OutputDefConfig * def = new OutputDefConfig(#name, #type);


#define OUTPUT_HANDLER_DEF_END cpconfig.addOutputDef(def); }										

#define PROPERTY(name, value) \
	def->setProperty(name, value);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VOLANTE_NAMESPACE_END

#endif //__COMMANDPROCESSORCONFIG_H__
