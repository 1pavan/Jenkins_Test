#ifndef __TervelaINPUTPARSER_H__
#define __TervelaINPUTPARSER_H__
#include "AbstractDataObject.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "TransformContext.h"
#include "ExternalObject.h"
#include "InputParser.h"
#include "tvaClientAPIInterface.h"
#include "TervelaFieldDef.h"

VOLANTE_NAMESPACE_BEGIN




class TervelaInputParser : public InputParser  {
protected:
	TervelaInputParser() {
		initialized = false;
	}
	~TervelaInputParser() {
	}
public:
	bool initialized;
protected:


	void fieldError(DataObject* object, int index, int erroCode) {

	}	
	bool isNull(const vstring& value)  {
        if(value.length() == 0) {
			return true;
        }
		return false;
	}
    void parseData(ExternalObject *,const Binary &, TransformContext &) {}

   	ExternalObject * parseData(const Binary &, TransformContext &) {
		return NULL;
	}
	void TervelaInputParser::parse(ExternalObject* externalObject, InputSource& input, TransformContext& cxt) {
	    DataObject* header= externalObject->getHeader();
	    DataObject* data= externalObject->getData();
	    DataObject* trailer= externalObject->getTrailer();
	    TervelaRawMessage* rawMessage = polymorphic_cast<TervelaRawMessage*>(&input);
	    TVA_MESSAGE_DATA_HANDLE tervelaMessage = rawMessage->getMessage();
		parseHeader(header, tervelaMessage, cxt);
		parseRecordData(header, tervelaMessage, cxt);
		parseTrailer(header, tervelaMessage, cxt);
	}
	virtual void parseHeader(DataObject* dobj, TVA_MESSAGE_DATA_HANDLE tervelaMessage, TransformContext& cxt) =0; 
	virtual void parseRecordData(DataObject* dobj, TVA_MESSAGE_DATA_HANDLE tervelaMessage, TransformContext& cxt)=0; 
	virtual void parseTrailer(DataObject* dobj, TVA_MESSAGE_DATA_HANDLE tervelaMessage, TransformContext& cxt)=0;
	public:
		TVA_STATUS getIntFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_INT32* fieldValue) {
	    	return tvaGetIntFromMessageByFieldId(tervelaMessage, fieldId, fieldValue);
		}
		TVA_STATUS getLongFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_INT64* fieldValue) {
	    	return tvaGetLongFromMessageByFieldId(tervelaMessage, fieldId, fieldValue);
		}
		TVA_STATUS getFloatFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_FLOAT* fieldValue) {
	    	return tvaGetFloatFromMessageByFieldId(tervelaMessage, fieldId, fieldValue);
		}
		TVA_STATUS getDoubleFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_DOUBLE* fieldValue) {
	    	return tvaGetDoubleFromMessageByFieldId(tervelaMessage, fieldId, fieldValue);
		}
		TVA_STATUS getShortFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_INT16* fieldValue) {
	    	return tvaGetShortFromMessageByFieldId(tervelaMessage, fieldId, fieldValue);
		}
		TVA_STATUS getStringFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, vstring* fieldValue) {
			char* buffer;
	    	TVA_STATUS status = tvaGetStringFromMessageByFieldId(tervelaMessage, fieldId, &buffer);
			if(status == TVA_OK) {
				*fieldValue = buffer;
			}
			return status;
		}

		TVA_STATUS getBytesFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, Binary* fieldValue) {
			TVA_UINT8* buffer;
			TVA_UINT32 fieldLength;
	    	TVA_STATUS status = tvaGetBytesFromMessageByFieldId(tervelaMessage, fieldId, &buffer, &fieldLength);
			if(status == TVA_OK) {
				(*fieldValue).assign((vbyte*)buffer, fieldLength);
			}
			return status;
		}

		TVA_STATUS getByteFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_UINT8* fieldValue) {
	    	return tvaGetByteFromMessageByFieldId(tervelaMessage,fieldId, fieldValue);
		}
		TVA_STATUS getDateTimeFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_DATE* fieldValue) {
	    	return tvaGetDateTimeFromMessageByFieldId(tervelaMessage,fieldId, fieldValue);
		}
		TVA_STATUS getBooleanFromMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_BOOLEAN* fieldValue) {
	    	return tvaGetBooleanFromMessageByFieldId(tervelaMessage,fieldId, fieldValue);
		}

    static vstring toString(const Binary& bytes) {
        return bytes.toString();
    }
    static short toShort(int value ) {
        return (short) value;
    }
    static TVA_UINT8 toByte(int value ) {
        return (TVA_UINT8) value;
    }
    static char toChar(int value ) {
        return (char) value;
    }
    static char toChar(TVA_UINT8 value ) {
        return (char) value;
    }
    static bool toBoolean(TVA_BOOLEAN value ) {
        return value != 0;
    }
    static DateTime toDate(TVA_DATE& value ) {
		static DateTime UNIX_EPOCH(Date(1970, 1, 1), Time());
		dlong time = value.timeInMicroSecs;
		bool negative = time < 0;
		time = time < 0 ? -time : time;
		dlong seconds = time/1000000;
		int millis = (int)((time/1000) % 1000);
		TimeSpan diff(seconds, millis);
		DateTime toRet = negative ? (UNIX_EPOCH - diff): (UNIX_EPOCH + diff);
		return toRet;
	}

    virtual TervelaFieldDef** getAllFieldDefs(int& count);
    void initialize(TVA_MESSAGE_DATA_HANDLE message)  {
        if(!initialized) {
			int count;
            TervelaFieldDef** tervelaFieldDefs = getAllFieldDefs(count);
            for (int i = 0; i < count; i++) {
                TervelaFieldDef* tervelaFieldDef = tervelaFieldDefs[i];
				TVA_UINT16 fieldId;	
				tvaGetFieldIDFromFieldName(message, (char*)tervelaFieldDef->getName().c_str(), &fieldId);
                tervelaFieldDef->setFieldId(fieldId);
            }
            initialized = true;
        }
    }

	 	int retValue;
		vstring tempString;
		int tempInt;
		TVA_UINT8 tempByte;
		TVA_BOOLEAN  tempBoolean;
		dlong  tempLong;
		double tempDouble;
		float tempFloat;
		short tempShort;
		Binary  tempBytes;
		TVA_DATE tempDateTime;

};

VOLANTE_NAMESPACE_END

#endif //__TervelaINPUTPARSER_H__

