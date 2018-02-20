#ifndef __FIXINPUTPARSER_H__
#define __FIXINPUTPARSER_H__
#include "AbstractDataObject.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "FIXException.h"
#include "FIXType.h"
#include "TransformContext.h"
#include "ExternalObject.h"
#include "InputParser.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FIXInputParser : public InputParser  {
protected:
	FIXInputParser() {
	}
	~FIXInputParser() {
	}
public:

protected:
	void missingTag(const vstring& value, int tag);
	void missingTag(int tag);

	void assertNotNull(AbstractDataObject* object, int index, int tag);
	void assertConstraints(AbstractDataObject* object, int index, int tag);
	void assertTagNew(AbstractDataObject* object, int index, int tag) {
		if(object->isNotNull(index)) {
			throwDuplicateTagException(object, index, tag);
		}
	}
	void throwDuplicateTagException(AbstractDataObject* object, int index, int tag);
	
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

#endif //__FIXINPUTPARSER_H__

