#ifndef __MESSAGE_H__
#define __MESSAGE_H__
#include "Object.h"
#include "DataObject.h"
#include "TransformContext.h"
#include "InputSource.h"
#include "RawMessage.h"
#include "ExceptionHandler.h"
#include "TransformException.h"
#include "Service.h"

VOLANTE_NAMESPACE_BEGIN
template <class T>
class Result {
public:
	Result(const T& output, ExceptionList& exceptionList) : exceptionList(exceptionList), output(output) {
	}
	Result(const T& output, CascadingExceptionHandler& cascadingExceptionHandler, TransformException& e) : output(output) {
		ExceptionList texceptions;
		e.getExceptionsAsList(texceptions);
		ExceptionList& cascadedExceptions = cascadingExceptionHandler.getExceptions();
		exceptionList.insert(exceptionList.end(), texceptions.begin(), texceptions.end());
		exceptionList.insert(exceptionList.end(), cascadedExceptions.begin(), cascadedExceptions.end());
	}
	bool hasException() {
		return exceptionList.size() > 0;
	}
	T& getOutput() {
		return output;
	}
	ExceptionList& getExceptions() {
		return exceptionList;
	}
  void addExceptionsToList(ExceptionList& addTo) {
      if(hasException()) {
				addTo.insert(addTo.end(), exceptionList.begin(), exceptionList.end());
      }
  }
	
private:
	T output;
	ExceptionList exceptionList;
};

/**
 * Represents a message processor service object that can be used to parse, validate and serialize a message. This
 * interface has methods that apply to the raw and the object representation of the message.
 * <ul>
 * <li>parse - converts raw message to message object
 * <li>serialize- converts message object to raw form
 * <li>validate - validates a message object
 * <li>create - create a uninitialized message object.
 * </ul>
 * <p>
 * <p>
 * Each concrete implementation of this interface typically is capable of parsing one
 * type of message (for e.g. New Order FIX message).
 * <p>
 * There are two major classifications of messages, internal and external. There is an interface each to
 * represent the two types of the messages,
 * <ul>
 * <li>{@link IInternalMessage}
 * <li>{@link IExternalMessage}
 * </ul>
 * <p>
 * <p>
 * This interface has two variants of the methods for performing an operation. The former performs the operation
 * and throws an exception in case of errors. The latter, which has a suffix '2' (as in parse2),
 * accumulates (cascades) the exceptions and returns a Result object.
 * The Result object, is a pair containing the output of the method and the accumulated exceptions. While the former,
 * returns an output or throws an exception, the latter, depending on the severity of the exception encountered during
 * processing, may return an output, exception or both.
 * <p>
 * <p>
 * <strong>Warning:</strong>
 * Applications may not invoke a method in this interface while another method is in
 * progress. They should create a new Message instance instead for each
 * nested (concurrent) call.  Once a method is complete, an application may reuse the same Message processor object
 * for executing any other method.
 *
 * @see ILookupContext#lookupMessage(const vstring&)
 * @see Result
 */
class VOLANTE_EXPORT IMessage : public IService {
public:
    /**
     * Creates an uninitialized message object. The returned object can be used for building a message object.
     *
     * @return uninitialized object representation of the message
     * @see DataObject
     */
    virtual DataObjectVal createObject() = 0;

    /**
     * Parses a document and returns an object representation of it. This method throws a TransformException if it
     * encounters any errors during parsing. Parsing stops on the first error and no output is produced.
     * <pre>
     *   try {
		 *			TransformContextImpl cxt;
     *      DataObjectVal parseObject = myMessage.parse(FileInputSource("input.txt"), cxt);
     *      // ...
     *  }
     *  catch(TransformException e) {
     *  }
     * </pre>
     * <p>
     * Applications may not invoke this method while a parse is in
     * progress (they should create a new Message instance instead for each
     * nested document).  Once a parse is complete, an
     * application may reuse the same Message processor object, for parsing or writing.
     *
     * @param source The input source for the document
     * @param cxt    The context in which parsing is done. This is typically used for passing parsing options.
     * @return the object representation of the message.
     * @throws TransformException Parsing exceptions
     * @see #parse2(InputSource&, TransformContext&)
     * @see #serialize(const DataObjectVal&, TransformContext&)
     * @see ByteArrayInputSource
     */
    virtual DataObjectVal parse(InputSource& source, TransformContext& cxt) = 0;
    virtual DataObjectVal parse(const RawMessage& source, TransformContext& cxt) = 0;

    /**
     * Parses a document and returns an object representation of it. This method throws a TransformException if it
     * encounters any errors during parsing. Parsing stops on the first error and no output is produced.
		 * This method is similar to #parse(const InputSource&, TransformContext&);
		 */
    virtual DataObjectVal parse(const Binary& source, TransformContext& cxt) = 0;


