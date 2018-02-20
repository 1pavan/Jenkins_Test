#ifndef __FIXHEADER_H__
#define __FIXHEADER_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FIXHeader : public AbstractDataObject {
public:
	void parseHeader(const char* recordStr, int recordLength);

	enum FieldIndices {
		MessageFormat_INDEX=0, 
		MessageVersion_INDEX=1, 
		MessageType_INDEX=2, 
		BeginString_INDEX=3, 
		BodyLength_INDEX=4, 
		MsgType_INDEX=5, 
		SenderCompID_INDEX=6, 
		TargetCompID_INDEX=7, 
		OnBehalfOfCompID_INDEX=8, 
		DeliverToCompID_INDEX=9, 
		MsgSeqNum_INDEX=10, 
		SenderSubID_INDEX=11, 
		TargetSubID_INDEX=12, 
		SendingTime_INDEX=13
	};
	FIXHeader()  :AbstractDataObject(&metaInfo, nullFields) {
		init(); 
		setMessageFormat("FIX");
	}
	FIXHeader(const FIXHeader& copyForm) :  AbstractDataObject(copyForm, nullFields) {
	}

	virtual Object* clone() const {
		return new FIXHeader(*this);
	}

	void init() {
	}
	const vstring& getMessageFormat() const {
		AbstractDataObject::ensureNotNull(0);
		return MessageFormat;
	}
	void setMessageFormat(const vstring& value){
		AbstractDataObject::setNotNull(0);
		this->MessageFormat=value;
	}

	const vstring& getMessageVersion() const {
		AbstractDataObject::ensureNotNull(1);
		return MessageVersion;
	}
	void setMessageVersion(const vstring& value){
		AbstractDataObject::setNotNull(1);
		this->MessageVersion=value;
	}
	const vstring& getMessageType() const {
		AbstractDataObject::ensureNotNull(2);
		return MessageType;
	}
	void setMessageType(const vstring& value){
		AbstractDataObject::setNotNull(2);
		this->MessageType=value;
	}


	const vstring& getBeginString() const {
		AbstractDataObject::ensureNotNull(3);
		return BeginString;
	}
	void setBeginString(const vstring& value){
		AbstractDataObject::setNotNull(3);
		this->BeginString=value;
		setMessageVersion(value.substr(4));

	}
	int getBodyLength() const {
		AbstractDataObject::ensureNotNull(4);
		return BodyLength;
	}

	void setBodyLength(int value){
		AbstractDataObject::setNotNull(4);
		this->BodyLength=value;
	}
	const vstring& getMsgType() const {
		AbstractDataObject::ensureNotNull(5);
		return MsgType;
	}
	void setMsgType(const vstring& value){
		AbstractDataObject::setNotNull(5);
		this->MsgType=value;
		setMessageType(MsgType);
	}
	const vstring& getSenderCompID() const {
		AbstractDataObject::ensureNotNull(6);
		return SenderCompID;
	}
	void setSenderCompID(const vstring& value){
		AbstractDataObject::setNotNull(6);
		this->SenderCompID=value;
	}
	const vstring& getTargetCompID() const {
		AbstractDataObject::ensureNotNull(7);
		return TargetCompID;
	}
	void setTargetCompID(const vstring& value){
		AbstractDataObject::setNotNull(7);
		this->TargetCompID=value;
	}
	const vstring& getOnBehalfOfCompID() const {
		AbstractDataObject::ensureNotNull(8);
		return OnBehalfOfCompID;
	}
	void setOnBehalfOfCompID(const vstring& value){
		AbstractDataObject::setNotNull(8);
		this->OnBehalfOfCompID=value;
	}
	const vstring& getDeliverToCompID() const {
		AbstractDataObject::ensureNotNull(9);
		return DeliverToCompID;
	}
	void setDeliverToCompID(const vstring& value){
		AbstractDataObject::setNotNull(9);
		this->DeliverToCompID=value;
	}
	int getMsgSeqNum() const {
		AbstractDataObject::ensureNotNull(10);
		return MsgSeqNum;
	}
	void setMsgSeqNum(int value){
		AbstractDataObject::setNotNull(10);
		this->MsgSeqNum=value;
	}
	const vstring& getSenderSubID() const {
		AbstractDataObject::ensureNotNull(11);
		return SenderSubID;
	}
	void setSenderSubID(const vstring& value){
		AbstractDataObject::setNotNull(11);
		this->SenderSubID=value;
	}
	const vstring& getTargetSubID() const {
		AbstractDataObject::ensureNotNull(12);
		return TargetSubID;
	}
	void setTargetSubID(const vstring& value){
		AbstractDataObject::setNotNull(12);
		this->TargetSubID=value;
	}
	const vstring& getSendingTime() const {
		AbstractDataObject::ensureNotNull(13);
		return SendingTime;
	}
	void setSendingTime(const vstring& value){
		AbstractDataObject::setNotNull(13);
		this->SendingTime=value;
	}


	// MessageHeader methods
	vstring getHeaderField(const vstring& fieldName) const;



public:

protected:
	Object* getField0(int index) const ;
	Object* getField0(int index, WrapperObject* wrapper) const;

protected:
	void setField0(int index, const Object* value);

protected: static DataObjectMetaInfo metaInfo;



private:
	vstring MessageFormat;
	vstring MessageVersion;
	vstring MessageType;
	vstring BeginString;
	int BodyLength;
	vstring MsgType;
	vstring SenderCompID;
	vstring TargetCompID;
	vstring OnBehalfOfCompID;
	vstring DeliverToCompID;
	int MsgSeqNum;
	vstring SenderSubID;
	vstring TargetSubID;
	vstring SendingTime;
	V_DECLARE_NULL_FLAG_FIELD(nullFields, 14);

};
VOLANTE_NAMESPACE_END

#endif //__FIXHEADER_H__
