\#include "Transform.h"

class ${NAME} : public IInputMapping {
    public: virtual void map(ExternalObject* invoiceInObj, NormalizedObject* no, TransformContext& cxt) {
        //perform mapping here
    }
};
REGISTER_CLASS(${NAME});