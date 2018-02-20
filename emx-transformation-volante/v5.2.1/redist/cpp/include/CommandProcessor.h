#ifndef __COMMANDPROCESSOR_H__
#define __COMMANDPROCESSOR_H__

#include "cp.h"
#include "CommandProcessorContext.h"
#include "CommandProcessorConfig.h"

VOLANTE_NAMESPACE_BEGIN

class CommandProcessor;
class CommandProcessor;
class VOLANTE_CP_EXPORT CommandProcessorContextImpl : public CommandProcessorContext {
	CommandProcessorConfig* config;
public:
	CommandProcessorContextImpl(CommandProcessorConfig* config);
	Handler* getHandler(const vstring& name);
};

class VOLANTE_CP_EXPORT CommandProcessor {
private:
	vstring home;
    CommandProcessorConfig& config;
    CommandProcessorContextImpl context;
	static Logger log;
   
public:
	//CommandProcessor(const vstring& home);
	CommandProcessor(const vstring& home, CommandProcessorConfig& config);
	void init();
	void exit();
    
    void createInputHandlers();
    
    void createOutputHandlers();
    
    void startInputHandlers();
    void stopInputHandlers();
    
    void startOutputHandlers();

    void stopOutputHandlers();
   
    static void enableLogging(vstring home);
};

VOLANTE_NAMESPACE_END

#endif //__COMMANDPROCESSOR_H__

