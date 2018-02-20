#ifndef __REUTERSINPUTPARSER_H__
#define __REUTERSINPUTPARSER_H__
#include "AbstractDataObject.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "TransformContext.h"
#include "ExternalObject.h"
#include "InputParser.h"
#include <time.h>
#include <math.h>

#include "RDM/RDM.h"
#include "Data/Data_API.h"
#include "Data/Map.h"
#include "Data/MapWriteIterator.h"
#include "Data/MapReadIterator.h"
#include "Data/MapEntry.h"

#include "Data/Vector.h"
#include "Data/VectorWriteIterator.h"
#include "Data/VectorReadIterator.h"
#include "Data/VectorEntry.h"

#include "Data/FieldList.h"
#include "Data/FieldListReadIterator.h"
#include "Data/FieldListWriteIterator.h"
#include "Data/FieldEntry.h"
#include "Data/FieldEntryDef.h"
#include "Data/FieldListDefWriteIterator.h"

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

#include "Data/Date.h"
#include "Common/Common.h"
#include "Message/RespMsg.h"
#include "reutersrt/ReutersHeader.h"

VOLANTE_NAMESPACE_BEGIN
class ReutersInputParser : public InputParser  {
protected:
	ReutersInputParser() {
		for(int i =rfa::data::ExponentNeg14; i <=ExponentPos7; ++i) {
			EXPONENTS[i] = pow(10.0, i - 14);
		}
	}
	~ReutersInputParser() {
	}
	ReutersHeader headerParser;
public:
	double EXPONENTS[25];
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
public:
	DateTime toDateTime(time_t time, unsigned int millis = 0) {
		struct tm* ptm = gmtime( &time );
		return DateTime(ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, millis);
	}
	DateTime toDate(int years, int month, int date) {
		return DateTime(years, month, date, 0, 0, 0);
	}
	ExternalObject* parseData(const Binary& input, TransformContext& cxt) {
		//inputObject.reset();
		//parseData(&inputObject, input, cxt);
		//return &inputObject;
		return NULL;
	}
	void parseData(ExternalObject* externalObject, const Binary& input, TransformContext& cxt) {
		rfa::common::Buffer newBuffer((const unsigned char*)input.data(), (int)input.size());
		try {
			parseRDMDataImpl(externalObject, newBuffer, cxt);
		}
		catch(rfa::common::Exception& e) {
			ReutersUtils::checkException(e);
		}
	}
	void parse(ExternalObject* externalObject, InputSource& input, TransformContext& cxt) {
		if(ReutersRespRawMessage* rawMessage = dynamic_cast<ReutersRespRawMessage*>(&input)) {
			const rfa::message::RespMsg* msg= rawMessage->getRespMessage();
			const Data& payload = msg->getPayload();
			headerParser.parseHeader(msg, externalObject->getHeader(), cxt);
			try {
				parseRDMDataImpl(externalObject, payload, cxt);
			}
			catch(rfa::common::Exception& e) {
				ReutersUtils::checkException(e);
			}
		}
		else {
			Binary binary = input.getAsBinary();
			parseData(externalObject, binary, cxt);
		}
	}

	virtual void parseRDMData(ExternalObject* externalObject, const rfa::data::Data& data, TransformContext& cxt) {
		try {
			parseRDMDataImpl(externalObject, data, cxt);
		}
		catch(rfa::common::Exception& e) {
			ReutersUtils::checkException(e);
		}
	}

	virtual void parseRDMDataImpl(ExternalObject* externalObject, rfa::common::Buffer& buffer, TransformContext& cxt) = 0;
	virtual void parseRDMDataImpl(ExternalObject* externalObject, const rfa::data::Data& data, TransformContext& cxt) = 0;

	int getInt32(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getInt32();
	}
	int getUInt32(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getUInt32();
	}
	dlong getInt32AsLong(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getInt32();
	}
	dlong getUInt32AsLong(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getUInt32();
	}
	dlong getInt64(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getInt64();
	}
	dlong getUInt64(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getUInt64();
	}
	BigInteger getUInt64AsBigInt(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return BigInteger(buffer.getUInt64());
	}
	double getDouble(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getDouble();
	}
	float getFloat(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getFloat();
	}
	float getReal32AsFloat(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::data::Real32& real32 =  buffer.getReal32();
		float value = (float)real32.getValue();
		rfa::common::UInt8 magnitude = real32.getMagnitudeType();
		if(magnitude < rfa::data::Divisor1) {
			value =  (float)(value * EXPONENTS[magnitude]);
		}
		else {
			int exponent = rfa::data::Divisor1 - magnitude;
			value = (float)(value* pow(2,exponent));
		}
		return value;
	}

	float getReal32AsDouble(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::data::Real32& real32 =  buffer.getReal32();
		double value = (double)real32.getValue();
		rfa::common::UInt8 magnitude = real32.getMagnitudeType();
		if(magnitude < rfa::data::Divisor1 ) {
			value =  (value * EXPONENTS[magnitude]);
		}
		else {
			int exponent = rfa::data::Divisor1  - magnitude;
			value = value* pow(2,exponent);
		}
		return (float)value;
	}
	double getReal64AsDouble(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::data::Real64& real64 =  buffer.getReal64();
		double value = (double)real64.getValue();
		rfa::common::UInt8 magnitude = real64.getMagnitudeType();
		if(magnitude < rfa::data::Divisor1) {
			value =  (value * EXPONENTS[magnitude]);
		}
		else {
			int exponent = rfa::data::Divisor1 - magnitude;
			value = value* pow(2,exponent);
		}
		return value;
	}
	BigDecimal getReal64AsBigDecimal(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::data::Real64& real64 =  buffer.getReal64();
		BigDecimal value(real64.getValue());
		rfa::common::UInt8 magnitude = real64.getMagnitudeType();
		if(magnitude < rfa::data::Divisor1) {
			value =  (value * BigDecimal(EXPONENTS[magnitude]));
		}
		else {
			int exponent = rfa::data::Divisor1 - magnitude;
			value = value * BigDecimal(pow(2,exponent));
		}
		return value;
	}
	BigDecimal getReal32AsBigDecimal(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::data::Real32& real32 =  buffer.getReal32();
		BigDecimal value(real32.getValue());
		rfa::common::UInt8 magnitude = real32.getMagnitudeType();
		if(magnitude < rfa::data::Divisor1) {
			value =  (value * BigDecimal(EXPONENTS[magnitude]));
		}
		else {
			int exponent = rfa::data::Divisor1 - magnitude;
			value = value * BigDecimal(pow(2,exponent));
		}
		return value;
	}

