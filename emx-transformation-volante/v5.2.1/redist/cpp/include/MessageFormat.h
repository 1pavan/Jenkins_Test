#ifndef __MESSAGEFORMAT_H__
#define __MESSAGEFORMAT_H__

#include "Object.h"
#include "Exceptions.h"
#include "FormatFunctions.h"

VOLANTE_NAMESPACE_BEGIN

class MessageFormat {
public:
	static vstring format(const vstring& pattern, const ObjectList& params);
};

VOLANTE_NAMESPACE_END


#endif //__MESSAGEFORMAT_H__

