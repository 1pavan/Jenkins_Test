#ifndef __REUTERSOUTPUTWRITER_H__
#define __REUTERSOUTPUTWRITER_H__
#include "TransformContext.h"
#include "DataObject.h"
#include "OutputWriter.h"
#include "Data/Data_API.h"


/*
*  BloombergOutputWriter.h
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
#include "RDM/RDM.h"
#include "Data/Map.h"
#include "Data/MapWriteIterator.h"
#include "Data/MapReadIterator.h"
#include "Data/MapEntry.h"
#include "Data/FieldList.h"
#include "Data/FieldListReadIterator.h"
#include "Data/FieldListWriteIterator.h"
#include "Data/FieldEntry.h"
#include "Data/FieldEntryDef.h"
#include "Data/FieldListDefWriteIterator.h"
#include "Data/Date.h"
#include "Common/Common.h"
#include "Message/RespMsg.h"
#include "MathUtil.h"

#include "Data/Vector.h"
#include "Data/VectorWriteIterator.h"
#include "Data/VectorReadIterator.h"
#include "Data/VectorEntry.h"

#include "Data/FilterList.h"
#include "Data/FilterListReadIterator.h"
#include "Data/FilterListWriteIterator.h"
#include "Data/FilterEntry.h"

#include "Data/ElementList.h"
#include "Data/ElementListReadIterator.h"
#include "Data/ElementListWriteIterator.h"
#include "Data/ElementEntry.h"

#include "Data/Series.h"
#include "Data/SeriesReadIterator.h"
#include "Data/SeriesWriteIterator.h"
#include "Data/SeriesEntry.h"

#include "Data/Array.h"
#include "Data/ArrayReadIterator.h"
#include "Data/ArrayWriteIterator.h"
#include "Data/ArrayEntry.h"

#include "reutersrt/ReutersUtil.h"
#include "reutersrt/ReutersHeader.h"

VOLANTE_NAMESPACE_BEGIN
using rfa::data::MagnitudeType;
class ReutersOutputWriter : public SimpleOutputWriter {
protected:
	ReutersHeader headerSerializer;
		rfa::message::RespMsg respMsg;
public:
	ReutersOutputWriter() {
		_ReusableFieldList = new rfa::data::FieldList();
		_ReusableMap = new rfa::data::Map();
		_ReusableVector= new rfa::data::Vector();
		_ReusableFilterList= new rfa::data::FilterList();
		_ReusableElementList= new rfa::data::ElementList();
		_ReusableSeries= new rfa::data::Series();
		_ReusableArray= new rfa::data::Array();
		dictID = 1;
	}
	virtual RawMessage writeExternalMessage(ExternalObject& outputObject, TransformContext& cxt)  {
		respMsg.clear();
		writeExternalMessage(outputObject, respMsg, cxt);
		return RawMessage(new ReutersRespRawMessage(&respMsg));
	}
	void writeExternalMessage(ExternalObject& outputObject, rfa::message::RespMsg& msg, TransformContext& cxt) {
		try {
			headerSerializer.serializeHeader(&msg, outputObject.getHeader(), cxt);
			rfa::data::Data* data = writeData(outputObject.getData(), cxt);
			msg.setPayload(*data);
		}
		catch(rfa::common::Exception& e) {
			ReutersUtils::checkException(e);
		}
		//writeTrailer(outputObject.getTrailer(), cxt);
	}
	vstring writeExternal(ExternalObject& outputObject, TransformContext& cxt) {
		rfa::message::RespMsg rspMsg;
		writeExternalMessage(outputObject, rspMsg, cxt);
		const rfa::common::Data& data = rspMsg.getPayload();
		const rfa::data::Buffer& buffer = data.getEncodedBuffer();
		const unsigned char * buf = buffer.c_buf();
		int size = buffer.size();
		return vstring((const char*)buf, size);
	}

	/*void writeHeader(DataObject* obj, TransformContext& cxt) {
	}


	virtual void writeTrailer(DataObject* obj, TransformContext& cxt) {
	}*/


	virtual rfa::data::Data* writeData(DataObject* obj, TransformContext& cxt)=0;



