#ifndef __RAWMESSAGE_H__
#define __RAWMESSAGE_H__

#include "PropertyMap.h"
#include "InputSource.h"
#include "Collections.h"

/**
 * Raw message is an abstraction for an unprocessed message. Apart from the content or the body of the message,
 * it supports features such as properties and attachments that are commonly supported in other message representations.
 * <ul>
 * <li>Provides a single, unified message API
 * <li>Provides an API suitable for creating messages that match the format used by message providers
 * </ul>
 * In its simplest form raw message just contains the body, which can either be a text or a stream of bytes.
 * Complex messages may contain typed properties and attachments.
 * Raw Messages are composed of the following parts:
 * <ul>
 * <li>	Body – This represents the content or the payload of the message. Two  types of message body are supported, text and a stream of uninterpreted bytes
 * * <li>	Properties - Each message contains a built-in facility for supporting application defined property values. Properties are name value pairs. Properties provide an efficient mechanism for supporting application defined message filtering (impl in future).
 * <li>Attachments, which themselves are named raw messages.
 * </ul>
 *
 * @see com.tplus.transform.runtime.FileInputSource
 * @see com.tplus.transform.runtime.ByteArrayInputSource
 * @see com.tplus.transform.runtime.StringInputSource
 * @see com.tplus.transform.runtime.RawOutputMessage
 */
VOLANTE_NAMESPACE_BEGIN
class VOLANTE_EXPORT IRawMessage :  public IPropertyMap, public InputSource {
public:
		//typedef SmartPtr<IRawMessage> RawMessage;
		//typedef VList<std::vector<RawMessage>, RawMessage>	  RawMessageList;
    static const vstring REPLY_TO_PROPERTY;
    static const vstring CORRELATION_ID_PROPERTY;
    static const vstring CORRELATION_GROUP_SIZE_PROPERTY;
    static const vstring CORRELATION_SEQUENCE_PROPERTY;
    //const vstring PLATFORM_DEFAULT_ENCODING = System.getProperty("file.encoding");

    virtual void setName(const vstring& inputSourceName) = 0;
    virtual vstring getName() =0;

    /**
     * Adds a map of properties to be associated with this message
     *
     * @param properties the properties add to this message
     */
    //virtual void addProperties(Map properties) =0;


    /**
     * Converts the message implementation into a String representation
     *
     * @param encoding The encoding to use when transforming the message (if necessary). The parameter is
     *                 used when converting from a byte array
     * @return String representation of the message payload
     * @throws TransformException Implementation may throw an endpoint specific exception
     */
    virtual vstring getAsString(const vstring& encoding)  =0;

    /**
     * Converts the message implementation into a String representation. If encoding is required it will
     * use the encoding set on the message
     *
     * @return String representation of the message payload
     * @throws TransformException Implementation may throw an endpoint specific exception
     */
    virtual vstring getAsString() =0;


    //virtual InputStream getAsStream() =0;

    /**
     * Converts the message implementation into a byte array representation
     *
     * @return byte array of the message
     * @throws TransformException Implemetation may throw an endpoint specific exception
     */
    virtual const char* getAsBytes(int& length)  =0;

    /**
     * @return the current message in its natural representation
     * @throws TransformException Implemetation may throw an endpoint specific exception
     */
    //virtual Object getAsObject() throws TransformException;

    /**
     * gets the unique identifier for the message. It's up to the implementation
     * to ensure a unique id
     *
     * @return a unique message id.  The Id should never be null. If the underlying transport does
     *         not have the notion of a message Id, one shuold be generated.  The generated Id should be a
     *         UUID.
     */
    //virtual vstring getUniqueId() =0;


    /**
     * Sets a correlationId for this message. The correlation Id can be used by
     * components in the system to manage message relations
     * <p/>
     * transport protocol. As such not all messages will support the notion of a
     * correlationId i.e. tcp or file. In this situation the correlation Id is
     * set as a property of the message where it's up to developer to keep the
     * association with the message. For example if the message is serialised to
     * xml the correlationId will be available in the message.
     *
     * @param id the Id reference for this relationship
     */
    //virtual void setCorrelationId(const vstring& id) =0;

    /**
     * Sets a correlationId for this message. The correlation Id can be used by
     * components in the system to manage message relations.
     * <p/>
     * The correlationId is associated with the message using the underlying
     * transport protocol. As such not all messages will support the notion of a
     * correlationId i.e. tcp or file. In this situation the correlation Id is
     * set as a property of the message where it's up to developer to keep the
     * association with the message. For example if the message is serialised to
     * xml the correlationId will be available in the message.
     *
     * @return the correlationId for this message or null if one hasn't been set
     */
    //virtual vstring getCorrelationId() =0;

    /**
     * Gets the sequence or ordering number for this message in the the
     * correlation group (as defined by the correlationId)
     *
     * @return the sequence number or -1 if the sequence is not important
     */
    //virtual int getCorrelationSequence() =0;

