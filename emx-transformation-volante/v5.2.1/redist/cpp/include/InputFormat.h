#ifndef __INPUTFORMAT_H__
#define __INPUTFORMAT_H__
#include "DataObject.h"
#include "TransformContext.h"
#include "InputSource.h"
#include "InputParser.h"
#include "Service.h"

VOLANTE_NAMESPACE_BEGIN

/**
*  The interface for accessing an input format generated by the designer. 
*  The input format object can be looked up by name using an environment specific context
*  object. For instance, using
*  <pre>
*  InputFormat inFmt = LookupContextFactory::getLookupContext()->lookupInputFormat("name");
*  </pre>
*   The 'name' is transformation name (or rule name) specfied in the designer.
*
*  <p>Typically a client looks up an input format and passes input to it. The input format
*  maps the input to normalized object and passes it to the business transaction for further
*  processing.
*
*  <p>The InputFormat is responsible for
*  <ul>
*    <li> Parsing the input data
*    <li> Validating the input data
*    <li> Mapping the input data to NormalizedObject
*  </ul>
*
*  @see ILookupContext#lookupInputFormat
*  @see BusinessTransaction
*  @see OutputFormat
*  @deprecated
*/
class VOLANTE_EXPORT IInputFormat : public IService {
public:

	/**
	*  Processes the input and maps it to normalized object and returns it. 
	*
	*  This method is responsible for
	*  <ul>
	*    <li> Parsing the input data
	*    <li> Validating the input data
	*    <li> Mapping the input data to NormalizedObject
	*  </ul>
	*
	*  @param source the input that needs to be processed. The input must be in a format
	*   that is acceptable to this input format. Typically, an array of bytes is acceptable
	*   to all input formats that use textual strings ( CSV, XML etc).
	*
	*  @param tcxt The context in which transformation occurs.
	*  @return normalized object, should be deleted by the caller
	*
	*  @see BusinessTransaction
	*  @see TransformContext
	*	@see NormalizedObject
	*/
	virtual NormalizedObject* handleInput(InputSource& source, TransformContext& tcxt) = 0;

	/**
	*  Processes the input, map it to normalized object and 
	*  routes the normalized object to the appropriate Business transaction (internal message)
	*  for further processing.
	*
	*  This method is responsible for
	*  <ul>
	*    <li> Validating the input data
	*    <li> Mapping the input data to NormalizedObject
	*    <li> Sending the NormalizedObject to the corresponding business transaction
	*  </ul>
	*
	*  @param source the input object needs to be processed. 
	*
	*  @param tcxt The context in which transformation occurs.
	*
	*  @see BusinessTransaction
	*  @see TransformContext
	*	@see NormalizedObject
	*/
	virtual void processInput(InputSource& source, TransformContext& tcxt) = 0;

	/**
	*  Returns the parser object. 
	*
	*/
	virtual InputParser& getInputParser() = 0;

};
typedef SmartPtr<IInputFormat> InputFormat;

VOLANTE_NAMESPACE_END

#endif //__INPUTFORMAT_H__

