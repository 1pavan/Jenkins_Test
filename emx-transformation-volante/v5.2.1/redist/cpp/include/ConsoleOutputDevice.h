#ifndef __CONSOLEOUTPUTDEVICE_H__
#define __CONSOLEOUTPUTDEVICE_H__
#include "Outputdevice.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT ConsoleOutputDevice : public AbstractOutputDevice {
public:
	ConsoleOutputDevice(const DeviceInfo& info) : AbstractOutputDevice(info) {

	}
	~ConsoleOutputDevice() {
	}

	virtual void write(const char* data, int length) {
		fwrite(data, length, 1, stdout);
	}
	virtual void close() {
	}
	void clear() {
	}
	const DeviceInfo& getDeviceInfo() {
		return info;
	}

};
VOLANTE_NAMESPACE_END

#endif //__CONSOLEOUTPUTDEVICE_H__

