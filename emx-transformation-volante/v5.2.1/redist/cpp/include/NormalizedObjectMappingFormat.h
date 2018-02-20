#ifndef __NORMALIZEDOBJECTMAPPINGFORMAT_H__
#define __NORMALIZEDOBJECTMAPPINGFORMAT_H__

#include "Service.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT INormalizedObjectMappingFormat : public IService {
public:
	virtual NormalizedObject* map(NormalizedObject* sourceNormalizedObject, TransformContext& tcxt) = 0;
	virtual NormalizedObject** map(NormalizedObject** sourceNormalizedObject, int length, TransformContext& tcxt) = 0;
	virtual vstring getDestinationMessageName() =0;
	virtual vstring getSourceMessageName() =0;
};

typedef SmartPtr<INormalizedObjectMappingFormat> NormalizedObjectMappingFormat;

VOLANTE_NAMESPACE_END

#endif //__NORMALIZEDOBJECTMAPPINGFORMAT_H__
