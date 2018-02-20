#if (${PACKAGE_NAME} != "")package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.handler.*;
import com.tplus.transform.runtime.*;

public class ${NAME} implements IProcessing {

    public void process(DataObject obj) throws ValidationException {
        try	{
            //perform processing here
        }
        catch(FieldNotFoundException fnf) {
            //throw new ValidationException("Field Not Found");
        }
        catch(FieldTypeMismatchException fme) {
            //throw new ValidationException("Field Type Mismatch");
        }
    }
}

