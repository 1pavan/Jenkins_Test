#ifndef __DATAOBJECT_H__
#define __DATAOBJECT_H__
/*
*  DataObject.h
*
*  © Copyright 2001-2006 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/

#include "Object.h"

VOLANTE_NAMESPACE_BEGIN

class DataObjectSection;
class DataObjectMetaInfo;
/**
* Generic object that encapsulates a hierarchical data structure. Fields of the data 
* structure can be accessed by name or by index. The index parameter is the 
* 0 based index of field as defined in the transform designer.
* The class also provides metainfo about the data structure. The names
* of the fields can be obtained using the method getFieldName(index).
*
*
* <pre>
*    for(int i =0; i< obj->getFieldCount(); ++i) {
*     	
*	  }
* </pre>
*  <p> 
* The interface provides two ways of accessing the fields, by index and by name.
* Access by index is faster than access by name. In case of repeated access of a field,
* you can convert the fieldname to its index and then access it based on index. 
*
* <p> 
*
* Note that object representing a section (automatically created when the parent DataObject is created)
* is accessed the same way as any other field.
*
*  <pre>
*
*  NormalizedObject 
*    |
*    |--- Section1
*    |     |
*    |     |-- SecFld1
*    |     |-- SecFld2
*    |
*    |---- fld1
*    
*  </pre>
*
*  To get the section1's object, use the getField() or getSection() method (this is similar to accessing 
*  other fields). This object contains an array of DataObjects each of which contains the 
*  the fields in the section.  
*
*   <pre>
*   DataObjectSection* section1 = obj->getSection("Section1");
*   for(int i =0; i< section1->getElementCount(); ++i) {
* 		 DataObject* obj = section1->getElement(i)
*       IntObject* value = polymorphic_cast<IntObject*>(obj->getField("SecFld1"));
*		 // do something with values
*		 delete value;
*	 }
*
*   // To set an int field
*      IntObject val(10);
*    	obj->setField("fld", &val);
or
*    	obj->setField("fld", IntObject(10));

*   
*   </pre>
*
*   
*   
*
* A concrete implementation of the interface may provide a way to directly access the
* the field. For instance getFirstName() instead of getField("FirstName"). If it is 
* acceptable, it is always efficient to cast to the appropriate type and access
* the field directly using the getter. Another advantage of direct access is that you do not need to clean up the
* the returned object, since it is always returned by value (or owned by the DataObject)
*
* <p>
* Note that all fields including primitives in the data object can have a null value. 
*
* @see DataObjectSection
* @see NormalizedObject
* @see Object
*/
class VOLANTE_EXPORT DataObject  : public ObjectRef {
public:
	virtual ~DataObject() {
	}
	/**
	* Returns the object representing the section. If no such section is found throws FieldNotFoundException.
	* @param secName name of the section (as declared in the designer)
	* @return The section object
	* @throws FieldNotFoundException if the field is not found
	*/
	virtual DataObjectSection* getSection(const vstring& secName) const = 0;
	/**
	* Returns the object representing the section. If the index specified exceeds the field count it throws FieldNotFoundException.
	* The object returned is not owned by the client and should not be deleted.
	* @param index index of the field (as declared in the designer)
	* @return The field's value
	* @throws FieldNotFoundException if the field is not found
	*/
	virtual DataObjectSection* getSection(int index) const  = 0;
	/**
	* Returns the value of field. If no such field is found throws FieldNotFoundException.
	* The object returned is a wrapper object (such as IntObject, SectionObject etc.)
	* The object returned is owned by the client and should be deleted by the calling code.
	* @param fieldName Name of the field
	* @return The field's value
	* @throws FieldNotFoundException if the field is not found
	*/
	virtual Object* getField(const vstring& fieldName) const = 0 ;
	virtual bool  getField(const vstring& fieldName, Object& valueObject) const = 0 ;
	/**
	* Returns the value of field. If no such field is found throws FieldNotFoundException.
	* The object returned is a wrapper object (such as IntObject, SectionObject etc.)
	* The object returned is owned by the client and should be deleted by the calling code.
	* @param index Index of the field (as defined in the Designer)
	* @return The field's value as wraped object
	* @throws FieldNotFoundException if the field is not found
	*/
	virtual Object* getField(int index) const = 0 ;
	virtual bool getField(int index, Object& valueObject) const = 0 ;
	virtual Object* getFieldCheckNull(int index) const = 0;

	/**
	* Returns the value of field. If no such field is found throws FieldNotFoundException. This method 
	* returns an auto_ptr wrapping the Object* that is normally returned (by getField methods). This allows
	* you use the returned value without worrying about deleting it.
	*
	*  <pre>
	*      std::cout << obj->getFieldVal("ABC")->toString() << std::endl;
	*  </pre>
	* @param fieldName Name of the field
	* @return The field's value
	* @throws FieldNotFoundException if the field is not found
	*/
	virtual ObjectVal getFieldVal(const vstring& fieldName) const = 0;
	/**
	* Returns the value of field. If no such field is found throws FieldNotFoundException. This method 
	* returns an auto_ptr wrapping the Object* that is normally returned (by getField methods). This allows
	* you use the returned value without worrying about deleting it.
	*
	*  <pre>
	*      std::cout << obj->getFieldVal(i)->toString() << std::endl;
	*  </pre>
	* @param index Index of the field (as defined in the Designer)
	* @return The field's value
	* @throws FieldNotFoundException if the field is not found
	*/
	virtual ObjectVal getFieldVal(int index) const = 0;
	virtual ObjectVal getFieldCheckNullVal(int index) const = 0;

