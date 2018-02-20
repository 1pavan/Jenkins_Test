\#include "Transform.h"

class ${NAME} : public IInvokable {
  public: virtual Object* run(const ObjectList& args, TransformContext& cxt) {
        // perform the operation here
        return NULL;
  }
};
REGISTER_CLASS(${NAME});
