#ifndef __SIACCanonicalOUTPUTFORMAT_H__
#define __SIACCanonicalOUTPUTFORMAT_H__
#include "AbstractOutputFormat.h"
#include "SIACCanonicalOutputWriter.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT SIACCanonicalOutputFormat : public AbstractOutputFormat {
public:
	SIACCanonicalOutputFormat();
	~SIACCanonicalOutputFormat();
};

VOLANTE_NAMESPACE_END


#endif //__SIACCanonicalOUTPUTFORMAT_H__
