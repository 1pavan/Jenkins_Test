## Method returns the object type for a Designer Type
#macro(getObjectType $paramtype)
#set($designerTypes = ["String","Integer","Character","Boolean","BigDecimal","BigInteger","Binary", "DateOnly","DateTime","Double","Float","ISODate","ISODateTime","ISOTime","Long","TimeOnly","DataObject","RawMessage","Section"])
#set($objectTypes = ["StringObject*","IntObject*","CharObject*","BoolObject*","BigDecimalObject*","BigIntegerObject*","BinaryObject*","DateObject*","DateObject*","DoubleObject*","FloatObject*","ISODateObject*","ISODateObject*","ISODateObject*","LongObject*","DateObject*","DataObject*","RawMessageObject*","SectionObject*"])
#set ($TINDEX = 0)
#foreach( $param1 in $designerTypes )
#if($param1 == $paramtype)
#set($objectType = $objectTypes.get($TINDEX))
#end
#set ($TINDEX = $TINDEX + 1)
#end
#end
##
## Method returns the primitive type for a Designer Type
#macro(getPrimitiveType $paramtype)
#set($designerTypes = ["String","Integer","Character","Boolean","BigDecimal","BigInteger","Binary", "DateOnly","DateTime","Double","Float","ISODate","ISODateTime","ISOTime","Long","TimeOnly","DataObject","RawMessage","Section"])
#set($primitiveTypes = ["vstring","int","char","bool","BigDecimal","BigInteger","Binary","DateTime","DateTime","double","float","ISODateTime","ISODateTime","ISODateTime","dlong","DateTime","DataObject","RawMessage","SectionObject*"])
#set ($TINDEX = 0)
#foreach( $param1 in $designerTypes )
#if($param1 == $paramtype)
#set($primitiveType = $primitiveTypes.get($TINDEX))
#end
#set ($TINDEX = $TINDEX + 1)
#end
#end
##
##! MESSAGE_FLOW=MessageFlow
##
\#include "Transform.h"
\#include "FileInputSource.h"

// Include the cartridge. This is to force the linker to link the generated code.
USING_CARTRIDGE(....)
int main(int argc, const char* argv[]) {
    const char* fileName;
    if(argc < 2) {
       fileName = "data1.txt";
    }
    else {
        fileName = argv[1];
    }
    // Get the lookup context for the current environment
    LookupContext lcxt = LookupContextFactory::getLookupContext();
    // Lookup message flow (defined in the cartridge)
    MessageFlow messageFlow = lcxt->lookupMessageFlow("${MESSAGE_FLOW.Name}");
    // Create a TransformContext. We have no special properties to set in the context.
    TransformContext cxt;
    // Prepare the input for the message flow.
#foreach($param in ${MESSAGE_FLOW.InputVariables.asList()})
#if( $param.type.toString() == "RawMessage") 
    RawMessage $param.name  = new FileInputSource (fileName);
#elseif($param.type.toString() == "Binary" ) 
    Binary $param.name  =  FileInputSource (fileName).getAsBinary();
#else 
#getPrimitiveType($param.type.toString())
    $primitiveType $param.name = ...;
#end
#end 
    ObjectList messageFlowArgs;
#foreach($param in ${MESSAGE_FLOW.InputVariables.asList()})
    messageFlowArgs.add($param.name);
#end
    // Execute the message flow.
    ObjectList output = messageFlow->run(messageFlowArgs, cxt);
    // Use output
#set ( $INDEX = 0 )
#foreach($param in ${MESSAGE_FLOW.OutputVariables.asList()})
#getObjectType($param.type.toString())
#if($param.fieldScope.toString() != "IN/OUT")
    $objectType $param.name = ($objectType)output[$INDEX];
#else
    $param.name = ($objectType)output[$INDEX];
#end
#set ( $INDEX = $INDEX + 1 )
#end 
    return 0;
}
