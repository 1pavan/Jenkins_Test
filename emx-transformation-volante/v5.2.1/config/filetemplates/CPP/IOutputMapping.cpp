\#include "Transform.h"

class ${NAME} : public IOutputMapping {

    public: virtual void mapHeader(NormalizedObject* no, DataObject* headerObj, TransformContext& cxt){
        //perform mapping here
    }

    public: virtual void mapData(NormalizedObject* no, DataObject* dataObj, TransformContext& cxt){
        //perform mapping here
    }

    public: virtual void mapTrailer(DataObject* record, DataObject* trailerObj, TransformContext& cxt)  {
        //perform mapping here
    }
};
REGISTER_CLASS(${NAME});
