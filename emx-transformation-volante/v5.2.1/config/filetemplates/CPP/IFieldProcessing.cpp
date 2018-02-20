\#include "Transform.h"

class ${NAME} : public IFieldProcessing {
	public:	virtual Object* processField(const vstring& fldName, DataObject* obj) {
       //perform processing here
       return NULL;
    }
};
REGISTER_CLASS(${NAME});