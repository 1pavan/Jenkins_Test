#ifndef __GENERICEXTERNALOBJECT_H__
#define __GENERICEXTERNALOBJECT_H__
#include "ExternalObject.h"
VOLANTE_NAMESPACE_BEGIN
template <class HeaderClass, class DataClass, class TrailerClass>
class GenericExternalObject : public ExternalObject {
public:
	GenericExternalObject() :ExternalObject(new HeaderClass(), new DataClass(), new TrailerClass()) {
	}
	GenericExternalObject(bool uninialized) :ExternalObject() {
	}
	HeaderClass* getHeaderObject() {
		return dynamic_cast<HeaderClass*>(getHeader());
	}
	DataClass* getDataObject() {
		return dynamic_cast<DataClass*>(getData());
	}
	TrailerClass* getTrailerObject() {
		return dynamic_cast<TrailerClass*>(getTrailer());
	}
	Object* clone() const {
		GenericExternalObject* clonedObject = new GenericExternalObject<HeaderClass, DataClass, TrailerClass>(true);
		GenericExternalObject* thisObj = const_cast<GenericExternalObject*>(this);
		DataObject* clonedHeader = NULL;
		DataObject* clonedData = NULL;
		DataObject* clonedTrailer = NULL;
		if (thisObj->getHeader() != NULL) {
			clonedHeader = dynamic_cast<DataObject*>(thisObj->getHeader()->clone());
		}
		clonedData= dynamic_cast<DataObject*>(thisObj->getData()->clone());
		if (thisObj->getTrailer()!= NULL) {
			clonedTrailer = dynamic_cast<DataObject*>(thisObj->getTrailer()->clone());
		}
		clonedObject->setExternalObjects(clonedHeader, clonedData, clonedTrailer);
		return clonedObject;
	}

};


VOLANTE_NAMESPACE_END


#endif //__GENERICEXTERNALOBJECT_H__
