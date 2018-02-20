#ifndef __REUTERSUTIL_H__
#define __REUTERSUTIL_H__
#include "Common/SystemException.h"			
#include "Common/GeneralExceptionStatus.h"
#include "Common/InvalidConfigurationException.h"
#include "Common/InvalidUsageException.h"

VOLANTE_NAMESPACE_BEGIN

class ReutersRespRawMessage : public AbstractRawMessage {
public:
	ReutersRespRawMessage(const rfa::message::RespMsg* respMsg) {
		this->respMsg = respMsg;
	}
	const char* getAsBytes(int& length) {
		const rfa::data::Buffer& buffer = respMsg->getPayload().getEncodedBuffer();
		const unsigned char * buf = buffer.c_buf();
		length = buffer.size();
		return (const char*)buf;
	}
	const rfa::message::RespMsg* getRespMessage() const {
		return respMsg;
	}
	const rfa::message::RespMsg* respMsg;
};
class ReutersUtils {
public:
	static inline vstring toVString(const rfa::common::RFA_String& str) {
		return vstring(str.c_str(), str.length());
	}
	static inline rfa::common::RFA_String toRMTESString(const vstring& str) {
		return rfa::common::RFA_String(str.c_str(), (int)str.length(), true);
	}
	static Binary toBuffer(const rfa::common::Buffer& str) {
		return Binary((const char*)str.c_buf(), str.size());
	}
	static rfa::common::Buffer toBinary(const Binary& str) {
		return rfa::common::Buffer((const unsigned char *)str.data(), (int)str.size());
	}

	static inline void checkException(rfa::common::Exception& e)
	{

		// Determine exception Severity
		int exceptionSeverity = e.getServerity();
		vstring excpSeverityStr;
		switch(exceptionSeverity)
		{
		case rfa::common::Exception::Error:
			excpSeverityStr = "Error";
			break;
		case rfa::common::Exception::Warning:
			excpSeverityStr = "Warning";
			break;
		case rfa::common::Exception::Information:
			excpSeverityStr = "Information";
			break;
		default:
			excpSeverityStr = "UNKNOWN Severity";
			break;
		}


		// Determine exception Classification
		int exceptionClassification = e.getClassification();
		vstring excpClassificationStr;
		switch(exceptionClassification)
		{
		case rfa::common::Exception::Anticipated:
			excpClassificationStr = "Anticipated";
			break;
		case rfa::common::Exception::Internal:
			excpClassificationStr = "Internal";
			break;
		case rfa::common::Exception::External:
			excpClassificationStr = "External";
			break;
		case rfa::common::Exception::IncorrectAPIUsage:
			excpClassificationStr = "IncorrectAPIUsage";
			break;
		case rfa::common::Exception::ConfigurationError:
			excpClassificationStr = "ConfigurationError";
			break;
		default:
			excpClassificationStr = "UNKNOWN Classification";
			break;
		}



		// Determine exception Type
		//rfa::common::Exception::CommonErrorType exceptionType;
		int exceptionType = e.getErrorType();
		vstring excpTypeStr;
		vstring excpStatusText;
		vstring	excpDetails;

		switch(exceptionType)
		{
		case rfa::common::Exception::InvalidUsageException:
			{
				excpTypeStr = "InvalidUsageException";
				InvalidUsageException& actualException = static_cast<InvalidUsageException&>(e);
				excpStatusText = actualException.getStatus().getStatusText().c_str();
				break;
			}
		case rfa::common::Exception::InvalidConfigurationException:
			{
				excpTypeStr = "InvalidConfigurationException";
				rfa::common::InvalidConfigurationException& actualException = static_cast<InvalidConfigurationException&>(e);
				excpStatusText = actualException.getStatus().getStatusText().c_str();
				excpDetails = vstring(actualException.getParameterName().c_str()) + " " + vstring(actualException.getParameterValue().c_str());
				break;
			}
#ifdef WIN32
		case rfa::common::Exception::SystemException:
			{
				excpTypeStr = "SystemException";
				SystemException& actualException = static_cast<SystemException&>(e);
				excpStatusText = actualException.getStatus().getStatusText().c_str();
				break;
			}
#endif
		default:
			{
				excpStatusText = "Unknown Exception Type!";
				break;
			}
		}

		// output exception information
		vstringbuffer tmpstr;
		tmpstr = "AN EXCEPTION HAS BEEN THROWN!  The following information describes the exception:";
		tmpstr.append("\n");
		tmpstr.append("Exception Type: ");
		tmpstr.append(excpTypeStr);
		tmpstr.append("\n");
		tmpstr.append("Exception Severity: ");
		tmpstr.append(excpSeverityStr);
		tmpstr.append("\n");
		tmpstr.append("Exception Classification: ");
		tmpstr.append(excpClassificationStr);
		tmpstr.append("\n");
		tmpstr.append("Exception Status Text: ");
		tmpstr.append(excpStatusText);
		tmpstr.append("\n");
		if (!excpDetails.empty())
		{
			tmpstr.append(excpDetails);
			tmpstr.append("\n");
		}

		std::cout << std::endl << std::endl;
		std::cout << tmpstr;
		TransformException te(excpStatusText);
		te.setSeverity(excpSeverityStr);
		throw te;
	}
};

VOLANTE_NAMESPACE_END
#endif //__REUTERSUTIL_H__
