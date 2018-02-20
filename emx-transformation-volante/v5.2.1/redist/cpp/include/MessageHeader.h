#ifndef __MESSAGEHEADER_H__
#define __MESSAGEHEADER_H__

VOLANTE_NAMESPACE_BEGIN
/**
 *  @deprecated
 */
class VOLANTE_EXPORT MessageHeader {
public:
	/**
	 * Returns the message's format ('FIX', 'Canonical', 'FCS') 
	 * @return a name indicating the message format 
	 */
	virtual vstring getMessageFormat() const = 0;
	/**
	 * Returns the type of the message. The type is format specfic. For instance in case of FIX, it can 'D', '8' etc.
	 * @return the format specific type 
	 */
	virtual vstring getMessageType() const = 0;
	/**
	 * Returns the version of the message. The version is format specfic. For instance in case of FIX, it can '4.1', '4.2' etc.
	 * @return the format's version 
	 */
	virtual vstring getMessageVersion() const = 0;
	/**
	 * Returns the value of the header field. This method lets you access format specific fields in the header.
	 * Fonr innstance, in case of SIAC Canonical message you get the subtype of the message by suing the field name 'CFT_MsgSubType'.
	 * @return the value of the field or an empty string.
	 */
	virtual vstring getHeaderField(const vstring& fieldName) const = 0;


	virtual ~MessageHeader() {
	}

	vstring stringform() {
		return "MessageFormat = " + getMessageFormat() + ", " + 
		"Message Version = " + getMessageVersion()+ ", " + 
		"Message Type = " + getMessageType();
	}

};

VOLANTE_NAMESPACE_END

#endif //__MESSAGEHEADER_H__

