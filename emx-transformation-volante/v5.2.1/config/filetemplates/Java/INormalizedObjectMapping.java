#if (${PACKAGE_NAME} != "")package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.handler.*;
import com.tplus.transform.runtime.*;

public class ${NAME} implements INormalizedObjectMapping {

    public void map(NormalizedObject sourceNormalizedObject, NormalizedObject destinationNormalizedObject, TransformContext cxt) throws ValidationException {  
        //perform mapping here
    }
}
