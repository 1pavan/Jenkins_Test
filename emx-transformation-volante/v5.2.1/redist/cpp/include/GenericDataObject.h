#ifndef __GENERICDATAOBJECT_H__
#define __GENERICDATAOBJECT_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT GenericDataObject : public DataObjectBase {
public:
	GenericDataObject(const GenericDataObject& copyFrom) ;
	GenericDataObject(DataObjectMetaInfo* metaInfo, bool ownMetaInfo = false) ;
	GenericDataObject(DataObjectSection* parentSection, DataObjectMetaInfo* metaInfo, bool ownMetaInfo = false) ;
	~GenericDataObject();
	void reset();
private:
	void init(DataObjectSection* parentSection, DataObjectMetaInfo* metaInfo, bool ownMetaInfo = false);
	void checkFieldIndex(int index)  const;
public:
	Object* getField(int index)  const;
	Object* getField(const vstring& fieldName)  const {
		return DataObjectBase::getField(fieldName);
	}
	bool getField(int index, Object& valueObject)  const;

	Object* getFieldCheckNull(int index)  const;
	DataObjectSection* getSection(const vstring& secName)  const;
	DataObjectSection* getSection(int index) const;
	/**
	* Returns true if the field is NULL. If the index specified exceeds the field count it throws FieldNotFoundException.
	* @param index index of the field (as declared in the designer)
	* @throws FieldNotFoundException if the field is not found
	* @return The field's value
	*/
	bool isNull(int index) const;
	bool isNull(const vstring& fieldName) const {
		return DataObjectBase::isNull(fieldName);
	}
	void setNull(int index);
	void setNull(const vstring& fieldName) {
		DataObjectBase::setNull(fieldName);
	}
	bool isSynthesized(int index) const;

	/**
	* Sets the field to the specified new value. If the index specified exceeds the field count it throws FieldNotFoundException.
	* @param fieldName Name of the field
	* @param value The field's value
	* @throws FieldNotFoundException if the field is not found
	* @throws FieldTypeMismatchException if the value cannot be set the specfied field
	*/
	void setField(int index, const Object* value);

	void setField(int index, const Object& value) {
		DataObjectBase::setField(index, value);
	}
	void setField(const vstring& fieldName, const Object* value) {
		DataObjectBase::setField(fieldName, value);
	}
	void setField(const vstring& fieldName, const Object& value) {
		DataObjectBase::setField(fieldName, value);
	}

	/**
	* Returns the section to which this object belongs or NULL if this a top level (root) object.
	* @return parent section
	*/
	DataObjectSection* getParentSection() const;
	void setParentSection(DataObjectSection* parentSection);
	/**
	* Returns the root data object. The root data object is top-level ancestor of this
	* object (getParentSection() on the root object returns NULL).
	* @return root object
	*/
	DataObject* getRootDataObject()  const;
	int getFieldCount() const ;
	int getFieldIndex(const vstring& fieldName) const;
	const vstring& getFieldType(const vstring& fieldName) const;
	const vstring&  getFieldType(int index) const;
	const vstring&  getFieldName(int index) const;
	FieldMetaInfo* getFieldMetaInfo(int index)  const;
	vstring getQualifiedName(const vstring& fieldName) const;
	vstring getQualifiedName(int index) const ;
	DataObjectMetaInfo* getMetaInfo()  const;
	DataObject* createSectionElement(const vstring& sectionName, DataObjectSection* parentSection) const;
	bool isEmpty() const;
	virtual vstring getRootXMLTag() const ;
	Object* clone() const;
private:
	DataObjectSection* parentSection;
	int fieldCount;
	Object** data;
	DataObjectMetaInfo* metaInfo;
	bool ownMetaInfo;
};


VOLANTE_NAMESPACE_END

#endif //__GENERICDATAOBJECT_H__