	DateTime getDate(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::data::Date& date = buffer.getDate();
		return DateTime(date.getYear(),date.getMonth(), date.getDay(), 0,0, 0);
	}
	DateTime getTime(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::data::Time& time = buffer.getTime();
		return DateTime(0, 1,1,time.getHour(), time.getMinute(), time.getSecond(), time.getMillisecond());
	}
	DateTime getDateTime(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::data::DateTime& dateTime = buffer.getDateTime();
		return DateTime(dateTime.getYear(),dateTime.getMonth(), dateTime.getDay(),dateTime.getHour(), dateTime.getMinute(), dateTime.getSecond(), dateTime.getMillisecond());
	}
	int enumToInt(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		return buffer.getEnumeration();
	}
	Binary getBuffer(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::common::Buffer& str = buffer.getBuffer();
		return Binary((const char*)str.c_buf(), str.size());
	}

	vstring getASCIIString(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::common::RFA_String& str = buffer.getAsString();
		return vstring(str.c_str(), str.length());
	}

	vstring getUTF8String(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::common::RFA_String& str = buffer.getAsString();
		return vstring(str.c_str(), str.length());
	}

	vstring getRMTESString(const rfa::data::DataBuffer& buffer) {
		rfa::common::UInt8 type = buffer.getDataBufferType();
		const rfa::common::RFA_String& str = buffer.getAsString();
		return vstring(str.c_str(), str.length());
	}
	dlong getQOS(const rfa::data::DataBuffer& buffer) {
		const rfa::common::QualityOfServiceInfo& qosInfo= buffer.getQualityOfServiceInfo();
		const rfa::common::QualityOfService& qos= qosInfo.getQualityOfService();
		return getQOS(qos);
	}
	dlong getQOS(const rfa::common::QualityOfService& qos) {
		long rate = qos.getRate();
		long timeliness = qos.getTimeliness();
		dlong toRet = rate << 32 | timeliness;
		return toRet;
	}
	dlong getRespStatus(const rfa::common::RespStatus& qos) {
		dlong toRet;
		long rate = qos.getDataState();
		long timeliness = qos.getStreamState();
		const rfa::common::RFA_String& txt = qos.getStatusText();
		return toRet;
	}
	// CAST FUNCTIONS
	void conversionError(const rfa::common::Data & data, rfa::data::DataEnumeration toType) {
		throw TransformException("Expected Data Format container of type " + toTypeStr(toType) + ", found " + toTypeStr((rfa::data::DataEnumeration)data.getDataType()));
	}
	void checkType(const rfa::common::Data & data, rfa::data::DataEnumeration toType) {
		if(data.getDataType() != toType) {
			conversionError(data, toType);
		}
	}
	vstring toTypeStr(rfa::data::DataEnumeration toType) {
		switch(toType) {
			case rfa::data::FieldListEnum:
				return "FieldList";
			case rfa::data::MapEnum:
				return "Map";
			case rfa::data::FilterListEnum:
				return "FilterList";
			case rfa::data::ElementListEnum:
				return "ElementList";
			case rfa::data::ArrayEnum:
				return "Array";
			case rfa::data::SeriesEnum:
				return "Series";
			case rfa::data::VectorEnum:
				return "Vector";
		}
		return "";
	}

	const rfa::data::Array& toArray(const rfa::common::Data & data) {
		checkType(data, rfa::data::ArrayEnum);
		return static_cast<const rfa::data::Array &>(data);
	}
	const rfa::data::FilterList& toFilterList(const rfa::common::Data & data) {
		checkType(data, rfa::data::FilterListEnum);
		return static_cast<const rfa::data::FilterList &>(data);
	}
	const rfa::data::FieldList& toFieldList(const rfa::common::Data & data) {
		checkType(data, rfa::data::FieldListEnum);
		return static_cast<const rfa::data::FieldList &>(data);
	}
	const rfa::data::ElementList& toElementList(const rfa::common::Data & data) {
		checkType(data, rfa::data::ElementListEnum);
		return static_cast<const rfa::data::ElementList &>(data);
	}
	const rfa::data::Map& toMap(const rfa::common::Data & data) {
		checkType(data, rfa::data::MapEnum);
		return static_cast<const rfa::data::Map &>(data);
	}
	const rfa::data::Vector& toVector(const rfa::common::Data & data) {
		checkType(data, rfa::data::VectorEnum);
		return static_cast<const rfa::data::Vector &>(data);
	}
	const rfa::data::Series& toSeries(const rfa::common::Data & data) {
		checkType(data, rfa::data::SeriesEnum);
		return static_cast<const rfa::data::Series &>(data);
	}

};



VOLANTE_NAMESPACE_END





#endif //__REUTERSINPUTPARSER_H__
