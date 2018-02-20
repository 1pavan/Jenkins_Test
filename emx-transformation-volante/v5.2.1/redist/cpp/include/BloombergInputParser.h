#ifndef __BLOOMBERGINPUTPARSER_H__
#define __BLOOMBERGINPUTPARSER_H__
#include "AbstractDataObject.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "TransformContext.h"
#include "ExternalObject.h"
#include "InputParser.h"
#include "BloombergLP/MDSI.h"
#include "BloombergLP/BDD.h"
#include <time.h>

VOLANTE_NAMESPACE_BEGIN

class BloombergInputParser : public InputParser  {
protected:
	BloombergInputParser() {
	}
	~BloombergInputParser() {
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
	bool checkResult(BloombergLP::SDMessage::Result result, const BloombergLP::Field*& field) {
		if(result >= 0) {
			return true;
		}
		if(result == BloombergLP::SDMessage::Result::ERROR_NOT_PRESENT) {
			return false;
		}
		if(result == BloombergLP::SDMessage::Result::ERROR_BAD_TYPE) {
			throw TransformException("Type conversion error for field " + vstring(field->name()) + ", expected type " + intToString(field->type()));
			//return false;
		}
		if(result == BloombergLP::SDMessage::Result::ERROR_BAD_FIELD) {
			field = 0;
		}
		throw TransformException("Error getting field " +  vstring(field->name()));
	}
public:
    const BloombergLP::Field* getBloombergField(const char *name)
    {
			const BloombergLP::DataDictionary *dd = BloombergLP::GetDataDictionary();
				if (0 == dd)
				{
            throw std::runtime_error("Data dictionary missing");
				}
        const BloombergLP::Field* fieldPtr = dd->field(name);
        if(!fieldPtr) {
            throw std::runtime_error(name);
        }

        return fieldPtr;
    }
    const BloombergLP::Field* getBloombergFieldOptional(const char *name)
    {
			const BloombergLP::DataDictionary *dd = BloombergLP::GetDataDictionary();
				if (0 == dd)
				{
            throw std::runtime_error("Data dictionary missing");
				}
        const BloombergLP::Field* fieldPtr = dd->field(name);
        return fieldPtr;
    }
		DateTime toDateTime(time_t time, unsigned int millis = 0) {
			struct tm* ptm = gmtime( &time );
			return DateTime(ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, millis);
		}
		DateTime toDate(int years, int month, int date) {
			return DateTime(years, month, date, 0, 0, 0);
		}
		vstring constantToValue(const BloombergLP::Constant *cons) {
				return cons->name();
		}
};


class BloombergSDRawMessage : public AbstractRawMessage {
public:
	BloombergSDRawMessage(const BloombergLP::SDMessage *sdMsg) {
		this->sdMsg = sdMsg;
	}
	const char* getAsBytes(int& length) {
		return "";
	}
	const BloombergLP::SDMessage * getSDMessage() {
		return sdMsg;
	}
	const BloombergLP::SDMessage *sdMsg;
};

VOLANTE_NAMESPACE_END



#endif //__BLOOMBERGINPUTPARSER_H__
