#ifndef __EXTERNALOBJECT_H__
#define __EXTERNALOBJECT_H__

#include "AbstractDataObject.h"
VOLANTE_NAMESPACE_BEGIN

/**
* Object representation of an external message. This object contains three parts,
* the header, data and the trailer.
*
* Fields in these three components can be accessed using methods in the DataObject interface.
*
* The structure of this object corresponds to the External Message defined using the Designer.
* The ExternalObject has a close relationship with {@link IExternalMessage} interface. The
* method of this interface, either return take an ExternalObject as parameter.
*
* <table>
*   <tr>
*     <td>{@link IExternalMessage#parse}</td>
*     <td>Returns an ExternalObject (object representation of the message)
*   </tr>
*   <tr>
*     <td>{@link IExternalMessage#validate}</td>
*     <td>Takes an ExternalObject as parameter(object to be validated)
*   </tr>
*   <tr>
*     <td>{@link IExternalMessage#serialize}</td>
*     <td>Takes an ExternalObject as parameter(object to be serialized)
*   </tr>
*   <tr>
*     <td>{@link IExternalMessage#createExternalObject()} and {@link IExternalMessage#createObject()}</td>
*     <td>Returns a uninitilaized ExternalObject
*   </tr>
* </table>
*
* @see IExternalMessage#parse(InputSource, TransformContext)
* @see IExternalMessage#validate(DataObjectVal, TransformContext)
* @see IExternalMessage#serialize(DataObjectVal, TransformContext)
* @see IExternalMessage#createExternalObject()
*/

class VOLANTE_EXPORT ExternalObject : public AbstractDataObject { 
public:
	ExternalObject() ;
	ExternalObject(DataObject* header, DataObject* data, DataObject* trailer);

	Object* getField0(int index) const;
	void setField0(int index, const Object* value);
	void setExternalObjects(DataObject* header, DataObject* data, DataObject* trailer) {
		this->header = header;
		this->data = data;
		this->trailer = trailer;
		setNotNull(0);
		setNotNull(1);
		setNotNull(2);
	}
	/**
	* Returns the header part of the external object.
	* @return the header part of the external object
	*/
	DataObject* getHeader() {
		return header.get();
	}
	/**
	* Returns the data part of the external object.
	* @return the data part of the external object
	*/
	DataObject* getData() {
		return data.get();
	}
	/**
	* Returns the trailer part of the external object.
	* @return the trailer part of the external object
	*/
	DataObject* getTrailer() {
		return trailer.get();
	}
	void reset() {
		if(!header.isNull()) {
			header->reset();
		}
		if(!data.isNull()) {
			data->reset();
		}
		if(!trailer.isNull()) {
			trailer->reset();
		}
	}
	vstring toXMLString() const ;
	vstring toXMLString(int indent)  const {
		return AbstractDataObject::toXMLString(indent);
	}
	Object* clone() const;
protected: 
	static DataObjectMetaInfo metaInfo;
	V_DECLARE_NULL_FLAG_FIELD (nullFields, 3);
private:
	DataObjectVal header;
	DataObjectVal data;
	DataObjectVal trailer;
};


typedef SmartPtr<ExternalObject> ExternalObjectVal;

VOLANTE_NAMESPACE_END


#endif //__EXTERNALOBJECT_H__
