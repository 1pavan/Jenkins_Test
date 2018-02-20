#ifndef __MEMORYOUTPUTDEVICE_H__
#define __MEMORYOUTPUTDEVICE_H__
#include "OutputDevice.h"

VOLANTE_NAMESPACE_BEGIN

#define MaxOf(a, b) (a > b) ? (a) : (b)
/**
 *  Stores the output in memory. Use it conjuction with ContextOutputProtocol.
 *  @see  ContextOutputProtocol
 */
class VOLANTE_EXPORT ByteArrayOutputDevice : public AbstractOutputDevice {
public:
	ByteArrayOutputDevice(const DeviceInfo& info, int length) : AbstractOutputDevice(info){
		buffer = new char[length + 1];
		bufferLength = length;
		size = 0;
	}
	ByteArrayOutputDevice(const DeviceInfo& info) : AbstractOutputDevice(info){
		buffer = NULL;
		bufferLength = 0;
		size = 0;

	}

	~ByteArrayOutputDevice() {
		delete[] buffer;
	}
	virtual void write(const char* data, int length) {
		if(bufferLength - size < length) {
			expand(length);
		}
		memcpy(buffer + size, data, length);
		size += length;
	}
	virtual void close() {
	}
	void clear() {
		delete[] buffer;
		buffer = NULL;
		bufferLength = 0;
		size = 0;
	}

	/**
	 *  Returns the output as char array. The return array should not be deleted by the caller.
	 */
	const char* getAsBytes(int& length) {
		if(buffer == NULL) {
			length = 0;
			return "";
		}
		buffer[size]=0;
		length = size;
		return buffer;
	}

	/**
	 *  Returns the output as char array. The return array should not be deleted by the caller.
	 */
	char* getAsString(int& length) {
		if(buffer == NULL) {
			length = 0;
			return const_cast<char*>("");
		}
		buffer[size]=0;
		length = size;
		return buffer;
	}

	/**
	 *  Returns the output as char array. The return array should not be deleted by the caller.
	 *  To get the length of the array use getLength()
	 */
	char* getAsString() {
		if(buffer == NULL) {
			return const_cast<char*>("");
		}
		buffer[size]=0;
		return buffer;
	}
	/**
	 *  Returns the length of the output.
	 */
	int getLength() {
		return size;
	}	

private:
	void expand(int length) {
		int newLength = MaxOf(bufferLength * 2, size + length + 1);
		char* newBuffer = new char[newLength];
		if(buffer != NULL) {
			memcpy(newBuffer, buffer , size);
			delete[] buffer;
		}
		buffer = newBuffer;
		bufferLength = newLength; 
	}

private:
	char* buffer;
	int size;
	int bufferLength;
};
typedef ByteArrayOutputDevice MemoryOutputDevice;

VOLANTE_NAMESPACE_END

#endif //__MEMORYOUTPUTDEVICE_H__

