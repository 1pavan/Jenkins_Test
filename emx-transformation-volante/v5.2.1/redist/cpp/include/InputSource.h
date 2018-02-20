#ifndef __INPUTSOURCE_H__
#define __INPUTSOURCE_H__

VOLANTE_NAMESPACE_BEGIN

/**
*  This class allows an application to encapsulate information about 
*  an input source in a single object. An InputSource object belongs 
*  to the application: the Volante runtime shall never modify it in 
*  any way.
*
*  The InputSource object is typically used as a parameter to to the 
*  processInput method of InputFormat.
*
* @see InputFormat#processInput
* @see ByteArrayInputSource
* @see FileInputSource
* @see MessageRouter
*/
class VOLANTE_EXPORT InputSource  {
public:
	/**
	*	Get the byte stream for this input source.
	*/
	virtual const char* getAsBytes(int& length) = 0;
	virtual Binary getAsBinary()  {
		int length;
		const char* bytes = getAsBytes(length);
		return Binary((const vbyte*)bytes, length);
	}
};

VOLANTE_NAMESPACE_END

#endif //__INPUTSOURCE_H__
