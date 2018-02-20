#if (${PACKAGE_NAME} != "")package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.handler.*;
import com.tplus.transform.runtime.*;

public class ${NAME} implements IExternalMapping {
    
    public void map(ExternalObject input, ExternalObject output, TransformContext cxt) throws ValidationException {
        //perform processing here
    }
}
