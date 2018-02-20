#ifndef __OUTPUTDEVICE_H__
#define __OUTPUTDEVICE_H__
#include "Object.h"
#include "DeviceInfo.h"

VOLANTE_NAMESPACE_BEGIN

/**
 *  Represent a device to which output can be written. 
 *  
 *
 *  @see ByteArrayOutputDevice
 *  @see DeviceInfo
 */
class VOLANTE_EXPORT OutputDevice : public Object {
public:
	virtual void write(const char* data, int length) = 0;
	virtual void close() = 0;
	virtual const DeviceInfo& getDeviceInfo() const = 0;

};

class VOLANTE_EXPORT AbstractOutputDevice : public OutputDevice {
	DeviceInfo info;
public:
	AbstractOutputDevice(const DeviceInfo& info) : info(info) {
	}
	const DeviceInfo& getDeviceInfo() const {
		return info;
	}

};


VOLANTE_NAMESPACE_END

#endif //__OUTPUTDEVICE_H__

