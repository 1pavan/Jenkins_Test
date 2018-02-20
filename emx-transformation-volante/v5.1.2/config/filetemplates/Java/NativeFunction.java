#macro(getActualType $paramtype)
#set($paramtypes = ["String","Integer","Character","Boolean","BigDecimal","BigInteger","Binary", "DateOnly","DateTime","Double","Float","ISODate","ISODateTime","ISOTime","Long","TimeOnly","DataObject","RawMessage","Section"])
#set($actualtypes = ["String","Integer","Character","Boolean","java.math.BigDecimal","java.math.BigInteger","byte[]","java.util.Date","java.util.Date","Double","Float","java.util.Calendar","java.util.Calendar","java.util.Calendar","Long","java.util.Date","DataObject","RawMessage","DataObjectSection"])
#set ($TINDEX = 0)
#foreach( $param1 in $paramtypes )
#if($param1 == $paramtype)
#set($actualType = $actualtypes.get($TINDEX))
#end
#set ($TINDEX = $TINDEX + 1)
#end
#end
##! FUNCTION=NativeFunction
#if (${PACKAGE_NAME} != "")package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.handler.*;
import com.tplus.transform.runtime.*;

public class ${NAME} implements IInvokable {

    public Object run(Object[] args, TransformContext cxt) throws TransformException {
#set ($INDEX = 0)
#foreach($param in ${FUNCTION.Parameters.asList()})
#getActualType($param.type.toString())
       $actualType $param.name = ($actualType) args[$INDEX];
#set ($INDEX = $INDEX + 1)
#end
       // perform the operation here
#set ($returnType =$FUNCTION.FunctionReturnType.toString())
#if ($returnType=="Void")
       return null;
#else
#getActualType($returnType)
       $actualType toRet = ...
       return toRet;
#end
    }
}