#if (${PACKAGE_NAME} != "")package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.handler.*;
import com.tplus.transform.runtime.*;

public class ${NAME} implements IFieldProcessing {

    public Object processField(String fldName, DataObject obj) throws FieldValidationException	{
        //perform processing here
        return null;
    }
}
