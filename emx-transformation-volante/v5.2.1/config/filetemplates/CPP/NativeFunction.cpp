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
##! FUNCTION=NativeFunction
\#include "Transform.h"

class ${NAME} : public IInvokable {
  public: virtual Object* run(const ObjectList& args, TransformContext& cxt) {
#set ( $INDEX = 0 )
#foreach($param in ${FUNCTION.Parameters.asList()})
#getObjectType($param.type.toString())
#if($param.type.toString()=="DataObject")       
       $objectType $param.name = polymorphic_cast<$objectType>(args[$INDEX]);
#else
       $objectType $param.name = ($objectType) args[$INDEX];
#end
#set ( $INDEX = $INDEX + 1 )
#end 
       // perform the operation here
#set ($returnType =$FUNCTION.FunctionReturnType.toString())
#if ($returnType=="Void")
       return null;
#else
#getObjectType($returnType)
       $objectType toRet = ...
       return toRet;
#end
  }
};
REGISTER_CLASS(${NAME});
