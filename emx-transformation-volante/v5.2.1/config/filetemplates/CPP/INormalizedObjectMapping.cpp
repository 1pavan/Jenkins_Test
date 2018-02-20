\#include "Transform.h"

class ${NAME} : public ICustomClass {
    public:	virtual void map(NormalizedObject* sourceNormalizedObject, NormalizedObject* destinationNormalizedObject, TransformContext& cxt) {
       //perform mapping here
    }
};
REGISTER_CLASS(${NAME});