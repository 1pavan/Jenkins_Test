#ifndef __IOUTPUTMAPPING_H__
#define __IOUTPUTMAPPING_H__

#include "ICustomClass.h"
VOLANTE_NAMESPACE_BEGIN

/** 
 * Interface for external classes to map the Normalized object to output.
 * The implementing method can access the fields in the Normalized objcet and update the fields 
 * in the Output object.
 *
 * Note that custom mapping class is called after applying the mappings
 * specified in the designer. 

 * <p>The implementing class,  
 * <ul>
 *     <li> should have a public default constructor
 *     <li> should be made available during linking as an external library 
 *     <li> should be stateless. The class should not maintain call specific data.
 *     <li> since you specify the name the class in the Designer you need to call REGISTER_CLASS(mappingclass)
 *          at the end of your class declaration (in CPP file) to make it available 
 *          to the runtime (for dynamic creation).
 * </ul>
 *
 * As many instances of the implementing class will be created as required. The class 
 * should not expect all calls to be made to one particular instance. 
 *
 */
class VOLANTE_EXPORT IOutputMapping : public ICustomClass {
public:
    /** 
     * Maps the Normalized object to header of the output.
     * The implementing method can access the fields of the Normalized object 
     * and update the fields of the Header.This method is called once for 
     * the entire batch with first NormalizedObject in the batch.
     * 
     * Note that custom mapping class is called after applying the mappings
     * specified in the designer. 
     *
     *
     * @param nf    The Normalized object.
     * @param header The output header that needs to be mapped from the normalized object. 
     * @param cxt   The context in which transformation occurs.
     *
     * @see DataObject#getField
     * @see DataObject#setField
     *
     * @exception ValidationException if a field was found to be invalid
     * and it affects further processing.
     */
    virtual void mapHeader(NormalizedObject* nf, DataObject* header, TransformContext& cxt) =0;


   /** 
     * Maps the Normalized object to output record.
     * The implementing method should access the fields of the Normalized object 
     * and update the fields of the record.
     * 
     * Note that custom mapping class is called after applying the mappings
     * specified in the designer. 
     *
     *
     *
     * @param nf    The Normalized object.
     * @param record The output record that needs to be mapped from the normalized object. 
     * @param cxt   The context in which transformation occurs.
     *
     * @see DataObject#getField
     * @see DataObject#setField
     *
     * @exception ValidationException if a field was found to be invalid
     * and it affects further processing.
     */
    virtual void mapData(NormalizedObject* nf, DataObject* record, TransformContext& cxt) =0;

    /** 
     * Maps the Data object (the record or the body of the output) to trailer.
     * The implementing method can access the fields of the record object 
     * and update the fields in the trauler.This method is called once for 
     * each record in the batch. The state of the trailer
     * is maintained across calls to this method (for the batch).
     *
     * Note that custom mapping class is called after applying the mappings
     * specified in the designer. 
     *
     *
     * @param record    The record or the body of the output
     * @param trailer The output trailer that needs to be mapped from the normalized object. 
     * @param cxt   The context in which transformation occurs.
     *
     * @see DataObject#getField
     * @see DataObject#setField
     *
     * @exception ValidationException if a field was found to be invalid
     * and it affects further processing.
     */
    virtual void mapTrailer(DataObject* record, DataObject* trailer, TransformContext& cxt)  = 0;
};

VOLANTE_NAMESPACE_END

#endif //__IOUTPUTMAPPING_H__