    /**
     * Parses a document and returns an object representation of it. Unlike the parse method, this method does not throw
     * a TransformException if it encounters any errors during parsing. Instead it accumulates (cascades) the exceptions
     * and returns them as part of the result.
     * <p>
     * The Result object, is a pair containing the output of the method and the accumulated exceptions.
     * Depending on the severity of the exception encountered during parsing, it may
     * may contain both the parsed object and list of exceptions.
     * <table>
     *
     * <tr><td>No Parsing errors</td>            <td>Parsed output only</td> </tr>
     * <tr><td>Non-fatal parsing errors</td>      <td>Parsed output along with list of exceptions</td> </tr>
     * <tr><td>Fatal parsing errors</td>          <td>List of exceptions. The last exception is fatal. No parsed object as output.</td> </tr>
     * </table>
     * <pre>
     *
		 * FileInputSource fis("input.txt")
		 * TransformContext cxt;
     * Result<DataObjectVal> result = myMessage.parse2(fis, cxt);
     *
     * // The parsed object may be null in case of fatal exceptions.
     * DataObjectVal parsedObject = result.getOutput();
     *
     * if(result.hasException()) {
     *     ExceptionList exceptions = result.getExceptions();
     *     // Do something with the exceptions
     * }
     * </pre>
     * <p>
     * Applications may not invoke this method while a parse is in
     * progress (they should create a new Message instance instead for each
     * nested document).  Once a parse is complete, an
     * application may reuse the same Message processor object for parsing or writing.
     *
     * @param source The input source for the document
     * @param cxt    The context in which parsing is done. This is typically used for passing parsing options.
     * @return a Result object containing the object representation of the message along with a list of exceptions.
     * @see #parse(InputSource&, TransformContext&)
     * @see #serialize(const DataObjectVal&, TransformContext&)
     * @see ByteArrayInputSource
     */
    virtual Result<DataObjectVal> parse2(InputSource& source, TransformContext& cxt) = 0;
    virtual Result<DataObjectVal> parse2(const Binary& source, TransformContext& cxt) = 0;


    /**
     * Executes the validations specified for the message. The object 'obj' is validated based
     * on the rules specified in the Message definition. Validation stops on failure.
     * <p>
     * The object 'obj' is validated based on the rules specified in the Message definition. Validation stops on failure.
     *
     * <pre>
     *    myMessage->validate(obj, cxt);
     * </pre>
     * This method throws an exception on first validation failure (even if the validation is set as cascadable). To
     * continue validation in case of failure use #validate2.
     * <p>
     * <strong>Warning:</strong>
     * Validating an object using this method does not necessarily guarantee it to be valid. This method
     * ensures that the object conforms to validation rules specified in the Designer. The object may still violate
     * some other format specific constraint. For instance, for an XML format object, this method does not check whether
     * it conforms to facets specified in the schema. Such format specific checks are made during parsing & serializing.
     * Hence an object which is validated using this method may still fail while serializing.
     * @param obj The object to be validated
     * @param cxt The context in which parsing is done. This is typically used for passing additional options.
     */
    virtual void validate(const DataObjectVal& obj, TransformContext& cxt) = 0;
    virtual void validate(const vstring& name, const DataObjectVal& obj, TransformContext& cxt) = 0;

    /**
     * Executes the validations specified for the message. Unlike the other validate method, this method does not throw
     * a TransformException if it encounters any errors during validation. Instead it accumulates (cascades) the exceptions
     * and returns them as part of the result.
     * <pre>
     *    Result result = myMessage->validate(obj, cxt);
     *    if(result.hasException()) {
     *       ExceptionList exceptions = result.getExceptions();
     *      // Do something with the exceptions
     *    }
     * </pre>
     * This method throws an exception only on encountering a non-cascadable validation failure. To
     * abort on first validation failure use #validate2.
     * <p>
     * <strong>Warning:</strong>
     * Validating an object using this method does not necessarily guarantee it to be valid. This method
     * ensures that the object conforms to validation rules specified in the Designer. The object may still violate
     * some other format specific constraint. For instance, for an XML format object, this method does not check whether
     * it conforms to facets specified in the schema. Such format specific checks are made during parsing & serializing.
     * Hence an object which is validated using this method may still fail while serializing.
     *
     * @param obj The object to be validated
     * @param cxt The context in which parsing is done. This is typically used for passing additional options.
     */
    virtual Result<DataObjectVal> validate2(const DataObjectVal& obj, TransformContext& cxt) = 0;
    virtual Result<DataObjectVal> validate2(const vstring& name, const DataObjectVal& obj, TransformContext& cxt) = 0;

