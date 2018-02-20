#ifndef __HANDLER_H__
#define __HANDLER_H__
#include "cp.h"
#include "Object.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "LogFactory.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT InitializationException : public TransformException{
public:
	InitializationException(const vstring& message) : TransformException(message){
	}
};

class CommandProcessorContext;
class VOLANTE_CP_EXPORT Handler : public Object {
public:
	static vstring HOME_DIRECTORY;
	static Logger log;

public:
	virtual void init(Properties& props, CommandProcessorContext& cxt) = 0;
	/**
	* Called by the command processor to inform
	* this handler that it should start its execution. It is called after
	* the <code>init</code> method was successful(if it does not THROW_EXCEPTION(an exception).)

	* <p>
	* A subclass of <code>Handler</code> should override this method to start
	* Input/Output operations. For example, a FIXInputHandler 
	* will start listening for fix messages.
	*
	* @see     Handler#init
	* @see     Handler#stop()
	*/
	virtual void start() =  0;

	/**
	* Called by the command processor to inform
	* this handler that it should stop its execution. It is called when command 
	* processor exits or when an handler is removed (not yet implemented).
	* <p>
	* A subclass of <code>Handler</code> should override this method if
	* it has any cleanup operation that it wants to perform. For example, the FixInputHandler
	* might stop listening for FIX messages. 
	* @see     Handler#init
	* @see     Handler#start()
	*/
	virtual void stop() =  0;


protected:


	static vstring getPropertyNoNull(Properties& props, const vstring& name);
};

VOLANTE_NAMESPACE_END

#endif //__HANDLER_H__

