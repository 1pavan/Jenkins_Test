#ifndef __MESSAGEFLOW_H__
#define __MESSAGEFLOW_H__
#include "Message.h"
#include "ExceptionHandler.h"
#include "ExternalObject.h"
#include "Service.h"
VOLANTE_NAMESPACE_BEGIN


/**
 * Defines an output port
 */
class VOLANTE_EXPORT OutputPortDef {
private:
	vstring name;
	vstring protocol;
	vstring outputDevice;

public:
	OutputPortDef(const vstring& name, const vstring& protocol, const vstring& outputDevice) {
		this->name = name;
		this->protocol = protocol;
		this->outputDevice = outputDevice;
	}

	vstring getName() {
		return name;
	}

	vstring getOutputDevice() {
		return outputDevice;
	}

	vstring getProtocol() {
		return protocol;
	}
};

class VOLANTE_EXPORT IMessageFlow : public IService {
public:
	/**
	* Executes the message flow and returns the output. The arguments to the message flow are passed as an
	* <code>ObjectList</code> and the output is also returned as an list of objects. The values in input <code>ObjectList</code>
	* are interpreted as values for variables that were marked as 'INPUT' (in the same order)
	* while defining the message flow in Designer. The output array also contains values for the
	* for variables that were marked as 'OUTPUT' (in the same order) while defining the message flow in Designer.
	* <p>
	* This method produces an output (ObjectList) if the message flow completes or throws a TransformException if it
	* encounters any errors during execution. The caller of this method should be aware of the
	* input parameters and output values returned by message flow.
	* <p>
	* <pre>
	* TransformContext cxt;
	* Binary rawData = FileInputSource("dat.txt").getAsBinary())
	* vstring msgtype = "XXX";
	* ObjectList output = messageFlow.run(ObjectList().add(rawData).add(msgtype), cxt);
	* Binary rawOut = ((BinaryObject*)output[0]).getValue();
	* </pre>
	* <p>
	* To use this method meaningfully, the caller of this method should be aware of the input parameters and
	* output values returned by message flow.
	*
	* @param messageFlowArgs Arguments to the message flow. Values in the array  correspond to the input parameters specified
	*                        (in the same order) during Message Flow design. The length of the array must be same the number of parameters.
	*                        Null values are allowed as long as it is gracefully handled in the Message flow that
	*                        you design. Passing wrong types will lead to ClassCastException.
	* @param cxt             The context in which message flow executes. This context can be used to pass additional options
	*                        to the message flow. When the activities in the message flow are invoked, this context
	*                        is passed as parameter to each of them
	* @return Returns the output of the message flows as a list objects. Values in the list correspond to the
	*         output variables specified (in the same order) during Message Flow design. Primitive values are boxed
	*         into their corresponding Object types (DoubleObject for double) etc.
	* @throws TransformException Exceptions encountered during execution of message flow.
	*                            (typically thrown by one of the activities).
	* @see #run2(ObjectList, TransformContext)
	* @see #run(DataObjectVal, TransformContext)
	*/

	virtual ObjectList run(const ObjectList& messageFlowArgs, TransformContext& cxt) = 0;

	/**
	* Executes the message flow and returns the output. The arguments to the message flow are passed as an
	* <code>ObjectList</code> and the output is returned as a {@link Result} object. The {@link Result} object, is a pair
	* containing the output of the message flow (ObjectList) and a list of accumulated exceptions. Unlike the
	* {@link #run(const ObjectList&, TransformContext&)} method, this method does not throw TransformException; instead it returns
	* the exceptions as a part of the Result object. The Result may contain the output of the message flow, list of
	* exceptions encountered during message flow or both.
	*
	* <p>
	* The values in input <code>ObjectList</code>
	* are interpreted as values for variables that were marked as 'INPUT' (in the same order)
	* while defining the message flow in Designer. The output array (as part of Result) also contains values for the
	* for variables that were marked as 'OUTPUT' (in the same order) while defining the message flow in Designer.
	*
	* <p>
	* <pre>
	* TransformContext cxt;
	* Bianry rawData = FileInputSource("dat.txt").getAsBinary())
	* vstring msgtype = "XXX";
	* Result<ObjectList) result = messageFlow.run2(ObjectList().add(rawData).add(msgtype), cxt);
	* ObjectList output = result.getOutput();
	* if(output != null) {
	*      // Get the actual output
	*      byte[] rawOut = output[0];
	* }
	* ExcetionList exceptions = result.getExceptions();
	* // do something with the output & exceptions
	* </pre>
	* <p>
	* To use this method meaningfully, the caller of this method should be aware of the input parameters and
	* output values returned by message flow.
	*
	* @param messageFlowArgs Arguments to the message flow. Values in the array  correspond to the input parameters specified
	*                        (in the same order) during Message Flow design. The length of the array must be same the number of parameters.
	*                        Null values are allowed as long as it is gracefully handled in the Message flow that
	*                        you design. Passing wrong types will lead to ClassCastException.
	* @param cxt             The context in which message flow executes. This context can be used to pass additional options
	*                        to the message flow. When the activities in the message flow are invoked, this context
	*                        is passed as parameter to each of them.
	* @return Returns a {@link Result} object, which is a pair containing the output of the message flow (ObjectList)
	*         and a list of accumulated exceptions. Values in the object array correspond to the output variables
	*         specified (in the same order) during Message Flow design. Primitive values are boxed into their
	*         corresponding Object types (Double for double) etc. The Result may contain the output of the
	*         message flow, list of exceptions encountered during message flow or both.
	* @see #run(ObjectList, TransformContext)
	* @see #run2(DataObjectVal, TransformContext)
	*/
	virtual Result<ObjectList> run2(const ObjectList& messageFlowArgs, TransformContext& cxt) = 0;