    /**
     * Serializes or writes the object to raw form. The raw form depends on the type of the message.
     * For external messages it depends on the message type (for example SWIFT, FIX etc.). For internal messages
     * it is always XML.
     *
     * <p>
     * This method throws a TransformException if it encounters any errors while serilizing.
     * Serialization stops on the first error and no output is produced.
     *
     * <pre>
     * try {
     *      Binary output = myMessage.serialize(obj, cxt);
     *      // ...
     *  }
     *  catch(TransformException e) {
     *  }
     * </pre>
     * <p>
     * In case of ExternalMessage the input object (obj) should be an ExternalObject while in case of InternalMessage
     * it should be a NormalizedObject. Passing the wrong type of object will lead to ClassCastException.
     * <p>
     * @param obj The object to be serialized (ExternalObject or Normalized Object)
     * @param cxt The context in which parsing is done. This is typically used for passing parsing options.
     * @return the raw representation of the message.
     * @throws TransformException Serialization exceptions, if the message object is not well formed (for e.g violates
     *                            not-null constraints).
     * @see #serialize2
     * @see #parse
     * @see #validate
     */
    virtual Binary serialize(const DataObjectVal& obj, TransformContext& cxt)= 0;


    /**
     * Serializes or writes the object to raw form. The raw form depends on the type of the message.
     * For external messages it depends on the message type (for example SWIFT, FIX etc.). For internal messages
     * it is always XML.
     * Unlike the other serialize method, this method does not throw
     * a TransformException if it encounters any errors during serialization. Instead it accumulates (cascades) the exceptions
     * and returns them as part of the Result.
     * <p>
     * The Result object, is a pair containing the output of the method (byte[]) and the accumulated exceptions.
     * Depending on the severity of the exception encountered during serialization, it may
     * may contain both the output and a list of exceptions.
     * <table>
     * <tr><td>No Serialization errors</td>            <td>Raw output only</td> </tr>
     * <tr><td>Non-fatal serialization errors</td>      <td>Raw output along with list of exceptions</td> </tr>
     * <tr><td>Fatal serialization errors</td>          <td>List of exceptions. The last exception is fatal. No raw output.</td> </tr>
     * </table>
     * <p>
     *
     * <pre>
     *   Result<Binary> result = myMessage->serialize(obj, cxt);
     *   Binary output = result.getOutput();
     *   if(result.hasExceptions()) {
     *       ExceptionList exceptions = result.getExceptions();
     *   }
     * </pre>
     * <p>
     * In case of ExternalMessage the input paramter (obj) should be an ExternalObject while in case of InternalMessage
     * it should be a NormalizedObject. Passing the wrong type of object will lead to ClassCastException.
     * <p>
     * @param obj The object to be serialized (ExternalObject or Normalized Object)
     * @param cxt The context in which parsing is done. This is typically used for passing parsing options.
     * @return a Result object containing the raw representation of the message along with a list of exceptions.
     * @return .
     * @see #serialize
     * @see #parse 
     * @see #validate
     */
    virtual Result<Binary> serialize2(const DataObjectVal& obj, TransformContext& cxt) = 0;


    /**
     * Serializes or writes the object to raw form. The raw form depends on the type of the message.
     * For external messages, it depends on the message type (for example SWIFT, FIX etc.). For internal messages,
     * it is always XML.
     * <p/>
     * <p/>
     * This method throws a TransformException if it encounters any errors while serilizing.
     * Serialization stops on the first error and no output is produced.
     * <p/>
     * <pre>
     * try {
     *      byte[] output = myMessage.serialize(obj, cxt);
     *      // ...
     *  }
     *  catch(TransformException e) {
     *  }
     * </pre>
     * <p/>
     * In case of ExternalMessage, the input object (obj) should be an ExternalObject; while in case of InternalMessage,
     * it should be a NormalizedObject. Passing the wrong type of object will lead to ClassCastException.
     * <p/>
     * Note: The method is not related to Java serialization.
     *
     * @param obj The object to be serialized (ExternalObject or Normalized Object)
     * @param cxt The context in which serialization is done. This is typically used for passing additional options.
     * @return The raw representation of the message.
     * @throws TransformException Serialization exceptions, if the message object is not well formed (for e.g violates
     *                            not-null constraints).
     * @throws RemoteException    Network exceptions, applicable only if this method is invoked remotely.
     * @see #serialize2
     * @see #parse
     * @see #validate
     */
    virtual RawMessage serializeMessage(const DataObjectVal& obj, TransformContext& cxt) = 0;
    virtual Result<RawMessage> serializeMessage2(const DataObjectVal& obj, TransformContext& cxt) = 0;

		static vstring XML_FORM;
		static vstring VOLANTE_FORM;
		static vstring MESSAGE_FORMAT;
		protected:
			static bool isVolanteFormat(const vstring& messageFormat) {
        return VOLANTE_FORM == messageFormat;
    }

};
typedef SmartPtr<IMessage> Message;

VOLANTE_NAMESPACE_END



#endif //__MESSAGE_H__
