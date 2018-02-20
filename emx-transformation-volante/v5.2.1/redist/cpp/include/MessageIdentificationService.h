#ifndef __MESSAGEIDENTIFICATIONSERVICE_H__
#define __MESSAGEIDENTIFICATIONSERVICE_H__

VOLANTE_NAMESPACE_BEGIN

class MessageIdentifier;
/**
 * Class used to identify and parse the header of a message.
 * <p>To get the header of a message,
 * <pre>
 *  DataObject* header = MessageIdentificationService::identifyMessage(message, length);
 *  vstring messageFormat = header->getField("MessageFormat");
 *  vstring messageType = header->getField("MessageType");
 *  if(messageFormat == "Canonical")) {
 * 	}
 *
 * </pre>
 */
class VOLANTE_EXPORT MessageIdentificationService {
public:
	~MessageIdentificationService();
	/**
	 * Guesses the message format by looking at the message.
	 * @return a name indicating the message format (FIX, Canonical, FCS) 
	 *    or empty string if the message is unrecognized
	 */
	//vstring guessMessageFormat(const char* message, int length);


	/**
	 * Guesses the message format by looking at the message and returns a DataObject representing the key fields of the message.
	 * The DataObject object must be deleted by the caller.
	 * @return DataObject representing the key fields of the message or null if the message is unrecognized.
	 */
	DataObject* identifyMessage(InputSource& inputSource);

	/**
	 *  @deprecated use identify message instead
	 */
	MessageHeader* parseMessageHeader(const char* message, int length);

	/**
	 *  Registers a messsage identifier, for internal use  only.
	 */ 
	void registerMessageIdentifer(MessageIdentifier* messageIdentifier);
	void registerMessageIdentifer(const vstring& className);
	void setMessageIdentiferProperty(const vstring& name, const vstring& value);
	
	static MessageIdentificationService* getDefault();
private:
	typedef std::vector<MessageIdentifier*> MessageIdentifiers;
	MessageIdentifiers messageIdentifiers;
};

VOLANTE_NAMESPACE_END

#endif //__MESSAGEIDENTIFICATIONSERVICE_H__
