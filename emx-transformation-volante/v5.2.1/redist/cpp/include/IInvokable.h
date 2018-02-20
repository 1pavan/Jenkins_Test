#ifndef __IINVOKABLE_H__
#define __IINVOKABLE_H__

#include "ICustomClass.h"
#include "TransformContext.h"
VOLANTE_NAMESPACE_BEGIN

/** 
* Interface for external classes to validate a field of a Normalized object (internal message)
* or Input/Output Object (external message). The implementing class should check the value of the field and 
* return false if it is not valid.
* <p>The implementing class,  
* <ul>
*     <li> should have public default constructor
*     <li> should be made available during linking as an external library 
*     <li> should be stateless. The class should not maintain call specific data.
*     <li> since you specify the name the class in the Designer you need to call REGISTER_CLASS(validationclass)
*          at the end of your class declaration (in CPP file) to make it available 
*          to the runtime (for dynamic creation).
*
* </ul>
* <p>
* As many instances of the implementing class will be created as required. The class 
* should not expect all calls to be made to one particular instance. 
*
*  <pre>
*   class MyValidation : public IFieldValidation {
*      bool validate(const vstring& fldName, Object* value, DataObject* obj) {
*          // do your validation here
*         IntObject* intVal = polymorphic_cast<IntObject*>(value);
*         return intVal->intValue() > 10 &&  intVal->intValue() < 20;
*      }
*
*   }
*  </pre>
*   REGISTER_CLASS(MyValidation);
*
*/
class VOLANTE_EXPORT IInvokable : public ICustomClass {
public:
	/** 
	* Executes external (platform specific) code.
	*
	*  @param args args to external code
	*
	*  @returns return value of the external code
	*
	*  @see DataObject
	* 
	*/
	virtual Object* run(const ObjectList& args, TransformContext& cxt) = 0;
};

typedef SmartPtr<IInvokable> Invokable;
VOLANTE_NAMESPACE_END




#endif //__IINVOKABLE_H__
