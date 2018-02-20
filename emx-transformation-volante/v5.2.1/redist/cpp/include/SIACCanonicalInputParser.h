#ifndef __SIACCanonicalINPUTPARSER_H__
#define __SIACCanonicalINPUTPARSER_H__
#include "AbstractDataObject.h"
#include "Exceptions.h"
#include "SIACCanonicalException.h"
#include "SIACCanonicalType.h"
#include "TransformContext.h"
#include "ExternalObject.h"
#include "InputParser.h"

VOLANTE_NAMESPACE_BEGIN

#define  CFT_EndInstance_TAG    26999
#define  CFT_EndGroup_TAG 		26000

class VOLANTE_EXPORT SIACCanonicalInputParser : public InputParser  {
public:

protected:
	SIACCanonicalInputParser() {
	}
	~SIACCanonicalInputParser() {
	}
protected:
	void missingTag(const vstring& value, int tag);
	void missingTag(int tag);

	void assertNotNull(AbstractDataObject* object, int index, int tag);
	void assertConstraints(AbstractDataObject* object, int index, int tag);
	void assertTagNew(AbstractDataObject* object, int index, int tag);
	
	void assertSectionEmpty(DataObjectSection* section, int tag);
	
	
	void ensureNotNull(const vstring& value, DataObject* object, int index);

	void ensureNotNull(const vstring& value, vstring fldName);

	bool isNull(const vstring& value)  {
        if(value.length() == 0) {
			return true;
        }
		return false;
	}
};

VOLANTE_NAMESPACE_END

#endif //__SIACCanonicalINPUTPARSER_H__

