#if (${PACKAGE_NAME} != "")package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.*;
import com.tplus.transform.runtime.handler.*;

public class ${NAME} implements IFieldValidation {

    public void validate(String fldName, Object value, DataObject obj) throws FieldValidationException {		
        //check value here
        //if(failed)
        //throw new FieldValidationException("CostValidation: Cost for book '"+ bookSec.getName() +"' should be less than 6000 for subject '" + subSec.getName() + "'", "cost");		
    }
}
