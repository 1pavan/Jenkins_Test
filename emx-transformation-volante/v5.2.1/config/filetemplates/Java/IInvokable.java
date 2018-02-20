#if (${PACKAGE_NAME} != "")
package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.handler.*;
import com.tplus.transform.runtime.*;

public class ${NAME} implements IInvokable {
    public Object run(Object[] args, TransformContext cxt) throws TransformException {
        // perform the operation here
       return null;
   }
}
