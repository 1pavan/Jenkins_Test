#ifndef __LOGGINGCONSTANTS_H__
#define __LOGGINGCONSTANTS_H__
#include "LogFactory.h"
VOLANTE_NAMESPACE_BEGIN
class VOLANTE_EXPORT LoggingConstants {
public:
	static vstring ROOT_CATEGORY;
	static vstring MESSAGE_FLOW_CATEGORY;
	static vstring MESSAGE_CATEGORY;
	static vstring MAPPING_CATEGORY;
	static Logger getMessageFlowLog(vstring messageFlowName);

	static Logger getMessageLog(vstring messageName);
	static Logger getMappingLog(vstring mappingName);

	static Logger getRuntimeLog();
};

VOLANTE_NAMESPACE_END

#endif //__LOGGINGCONSTANTS_H__
