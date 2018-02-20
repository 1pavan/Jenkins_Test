#ifndef __SIACCANONICALSIACINPUTPARSER_H__
#define __SIACCANONICALSIACINPUTPARSER_H__
#include "SIACCanonicalInputParser.h"

VOLANTE_NAMESPACE_BEGIN

class SIACCanonicalSIACInputParser : public SIACCanonicalInputParser {
protected:
    IncomingCanonical inCan; 
		SIACCanonicalSIACInputParser() : inCan(CFO_NO_NULL_TERMINATION){
		}
		void handleParsingError(int result) {
        ErrorDetail detail;
        inCan.CF_GetErrorDetail(0, &detail);
				SIACCanonicalParsingException ex("Parsing error. Error Code = " + intToString(result));
				
        ex.setErrorCode(intToString(result));
        THROW_EXCEPTION(ex);
		}
		void handleFieldGetParsingError(int result) {
        ErrorDetail detail;
        inCan.CF_GetErrorDetail(0, &detail);
        SIACCanonicalParsingException ex("Parsing error. Error Code = " + intToString(result));
        ex.setErrorCode(intToString(result));
        THROW_EXCEPTION(ex);
		}
};
VOLANTE_NAMESPACE_END



#endif //__SIACCANONICALSIACINPUTPARSER_H__