	/**
	* Executes the message flow and returns the output. This is a convenience method that can be used if your
	* message flow takes only a raw message (<code>Bainry</code>) as input parameter. The output of the
	* message flow is returned as an array of objects.
	* <p>
	* This method produces an output (ObjectList) if the message flow completes or throws a TransformException if it
	* encounters any errors during execution.
	* <pre>
	* TransformContext cxt;
	* ObjectList output = messageFlow.run(FileInputSource("dat.txt"), cxt);
	* Binary rawOut = output[0];
	* </pre>
	* <p>
	* To use this method meaningfully, the caller of this method should be aware of the input parameters and
	* output values returned by message flow.
	*
	* @param input Arguments to the message flow. Values in the array  correspond to the input parameters specified
	*              (in the same order) during Message Flow design. The length of the array must be same the number of parameters.
	*              Null values are allowed as long as it is gracefully handled in the Message flow that
	*              you design. Passing wrong types will lead to ClassCastException.
	* @param cxt   The context in which message flow executes. This context can be used to pass additional options
	*              to the message flow. When the activities in the message flow are invoked, this context
	*              is passed as parameter to each of them.
	* @return Returns the output of the message flows as a list of  objects. Values in the list correspond to the
	*         output variables specified (in the same order) during Message Flow design. Primitive values are boxed
	*         into their corresponding Object types (Double for double) etc.
	* @throws TransformException Exceptions encountered during execution of message flow.
	*                            (typically thrown by one of the activities).
	* @see #run(ObjectList, TransformContext)
	* @see #run(DataObjectVal, TransformContext)
	*/
	virtual ObjectList run(InputSource& input, TransformContext& cxt) =0;

	/**
	* Executes the message flow and returns the output as a DataObject. The arguments to the message flow are passed as an
	* <code>DataObject</code> and the output is also returned as a DataObject. Use {@link #createInputDataObject()}
	* to create a DataObject representing the input parameters. The fields in this object are same as variables
	* that were marked as 'INPUT' while defining the message flow in Designer. Set the
	* fields in this object using <code>setField("XXX", value)</code> methods and invoke this method.
	* <p>
	* The returned DataObject represents the output of the message flow. The fields in this object are same as variables
	* that were marked as 'OUTPUT' while defining the message flow in Designer. Using run() with a DataObject has
	* better type safety compared to ObjectList since the incorrectly typed values will be caught while
	* constructing the DataObject.
	* <p>
	* <p>
	* This method produces an output (DataObject) if the message flow completes or throws a TransformException if it
	* encounters any errors during execution. There is another variant of this method {@link #run2(const DataObjectVal&, TransformContext&)}
	* which returns both the output and the exceptions as a Result object (instead of throwing the exception)
	* <p>
	* <pre>
	* TransformContext cxt;
	* DataObjectVal input = messageFlow->createInputDataObject();
	* input->setField("rawIn", FileInputSource("dat.txt").getAsBinary());
	* input->setField("msgType", "XXX");
	* DataObjectVal output = messageFlow->run(input, cxt);
	* Binary rawOut = ((BinaryObject*)output.getField("rawOut"))->getValue();
	* </pre>
	* <p>
	* To use this method meaningfully, the caller of this method should be aware of the input parameters and
	* output values returned by message flow.
	*
	* @param input DataObject representing input parameters for the message flow. Use {@link #createInputDataObject()}
	*              to create a DataObject and set it fields using setField("XXX", value) methods.
	* @param cxt   The context in which message flow executes. This context can be used to pass additional options
	*              to the message flow. When the activities in the message flow are invoked, this context
	*              is passed as parameter to each of them
	* @return Returns the output of the message flows as a DataObject. Fields in the DataObject correspond to the
	*         output variables specified (in the same order) during Message Flow design. Primitive values are boxed
	*         into their corresponding Object types (Double for double) etc.
	* @throws TransformException Exceptions encountered during execution of message flow.
	*                            (typically thrown by one of the activities).
	* @see #run(ObjectList, TransformContext)
	* @see #run2(DataObjectVal, TransformContext)
	*/

	virtual DataObjectVal run(const DataObjectVal& input, TransformContext& cxt) =0;

