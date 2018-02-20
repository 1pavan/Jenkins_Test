#if (${PACKAGE_NAME} != "")package ${PACKAGE_NAME};
#end
import com.tplus.transform.runtime.handler.*;
import com.tplus.transform.runtime.*;

public class ${NAME} implements IOutputMapping {

    public void mapHeader(NormalizedObject nf, DataObject header, TransformContext cxt) throws ValidationException {
        //perform mapping for header here
    }

    public void mapData(NormalizedObject nf, DataObject record, TransformContext cxt) throws ValidationException {
        //perform mapping for data here
    }

    public void mapTrailer(DataObject record, DataObject trailer, TransformContext cxt) throws ValidationException {
        //perform mapping for trailer here
    }
}
