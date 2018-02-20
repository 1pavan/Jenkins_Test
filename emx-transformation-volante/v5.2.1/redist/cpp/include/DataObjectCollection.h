#ifndef __DATAOBJECTCOLLECTION_H__
#define __DATAOBJECTCOLLECTION_H__

VOLANTE_NAMESPACE_BEGIN

/*
*  DataObjectCollection.h
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
 *  DataObject* is created and is accessed the same way as any other field.
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
 *  To get the section1's object, use the getField() method (this is similar to accessing 
 *  other fields). This object contains an array of DataObjects each of which contains the 
 *  the fields in the section.  
 *
 *   <pre>
 *   DataObjectSection section1 = no.getField("Section1")=0;
 *   for(int i =0; i< section1.getElementCount()=0; ++i) {
 *       Integer value = (Integer)section1.getElement(i).getField("SecFld1")
 *	 }
 *   </pre>
 *  
 *
 *
 * @see DataObject*
 * @see DataObject*#getField(java.lang.String)
 * @see NormalizedObject
 */
class VOLANTE_EXPORT DataObjectCollection   {

public:
	virtual ~DataObjectCollection() {
	}

    /**
     * Returns the DataObject* at the specified index. If the index specified 
     * exceeds the number of object it .
     * @param index index of the object 
     * @return The DataObject* at the index
     * @ if the index exceeds size of the section
     */
    virtual DataObject* getElement(int index) const =0;
    
    /**
     * Removes the DataObject* at the specified index. If the index specified 
     * exceeds the section's size it .
     * @param index index of the object 
     * @return true
     * @ if the index exceeds size of the section
     */
    virtual bool removeElement(int index) =0;
    
    
    /**
     * Adds the specified data object to the end of this section, increasing its size by one.
     * Note that the following should be true.
     *      elm.getParentSection() == this
     */
    virtual void addElement(DataObject* elm) =0;
    
    /**
     * Returns the index of the specfied DataObject* or -1 if elm is not a child of this section
     * Note that the following should be true.
     *      elm.getParentSection() == this
     * @return The elements index or -1
     */
    virtual int getElementIndex(DataObject* elm) const =0;
    
    /** 
     * Returns the number of elements in this section.
     * @return Number of elements in the section.
     */
    virtual int getElementCount() const =0;
    
};

VOLANTE_NAMESPACE_END

#endif //__DATAOBJECTCOLLECTION_H__

