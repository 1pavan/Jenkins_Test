#ifndef __OUTPUTPROTOCOLDEVICEFACTORY_H__
#define __OUTPUTPROTOCOLDEVICEFACTORY_H__
#include "OutputDevice.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT IOutputDeviceFactory : public ObjectRef {
public:
	virtual OutputDevice* createDevice(DeviceInfo& info) =0; 
};
typedef SmartPtr<IOutputDeviceFactory> OutputDeviceFactory;

VOLANTE_NAMESPACE_END

#endif //__OUTPUTPROTOCOLDEVICEFACTORY_H__
