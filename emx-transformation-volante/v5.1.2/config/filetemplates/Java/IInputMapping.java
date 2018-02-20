#if (${PACKAGE_NAME} != "")package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.handler.*;
import com.tplus.transform.runtime.*;

public class ${NAME} implements IInputMapping {
    
    public void map(InputObject input, NormalizedObject nf, TransformContext cxt) throws ValidationException {
        //perform processing here
    }
}
