#ifndef __TervelaFieldDef_H__
#define __TervelaFieldDef_H__
#include "AbstractDataObject.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "TransformContext.h"
#include "ExternalObject.h"
#include "InputParser.h"

VOLANTE_NAMESPACE_BEGIN


class TervelaFieldDef {
    public:
	 TervelaFieldDef(const vstring& name, const vstring& type, bool optional) {
        this->name = name;
        this->type = type;
        this->optional = optional;
    }


    const vstring& getName() {
        return name;
    }

    const vstring& getType() {
        return type;
    }

    bool isOptional() {
        return optional;
    }

    TVA_UINT16 getFieldId() {
        return fieldId;
    }

    void setFieldId(TVA_UINT16 fieldId) {
        this->fieldId = fieldId;
    }

    private:
	vstring name;
    vstring type;
    bool optional;
    TVA_UINT16 fieldId;
};


class TervelaRawMessage : public AbstractRawMessage {
public:
	TervelaRawMessage(TVA_MESSAGE_DATA_HANDLE msgData) {
		this->msgData = msgData;
	}
	const char* getAsBytes(int& length) {
		return "";
	}
	TVA_MESSAGE_DATA_HANDLE getMessage() {
		return msgData;
	}
	TVA_MESSAGE_DATA_HANDLE msgData;
};

VOLANTE_NAMESPACE_END

#endif //__TervelaFieldDef_H__

