#ifndef __ABSTRACTMESSAGEMAPPING_H__
#define __ABSTRACTMESSAGEMAPPING_H__
#include "MessageMapping.h"

VOLANTE_NAMESPACE_BEGIN
class VOLANTE_EXPORT AbstractMessageMapping : public IMessageMapping {
public:
	AbstractMessageMapping(const vstring& mappingName);

public:
	vstring getSourceMessageName();

	void setSourceMessageName(vstring sourceMessageName);

	vstring getDestinationMessageName();


	void setDestinationMessageName(vstring destinationMessageName);
	MappingInfo* getMappingInfo();

private:
	vstring mappingName;
protected:
	vstring sourceMessageName;
	vstring destinationMessageName;
};

VOLANTE_NAMESPACE_END

#endif //__ABSTRACTMESSAGEMAPPING_H__
