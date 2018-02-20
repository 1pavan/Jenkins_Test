#ifndef __DEVICEINFO_H__
#define __DEVICEINFO_H__

VOLANTE_NAMESPACE_BEGIN

/** 
 * Provides additional information about a output device and the message that was written to it.
 * @see ByteArrayOutputDevice
 * @see OutputDevice
 */
class VOLANTE_EXPORT DeviceInfo {
public:
	DeviceInfo(const vstring& deviceName,	const vstring& messageIdentifier, const vstring& outputFormatName) 
		: deviceName(deviceName), 
		  messageIdentifier(messageIdentifier),  
		  outputFormatName(outputFormatName) {
	}
	DeviceInfo(const DeviceInfo& info)
		: deviceName(info.deviceName), 
		  messageIdentifier(info.messageIdentifier),  
		  outputFormatName(info.outputFormatName) {
		
	}
	/** 
     *  Name of this device
     */
	vstring getDeviceName() const {
		return deviceName;
	}
	/** 
     *  Name of input message (TransformContext::INPUT_SOURCE_NAME) that resulted in this output.
	 *
     */
	vstring getMessageIdentifier() const {
		return messageIdentifier;
	}
	/** 
     *  Name of the output format (as defined in Designer) that wrote this message.
	 *
     */
	vstring getOutputFormatName() const {
		return outputFormatName;
	}
private:
	vstring deviceName;
	vstring messageIdentifier;
	vstring outputFormatName;
};

VOLANTE_NAMESPACE_END

#endif //__DEVICEINFO_H__
