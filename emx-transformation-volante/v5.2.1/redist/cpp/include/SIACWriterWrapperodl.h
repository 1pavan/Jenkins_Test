#ifndef __SIACWRITERWRAPPER_H__
#define __SIACWRITERWRAPPER_H__
#include "cf.h"
#include "tags.h"
#include "SIACCanonicalOutputWriter.h"

VOLANTE_NAMESPACE_BEGIN

class SIACWriterWrapper {
	class TagInfo {
	public:
		int type;
		int tag;
		vstring strValue;
		vstring primitiveValue;
		bool primitive;
		AbstractDataObject* dataObj;
		int index;
	};
private:
	// FIX ME - what should be max buf len?
#define MAX_SIAC_BUF_LEN 904999
	char outBuf[MAX_SIAC_BUF_LEN];
	unsigned int retnBufLen;
	OutgoingCanonical outCan;
	int result;
	bool includeChecksum;
	TagInfo tagInfo;
public:
	SIACWriterWrapper() : outCan(CFO_NO_NULL_TERMINATION) {
		this->includeChecksum = false;
		tagInfo.type = 0;	
	}
	void setChecksum(bool includeChecksum) {
		this->includeChecksum = includeChecksum;
	}
	void initMessage() {
		//Reinitialize OutgoingCanonical - Is this really needed?
		//outCan.~OutgoingCanonical();
		//new (&outCan) OutgoingCanonical(CFO_NO_NULL_TERMINATION);
		tagInfo.type = 0;	
		result = outCan.CF_SetOutputVersion(0, CANONICAL_1_00_VERSION_ID);
		checkResult(result, NULL, 0);
		int option = 0;
		if(includeChecksum) {
			option = CFO_ADD_CHECKSUM;
		}
		option |= CFO_TAG_INSTANCE_DELIMITER;
		result = outCan.CF_CreateMsg(option, outBuf, MAX_SIAC_BUF_LEN);
		checkResult(result, NULL, 0);
	}

	vstring endMessage() {
		flush(true);
		return vstring(outBuf, retnBufLen);
	}
private:
	inline void newPutField(int tag, AbstractDataObject* dataObj, int index) {
		tagInfo.type = 1;
		tagInfo.tag = tag;
		tagInfo.dataObj = dataObj;
		tagInfo.index = index;
	}
	inline void putNextFieldPrimitive(int tag, AbstractDataObject* dataObj, int index) {
		newPutField( tag, dataObj, index);
		tagInfo.primitive = true;
	}
public:
	void putNextField(int tag, int tagValue, AbstractDataObject* dataObj, int index) {
		flush();
		intToString(tagValue, tagInfo.primitiveValue);
		putNextFieldPrimitive(tag, dataObj, index);
	}
	void putNextField(int tag, char tagValue, AbstractDataObject* dataObj, int index) {
		flush();
		charToString(tagValue, tagInfo.primitiveValue);
		putNextFieldPrimitive(tag, dataObj, index);
	}
	void putNextField(int tag, double tagValue, AbstractDataObject* dataObj, int index) {
		flush();
		doubleToString(tagValue, tagInfo.primitiveValue);
		putNextFieldPrimitive(tag, dataObj, index);
	}
	void putNextField(int tag, float tagValue, AbstractDataObject* dataObj, int index) {
		flush();
		floatToString(tagValue, tagInfo.primitiveValue);
		putNextFieldPrimitive(tag, dataObj, index);
	}
	void putNextField(int tag, dlong tagValue, AbstractDataObject* dataObj, int index) {
		flush();
		dlongToString(tagValue, tagInfo.primitiveValue);
		putNextFieldPrimitive(tag, dataObj, index);
	}
	void putNextField(int tag, const BigInteger& tagValue, AbstractDataObject* dataObj, int index) {
		flush();
		bigIntegerToString(tagValue, tagInfo.primitiveValue);
		putNextFieldPrimitive(tag, dataObj, index);
	}
	void putNextField(int tag, const BigDecimal& tagValue, AbstractDataObject* dataObj, int index) {
		flush();
		bigDecimalToString(tagValue, tagInfo.primitiveValue);
		putNextFieldPrimitive(tag, dataObj, index);
	}
	void putNextField(int tag, const vstring& tagValue, AbstractDataObject* dataObj, int index) {
		if(tagValue.length() > 0) {
			flush();
			newPutField( tag, dataObj, index);
			tagInfo.strValue = tagValue;
			tagInfo.primitive = false;
		}
		// FIX for Ignore empty tags Bug #111
	}
	void beginGroup(int tag, AbstractDataObject* dataObj, int index) {
		flush();
		result = outCan.CF_BeginGroup(0, tag);
		checkResult(result, dataObj, index);
	}
	void putNextGroupInstance(AbstractDataObject* dataObj, int index) {
		flush();
		result = outCan.CF_PutNextGroupInstance(0);
		checkResult(result, dataObj, index);
	}
	void endGroup(int tag, AbstractDataObject* dataObj, int index) {
		flush();
		tagInfo.type = 2;
		tagInfo.tag = tag;
		tagInfo.dataObj = dataObj;
		tagInfo.index = index;
	}

private:
	void flush(bool lastField = false) {
		if(tagInfo.type == 1) {
			putNextField0(lastField); 						
		}
		else if(tagInfo.type == 2) {
			endGroup0(lastField); 						
		}
		tagInfo.type = 0;
	}
	int putNextField0(bool lastField) {
		int option = CFO_ORIGINAL_FORM | (lastField ? CFO_LAST_FIELD : 0);
		if(tagInfo.primitive) {
			result = outCan.CF_PutNextField(option, tagInfo.tag, (void*)tagInfo.primitiveValue.data(), (unsigned int) tagInfo.primitiveValue.length(), &retnBufLen);
		}
		else {
			result = outCan.CF_PutNextField(option, tagInfo.tag, (void*)tagInfo.strValue.data(), (unsigned int) tagInfo.strValue.length(), &retnBufLen);
		}
		checkResult(result, tagInfo.dataObj, tagInfo.index);
		return result;
	}

	int endGroup0(bool lastField) {
		int option = (lastField ? CFO_LAST_FIELD : 0);
		result = outCan.CF_EndGroup(option, tagInfo.tag, &retnBufLen);
		checkResult(result, tagInfo.dataObj, tagInfo.index);
		return result;
	}

private:
	inline void checkResult(int result, DataObject* dataObj, int index) {
		if(result < 0) {
			throwWriterException(result, dataObj, index);
		}
	}
	void throwWriterException(int result, DataObject* dataObj, int index) {
		SIACCanonicalWriterException ex("Error writing field '" + dataObj->getFieldName(index) + "'" + ". Error code = " + intToString(result));
		ex.setErrorCode(intToString(result));		
		THROW_EXCEPTION(ex);
	}
};

VOLANTE_NAMESPACE_END

#endif //__SIACWRITERWRAPPER_H__

