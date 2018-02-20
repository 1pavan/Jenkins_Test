#ifndef __TRANSFORMCONTEXT_H__
#define __TRANSFORMCONTEXT_H__
#include "OutputContext.h"

VOLANTE_NAMESPACE_BEGIN

/**
*  Defines the context in which the current transformation occurs.
*  This context object contains a set of properties (name-value) pairs
*  related to the current transformation. This object is passed to all
*  the components (input format, business transaction, trigger etc.) 
*  that take part in processing. The external entity (for instance CP)
*  that sends input to the runtime sets properties related to input 
*  and output formats. Along the way, a component processing input may set more
*  properties to be used by rest of components. These properties are 
*  contain processing instructions such as what is the output format,
*  and how it should be sent out (protocol).
*
*  @see OutputContext
*/
class VOLANTE_EXPORT TransformContext : public Object {
public:
	typedef std::map<vstring, vstring> StringMap;
	typedef ObjectPtrMap<Object> ObjectProperyMap;
public:
	TransformContext() {
		propertyMapTemp = NULL;
		objectPropertyMapTemp = NULL;
	}
	~TransformContext();
	virtual void setContextProperty(const vstring& name, const vstring& value);

	/**
	*  Sets the value of specified property. The properties are name-object pairs.
	*/
	virtual void setProperty(const vstring& name, const vstring& value);
	virtual void setObjectProperty(const vstring& name, Object* value);

	/**
	*  Returns the value of specified property. The properties are name-object pairs.
	*  This class defines names of some of the standard properties used in the system.
	*  @return the value of the property, or empty string if no such property exists.
	*/
	virtual vstring getProperty(const vstring& name);
	virtual Object* getObjectProperty(const vstring& name);

	/**
	*  Creates an Output context. Output context is needed if the client code needs to
	*  get back the output produced.
	*/
	virtual void createOutputContext();
	/**
	*  Returns the Output Context associated with this TransformContext. Output context
	*  contains the outputs produced during message processing.
	*  You should have called createOutputContext() before calling this.
	*
	*  <pre>
	*    cxt.createOutputContext();
	*    // Process message
	*    OutputContext ocxt = cxt.getOutputContext();
	*
	*/
	virtual OutputContext getOutputContext();

	/**
	* For internal use
	*/
	virtual void copyTo(TransformContext& to) {
		to.getPropertyMap() = getPropertyMap();
		to.outputContext = outputContext;
	}
	/**
	* Removes all the outputs produced and the properties asscoiated with this context.
	* You need to call this if you want to reuse the TansformContext object that was
	* used as context for a message processing.
	*/
	virtual void clear();
	void putAll(const StringMap& properties);
	static TransformContext EMPTY;
public:
	static vstring INPUT_FORMAT_PROPERTY;
	static vstring INPUT_SOURCE_PROPERTY;
	static vstring INPUT_MODE_PROPERTY;
	static vstring INPUT_BATCH_CONTEXT_PROPERTY;
	static vstring INPUT_BATCH_ID_PROPERTY;
	static vstring INPUT_BATCH_SIZE_PROPERTY;

	static vstring OUTPUT_DESTINATION_PROPERTY;
	static vstring DEFAULT_OUTPUT_DESTINATION_PROPERTY;
	static vstring OUTPUT_FORMAT_PROPERTY;
	static vstring OUTPUT_PROTOCOL_PROPERTY;
	static vstring OUTPUT_DEVICE_PROPERTY;


	static vstring OUTPUT_FORMAT_SUFFIX;
	static vstring BATCH_MODE;
	static vstring RECORD_MODE;

protected:
	StringMap& getPropertyMap();
	ObjectProperyMap& getObjectPropertyMap();
private:
	StringMap* propertyMapTemp;
	ObjectProperyMap* objectPropertyMapTemp;
	TransformContext(const TransformContext&);
	OutputContext outputContext;

};


class VOLANTE_EXPORT TransformContextWrapper : public TransformContext {
	TransformContext* cxt;
public:
	TransformContextWrapper() {
		this->cxt = &TransformContext::EMPTY;
	}
	TransformContextWrapper(TransformContext* cxt) {
		this->cxt = cxt;
	}
	void setTransformContext(TransformContext* cxt) {
		this->cxt = cxt;
	}
	TransformContext* getTransformContext() {
		return cxt;
	}
	vstring getProperty(const vstring& name);
	void setProperty(const vstring& name, const vstring& value);

	void createOutputContext() {
		cxt->createOutputContext();
	}
	OutputContext getOutputContext(){
		return cxt->getOutputContext();
	}
	void clear() {
		cxt->clear();
	}
};

VOLANTE_NAMESPACE_END

#endif //__TRANSFORMCONTEXT_H__

