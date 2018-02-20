#ifndef __OUTPUTPROTOCOL_H__
#define __OUTPUTPROTOCOL_H__
#include "OutputDevice.h"
#include "OutputDeviceFactory.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT IOutputProtocol : public ObjectRef {
public:
	virtual OutputDevice* createDevice(DeviceInfo& info, TransformContext& cxt) =0; 
};
typedef SmartPtr<IOutputProtocol> OutputProtocol;

VOLANTE_NAMESPACE_END

#endif //__OUTPUTPROTOCOL_H__
