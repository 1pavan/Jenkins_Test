#ifndef __OUTPUTFORMAT_H__
#define __OUTPUTFORMAT_H__
#include "OutputDevice.h"
#include "DataObject.h"
#include "TransformContext.h"
#include "Service.h"
VOLANTE_NAMESPACE_BEGIN
/**
 *  @deprecated
 */
class VOLANTE_EXPORT IOutputFormat : public IService {
public:
	virtual void setOutputDevice(OutputDevice* device) = 0;
    /**
     *  Writes the output mapped from the DataObject* to a device using the
     *   protocol specified in the context.
     *
     *  <p>This method is responsible for,
     *  <ul>
     *    <li> Mapping the DataObject* to output
     *    <li> Validating the output
     *    <li> Sending the output to a device using the protocol specified in the context.
     *  </ul>
     *
     *  @see DataObject*
     *  @see TransformContext&
     */
    virtual void write(NormalizedObject* no, TransformContext& cxt)=0;

};

typedef SmartPtr<IOutputFormat> OutputFormat;

VOLANTE_NAMESPACE_END

#endif //__OUTPUTFORMAT_H__

