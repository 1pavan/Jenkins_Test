
#ifndef __CONTEXTOUTPUTPROTOCOL_H__
#define __CONTEXTOUTPUTPROTOCOL_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT ContextOutputProtocol : public IOutputProtocol {
public:
	OutputDevice* createDevice(DeviceInfo& info, TransformContext& cxt) {
		OutputContext outputContext = cxt.getOutputContext();
		OutputDevice* device = outputContext->createOutputDevice(info);
		return device;
	}
};

VOLANTE_NAMESPACE_END

#endif //__CONTEXTOUTPUTPROTOCOL_H__