	/**
	* Returns true if the field is null. If the index specified exceeds the field count it throws FieldNotFoundException.
	* @param index index of the field (as declared in the designer)
	* @throws FieldNotFoundException if the field is not found
	* @return true if field has a null value else false.
	*/
	virtual bool isNull(int index) const = 0;

	/**
	* Returns true if the field is null. If no such field is found throws FieldNotFoundException.
	* @param fieldName Name of the field
	* @throws FieldNotFoundException if the field is not found
	* @return true if field has a null value else false.
	*/
	virtual bool isNull(const vstring& fieldName) const = 0;
	/**
	* Sets the field at the specfied index to null. If no such field is found throws FieldNotFoundException.
	* @param index index of the field (as declared in the designer)
	* @throws FieldNotFoundException if the field is not found
	*/
	virtual void setNull(int index)  = 0;

	/**
	* Sets the field at the specfied index to null. If no such field is found throws FieldNotFoundException.
	* @param fieldName Name of the field
	* @throws FieldNotFoundException if the field is not found
	*/
	virtual void setNull(const vstring& fieldName)  = 0;

	/**
	* Sets the field to the specified new value. If not such field is found throws FieldNotFoundException. Note the
	* the parameter passed (value) is owned by the caller and should be properly cleaned up if it was allocated on the heap.
	* @param fieldName Name of the field
	* @param value The field's value
	* @throws FieldNotFoundException if the field is not found
	* @throws FieldTypeMismatchException if the value cannot be set the specfied field
	*/
	virtual void setField(const vstring& fieldName, const Object* value)  = 0;
	virtual void setField(const vstring& fieldName, const Object& value)  = 0;


	/**
	* Sets the field to the specified new value. If the index specified exceeds the field count it throws FieldNotFoundException. Note the
	* the parameter passed (value) is owned by the caller and should be properly cleaned up if it was allocated on the heap.
	* @param index index of the field (as declared in the designer)
	* @param value The field's value
	* @throws FieldNotFoundException if the field is not found
	* @throws FieldTypeMismatchException if the value cannot be set the specified field
	*/
	virtual void setField(int index, const Object* value)  = 0;
	virtual void setField(int index, const Object& value)  = 0;

	/**
	* Returns the index of the field with specified name.
	* @throws FieldNotFoundException if the field is not found
	* @return field index
	*/
	virtual int getFieldIndex(const vstring& fieldName) const = 0;


	/**
	* Returns the type of the field at the specfied index as defined in the designer.
	* @ if the index is not valid
	* @return type of the field
	*/
	virtual const vstring& getFieldType(int index) const = 0;

	/**
	* Returns the type of the field at the specfied index as defined in the designer.
	* @throws FieldNotFoundException if the index is not valid
	* @return type of the field
	*/
	virtual const vstring& getFieldType(const vstring& name) const = 0;


	/**
	* Returns the name of the field at the specified index.
	* @throws FieldNotFoundException if the index is not valid
	* @return name of the field
	*/
	virtual const vstring& getFieldName(int index) const = 0;

	/**
	* Returns the qualified name of the field at the specified index.
	* @throws FieldNotFoundException if the index is not valid
	* @return name of the field
	*/
	virtual vstring getQualifiedName(int index) const = 0;

	/**
	* Returns the number of fields in the object. 
	* @return number of fields
	*/
	virtual int getFieldCount() const = 0;

	/**
	* Returns the section to which this object belongs or NULL(0) if this a top level (root) object.
	* @return parent section
	*/
	virtual DataObjectSection* getParentSection() const = 0;
	virtual void setParentSection(DataObjectSection* parentSection) = 0;

	virtual vstring toXMLString(int indent) const = 0;

	/**
	* Returns a XMLized string representation of this object. The tag names used are the field names defined 
	* in the designer. Since these name are allowed to have non-xml characters in between, the tag used is a 
	* mangled form of the field name (all special character are repleace by '-'.
	* 
	* 
	* @return XML string
	*/
	virtual vstring toXMLString() const = 0;

	/**
	* Returns the root data object. The root data object is top-level ancestor of this
	* object. Note that getParentSection() on the root object returns NULL.
	* @return root object
	*/
	virtual DataObject* getRootDataObject() const = 0;

	/**
	* Returns true if all the fields in this object are null and the sections have no elements
	* @return true if all fields are empty.
	*/
	virtual bool isEmpty() const = 0;
	//virtual void fromMap(java.util.Map map)throws TransformException = 0;

	virtual DataObjectMetaInfo* getMetaInfo() const =0;
	virtual void read(std::istream& in) =0 ;
	virtual void write(std::ostream& out) const =0;
	virtual void reset() = 0;

};

typedef DataObject NormalizedObject;

/**
*   DataObject wrapped by a auto_ptr. Useful for automatic cleanup.
*/
typedef SmartPtr<DataObject> DataObjectVal;

VOLANTE_NAMESPACE_END

#endif //__DATAOBJECT_H__

