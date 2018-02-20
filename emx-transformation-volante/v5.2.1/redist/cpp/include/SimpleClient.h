#ifndef __SIMPLECLIENT_H__
#define __SIMPLECLIENT_H__
#include "cp.h"

VOLANTE_NAMESPACE_BEGIN

//typedef std::vector<vstring> StringArray;
typedef std::map<vstring, vstring> OutputMap;
typedef std::map<vstring, vstring> InputMap;
typedef std::map<vstring, vstring> StringMap;

class VOLANTE_CP_EXPORT SimpleClient {
public:
	void submit(const char* message, int size, const vstring& inputFormat, const vstring& outputFormat, const StringList& outputChannels, OutputMap& outputMap, bool performance);
	void parseExternalMessage(const char* message, int size, const vstring& inputFormat, bool validate, bool write, OutputMap& outputMap, bool performance);
	void submitMessageFlowData(InputMap& inputMap, const vstring& inputFormat, OutputMap& outputMap, bool performance);
	void mapData(const char* message, int size, const vstring& inputFormat, OutputMap& outputMap, bool performance);

    StringList getExternalMessages();
    StringList getMessageMappings();
    StringList getMessageFlows();
    StringList getInternalMessages();
    StringList getInputFormats();
    StringList getOutputFormats();

};

VOLANTE_NAMESPACE_END

#endif //__SIMPLECLIENT_H__
