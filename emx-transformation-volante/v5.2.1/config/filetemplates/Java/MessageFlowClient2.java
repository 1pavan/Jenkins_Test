#macro(getActualType $paramtype)
#set($paramtypes = ["String","Integer","Character","Boolean","BigDecimal","BigInteger","Binary", "DateOnly","DateTime","Double","Float","ISODate","ISODateTime","ISOTime","Long","TimeOnly","DataObject","RawMessage","Section"])
#set($actualtypes = ["String","Integer","Character","Boolean","java.math.BigDecimal","java.math.BigInteger","byte[]","java.util.Date","java.util.Date","Double","Float","java.util.GregorianCalendar","java.util.GregorianCalendar","java.util.GregorianCalendar","Long","java.util.Date","DataObject","RawMessage","DataObjectSection"])
#set ($TINDEX = 0)
#foreach( $param1 in $paramtypes )
#if($param1 == $paramtype)
#set($actualType = $actualtypes.get($TINDEX))
#end
#set ($TINDEX = $TINDEX + 1)
#end
#end
##! MESSAGE_FLOW=MessageFlow
#if (${PACKAGE_NAMES} != "")
package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.*;
import java.io.IOException;

public class ${NAME} {

	public static void main(String[] args) {
		com.tplus.transform.util.LoggingUtil.enableLogging("log.xml");
        String fileName = "data.txt";
        if(args.length > 0) {
            fileName = args[0];
        }

	    try {
			// Get the lookup context for the current environment
			LookupContext lcxt = LookupContextFactory.getLookupContext();
	
			// Lookup message flow (defined in the cartridge)
			MessageFlow messageFlow = lcxt.lookupMessageFlow("${MESSAGE_FLOW.Name}");
	
			// Create a TransformContext. We have no special properties to set in the context.
			TransformContext cxt = new TransformContextImpl();

	      	// Prepare the input for the message flow.
#foreach($param in ${MESSAGE_FLOW.InputVariables.asList()})
#set ($FIELD_SCOPE = $param.fieldScope.toString())
#set ($DESIGNER_TYPE = $param.type.toString())
#if($param.type.toString() == "Binary" || $param.type.toString() == "RawMessage") 
#if($FIELD_SCOPE != "IN/OUT")
	      	RawMessage $param.name  = new FileInputSource(fileName);
#else
	      	RawMessage $param.name  = new FileInputOutputMessage(fileName);
#end
#else 
#getActualType($DESIGNER_TYPE)
			$actualType $param.name = ...;
#end
#end 
	      	Object[] messageFlowArgs = new Object[] { #foreach($param in ${MESSAGE_FLOW.InputVariables.asList()}) $param.name, #end };

	      	// Execute the message flow.
	      	Object[] output = messageFlow.run(messageFlowArgs, cxt);

			// Use output
#set ( $INDEX = 0 )
#foreach($param in ${MESSAGE_FLOW.OutputVariables.asList()})
#getActualType($DESIGNER_TYPE)
#if($FIELD_SCOPE != "IN/OUT")
			$actualType $param.name = ($actualType)output[$INDEX];
#else
			$param.name = ($actualType)output[$INDEX];
#end
#set ( $INDEX = $INDEX + 1 )
#end 
	
	    }
	    catch(TransformException e) {
	      System.err.println(e.toXMLString());
	    }
	    catch(javax.naming.NamingException e) {
	      e.printStackTrace();
	    }
	    catch(java.rmi.RemoteException e) {
	      e.printStackTrace();
	    }
	    catch(java.io.IOException e) {
	      e.printStackTrace();
	    }
	}
}