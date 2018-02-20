#ifndef __OUTPUTCONTEXT_H__
#define __OUTPUTCONTEXT_H__
#include "MemoryOutputDevice.h"

VOLANTE_NAMESPACE_BEGIN

/**
 *  Used to return output to client through the transform context.
 *  
 *
 *   <pre>
 * 
 *          TransformContext cxt;
 * 			cxt.clear();
			cxt.createOutputContext();
			cxt.setProperty(TransformContext::OUTPUT_FORMAT_PROPERTY ,"CanonicalException");
			cxt.setProperty(TransformContext::INPUT_SOURCE_PROPERTY , "XXX");
			cxt.setProperty(TransformContext::OUTPUT_DEVICE_PROPERTY ,outputDeviceExceptionOut);
			InputFormat inFmt = lcxt->lookupInputFormat("formatName");
			inFmt->processMessage(source, cxt);
			// A trigger in cartridge writes output to a device named 'myoutputdevice'
			if(MemoryOutputDevice* outputDevice = cxt.getOutputContext()->getOutputDevice("myoutputdevice")) {
                int len;	
                vstring outMsg = outputDevice->getAsString(len);
			}
 *  </pre>
 *
 *  @see TransformContext#createOutputContext
 *
 *
 *
 */
class VOLANTE_EXPORT IOutputContext : public ObjectRef {
public:

	/**
     *  Get the output device with the specified name. A event handler in the cartridge should have been configured to
     *  write to this device. This method should be called from the client after message processing is completed.
     */
	virtual ByteArrayOutputDevice* getOutputDevice(const vstring& name) const = 0;
	
	/**
     *  Returns the number of output devices bound to this output context.
	 *  This method should be called from the client after message processing is completed.
     */
	virtual int getOutputCount() const = 0;
	/**
     *  Returns the names of output devices bound to this context.
     *  You can use these name as parameter to getOutputDevice(). Normally 
     *  you would know the name of output device (configured in Designer) in which the output will be written.
     *  This method is a generic alternative.
	 *  This method should be called from the client after message processing is completed.
     */
	virtual StringList getOutputNames() const = 0;

	/**
     *  Removes all the output devices bound to this context. This is automatically called 
     *  when you clear the TransformContext.
     */
	virtual void clear() = 0;


    virtual ByteArrayOutputDevice* createOutputDevice(const DeviceInfo& deviceInfo)  = 0;
    typedef std::vector<ByteArrayOutputDevice*> OutputDevices;
    virtual const OutputDevices& getOutputDevices() const = 0;

};

typedef std::vector<MemoryOutputDevice*> OutputDevices;

class VOLANTE_EXPORT IOutputContextImpl : public IOutputContext {
public:
    ByteArrayOutputDevice* createOutputDevice(const DeviceInfo& deviceInfo);
    const OutputDevices& getOutputDevices() const ;
	ByteArrayOutputDevice* getOutputDevice(const vstring& name) const ;
	int getOutputCount()const ;
	StringList getOutputNames()const ;
	void clear();
	~IOutputContextImpl();
private:
	void bind(const vstring& name, ByteArrayOutputDevice*  outputDevice);
	OutputDevices outputDevices;

};


typedef SmartPtr<IOutputContext> OutputContext;

VOLANTE_NAMESPACE_END

#endif //__OUTPUTCONTEXT_H__
