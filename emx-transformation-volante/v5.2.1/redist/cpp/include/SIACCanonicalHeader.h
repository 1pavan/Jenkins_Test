#ifndef __SIACCANONICALHEADER_H__
#define __SIACCANONICALHEADER_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT SIACCanonicalHeader : public AbstractDataObject {
    public:
	void parseHeader(const char* recordStr, int recordLength);
    enum FieldIndices {
        MessageFormat_INDEX=0, 
        MessageVersion_INDEX=1, 
        MessageType_INDEX=2, 
        CFT_CanonicalVersion_INDEX=3, 
        CFT_BodyLength_INDEX=4, 
        CFT_SIACMsgType_INDEX=5, 
        CFT_MsgSubType_INDEX=6, 
        CFT_MsgOrigin_INDEX=7, 
        CFT_MsgDest_INDEX=8, 
        CFT_MsgSeqNo_INDEX=9
    };
    public:
    SIACCanonicalHeader()  :AbstractDataObject(&metaInfo, nullFields) {
        init();
				setMessageFormat("Canonical");

    }
		SIACCanonicalHeader(const SIACCanonicalHeader& copyForm) :  AbstractDataObject(copyForm, nullFields) {
		}
    virtual Object* clone() const {
        return new SIACCanonicalHeader(*this);
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

    const vstring& getCFT_CanonicalVersion() const {
        AbstractDataObject::ensureNotNull(3);
        return CFT_CanonicalVersion;
    }
    void setCFT_CanonicalVersion(const vstring& value){
        AbstractDataObject::setNotNull(3);
        this->CFT_CanonicalVersion=value;
		setMessageVersion(value.substr(10));
    }
    const vstring& getCFT_BodyLength() const {
        AbstractDataObject::ensureNotNull(4);
        return CFT_BodyLength;
    }
    void setCFT_BodyLength(const vstring& value){
        AbstractDataObject::setNotNull(4);
        this->CFT_BodyLength=value;
    }
    const vstring& getCFT_SIACMsgType() const {
        AbstractDataObject::ensureNotNull(5);
        return CFT_SIACMsgType;
    }
    void setCFT_SIACMsgType(const vstring& value){
        AbstractDataObject::setNotNull(5);
        this->CFT_SIACMsgType=value;
		setMessageType(value);
    }
    const vstring& getCFT_MsgSubType() const {
        AbstractDataObject::ensureNotNull(6);
        return CFT_MsgSubType;
    }
    void setCFT_MsgSubType(const vstring& value){
        AbstractDataObject::setNotNull(6);
        this->CFT_MsgSubType=value;
    }
    const vstring& getCFT_MsgOrigin() const {
        AbstractDataObject::ensureNotNull(7);
        return CFT_MsgOrigin;
    }
    void setCFT_MsgOrigin(const vstring& value){
        AbstractDataObject::setNotNull(7);
        this->CFT_MsgOrigin=value;
    }
    const vstring& getCFT_MsgDest() const {
        AbstractDataObject::ensureNotNull(8);
        return CFT_MsgDest;
    }
    void setCFT_MsgDest(const vstring& value){
        AbstractDataObject::setNotNull(8);
        this->CFT_MsgDest=value;
    }
    int getCFT_MsgSeqNo() const {
        AbstractDataObject::ensureNotNull(9);
        return CFT_MsgSeqNo;
    }
    void setCFT_MsgSeqNo(int value){
        AbstractDataObject::setNotNull(9);
        this->CFT_MsgSeqNo=value;
    }



    protected:
    Object* getField0(int index) const ;

    protected:
    void setField0(int index, const Object* value);

    protected: static DataObjectMetaInfo metaInfo;

	vstring getHeaderField(const vstring& fieldName) const;




    private:
    vstring MessageFormat;
    vstring MessageVersion;
    vstring MessageType;
    vstring CFT_CanonicalVersion;
    vstring CFT_BodyLength;
    vstring CFT_SIACMsgType;
    vstring CFT_MsgSubType;
    vstring CFT_MsgOrigin;
    vstring CFT_MsgDest;
    int CFT_MsgSeqNo;

	  V_DECLARE_NULL_FLAG_FIELD(nullFields, 10);

};
VOLANTE_NAMESPACE_END

#endif //__SIACCANONICALHEADER_H__

