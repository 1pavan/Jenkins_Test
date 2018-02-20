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
##! MAPPING=Mapping
#if (${PACKAGE_NAME} != "")
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
			MessageMapping mapping = lcxt.lookupMessageMapping("${MAPPING.Name}");
	
			// Create a TransformContext. We have no special properties to set in the context.
			TransformContext cxt = new TransformContextImpl();

	      	DataObject input = mapping.createInputDataObject();
	      	// Prepare the input for the mapping.
#set ( $INDEX = 0 )
#foreach($param in ${MAPPING.getSourceFormat().asList()})
#set ($DESIGNER_TYPE = $param.type.toString())
#if($param.type.toString() == "Binary" || $param.type.toString() == "RawMessage") 
	      	RawMessage $param.name  = new FileInputSource(fileName);
#else 
#getActualType($DESIGNER_TYPE)
			$actualType $param.name = ...;
#end
			input.setField($INDEX, $param.name);
#set ( $INDEX = $INDEX + 1 )
#end 

	      	DataObject output = mapping.createOutputDataObject();
	      	// Prepare the output for the mapping (optional).
#set ( $INDEX = 0 )
#foreach($param in ${MAPPING.getDestinationFormat().asList()})
#if($param.type.toString() == "DataObject" || $param.type.toString() == "DataObjectSection") 
			//output.setField($INDEX, $param.name);
#end
#set ( $INDEX = $INDEX + 1 )
#end 

	      	// Execute the mapping.
	      	mapping.map(input, output, cxt);

			// Use output
#set ( $INDEX = 0 )
#foreach($param in ${MAPPING.getDestinationFormat().asList()})
#set ($DESIGNER_TYPE = $param.type.toString())
#getActualType($DESIGNER_TYPE)
			$actualType $param.name = ($actualType)output.getField($INDEX);
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