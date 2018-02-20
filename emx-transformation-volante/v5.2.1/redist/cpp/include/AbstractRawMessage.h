#ifndef __ABSTRACTRAWMESSAGE_H__
#define __ABSTRACTRAWMESSAGE_H__

#include "RawMessage.h"
VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT AbstractRawMessage :  public IRawMessage {
private:
	typedef std::map<vstring, RawMessage> AttachmentMap;
private:
	AttachmentMap* _attachments;
	vstring encoding;
	vstring messageName;
protected :
	vstring id;
	PROPERTY_MAP_DELETE
public:
	vstring getName() {
		return messageName;
	}

	void setName(const vstring& inputSourceName) {
		this->messageName = inputSourceName;
	}
	void addAttachment(const vstring& name, RawMessage rawMessage);

	void removeAttachment(const vstring& name);

	void removeAllAttachments();

	RawMessage getAttachment(const vstring& name);
	RawMessageList getAttachments();

	bool hasAttachment(const vstring& name);
	StringList getAttachmentNames();

	vstring getEncoding() {
		return encoding;
	}

	/**
	* Sets the encoding for this message
	*
	* @param encoding the encoding to use
	*/
	void setEncoding(const vstring& encoding) {
		this->encoding = encoding;
	}
	/**
	* Converts the message implementation into a String representation. If
	* encoding is required it will use the encoding set on the message
	*
	* @return String representation of the message payload
	* @throws TransformException Implementation may throw an endpoint specific exception
	*/
	vstring getAsString() ;
	virtual const char* getAsBytes(int& length) =0;

	vstring getAsString(const vstring& encoding);
	AttachmentMap& getAttachmentMap();

	vstring toString();
};
VOLANTE_NAMESPACE_END

#endif //__ABSTRACTRAWMESSAGE_H__
