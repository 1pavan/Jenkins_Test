#ifndef __TervelaOUTPUTWRITER_H__
#define __TervelaOUTPUTWRITER_H__
#include "TransformContext.h"
#include "DataObject.h"
#include "OutputWriter.h"
#include "tvaClientAPIInterface.h"
#include "TervelaFieldDef.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  TervelaOutputWriter.h
*
*  © Copyright 2001-2006 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/
class TervelaOutputWriter : public SimpleOutputWriter {
protected:
public:
	TervelaOutputWriter() {
	}
	virtual RawMessage writeExternalMessage(ExternalObject& outputObject, TransformContext& cxt)  {
		TVA_PUBLISH_MESSAGE_DATA_HANDLE tervalaMessage;
		writeHeader(outputObject.getHeader(), tervalaMessage, cxt);
		writeData(outputObject.getData(), tervalaMessage, cxt);
		writeTrailer(outputObject.getTrailer(), tervalaMessage, cxt);
		TervelaRawMessage* mes = new TervelaRawMessage(tervalaMessage);
		return RawMessage(mes);
	}
	virtual vstring writeExternal(ExternalObject& outputObject, TransformContext& cxt) {
		throw TransformException("Write to string not supported");
	}

	virtual void writeHeader(DataObject* obj, TVA_PUBLISH_MESSAGE_DATA_HANDLE tervalaMessage, TransformContext& cxt) = 0;

	virtual void writeData(DataObject* obj, TVA_PUBLISH_MESSAGE_DATA_HANDLE tervalaMessage, TransformContext& cxt)=0;

	virtual void writeTrailer(DataObject* obj, TVA_PUBLISH_MESSAGE_DATA_HANDLE tervalaMessage, TransformContext& cxt)=0;


	TVA_STATUS setIntIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_INT32 fieldValue) {
    	return tvaSetIntIntoMessageByFieldId(tervelaMessage, fieldId, fieldValue);
	}
	TVA_STATUS setIntIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, char fieldValue) {
    	return tvaSetIntIntoMessageByFieldId(tervelaMessage, fieldId, toInt(fieldValue));
	}
	TVA_STATUS setLongIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_INT64 fieldValue) {
    	return tvaSetLongIntoMessageByFieldId(tervelaMessage, fieldId, fieldValue);
	}
	TVA_STATUS setFloatIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_FLOAT fieldValue) {
    	return tvaSetFloatIntoMessageByFieldId(tervelaMessage, fieldId, fieldValue);
	}
	TVA_STATUS setDoubleIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_DOUBLE fieldValue) {
    	return tvaSetDoubleIntoMessageByFieldId(tervelaMessage, fieldId, fieldValue);
	}
	TVA_STATUS setBooleanIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_BOOLEAN fieldValue) {
    	return tvaSetBooleanIntoMessageByFieldId(tervelaMessage, fieldId, fieldValue);
	}
	TVA_STATUS setShortIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, int fieldValue) {
    	return tvaSetShortIntoMessageByFieldId(tervelaMessage, fieldId, toShort(fieldValue));
	}
	TVA_STATUS setByteIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, int fieldValue) {
    	return tvaSetByteIntoMessageByFieldId(tervelaMessage, fieldId, toByte(fieldValue));
	}
	TVA_STATUS setByteIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, TVA_UINT8 fieldValue) {
    	return tvaSetByteIntoMessageByFieldId(tervelaMessage, fieldId, fieldValue);
	}
	TVA_STATUS setByteIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, char fieldValue) {
    	return tvaSetByteIntoMessageByFieldId(tervelaMessage, fieldId, toByte(fieldValue));
	}
	TVA_STATUS setStringIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, const vstring& fieldValue) {
    	return tvaSetStringIntoMessageByFieldId(tervelaMessage, fieldId, (char*)fieldValue.c_str());
	}
	TVA_STATUS setBytesIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, const Binary& fieldValue) {
    	return tvaSetBytesIntoMessageByFieldId(tervelaMessage, fieldId, (TVA_UINT8*)fieldValue.data(), fieldValue.length());
	}

	TVA_STATUS setBytesIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, const vstring& fieldValue) {
    	return tvaSetBytesIntoMessageByFieldId(tervelaMessage, fieldId, (TVA_UINT8*)fieldValue.data(), fieldValue.length());
	}
	TVA_STATUS setDateTimeIntoMessageByFieldId(TVA_MESSAGE_DATA_HANDLE tervelaMessage, TVA_UINT16 fieldId, const DateTime& fieldValue) {
    	return tvaSetDateTimeIntoMessageByFieldId(tervelaMessage, fieldId,  toTVADate(fieldValue));
	}

public :    
	TVA_DATE toTVADate(const DateTime& dt) {
		static DateTime UNIX_EPOCH(Date(1970, 1, 1), Time());
		TVA_DATE toRet;
		TimeSpan diff = (dt - UNIX_EPOCH);
		dlong elapsedSecs=  diff.elapsedseconds();
		dlong utc = elapsedSecs * 1000000 + (dt.getMilliSeconds()* 1000);
		toRet.timeInMicroSecs = utc;
		return toRet;
	}
    static Binary toBytes(const vstring& value) {
        return Binary(value);
    }
    static short toShort(int value) {
        return (short) value;
    }
    static TVA_UINT8 toByte(int value) {
        return (TVA_UINT8) value;
    }
    static int toInt(char value) {
        return value;
    }
    static TVA_UINT8 toByte(char value) {
        return (TVA_UINT8) value;
    }

protected:
	void requiredFieldMissing(AbstractDataObject* object, int index) {
	}
public:
};

VOLANTE_NAMESPACE_END

#endif //__TervelaOUTPUTWRITER_H__

