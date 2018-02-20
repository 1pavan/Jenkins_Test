#ifndef __CLIENTPROXY_H__
#define __CLIENTPROXY_H__
#include "cp.h"
extern "C" {
	int getInternalMessages(char* buffer, int bufferSize);
	int getInputFormats(char* buffer, int bufferSize);
	int getOutputFormats(char* buffer, int bufferSize);
	int getExternalMessages(char* buffer, int bufferSize);
	int getMessageMappings(char* buffer, int bufferSize);
	int getMessageFlows(char* buffer, int bufferSize);
	void submit(const char* message, int messageSize, const char* inputFormatName, const char* outputFormatName, const char* outputChannelsBuffer, int outputChannelsCount, char* outputMapBuffer, int outputMapBufferSize, int* outputCount, bool performance);
	void parseExternalMessage(const char* message, int size, const char* inputFormatName,  bool validate, bool write, char* outputMapBuffer, int outputMapBufferSize, int* outputCount, bool performance);
	void submitMessageFlowData(const char* inputs, int size, int inputCount, const char* inputFormatName,  char* outputMapBuffer, int outputMapBufferSize, int* outputCount, bool performance);
	void mapData(const char* message, int size, const char* inputFormatName,  char* outputMapBuffer, int outputMapBufferSize, int* outputCount, bool performance);
};

struct VOLANTE_CP_EXPORT DynaClient {
    int (* getInternalMessages) (char* buffer, int bufferSize);
	int (*getInputFormats)(char* buffer, int bufferSize);
	int (*getOutputFormats)(char* buffer, int bufferSize);
	int (*getExternalMessages)(char* buffer, int bufferSize);
	int (*getMessageMappings)(char* buffer, int bufferSize);
	int (*getMessageFlows)(char* buffer, int bufferSize	);
	void (*submit)(const char* message, int messageSize, const char* inputFormatName, const char* outputFormatName, const char* outputChannelsBuffer, int outputChannelsCount, char* outputMapBuffer, int outputMapBufferSize, int* outputCount, bool performance);
	void (*parseExternalMessage)(const char* message, int size, const char* inputFormatName,  bool validate, bool write, char* outputMapBuffer, int outputMapBufferSize, int* outputCount, bool performance);
	void (*submitMessageFlowData)(const char* inputs, int size, int inputCount, const char* inputFormatName,  char* outputMapBuffer, int outputMapBufferSize, int* outputCount, bool performance);
	void (*mapData)(const char* message, int size, const char* inputFormatName,  char* outputMapBuffer, int outputMapBufferSize, int* outputCount, bool performance);
	DynaClient();
};

#endif //__CLIENTPROXY_H__
