#ifndef __SIACCanonicalSIACOUTPUTFORMAT_H__
#define __SIACCanonicalSIACOUTPUTFORMAT_H__
#include "AbstractOutputFormat.h"
#include "SIACCanonicalOutputWriter.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT SIACCanonicalSIACOutputFormat : public AbstractOutputFormat {
public:
	SIACCanonicalSIACOutputFormat();
	~SIACCanonicalSIACOutputFormat();
	//void write(NormalizedObject* no, TransformContext& tcxt);
	//virtual OutputWriter* getOutputWriter()  = 0;
};

VOLANTE_NAMESPACE_END

#endif //__SIACCanonicalSIACOUTPUTFORMAT_H__
