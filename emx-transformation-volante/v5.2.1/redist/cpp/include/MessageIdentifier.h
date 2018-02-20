#ifndef __MESSAGEIDENTIFIER_H__
#define __MESSAGEIDENTIFIER_H__

VOLANTE_NAMESPACE_BEGIN


/**
* Identifies the message and returns a collection of key fields in the message. Before calling
 * the idetifyMessage method, the message identifier should be intialized by calling the init
 * method with the required  properties (specific to message identifier).
 *
 *  Volante C++ library ships with message identifiers for FIX and Canonical messages.
 *  <ul>
 *  <li>FIXMessageIdentifier
 *  <li>SIACCanonicalMessageIdentifier
 *  <li>CartridgeMessageIdentifier
 *  </ul>
*/
class VOLANTE_EXPORT MessageIdentifier : public Object {
public:
/**
     * Identifies the message and returns a DataObject with key (important) fields of the message.
     * Typically, the header portion of the input is parsed and important fields that are likely to be used
     * to uniquely identify a message (and route it) are returned as part of the DataObject.
     *
     * By convention, the DataObject can contain fields like,
     * <ul>
     * <li>MessageFormat   -- Format of the message (SWIFT, FIX etc)
     * <li>MessageVersion  -- Version of the message (e.g. 4.1)
     * <li>MessageType     -- Type of the message (e.g MT950)
     *
     * @param is InputSource object that represents the message to be identified
     * @return  A structure that represents important fields of the input or null if the message is not recognized
     * return null if it cannot positively identify a message. Only in rare circumstances such as when the message
     * identifer is not properly initialized should this runtime exception be raised.
     */
	virtual DataObject* identifyMessage(InputSource& inputSource) = 0;

    /**
     * Initialize the message identifier object with a property. Message identifier should be 
	 * intialized before if used.
     * @param properties initialization property (name-value pairs)
     */
	virtual void setProperty(const vstring& name,  const vstring& value) {
	}
	virtual ~MessageIdentifier();

	// Removed in V2.4.1
	//virtual bool isMatch(const char* message, int length) = 0;
	//virtual vstring getMessageFormat() = 0;

};


VOLANTE_NAMESPACE_END

#endif //__MESSAGEIDENTIFIER_H__

