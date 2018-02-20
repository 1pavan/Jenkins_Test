#ifndef __DATAOBJECTSECTION_H__
#define __DATAOBJECTSECTION_H__
#include "DataObject.h"
#include "DataObjectCollection.h"

VOLANTE_NAMESPACE_BEGIN


/*
*  DataObjectSection.h
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

/**
 * The runtime representation of a section.
 * The DataObjectSection interface encapsulates an array(growable) of data objects. 
 *  Note that object representing a section is automatically created when the parent 
 *  DataObject is created and is accessed the same way as any other field.
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
 *   DataObjectSection* section1 = no->getSection("Section1");
 *   for(int i =0; i< section1->getElementCount(); ++i) {
 *       IntObject* value = polymorphic_cast<IntObject*>(section1->getElement(i)->getField("SecFld1"));
 *		 // do something with values
 *		 delete value;
 *	 }
 *   </pre>
 *  
 *   You can iterate over the elements of the section, cast them to appropriate type and access its fields.
 *
 * @see DataObject
 * @see DataObject#getField
 * @see DataObject#getSection
 */
class VOLANTE_EXPORT DataObjectSection : public DataObjectCollection {

public:


    /**
     * Returns the DataObject at the specified index. If the index specified 
     * exceeds the number of object it throws FieldNotFoundException.
     * @param index index of the object 
     * @return The DataObject at the index
     * @throws FieldNotFoundException if the index exceeds size of the section
     */
	virtual DataObject* getElement(int index) const  =0;

    /**
     * Removes the DataObject at the specified index. If the index specified 
     * exceeds the section's size it throws FieldNotFoundException.
     * @param index index of the object 
     * @return true
     * @throws FieldNotFoundException if the index exceeds size of the section
     */
	virtual bool removeElement(int index)  =0;

    /**
     * Creates a new raw data object that <b>can</b> be added to this section.
     * @return The child DataObject.
     */
	virtual DataObject* createElement() =0;

	/**
	* Adds the specified data object to the end of this section, increasing its size by one.
	* Note that the following should be true.
	* elm->getParentSection() == this
	*/
	virtual void addElement(DataObject* elm) =0;

	/**
	* Returns the index of the specfied DataObject* or -1 if elm is not a child of this section
	* Note that the following should be true.
	*      elm->getParentSection() == this
	* @return The elements index or -1
	*/
	virtual int getElementIndex(DataObject* elm) const =0;

	/** 
	* Returns the number of elements in this section.
	* @return Number of elements in the section.
	*/
	virtual int getElementCount() const =0;

	/** 
	* Returns the name of this section (as specfied in the designer).
	*/
	virtual vstring getName() const =0;

	/** 
	* Returns the fully qialified name of this section. It includes the names of all its
	* ancestor separated by '.'.
	*/
	virtual vstring getQualifiedName() const =0;

	/**
	* Returns the parent DataObject. This section object is a field in the returned DataObject.
	* For instance the following is true, 
	* <pre>
	*    section->getParent()->getField(section.getName()) == section
	* <pre>
	*/
	virtual DataObject* getParent() const =0;

	/**
	* Returns the root data object. The root data object is top-level ancestor of this
	* section (getParentSection() of the root returns null).
	* @return root object
	*/
	virtual DataObject* getRootDataObject() const =0;

	/**
	* Asserts the cardinality constraints for the section. If this object 
	* does not satisfy the constraints a SectionConstraintException is thrown.
	* Normally, you would not have to call this method. It is called internally 
	* as part of DataObject validation.
	*/
	virtual void assertConstraints()const  =0;

    /**
     * Returns true if this section has zero elements or if every element it contains has all fields as null.
     * @return true if this section is empty.
     */
	virtual bool isEmpty()const =0;

	virtual void removeLastElement() =0;

  virtual void clear() = 0;

	virtual DataObjectSection* clone() const = 0; 

	static void assign(DataObjectSection* dest,DataObjectSection* src);
};

VOLANTE_NAMESPACE_END

#endif //__DATAOBJECTSECTION_H__

