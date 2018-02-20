\#include "Transform.h"

class ${NAME} : public IFieldValidation{
    public:	bool validate(const vstring& fldName, const Object* value, DataObject* obj) {
       //check value here
       //if(failed)
       //THROW_EXCEPTION(FieldValidationException("Invalid Value", fldName));
       return true;
    }
};
REGISTER_CLASS(${NAME});