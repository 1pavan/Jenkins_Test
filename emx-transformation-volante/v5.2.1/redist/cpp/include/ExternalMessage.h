#ifndef __EXTERNALMESSAGE_H__
#define __EXTERNALMESSAGE_H__
#include "Message.h"
#include "ExceptionHandler.h"
#include "ExternalObject.h"
VOLANTE_NAMESPACE_BEGIN

/**
 * Represents a External Message service object that can be used to parse, validate and serialize
 * an external message. External messages are defined using the Designer and code generated from it contains
 * the implementation of this interface. The main methods of this interface are inherited from {@link IMessage}.
 *
 * <p>
 * The object form of an external message is {@link ExternalObject}. Most methods in this interface take a
 * external object as input or return one as output.
 *
 * <p>
 * The raw form or the external representation of an external message depends on how it was defined in the Designer.
 * Designer has number of plug-ins to define external messages fo various representations (such as XML, SWIFT etc).
 *
 * All the methods that convert from External Object to raw form and vice versa (such as parse & serialize) make use
 * of the appropriate raw representation.
 *
 * <p>
 * Like other service objects, you can get access to an ExternalMessage object by looking up using LookupContext
 * {@link ILookupContext#lookupExternalMessage(const vstring&)}.
 *
 *
 * @see ILookupContext#lookupExternalMessage(const vstring&)
 * @see ExternalObject
 */
class VOLANTE_EXPORT IExternalMessage : public IMessage {
public:
    /**
     * Creates a new uninitialized external object.
     * This method is equivalent to {@link #createObject()}.
     * @return uninitialized external object.
     * @see ExternalObject
     */
    virtual ExternalObjectVal createExternalObject() = 0;
};


typedef SmartPtr<IExternalMessage> ExternalMessage;

VOLANTE_NAMESPACE_END

#endif //__EXTERNALMESSAGE_H__
