#ifndef __TRANSFORMEXCEPTIONINTERNALMESSAGE_H__
#define __TRANSFORMEXCEPTIONINTERNALMESSAGE_H__

#include "AbstractInternalMessage.h"

VOLANTE_NAMESPACE_BEGIN


class VOLANTE_EXPORT TransformExceptionInternalMessage : public AbstractInternalMessage {
public:
	TransformExceptionInternalMessage() : AbstractInternalMessage("TransformException") {
    }

    NormalizedObject* createNormalizedObject()  {
        return new TransformException("");
    }

    NormalizedObject* processNormalizedObject(NormalizedObject* obj, ExceptionHandler* exceptionHandler, TransformContext& cxt)  {
        return obj;
    }
		ProcessingRules* getProcessingRules() {
			return NULL;
		}

};

VOLANTE_NAMESPACE_END

#endif //__TRANSFORMEXCEPTIONINTERNALMESSAGE_H__
