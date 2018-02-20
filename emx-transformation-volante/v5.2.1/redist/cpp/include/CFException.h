/*****************************************************************************
*                                                                            *
* Module  CFException.h                                                      *
*                                                                            *
* Date     Item Release  Author Descriptions                                 *
* -------- ---- -------- ------ ------------                                 *
* 12/08/04      03.10.02 Z.P    Initial version of CFException class         *
*                                                                            *
*****************************************************************************/
#ifndef CF_Exception
#define CF_Exception

#ifdef _NT_BUILD
#define DECLSPEC	1
#ifdef _NT_EXE_BUILD
#define	DECLSPEC_TOKEN	dllimport
#define	DECLSPEC_TOKEN2	dllimport
#endif
#ifdef _NT_LIB_BUILD
#define	DECLSPEC_TOKEN	dllexport
#define	DECLSPEC_TOKEN2	dllimport
#endif
#ifdef _NT_LIB2_BUILD
#define	DECLSPEC_TOKEN	dllimport
#define	DECLSPEC_TOKEN2	dllexport
#endif
#endif

#define CFE_MAX_TEXT_SIZE 200

class CFException
{
public:
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CFException(int code=0, const char* text=(const char*)0, int severity=0)
	{
		lCode = code;
		if (text != (const char*)0)
			strncpy(lText,text,strlen(text)>CFE_MAX_TEXT_SIZE?CFE_MAX_TEXT_SIZE:strlen(text));
		lSeverity = severity;
	}

#ifdef DECLSPEC   
__declspec( DECLSPEC_TOKEN ) 
#endif
	int getCode() {return (lCode);}
#ifdef DECLSPEC   
__declspec( DECLSPEC_TOKEN ) 
#endif
	const char* getText() {return (lText);}
#ifdef DECLSPEC   
__declspec( DECLSPEC_TOKEN ) 
#endif
	int getSeverity() {return (lSeverity);}

protected:
	int lCode;
	char lText[200];
	int lSeverity;
};
#endif // CFException
