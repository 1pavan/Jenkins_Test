#ifndef __FILEINPUTSOURCE_H__
#define __FILEINPUTSOURCE_H__

#include "AbstractRawMessage.h"
VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FileInputSource : public AbstractRawMessage {
public:
	FileInputSource(const vstring& fileName);
	~FileInputSource();
	const char* getAsBytes(int& length);
private:
	int length;
	char* source;
};

VOLANTE_NAMESPACE_END

#endif //__FILEINPUTSOURCE_H__