private:    
protected:
	void requiredFieldMissing(AbstractDataObject* object, int index, int tag) {
	}
	void setInt32(rfa::data::DataBuffer& buffer, int value) {
		buffer.setInt32(value);
	}
	void setUInt32(rfa::data::DataBuffer& buffer, int value) {
		buffer.setUInt32(value);
	}
	void setInt32(rfa::data::DataBuffer& buffer, dlong value) {
		buffer.setInt32((rfa::common::Int32)value);
	}
	void setUInt32(rfa::data::DataBuffer& buffer, dlong value) {
		buffer.setUInt32((rfa::common::UInt32)value);
	}
	void setInt64(rfa::data::DataBuffer& buffer, dlong value) {
		buffer.setInt64(value);
	}
	void setInt64(rfa::data::DataBuffer& buffer, const BigInteger& value) {
		buffer.setInt64(value.toLong());
	}
	void setUInt64(rfa::data::DataBuffer& buffer, dlong value) {
		buffer.setUInt64(value);
	}
	void setUInt64(rfa::data::DataBuffer& buffer, const BigInteger& value) {
		buffer.setUInt64(value.toULong());
	}
	void setBuffer(rfa::data::DataBuffer& buffer, const Binary& value) {
		tmpBuffer.setFrom((const unsigned char*)value.data(), (int)value.size());
		buffer.setBuffer(tmpBuffer, rfa::data::DataBuffer::DataBufferEnumeration::BufferEnum);			
	}

	void setASCIIString(rfa::data::DataBuffer& buffer, const vstring& value) {
		tmpString.set(value.data(), (unsigned int)value.size(), true);
		buffer.setFromString(tmpString, rfa::data::DataBuffer::DataBufferEnumeration::StringAsciiEnum);
	}

	void setRMTESString(rfa::data::DataBuffer& buffer, const vstring& value) {
		tmpString.set(value.data(), (unsigned int)value.size(), true);
		buffer.setFromString(tmpString, rfa::data::DataBuffer::DataBufferEnumeration::StringRMTESEnum);
	}
	void setUTF8String(rfa::data::DataBuffer& buffer, const vstring& value) {
		tmpString.set(value.data(), (unsigned int)value.size(), true);
		buffer.setFromString(tmpString, rfa::data::DataBuffer::DataBufferEnumeration::StringUTF8Enum);
	}
	void setReal32(rfa::data::DataBuffer& buffer, double value) {
		buffer.setReal32FromFloat((float)value, rfa::data::ExponentNeg6);
		/*
		double decimalPart = MathUtil::abs(value - MathUtil::round(value));
		if(decimalPart > 0) {
			value = value * 1000;
			real32.setValue((rfa::common::Int32)MathUtil::round(value));
			real32.setMagnitudeType(RWF_RH_EXPONENT_3);
		}
		else {
			real32.setValue((rfa::common::Int32)value);
			real32.setMagnitudeType(RWF_RH_EXPONENT0);
		}
		buffer.setReal32(real32);*/
	}
	void setReal32(rfa::data::DataBuffer& buffer, float value) {
		buffer.setReal32FromFloat(value, rfa::data::ExponentNeg6);
	}
	void setReal32(rfa::data::DataBuffer& buffer, const BigDecimal& value) {
		buffer.setReal32FromFloat((float)value.toDouble(), rfa::data::ExponentNeg6);
	}

	void setReal64(rfa::data::DataBuffer& buffer, double value) {
		buffer.setReal64FromDouble(value, rfa::data::ExponentNeg6);
/*
		double decimalPart = MathUtil::abs(value - MathUtil::round(value));
		if(decimalPart > 0) {
			value = value * 1000000;
			real64.setValue((rfa::common::Int64)MathUtil::round(value));
			real64.setMagnitudeType(RWF_RH_EXPONENT_6);
		}
		else {
			real64.setValue((rfa::common::Int64)value);
			real64.setMagnitudeType(RWF_RH_EXPONENT0);
		}
		buffer.setReal64(real64);*/
	}
	void setReal64(rfa::data::DataBuffer& buffer, const BigDecimal& value) {
		buffer.setReal64FromDouble((float)value.toDouble(), rfa::data::ExponentNeg6);
	}

	void setDouble(rfa::data::DataBuffer& buffer, double value) {
		buffer.setDouble(value);
	}

	void setFloat(rfa::data::DataBuffer& buffer, float value) {
		buffer.setFloat(value);
	}

	void setDate(rfa::data::DataBuffer& buffer, const DateTime& value) {
		tmpDate.setYear(value.getYear());
		tmpDate.setMonth(value.getMonth());
		tmpDate.setDay(value.getDate());
		buffer.setDate(tmpDate);
	}

	void setTime(rfa::data::DataBuffer& buffer, const DateTime& value) {
		tmpTime.setHour(value.getHours());
		tmpTime.setMinute(value.getMinutes());
		tmpTime.setSecond(value.getSeconds());
		tmpTime.setMillisecond(value.getMilliSeconds());
		buffer.setTime(tmpTime);
	}

	void setDateTime(rfa::data::DataBuffer& buffer, const DateTime& value) {
		tmpDateTime.setYear(value.getYear());
		tmpDateTime.setMonth(value.getMonth());
		tmpDateTime.setDay(value.getDate());
		tmpDateTime.setHour(value.getHours());
		tmpDateTime.setMinute(value.getMinutes());
		tmpDateTime.setSecond(value.getSeconds());
		tmpDateTime.setMillisecond(value.getMilliSeconds());
		buffer.setDateTime(tmpDateTime);
	}

	rfa::data::Real32 real32;
	rfa::data::Real64 real64;
	rfa::common::RFA_String tmpString;
	rfa::common::Buffer tmpBuffer;
	rfa::data::Date tmpDate;
	rfa::data::Time tmpTime;
	rfa::data::DateTime tmpDateTime;
	//rfa::data::FieldListWriteIterator flWIt;
	//rfa::data::FieldEntry fieldEntry;
	rfa::data::DataBuffer	dataBuffer;
	rfa::data::FieldList * _ReusableFieldList;
	rfa::data::Map * _ReusableMap;
	rfa::data::Vector * _ReusableVector;
	rfa::data::FilterList * _ReusableFilterList;
	rfa::data::ElementList * _ReusableElementList;
	rfa::data::Series * _ReusableSeries;
	rfa::data::Array * _ReusableArray;

	rfa::common::Int16 dictID;

public:
	Object* writeBodyStart()  {
		return NULL;
	}

	Object* writeBodyEnd()  {
		return NULL;
	}

	Object* writeBatchStart() {
		return NULL;
	}

	Object* writeBatchEnd() {
		return NULL;
	}
};

VOLANTE_NAMESPACE_END





#endif //__REUTERSOUTPUTWRITER_H__
