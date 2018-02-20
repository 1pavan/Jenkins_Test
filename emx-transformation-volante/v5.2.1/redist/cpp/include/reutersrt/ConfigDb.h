#ifndef _RFA_EXAMPLE_ConfigDb_h
#define _RFA_EXAMPLE_ConfigDb_h

#include "Common/RFA_String.h"
#include "Config/Config.h"

namespace rfa {
	namespace config {
		class ConfigDatabase;
		class StagingConfigDatabase;
		class ConfigTree;
	}
}

using namespace rfa::common;
using namespace rfa::config;

class ConfigDb
{
public:
	ConfigDb(const RFA_String & configName);
	virtual ~ConfigDb();

#ifdef WIN32
	bool initRegistry(const RFA_String & regKey);
#endif

	bool initFile(const RFA_String & configFileName);
	void cleanup();

	bool getBool(const RFA_String & variableName, bool defaultVal) const;
	const RFA_String getString(const RFA_String & variableName, const RFA_String & defaultVal) const;
	long getLong(const RFA_String & variableName, long defaultVal) const;
	const ConfigTree* getTree(const RFA_String& variableName);

protected:
	void initTree();
	bool load(ConfigRepositoryType type, const RFA_String & location);

	RFA_String _configName;
	
	ConfigDatabase *_configDatabase;
	StagingConfigDatabase *_stagingConfigDatabase;
	const ConfigTree* _configTree;
};

#endif
