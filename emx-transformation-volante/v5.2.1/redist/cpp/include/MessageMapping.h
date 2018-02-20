#ifndef __MESSAGEMAPPING_H__
#define __MESSAGEMAPPING_H__
#include "Message.h"
#include "ExceptionHandler.h"
#include "ExternalObject.h"
#include "Service.h"
VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT MappingInfo : public Object {

};

/**
* The interface for mapping a source message to a destination message. The mapping definition should have been
* defined using the Designer and deployed in this runtime environment. The primary method in this interface is
* the {@link #map} method which maps a source message object to a destination message object.
* <p>
* Message Mapping comes in four different flavors,
* <ul>
* <li> External to Internal
* <li> External to External
* <li> Internal to External
* <li> Internal to Internal
* </ul>
* <p>
* Like other service objects, you can get access to a MessageMapping object by looking up using LookupContext
* {@link ILookupContext#lookupMessageMapping(const vstring&)}. The preferred way of using a MessageMapping is through a
* message flow and not directly from client applications.
* <p>
* <p>The MessageMapping is responsible for
* <ul>
* <li> Mapping the source message object to destination message object
* </ul>
*
* @see ILookupContext#lookupMessageMapping(vstring)
* @see IMessage#createObject()
* @see DataObject
*/

class VOLANTE_EXPORT IMessageMapping : public IService {
public:
	/**
	* Maps the source object to destination object using the mapping  defined in the Designer.
	*
	* @param src  source message object for mapping. It should be of a type expected by this MessageMapping.
	* @param dest destination message object for mapping. It should be of a type expected by this MessageMapping
	* @param cxt  The context in which mapping executes. This context can be used to pass additional options
	*             to the MessageMapping. Currently no such properties are recognized.
	* @throws TransformException       Exceptions encountered during mapping.
	*                                  (most exceptions during mapping are due to programming errors
	*                                  and are unrecoverable Runtime exceptions).
	*/
	virtual DataObjectVal map(const DataObjectVal& src, const DataObjectVal& dest, TransformContext& cxt) =0;

	/**
	* Returns the lookup name of the source message (the source of the mapping). This name can used to lookup the
	* the message object using the LookupContext.
	* <pre>
	* LookupContext lcxt = LookupContextFactory::getLookupContext();
	* vstring name = mapping.getSourceMessageName();
	* Message srcMessage = lcxt->lookupMessage(name);
	* </pre>
	*
	* @return the name of the source message.
	*/
	virtual vstring getSourceMessageName() =0;

	/**
	* Returns the lookup name of the destination message. This name can used to lookup the
	* the message object using the LookupContext.
	* <pre>
	* LookupContext lcxt = LookupContextFactory::getLookupContext();
	* vstring name = mapping->getDestinationMessageName();
	* Message destMessage = lcxt->lookupMessage(name);
	* DataObjectVal destObj = destMessage->createObject();
	* </pre>
	*
	* @return the name of the source message.
	*/
	virtual vstring getDestinationMessageName() =0;

	/**
	* Provides meta information about this mapping. The MappingInfo object can be used to convert a
	* fieldName or fieldId of the source message to the mapped fieldName or fieldId in the
	* destination message (and vice versa). This information is generated during code generation phase in Designer.
	* Not support in C++.
	* @return meta information for this mapping
	*/
	virtual MappingInfo* getMappingInfo() =0 ;
};

typedef SmartPtr<IMessageMapping> MessageMapping;

VOLANTE_NAMESPACE_END


#endif //__MESSAGEMAPPING_H__
