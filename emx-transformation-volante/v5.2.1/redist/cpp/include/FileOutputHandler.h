#ifndef __FILEOUTPUTHANDLER_H__
#define __FILEOUTPUTHANDLER_H__

#include "cp.h"
#include "OutputHandler.h"


VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT FileOutputHandler : public OutputHandler {
public:
	static vstring OUTPUT_DIRECTORY;
public:
    void init(Properties& props, CommandProcessorContext& cxt);
	virtual OutputDevice* createDevice(DeviceInfo& info);
	void start();

private:
	vstring outputDir;
	vstring specifiedOutputDir;
};

VOLANTE_NAMESPACE_END

#endif //__FILEOUTPUTHANDLER_H__

