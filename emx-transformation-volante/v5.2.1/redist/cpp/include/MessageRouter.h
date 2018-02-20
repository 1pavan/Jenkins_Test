#ifndef __MESSAGEROUTER_H__
#define __MESSAGEROUTER_H__

VOLANTE_NAMESPACE_BEGIN

class MessageIdentificationService;
class MessageConfiguration;


/**
 *  Routes input messages based on the specified configuration. Roughly equivalent to Command processor.
 *  It parses the message header using the message identifiers and selects the message configuration that 
    matches the message.

	The incoming message is identified and matched with a set of message templates and routed to the appropriate 
    input format. The configuration for routing is specified using a collection (series) of  
    MESSAGE_CONFIG_BEGIN elements. 

    <h3>Message Identification</h3>

	<p>Once the input handler receives an input message, it sends the input message to the specified 
    message identifiers in the order they are given. A message identifier is a custom class that returns
    the values of key fields in the message in the form of a DataObject (a DataObject
	is nothing but an hashtable of fields with their values). The message identifier might 
    peek into the message to construct the DataObject. If a message identifier is unable to 
    identify a message, it returns null instead of a DataObject. If a message identifier returns 
    null, the router continues with the next message identifier in the list of message identifiers. 
    But if none of the specified message identifiers return a DataObject, the input handler throws 
	UnrecognizedMessageException.

    Volante provides predefined message identifiers for FIX (FIXMessageIdentifier), 
	and Canonical (CanonicalMessageIdentifier) messages. There is also generic message identifier
	based on an input format defined in a cartridge.  

	<pre>
			MESSAGE_IDENTIFIERS_BEGIN
				MESSAGE_IDENTIFIER(CartridgeMessageIdentifier)
				MESSAGE_IDENTIFIER_PROPERTY("input.format", "DOR_ROUTER_IN")
			MESSAGE_IDENTIFIERS_END
	</pre>

	The other predefined message identifier do not require any configuartion properties.


    Each routing config has a message template for matching and a transform context for processing. 

	<h3>Message Template Properties</h3>

	<p>These properties specify the key fields to be matched for identification of an input message. 
        MessageType and MessageVersion are some of the commonly used message identification properties.
	    If a field you specify in the template is missing or does not match the value in the identified message, 
        it is treated as a failed match.

	    Specify message template properties using the macro MESSAGE_PROPERTY.
	

	<code>MESSAGE_PROPERTY("MessageType", "D") </code>

    If it fails to match with all the templates, an UnhandledMessageException is thrown.

	<h3>Message Transformation Properties</h3>

	<p>Once the input message is identified and matched, it is transformed using the transformation properties 
    such as 'input.format' and 'internal.message'. You can also specify other properties such as 'output.format', 
    'output.device' and 'output.protocol' that may be used during the transformation. 
	 Specify the transform context properties using the macro CONTEXT_PROPERTY.

	 <code>CONTEXT_PROPERTY("input.format", "Order41IN")</code>

    The 'input.format' is mandatory. 


	The config info must be defined in your CPP file (global scope).
	<p>Sample config
	<pre>	
		MESSAGE_ROUTER_BEGIN(MyRouter)

			MESSAGE_IDENTIFIERS_BEGIN
				MESSAGE_IDENTIFIER(CartridgeMessageIdentifier)
				MESSAGE_IDENTIFIER_PROPERTY("input.format", "DOR_ROUTER_IN")
			MESSAGE_IDENTIFIERS_END
		
			MESSAGE_CONFIG_BEGIN(FIX41D)
				MESSAGE_FORMAT("FIX")
				MESSAGE_VERSION("4.1")
				MESSAGE_TYPE("D") // or MESSAGE_PROPERTY("MessageType", "D")
				CONTEXT_PROPERTY("input.format", "Order41IN")
				CONTEXT_PROPERTY("output.format", "CanonicalOrder")
				CONTEXT_PROPERTY("output.device", "default")
			MESSAGE_CONFIG_END
		
			MESSAGE_CONFIG_BEGIN(CANONICAL)
				MESSAGE_FORMAT("Canonical")
				MESSAGE_VERSION("1.00")
				MESSAGE_TYPE("CFM_PREORDER")
				CONTEXT_PROPERTY("input.format", "OrderInCan")
				CONTEXT_PROPERTY("output.format", "CanonicalOrder")
				CONTEXT_PROPERTY("output.device", "default")
			MESSAGE_CONFIG_END
		
		MESSAGE_ROUTER_END
	</pre>	

	This defines a global method <code>getMessageRouterMyRouter</code>.

	To initialize the router object,
	<pre>
		MessageRouter router;
		getMessageRouterMyRouter(router);
	</pre>

	To process a message,

	<pre>
		FileInputSource fis(fileName); 
		router.processMessage(fis);
	</pre>

	
	An object of this class is <strong>not</strong> thread safe.

	@see CartridgeMessageIdentifier
	@see FIXMessageIdentifier
	@see CanonicalMessageIdentifier
	@see TransformContext
	@see InputSource

 */