	/**
	* Executes the message flow and returns the output as a DataObject. The arguments to the message flow are passed as an
	* <code>DataObject</code> and the output is returned as a {@link Result} object. The {@link Result} object, is a pair
	* containing the output of the message flow (DataObject) and a list of accumulated exceptions. Unlike the
	* {@link #run(const DataObjectVal&, TransformContext&)} method, this method does not throw TransformException; instead it returns
	* the exceptions as a part of the Result object. The Result may contain the output of the message flow, list of
	* exceptions encountered during message flow or both.
	*
	* <p>
	* Use {@link #createInputDataObject()} to create a DataObject representing the input parameters.
	* The fields in this object are same as variables that were marked as 'INPUT' while defining the
	* message flow in Designer. Set the fields in this object using <code>setField("XXX", value)</code> methods and
	* invoke this method.
	* <p>
	* The returned DataObject represents the output of the message flow. The fields in this object are same as variables
	* that were marked as 'OUTPUT' while defining the message flow in Designer. Using run() with a DataObject has
	* better type safety compared to Objectist since the incorrectly typed values will be caught while
	* constructing the DataObject.
	* <p>
	* <p>
	* This method produces an output (DataObject) if the message flow completes or throws a TransformException if it
	* encounters any errors during execution. There is another variant of this method {@link #run2(const DataObjectVal&, TransformContext&)}
	* which returns both the output and the exceptions as a Result object (instead of throwing the exception)
	* <p>
	* <pre>
	* TransformContext cxt;
	* DataObjectVal input = messageFlow->createInputDataObject();
	* input->setField("rawIn", FileInputSource("dat.txt").getAsBinary());
	* input->setField("msgType", "XXX");
	* Result<DataObjectVal> result = messageFlow->run2(input, cxt);
	* DataObjectVal output = result.getOutput();
	* if(!output.isNull()) {
	Binary rawOut = output.getField("rawOut");
	* }
	* ExceptionList exceptions = result.getExceptions();
	* // do something with the output & exceptions
	* </pre>
	* <p>
	* To use this method meaningfully, the caller of this method should be aware of the input parameters and
	* output values returned by message flow.
	*
	* @param input DataObject representing input paramters for the message flow. Use {@link #createInputDataObject()}
	*              to create a DataObject and set it fields using setField("XXX", value) methods.
	* @param cxt   The context in which message flow executes. This context can be used to pass additional options
	*              to the message flow. When the activities in the message flow are invoked, this context
	*              is passed as parameter to each of them
	* @return Returns a {@link Result} object, which is a pair containing the output of the message flow (DataObject)
	*         and a list of accumulated exceptions. Fields in the DataObject correspond to the
	*         output variables specified (in the same order) during Message Flow design. Primitive values are boxed
	*         into their corresponding Object types (Double for double) etc. The Result may contain the output of the
	*         message flow, list of exceptions encountered during message flow or both.
	* @see #run2(ObjectList, TransformContext)
	* @see #run(DataObjectVal, TransformContext)
	*/
	virtual Result<DataObjectVal> run2(const DataObjectVal& input, TransformContext& cxt) =0;

	/**
	* Returns a {@link DataObject} that represents the input parameters of the message flow. The fields
	* in this object are same as variables that were marked as 'INPUT' while defining the message flow
	* in Designer. The order of the fields is also same as it is defined in the Designer.
	* <p>
	* For example, if you have defined two variables in the Message flow as input say, 'rawIn' and 'msgType'.
	* The input DataObject would contain these two as fields. You can use the methods {@link DataObject#setField(const vstring&, const Object*)}
	* to set the output values.
	* <pre>
	* <p>
	* DataObjectVal input = messageFlow->createInputDataObject();
	* input->setField("rawIn", BinaryObject(FileInputSource("dat.txt").getAsBinary()));
	* input->setField("msgType", StringObject("XXX"));
	* <p>
	* DataObjectVal output = messageFlow->run(input);
	* </pre>
	*
	* @return object representing the input parameters of the message flow
	*/
	virtual DataObjectVal createInputDataObject() =0;

	/**
	* Returns a DataObject that represents the output parameters of the message flow. The fields
	* in this object are same as variables that were marked as 'OUTPUT' while defining the message flow
	* in Designer. The order of the fields is also same as it is defined in the Designer.
	* <p>
	* For example, if you have defined two variables in the Message flow as output say, 'no' and 'retType'.
	* The output DataObject would contain these two as fields. You can use the methods {@link DataObject#getField(const vstring&) const}
	* to access the output values.
	*
	* @return object representing the output parameters of the message flow
	*/
	virtual DataObjectVal createOutputDataObject() =0;

	typedef std::vector<OutputPortDef> OutputPortList;
	/**
	* Returns a list of ports ({@link OutputPortDef}) definitions.
	*
	* @return list of ports
	*/
	virtual OutputPortList getOutputPorts() = 0;


};

typedef SmartPtr<IMessageFlow> MessageFlow;

VOLANTE_NAMESPACE_END


#endif //__MESSAGEFLOW_H__
