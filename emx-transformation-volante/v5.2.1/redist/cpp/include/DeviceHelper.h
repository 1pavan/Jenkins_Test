#ifndef __DEVICEHELPER_H__
#define __DEVICEHELPER_H__
#include <vector>
#include <map>
#include <string>

VOLANTE_NAMESPACE_BEGIN

class DeviceHelper {
  ObjectMap<ContextOutputProtocol*> devices;
	LookupContext cxt;
public:
	DeviceHelper(MessageFlow messageFlow, LookupContext cxt) {
		  this->cxt = cxt;
			IMessageFlow::OutputPortList ports = messageFlow->getOutputPorts();
			for(IMessageFlow::OutputPortList::iterator it = ports.begin(); it != ports.end(); ++it) {
				OutputPortDef def = *it;
				vstring protocol = def.getProtocol();
				vstring device = def.getOutputDevice();
				ContextOutputProtocol* cxtProtocol = new ContextOutputProtocol();
				cxt->bind(device, cxtProtocol);
				devices.put(device, cxtProtocol);
			}
	}
	~DeviceHelper() {
			for(ObjectMap<ContextOutputProtocol*>::iterator it2 = devices.begin(); it2 != devices.end(); ++it2) {
				vstring outputDevice = it2->first;
				ContextOutputProtocol* proto = devices.get(outputDevice);
				cxt->unbind(outputDevice);
			}
	}
	void populateResult(TransformContext& tcxt, OutputMap& result)  {
		OutputContext outcxt = tcxt.getOutputContext();
		const OutputDevices& outputDevices = outcxt->getOutputDevices();
		for(OutputDevices::const_iterator it = outputDevices.begin();it != outputDevices.end(); ++it) {
			ByteArrayOutputDevice* bs = *it;
			const DeviceInfo& info = bs->getDeviceInfo();
			vstring name = info.getDeviceName();
			int length;
			const char* bytes = bs->getAsString(length);
			vstring toPut(bytes, length);
			OutputMap::iterator foundIt = result.find(name);
			if(foundIt != result.end()) {
				vstring existingData = foundIt->second;
				toPut = existingData + "\n-------------------------------------------\n" + toPut;
				result.erase(foundIt);
			}
			result.insert(OutputMap::value_type(name, toPut));
		}
	}
};

VOLANTE_NAMESPACE_END


#endif //__DEVICEHELPER_H__