class VOLANTE_EXPORT MessageRouter : public Object {
public:
	MessageRouter(MessageIdentificationService* mis = NULL);
	~MessageRouter();

	/**
	 *  Processes the given message based on the routing configuration. The method uses the TransformContext 
	 *  instead of creating one by itself. Refer to the doc for this class for details on routing.
	 *  @see MessageRouter
     */
	void processMessage(InputSource& source, TransformContext& tcxt) const;
	/**
	 *  Processes the given message based on the routing configuration. Refer to the doc for this class for details on routing.
	 *  @see MessageRouter
     */
	void processMessage(InputSource& source) const;

	MessageConfiguration* getMessageConfiguration(InputSource& inputSource) const;
	bool onInit();
	void clear();
	void clearMessageIdentificationService();
	void addMessageConfiguration(MessageConfiguration* msgConfig);
	void setMessageIdentificationService(MessageIdentificationService* mis);
private:
	MessageRouter(const MessageRouter&);
	const MessageRouter& operator = (const MessageRouter&);

private:
	MessageIdentificationService* mis;
	typedef std::vector<MessageConfiguration*> Messages;
	Messages messages;
	bool initialized;
	LookupContext lcxt;
	mutable vstring lastInputFormatName;
	mutable InputFormat lastInputFormat;
	typedef ObjectMap<InputFormat> InputFormatMap;
	mutable InputFormatMap inputFormats;
	bool ownService; 

};


class VOLANTE_EXPORT MessageConfiguration {
public:
	void setMessageFormat(const vstring& value);
	void setMessageVersion(const vstring& value);
	void setMessageType(const vstring& value);
	void setMessageAttribute(const vstring& name, const vstring& value);
	void setContextProperty(const vstring& name, const vstring& value);
	void setProperty(const vstring& name, const vstring& value);
	bool isMatch(DataObject* header);

	Properties& getContextProperties() {
		return contextProps;
	}
private:
	vstring messageFormat;
	vstring messageVersion;
	vstring messageType;
	Properties contextProps;
	Properties props;
};

#define MESSAGE_ROUTER_BEGIN(name) \
	void getMessageRouter ##name (MessageRouter& router) { \
		router.clear();	\


#define MESSAGE_ROUTER_END	}



//////////////////////////////////////////////////////////////////////////////////////////

#define MESSAGE_IDENTIFIERS_BEGIN \
	MessageIdentificationService* mis = new MessageIdentificationService();


#define MESSAGE_IDENTIFIERS_END \
	router.setMessageIdentificationService(mis);
	

#define MESSAGE_IDENTIFIER(className) \
	USING_CLASS(className); \
	mis->registerMessageIdentifer(#className);

#define MESSAGE_IDENTIFIER_BEGIN(className) \
	mis->registerMessageIdentifer(className);

#define MESSAGE_IDENTIFIER_PROPERTY(name, value) \
	mis->setMessageIdentiferProperty(name, value);

//////////////////////////////////////////////////////////////////////////////////////////


#define MESSAGE_CONFIG_BEGIN(name) \
	{										\
	MessageConfiguration * def = new MessageConfiguration();


#define MESSAGE_CONFIG_END router.addMessageConfiguration(def); }										


#define MESSAGE_PROPERTY(name, value) \
	def->setProperty(name, value);


#define CONTEXT_PROPERTY(name, value) \
	def->setContextProperty(name, value);


#define MESSAGE_FORMAT(value) \
	def->setMessageFormat(value);

#define MESSAGE_TYPE(value) \
	def->setMessageType(value);


#define MESSAGE_VERSION(value) \
	def->setMessageVersion(value);


VOLANTE_NAMESPACE_END

#endif //__MESSAGEROUTER_H__

