\#include "Transform.h"

class ${NAME} : public IExternalMapping {
    public: virtual void map(ExternalObject* input, ExternalObject* output, TransformContext& cxt) {
        //perform mapping here
    }
};
REGISTER_CLASS(${NAME});