    /**
     * Gets the sequence or ordering number for this message in the the
     * correlation group (as defined by the correlationId)
     *
     * @param sequence the sequence number or -1 if the sequence is not
     *                 important
     */
    //virtual void setCorrelationSequence(int sequence) =0;

    /**
     * Determines how many messages are in the correlation group
     *
     * @return total messages in this group or -1 if the size is not known
     */
    //virtual int getCorrelationGroupSize() =0;

    /**
     * Determines how many messages are in the correlation group
     *
     * @param size the total messages in this group or -1 if the size is not
     *             known
     */
    //virtual void setCorrelationGroupSize(int size);

    /**
     * Sets a replyTo address for this message. This is useful in an
     * asynchronous environment where the caller doesn't wait for a response and
     * the response needs to be routed somewhere for further processing. The
     * value of this field can be any valid endpointUri url.
     *
     * @param replyTo the endpointUri url to reply to
     */
    //virtual void setReplyTo(Object replyTo) =0;

    /**
     * Returns a replyTo address for this message. This is useful in an
     * asynchronous environment where the caller doesn't wait for a response and
     * the response needs to be routed somewhere for further processing. The
     * value of this field can be any valid endpointUri url.
     *
     * @return the endpointUri url to reply to or null if one has not been set
     */
    //virtual Object* getReplyTo();

    /**
     * Adds a named attachhment.
     *
     * @param name        name of the attachment
     * @param dataHandler attachment
     * @throws Exception exception while extracting data from the DataHandler
     */
    //virtual void addAttachment(String name, DataHandler dataHandler) throws Exception;

    /**
     * Adds a named attachhment.
     *
     * @param name       name of the attachment
     * @param attachment attachment
     */
    virtual void addAttachment(const vstring& name, RawMessage attachment) =0;

    /**
     * Removes a previously added attachment
     *
     * @param name name of the attachment to remove
     */
    virtual void removeAttachment(const vstring& name) =0;

    /**
     * Returns the attachment by name
     *
     * @param name name of the attachment to remove
     * @return attached message or nul if no such attachement exists
     * @see #addAttachment(vstring,RawMessage)
     */
    virtual RawMessage getAttachment(const vstring& name) =0;

    /**
     * Retruns true if an attachment by the specified name exists
     *
     * @param name name of the attachment
     * @return true if an attachment by the specified name exists, false otherwise
     */
    virtual bool hasAttachment(const vstring& name) =0;

    /**
     * Returns a set of all attachement names
     *
     * @return set of attatchment names
     */
    virtual StringList getAttachmentNames() = 0;

    //virtual RawMessageList getAttachments() =0;

    /**
     * Gets the encoding for the current message. For potocols that send encoding
     * Information with the message, this method should be overriden to expose the
     * transport encoding, otherwise the default encoding in the Mule configuration will be used
     *
     * @return the encoding for this message.  This method must never return null
     */
    virtual vstring getEncoding() =0;

    /**
     * Sets the encoding for this message
     *
     * @param encoding the encoding to use
     */
    virtual void setEncoding(const vstring& encoding) =0;


};
typedef SmartPtr<IRawMessage> RawMessageBase;

class RawMessage : public RawMessageBase {
public:
	RawMessage() {
	}
	RawMessage(IRawMessage* obj) : RawMessageBase(obj) {
	}
	RawMessage(const RawMessage& right)  : RawMessageBase(right){	
	}
	RawMessage& operator=(const RawMessage& right) {	
		RawMessageBase::operator =(right);
		return (*this);
	}
	RawMessage& operator=(IRawMessage* obj) {	
		RawMessageBase::operator =(obj);
		return (*this);
	}

	inline IRawMessage *operator->() const {	
		return RawMessageBase::operator ->();
	}
	inline IRawMessage& operator*() const 	{	
		return RawMessageBase::operator *();
	}

};

typedef VList<std::vector<RawMessage>, RawMessage>	  RawMessageList;
inline vstring valueToString(const RawMessage& val) {
	return val->getAsString();
}

class VOLANTE_EXPORT RawMessageObject : public WrapperObject {
public:
	RawMessageObject(const RawMessage& value) {
		this->value = value;
	}
	const RawMessage& getValue() const {
		return value;
	}
	vstring toString() const {
		return valueToString(value);
	}
	virtual Object* clone() const  {
		return new RawMessageObject(value);
	}
	const vstring& getObjectType() const {
		return DesignerTypes::RAW_MESSAGE_TYPE;
	}
	const RawMessage& getRawMessage() const {
			return value;
	}
	void setRawMessage(const RawMessage& value)  {
			this->value = value;
	}
	void setObject(const Object* obj) {
		setRawMessage(obj->getRawMessage());
	}

private:
	RawMessage value;
};


VOLANTE_NAMESPACE_END





#endif //__RAWMESSAGE_H__
