/**********************************************************************
**                                                                    *
**  Copyright (c) The Bank of New York, January 19, 2007               *
**  All Rights Reserved.                                              *
**                                                                    *
**  The information contained herein is confidential and proprietary  *
**  to Bank of New York.  Any unauthorized use, duplication, or       *
**  disclosure is prohibited by law.                                  *
**                                                                    *
**********************************************************************/

/**********************************************************************
**                                                                    *
**  Author:		Liping Shen                                           *
**                                                                    *
**	Comments:	This module contains the functions to format the CHP  *
**				messages for MTS.                                     *
**                                                                    *
**	History:	                                                      *
**  Date:		Name:			Description of current change:        *
**  ----------	-----------		------------------------------        *
**	01/19/2007	Liping Shen		Initial Version						  *
**                                                                    *
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "fniGwyStatus.h"
#include "fniGwyTime.h"
#include "fniGwySharedMemory.h"
#include "fniGwyTrace.h"
#include "fniGwyTraceWrap.h"
#include "fniGwyXml.h"
#include "fniGwyEnv.h"

#include "fniGwyBusiness.h"
#include "fniGwyBm.h"
#include "fniGwyAuth.h"
#include "fniGwySwfStr.h"
#include "fniGwyLTEnv.h"
#include "fniGwySvcClient.h"

#define MAXCORRDATALEN		512

#define APPHOST				"ApplicationHost"
#define MTSSOURCE			"MTSSource"
#define MTSHIGHSOURCE		"MTSHighSource"
#define MTSMEDIUMSOURCE		"MTSMediumSource"
#define MTSLOWSOURCE		"MTSLowSource"
#define MTSIBRSOURCE		"MTSIBRSource"
#define MTSIBRHSOURCE		"MTSIBRHSource"
#define MTSIBRMSOURCE		"MTSIBRMSource"
#define MTSERRSOURCE		"MTSErrSource"
#define CHECKSUM			"Checksum"
#define USESAT				"UseSat"
#define CHANGESEQ			"ChangeSequenceNumber"
#define IBRBIC8NAME			"IBRBIC8Name"
#define IBRBIC8LIST			"IBRBIC8NameList"
#define HANDLEBLOCK3FORIBR	"HandleBlock3ForIBR"
#define NOIBRFORSAMEBIC		"NoIBRForSameBIC"
#define BIC8NAME			"BIC8Name"
#define LTERMDEFLIST		"LTermDefList"
#define LTERMDEF			"LTermDef"
#define LTERMNAME			"LTermName"
#define APPLICATIONID		"Application ID:"
#define IBRSEQFILENAME		"IBRSeqFileName"
#define	DEFAULTERRORCODE	"ERR"
#define SVCSERVERLIST		"SvcServerList"
#define SVCSERVERDEF		"SvcServerDef"
#define HOSTNAME			"HostName"
#define PORT				"Port"
#define SERVER				"Server"
#define DEFAULTSVCPORT		"DefaultSvcPort"
#define DEFAULTSVCSVR		"DefaultSvcSvr"
#define EDITSUCCESS			"SUCCESS"
#define EDITCHECKBYSWIFT	"EditCheckBySwift"
#define PASSERRMSGTOSWF		"PassErrMsgToSwf"
#define ERRCODE				"ERRCODE"
#define VLERROR				"VLERROR"
#define PROCESSIBR			"ProcessIBR"
#define ALERTEMAILLIST		"AlertEmailList"
#define ALERTEMAILADDRESS	"AlertEmailAddress"
#define TRANSFORINTERNALFMT	"TransformInternalFmt"
#define TRANSFORSWIFTTOSWIFT	"TransformSwiftToSwift"
#define NoVALIDATION			"NoValidation"
#define RESERVEADDRESS			"ReserveAddress"

#define MAX_ALERTEMAILS		20
#define EMAILADDRESSLEN		128



#define CORRELATION_DATA	"Correlation-Data: "
#define PRIORITY_DATA		"Priority: "
#define HIGH				"High"
#define MEDIUM				"Medium"
#define LOW					"Low"
#define MSGRTRBLOCK1		"[{1:"
#define APPID				"ApplicationId"
#define MAINAPPID			"MainApplicationId"
#define MERVA				1
#define MSGRTR				2
#define BLOCK1				"{1:"
#define BLOCK2				"{2:"
#define DATABEG				"?DATA"
#define TAG97				":97A:"
#define TAG25				":25:"
#define OWNBIC8POSITIN		6
#define CORRBIC8POSITIN		7
#define GPAORFINLEN			3
#define APPIDLEN			3
#define PRIORITYPOS			19
#define BIC8LEN				8
#define BIC11LEN			11
#define B2ILTPOS			7
#define B2IMTPOS			4
#define LTERMLEN			9
#define TIDLEN				1
#define TIDPOS				15
#define BIC8POS				13
#define B1BIC8POS			6
#define B2BIC8POS			14
#define B2BRANCHPOS			23
#define B1SEQNUMPOS			22
#define SEQNUMBELEN			6
#define MAXMTLTERMLIST		128
#define BRANCHLEN			3
#define FIELDLEN			256
#define MAX_MTTYPE			256
#define SVCSVR_LEN			256
#define MAX_APPLTERMS		5
#define BIC12LEN			12
#define B2MTTYPEPOS			4


#define PRIORITYHIGH		1
#define PRIORITYMEDIUM		2
#define PRIORITYLOW			3

#define HOSTNAMELEN			32
#define MAX_SVCSERVER		16
#define NOSVC				-1
#define MAX_EDIT_LENGTH		20000
#define MAX_SVC_BUF			20000
#define FORMAT_LEN			4
#define SVCHANDLER_LEN		8
#define MTSRSPLEN			10
#define MTSTRNLEN			16
#define MRVRSPOK			"Yes"
#define MRVRSPDEL			"DEL"
#define MRVRSPERR			"ERR"
#define MRVRSPNEW			"NEW"

#define NEWGAP				-2
#define DUPLICATED			-1
#define MAXIMUMGAP			"MaximumGap"
#define MAXIMUMNUMBEROFGAPS	"MaximumNumberOfGaps"
#define MAXIMUMSEQNUMBER	"MaximumSequenceNumber"
#define EXCEEDMAXIMUMGAP	"Sequence gap exceeds the maximum gap limit"
#define DUPLICATEDMESSAGE	"FNI ISN gateway is down -- received duplicate message"
#define EXCEEDMAXIMUMNUMGAP	"The number of sequence gaps exceeds the maximum limit"
#define PASSAREALENGTH		"PassAreaLength"
#define SEQNUMBERLENGTH		"SeqNumberLength"
#define SEQNUMBERSTARTPOS	"SeqNumberStartPos"
#define EDITSVCFAIL			"{ERRCODE:40002}{ERRMSG:The service of Swift edit check is down.}"
#define EDITCHKFAIL			"{ERRCODE:40001}{ERRMSG:Swift edit check failed.}"

#define PRIORITYDEFLIST		"PriorityDefList"
#define PRIORITYDEF			"PriorityDef"
#define PRIORITY			"Priority"
#define MTTYPE				"MTType"
#define SUPPORTEDMTTYPELIST	"SupportedMTTypeList"
#define PROCESSGAPCHECK		"ProcessGapCheck"
#define RCVREPMSG			"ReceiveRepairedMsg"

#define EDITCHECK			"EditCheck"
#define EDITCHECKOP			"editCheckOp"
#define TRANSFORMOP			"transformOp"
#define TRANSFORM			"Transform"
#define GENGTMACK			"FniAckGtm"
#define GENGTMACKOP			"gtmAckOp"
#define RECEIVED			"Received"
#define BNYPA1200TYPE1TOSWIFT		"BNYPA1200Type1ToSwift"
#define BNYINTERNALTOSWIFTBLOCK4	"BNYInternalToSwiftBlock4"
#define SWIFTTOSWIFTBLOCK4			"SwiftToSwiftBlock4"
#define SWIFTTOSWIFTBLOCK4NV		"SwiftToSwiftBlock4NV"

#define USEMATADATA			"UseMetaData"
#define USEBLOCK1SEQNUM		"UseBlock1SeqNum"

#define INOGAPCHECK			0
#define IUSE1200PASSAREA	1
#define IUSEMATADATA		2
#define IUSEBLOCK1SEQNUM	3


#define MISSINGBLOCK1		"{ERRCODE:30001}{ERRMSG:Missing Block 1}"
#define MISSINGBLOCK2		"{ERRCODE:30002}{ERRMSG:Missing Block 2}"
#define INVALIDLT			"{ERRCODE:30003}{ERRMSG:Invalid Logical Terminal}"
#define INVALIDMTTYPE		"{ERRCODE:30004}{ERRMSG:Invalid MT Type}"
#define INVALIDPASSAREA		"{ERRCODE:30005}{ERRMSG:Invalid Pass Area}"
#define TRANSFORMERR		"{ERRCODE:30006}{ERRMSG:Failed to Transform Internal Format to Swift Format}"
#define GETGTMERR			"{ERRCODE:30007}{ERRMSG:Failed to Get GTM ACK}"
#define TRANSFORMERRSWIFT	"{ERRCODE:30008}{ERRMSG:Failed to Transform Swift Format to Swift Format}"
#define BADSWFADDRESS		"{ERRCODE:30009}{ERRMSG:Failed to Find Swift Address From CIF Database}"
#define STOSERRCODE			"{ERRCODE:30009}{ERRMSG:"
#define OUTSRCERRCODE		"{ERRCODE:30010}{ERRMSG:Invalid Outsoucing code: "
#define INVALIDBIC			"{ERRCODE:30011}{ERRMSG:Invalid BIC: "

#define MISSINGBLOCK1ERRCODE	"2001"
#define MISSINGBLOCK2ERRCODE	"2002"
#define INVALIDLTERRCODE		"2003"
#define INVALIDMTTYPEERRCODE	"2004"
#define MESSAGEFORMAT			"MessageFormat"
#define NORMALFORMAT			"Normal"
#define STDFORMAT				"Standard"
#define INORMALFORMAT			1
#define ISTDFORMAT				2
#define BLOCK3					"{3:"
#define TAG108					"{108:"
#define MERVABLOCK1				"{1:"
#define ANNUALFORMAT			"AnnualFormat"
#define USEWEBSVC				"UseWebSvc"
#define METADATA				"{METADATA:"
#define CORRID					"{CORRID:"
#define APPDEFLIST				"AppDefList"
#define APPDEF					"AppDef"
#define APPNAME					"ApplicationName"
#define APPLTERMLIST			"AppLTermList"
#define APPLTERM				"AppLTerm"
#define PASSAREA				"PassArea"
#define PASSAREALEN				1200
#define PASSAREALENSTR			"1200"
#define NUMBEROFONDEMANDMQS		"NumberOfOnDemandMQs"
#define CREATEHEADERBLOCK		"CreateHeaderBlock"
#define DRAINMESSAGE			"DrainMessage"
#define SUPPORTTEO				"SupportTEO"
#define TEO						"TEO"
#define BNYTRN					"BNYTRN"
#define CUSTID					"CUSTID"
#define RCVADD1					"RCVADD1"
#define RCVADD2					"RCVADD2"

#define BNYTRNPOS				13
#define BNYTRNLEN				16
#define CUSTIDPOS				966
#define CUSTIDLEN				5
#define RCVADD1POS				292
#define RCVADD1LEN				35
#define RCVADD2POS				327
#define RCVADD2LEN				35
#define SRFLAGPOS				1066
#define SRFLAGLEN				1
#define FSINDPOS				949
#define FSINDLEN				1
#define RECVADDPOS				292
#define CHRGADDPOS				553
#define ADDRESSLEN				35
#define MSGIDPOS				243
#define MSGIDLEN				7

#define ASN_LEN					9
#define ASNNUM_LEN				5
#define ASNNUMPOS				8
#define ASNPOS					4

#define MTSTRN					"MTSTRN: "
#define APPREP					"APP: "
#define MRVRESP					"MRV-RESP:"
#define MRVDE					"MRV-DE:"
#define MRVTRAC					"MRV-TRACE:"
#define APPDE					"APPL:"
#define MRVCORRID				"CORR-ID: "

#define HB2BIC8POS				953
#define HB2SBCHPOS				961
#define SBCHLEN					3
#define MTTYPEPOS				950
#define MTTYPELEN				3
#define SESSSEQLEN				11
#define IBLK2LEN				4
#define HB1SBCHPOS				1175
#define REJECTPOS				863
#define ORGASNPOS				30
#define ORGASNLEN				3
#define CUSTINDPOS				432
#define ORGTRNPOS				13
#define ORGTRNLEN				3
#define ORGTRNSEQLEN			16
#define NMKYCIDINDPOS			44
#define ORIGASNLEN				10
#define TIMECOMPLETEDPOS		1088
#define TIMECOMPLETEDLEN		14
#define ACCTNUMPOS				104
#define ACCTNUMLEN				10
#define ORIGDEPTPOS				77
#define ORIGDEPTLEN				20
#define CHRGACCTPOS				693
#define CHRGACCTLEN				10

#define B3T103POS				212
#define B3T113POS				215
#define B3T108POS				219
#define B3T119POS				235

#define TAG103LEN				3
#define TAG113LEN				4
#define TAG108LEN				16
#define TAG119LEN				8


#define TAG108TYP1POS			13

#define TAG108TYP2POS			13
#define TAG108TYP2LEN			13

#define	FORMATBLOCK3			"FormatOfBlock3"
#define BLOCK3TYPE1				"Block3Type1"
#define BLOCK3TYPE2				"Block3Type2"
#define BLOCK3TYPE3				"Block3Type3"

#define SENDERBIC				"SenderBiC8"
#define VALIDRCVBIC8			"ValidRcvBIC8"

#define IBLOCK3NONE					0
#define IBLOCK3TYPE1				1
#define IBLOCK3TYPE2				2
#define IBLOCK3TYPE3				3

#define DONOTDRAINMSG				0
#define DRAINDUPLICATEDMSG			1
#define DRAINLARGERMSG				2

#define NOTDRAINMSG					"No"
#define LESSTHANEXPSEQ				"LessThanExpectedSeq"
#define LARGERTHANEXPSEQ			"GreaterThanExpectedSeq"
#define ADDPDE						"AddPDE"
#define REPLACEINVALIDCHAR			"ReplaceInvalidChar"

#define ASNPREFIXLEN				4
#define ASNPREFIXLIST				"AsnPrefixList"
#define ASNPREFIX					"AsnPrefix"
#define MAX_ASNPREFIX				16

#define TRNPREFIXLEN				3
#define MAX_TRNPREFIX				64
#define GTMTRNPREFIXLIST			"GTMTrnPrefixList"
#define GTMTRNPREFIX				"GTMTrnPrefix"

#define FMTSUCCESS					"SUCCESS:"
#define FMTFAILURE					"FAILURE:"
#define OFACIND						"{OFAC:"

#define TRANSFORMSKIPLEN			38
#define CIDLEN						10

#define SUPPORTNAMEKEY				"SupportNameKey"
#define NAMEKEYPOS					45
#define NAMEKEYCIDINDPOS			44
#define NAMEKEYLEN					15
#define NAMEKEY						"NameKey"
#define NAMEKEYASNLEN				3
#define NAMEKEYASN					"NameKeyAsn"
#define NAMEKEYTRNLEN				3
#define NAMEKEYTRN					"NameKeyTrn"
#define CUSTCODELEN					1
#define CUSTCODE					"CustomerCode"
#define OUTPUTQUELEN				32
#define OUTPUTQUE					"OutputQueue"
#define OUTPUTQUELEN				32
#define OUTPUTQUE					"OutputQueue"
#define DESAPPLEN					3
#define DESDIRLEN					1
#define DESAPP						"DesApp"
#define NAMEKEYDEFLIST				"NameKeyDefList"
#define NAMEKEYDEF					"NameKeyDef"
#define MAX_NAMEKEYS				512
#define ROWDEFLIST					"RowDefList"
#define ROWDEF						"RowDef"
#define MAX_ROWS					32

#define OUTSRCCODE					"OutSourceCode"
#define OUTSRCCODELEN				3
#define OUTSRCRCVBIC				"OutSourceRcvBIC"
#define OUTSRCRCVBICLEN				8
#define SENDINGBANKPOS				1172
#define SENDINGBANKLEN				6
#define OUTSRCCODEPOS				1175
#define SWFADDRESSPOS				953
#define SWFADDRESSLEN				11
#define SUPPORTOUTSRC				"SupportOutSourcing"
#define OUTSRCDEFLIST				"OutSrcDefList"
#define OUTSRCDEF					"OutSrcDef"
#define MAX_OUTSRC					32
#define ASSIGNLT					"AssignLT"
#define CREATETAG108				"CreateTAG108"
#define SWITCHTOIBR					"SwitchToIBR"
#define USE1ASIBRFLAG				"Use1AsIBRFlag"
#define BLOCK2TID					"Block2Tid"

#define SWITCHIBRDEFLIST			"SwiftIBRDefList"
#define SWITCHIBRDEF				"SwiftIBRDef"
#define SNDBIC8						"SndBic8"
#define SNDSUBBRANCH				"SndSubBranch"
#define RCVBIC8						"RcvBic8"
#define RCVSUBBRANCH				"RcvSubBranch"
#define DESDIRECTION				"DesDirection"
#define BICDEFLIST					"BicDefList"
#define BICDEF						"BicDef"
#define MAX_SWITCHIBRSTR			64
#define MAX_SWITCHIBRBICDEF			64
#define EDIMGOUT					"EDIMGOUT"

#define MNAMEKEY					"{NAMEKEY:"
#define MASNPREFIX					"{ASNPREFIX:"
#define CID							"{CID:"
#define CIFLOOKUP					"{CIFLOOKUP:"
#define OUTSRC						"{OUTSRC:"
#define OUTSRCLEN					6
#define STDOUTSRCCODEPOS			3

#define CIFINFO						"CIFInfo"
#define CIFFETCH					"CIFFetch"

#define SUPPORTCIBC					"SupportCIBC"
#define SRCREFPOS					30
#define SRCREFLEN					18
#define TOTIMESTAMPPOS				48
#define TOTIMESTAMPLEN				7
#define TOADDRPOS					55
#define TOADDRLEN					12
#define TOSEQPOS					67
#define TOSEQLEN					5
#define FROMTIMESTAMPPOS			74
#define FROMTIMESTAMPLEN			7

#define FROMADDRPOS					81
#define FROMADDRLEN					12
#define FROMSEQPOS					93
#define FROMSEQLEN					5
#define CIBCMTTYPEPOS				100
#define CIBCMTTYPELEN				3
#define MSGTEXTPOS					108
#define MSGEND						"-"
#define MSGENDPDE					"-PDE"
#define MSGENDAPDE					"<03><00>"

#define KEEPSWFHEADERINFO			"KeepSwfHeaderInfo"
#define MAX_CIF_LENGTH				256

#define CORRELATIONID				"CorrelationID"
#define USEASN						"UseAsn"
#define CHECKERRSTATUS				"CheckErrStatusInPassarea"
#define ICORRNORMAL					1
#define ICORRSTANDARD				2
#define ICORRUSEASN					3
#define BLOCK4ONLY					"Block4Only"
#define OUTSRCLIST					"OutSrcList"
#define MAX_OUTSRCLIST				16

#define PDE							"PDE/"
#define PDELEN						4

#define	ERRSTATUSPOS				877
#define CASFMTERR					"FMT FAILURE"
#define GAPCHECK					"GapCheck"
#define FETCHOP						"fetchOp"
#define SAVEOP						"saveOp"
#define CHECKOP						"checkOp"
#define GAPCHECKBYSVC				"GapCheckBySvc"
#define STOP						"STOP"
#define NUMOFMSG					"NumberOfMessagesToDrain"

#define SUPPORTGPII					"SupportGPII"
#define METADATABUFLEN				1024



#include "fniGwyBic8CvtStr.h"

typedef struct {
	char alertEmailAddress[EMAILADDRESSLEN + 1];
} ALERTEMAILSTR, *PALERTEMAILSTR;

typedef struct {
	char trnPrefix[TRNPREFIXLEN + 1];
} TRNPREFIXSTR, *PTRNPREFIXSTR;

typedef struct {
	char bic8Name[BIC8LEN + 1];
} ISNBIC8STR, *PISNBIC8STR;

typedef struct {
	char mtType[MTTYPE_LEN + 1];
} ISNMTTYPESTR, *PISNMTTYPESTR;

typedef struct {
	char lTerm[LTERMLEN + 1];
} LTERMNAMESTR, *PLTERMNAMESTR;


typedef struct {
	char appLTerm[LTERMLEN + 1];
} APPLTERMSTR, *PAPPLTERMSTR;

typedef struct {
	char asnPrefix[ASNPREFIXLEN + 1];
	int outputModuleIndex;
} ASNPREFIXSTR, *PASNPREFIXSTR;

typedef struct {
	char lTerm[LTERMLEN + 1];
	char lowSrc[MTS_SOURCE_LEN + 1];
	char mediumSrc[MTS_SOURCE_LEN + 1];
	char highSrc[MTS_SOURCE_LEN + 1];
	char ibrSrc[MTS_SOURCE_LEN + 1];
	char ibrHSrc[MTS_SOURCE_LEN + 1];
	char ibrMSrc[MTS_SOURCE_LEN + 1];
	char errSrc[MTS_SOURCE_LEN + 1];
} ISNLTERMSTR, *PISNLTERMSTR;

typedef struct {
	char sndBic8Name[BIC8LEN + 1];
	char sndSubBranch[BRANCHLEN + 1];
	char desBic8Name[BIC8LEN + 1];
	char desSubBranch[BRANCHLEN + 1];
	char desApp[DESAPPLEN+1];
	char desDirection[DESDIRLEN+1];
} BIC11STR, *PBIC11STR;

typedef struct {
	char mtType[MTTYPE_LEN + 1];
	int numberOfBic11Str;
	PBIC11STR pBic11Str;
} SWITCHIBRSTR, *PSWITCHIBRSTR;


typedef struct {
	char mtType[MTTYPE_LEN + 1];
	char nameKeyAsn[NAMEKEYASNLEN + 1];
	char customerCode[CUSTCODELEN + 1];
	char outputQueue[OUTPUTQUELEN + 1];
	char nameKeyTrn[NAMEKEYTRNLEN + 1];
} NAMEKEYROWSTR, *PNAMEKEYROWSTR;

typedef struct {
	char nameKey[NAMEKEYLEN + 1];
	int numberOfRows;
	PNAMEKEYROWSTR pNameKeyRowStr;
} NAMEKEYSTR, *PNAMEKEYSTR;

typedef struct {
	char mtType[MTTYPE_LEN + 1];
	LTERMNAMESTR lTermStr[MAXMTLTERMLIST];
	char destBIC11[BIC11LEN + 1];
	char lastMtType[MTTYPE_LEN + 1];
	int currentLTIdx;
	int numberOfLTerms;
} MTLTERMSTR, *PMTLTERMSTR;

typedef struct {
	char mtType[MTTYPE_LEN + 1];
	char lastMtType[MTTYPE_LEN + 1];
	char srcBic8Name[BIC8LEN + 1];
	char destBIC11[BIC11LEN + 1];
	int currentLTIdx;
} MSGHEADERSTR, *PMSGHEADERSTR;


typedef struct {
	char bic8Name[BIC8LEN + 1];
	PMTLTERMSTR pMTLTermStr;
	int numberOfMTLTs;
} SELLTERMSTR, *PSELLTERMSTR;

typedef struct {
	char mtType[MTTYPE_LEN + 1];
	int priority;
} PRIORITYSTR, *PPRIOITYSTR;

typedef struct {
	char bnyTRn[BNYTRNLEN + 1];
	char custId[CUSTIDLEN + 1];
	char rcvAdd1[RCVADD1LEN + 1];
	char rcvAdd2[RCVADD2LEN + 1];
} CITTEOSTR, *PCITTEOSTR;

typedef struct {
	char outSrcCode[OUTSRCCODELEN + 1];
	char outSrcBic[BIC8LEN + 1];
} OUTSRCSTR, *POUTSRCSTR;

typedef struct {
	char outSrcCode[OUTSRCCODELEN + 1];
} SUPPORTOUTSRCSTR, *PSUPPORTOUTSRCSTR;

typedef struct {
	char correlationData[MAXCORRDATALEN];
	char gapTableFileName[MAX_FILE_NAME_LEN];
	char fniCopyCSAReport[MAX_FILE_NAME_LEN];
	char src[MTS_SOURCE_LEN + 1];
	char appId[APPIDLEN+1];
	char mainAppId[APPIDLEN+1];
	char asnPrefix[ASNPREFIXLEN + 1];
	char errMsg[ERRMSG_LEN + 1];
	char errCode[ERRCODE_LEN+1];
	char orgMtsTrn[MTSTRNLEN + 20];
	char mtsTrn[MTSTRNLEN + 20];
	char mrvRsp[MTSRSPLEN + 20];
	char gtmAckMsg[MAX_SVC_BUF];
	char desApp[DESAPPLEN + 1];
	char ourSrcCode[OUTSRCLEN + 1];
	char block2Tid[TIDLEN+1];
	char desAppPerMsg[DESAPPLEN+1];
	char desDirectionPerMsg[DESDIRLEN+1];
	char nameKeyOutputQueue[OUTPUTQUELEN + 1];
	char rcvBic12[BIC12LEN+1];
	char outSrcBic[BIC8LEN+1];
	char nameKey[NAMEKEYLEN + 1];
	char nameKeyFromPA[NAMEKEYLEN + 1];
	char mtType[MTTYPELEN + 1];
	char origAsn[ORIGASNLEN + 1];
	char timeCompleted[TIMECOMPLETEDLEN + 1];
	char origDept[ORIGDEPTLEN + 1];
	char charAcct[CHRGACCTLEN + 1];
	char acctNum[ACCTNUMLEN + 1];
	char msgId[MSGIDLEN + 1];
	char cusIndId;
	char cid[CIDLEN + 1];
	char cidFromPA[CIDLEN + 1];
	char orgMTType[MTTYPELEN + 1];
	char trnPrefix[TRNPREFIXLEN + 1];
	char orgTrn[ORGTRNSEQLEN+1];
	char trnPA[ORGTRNSEQLEN+1];
	char recvAdd1[ADDRESSLEN + 1];
	char recvAdd2[ADDRESSLEN + 1];
	char recvAdd3[ADDRESSLEN + 1];
	char recvAdd4[ADDRESSLEN + 1];
	char chrgAdd1[ADDRESSLEN + 1];
	char chrgAdd2[ADDRESSLEN + 1];
	char chrgAdd3[ADDRESSLEN + 1];
	char chrgAdd4[ADDRESSLEN + 1];
	char metadfataBuff[METADATABUFLEN +1];
	char* pGapTableStr;
	bool checksum;
	bool useSat;
	PISNBIC8STR pIsnBIC8Str;
	PPRIOITYSTR pPriorityStr;
	PISNLTERMSTR pIsnLTermStr;
	PSELLTERMSTR pSelLTermStr;
	PMSGHEADERSTR pMsgHeaderStr;
	PALERTEMAILSTR pAlertEmailStr;
	int numberOfAlertEmails;
	int numberOfBic8;
	int numberOfPriorityDef;
	int numberOfLTerms;
	int numberOfIsnBic8s;
	int numberOfOnDemandMQs;
	bool firstTime;
	bool handleBlock3ForIBR;
	bool noIBRForSameBIC;
	bool ibrForSenderBic;
	char priority[TIDLEN + 1];
	int lTermIndex;
	int maximumGap;
	int maximumNumberOfGaps;
	int maximumSequenceNumber;
	int processGapCheck;
	int passAreaLength;
	int seqNumberLength;
	int seqNumberStartPos;
	bool getGapTable;
	char prodBic8fileName[MAX_FILE_NAME_LEN];
	char bi8ExceptionfileName[MAX_FILE_NAME_LEN];
	char alertEmailFileName[MAX_FILE_NAME_LEN];
	char annualFormat[FORMAT_LEN + 1];
	int numberOfBic8CvtStr;
	int numberOfBic8Excep;
	int numberOfIsnMTType;
	PBIC8CVTSTR pBic8CvtStr;
	PBIC8ECPSTR pPodBic8Excep;
	PBIC8ECPSTR pTandtBic8Excep;
	PISNMTTYPESTR pIsnMTTypeStr;
	bool convertBic8;
	int* pGapTable;
	void* pSvcClient;
	int	defaultSvcPort;
	char defaultSvcSvr[SVCSVR_LEN+1];
	bool editCheckBySwift;
	bool processIBR;
	int	messageFormat;
	bool editSvcFailed;
	bool passErrMsgToSwf;
	char svcHandler[SVCHANDLER_LEN + 1];
	char svcTFMHandler[SVCHANDLER_LEN + 1];
	char svcGTMAckHandler[SVCHANDLER_LEN + 1];
	char svcCIFHandler[SVCHANDLER_LEN + 1];
	char svcGapCheckHandler[SVCHANDLER_LEN + 1];
	bool useWebSvc;
	bool rcvRepMsg;
	char* pMervaTrace;
	PSELLTERMSTR pAppLTermStr;
	int numberofAppLTerms;
	bool putGapTable;
	bool forwardPassArea;
	bool processPassArea;
	char asn[ASN_LEN+1];
	int currentPassAreaIndex;
	bool createHeaderBlock;
	int block3Type;
	char senderBic8[BIC8LEN + 1];
	char validRcvBic8[BIC8LEN + 1];
	bool drainMessage;
	bool addPDE;
	bool replaceInvalidChar;
	bool invalidPassArea;
	int numberOfAsnPrefix;
	PASNPREFIXSTR pAsnPrefixStr;
	int numberOfTrnPrefix;
	PTRNPREFIXSTR pTrnPrefixStr;
	bool transformInternalFmt;
	bool transformInternalFmtLocal;
	bool failToTransform;
	bool checkOFAC;
	bool gtmAck;
	bool firstGTMAck;
	bool sendGTMAck;
	bool failToGetGTM;
	bool supportTEO;
	bool handleTEO;
	bool ibrOnly;
	PCITTEOSTR pCitTEOStr;
	PNAMEKEYSTR pNameKeyStr;
	bool supportNameKey;
	int numberOfNameKeys;
	bool handleNameKey;
	POUTSRCSTR pOutSrcStr;
	int numberOfOutSrc;
	bool supportOutSrc;
	bool assignLT;
	bool transformSwiftToSwift;
	bool createTag108;
	bool switchToIBR;
	bool use1AsIBRFlag;
	PSWITCHIBRSTR pSwiftIBRStr;
	PSUPPORTOUTSRCSTR pSupportOutSrcStr;
	int numberOfSupportOutSrc;
	int numberOfSwiftIBRStr;
	bool setSwitchToIBR;
	bool cifLookup;
	bool handleCIBC;
	bool handleOutSrc;
	bool supportCIBC;
	bool keepSwfHeaderInfo;
	bool registerCIFSvc;
	int correlationId;
	bool block4Only;
	bool noValidation;
	bool checkErrStatusInPassarea;
	bool handleErrInPassarea;
	int expectedSeq;
	bool bContinue;
	bool gapCheckBySvc;
	int numberOfMessagesToDrain;
	int countOfMsgDrain;
	bool reserveAddress;
	bool isFirstMessage;
	bool supportGPII;
} BMDEF, *PBMDEF;

#define initBMDef() \
	pModuleStr->correlationData[0] = '\0'; \
	pModuleStr->src[0] = '\0'; \
	pModuleStr->appId[0] = '\0'; \
	pModuleStr->asnPrefix[0] = '\0'; \
	pModuleStr->errMsg[0] = '\0'; \
	pModuleStr->errCode[0] = '\0'; \
	pModuleStr->gtmAckMsg[0] = '\0'; \
	pModuleStr->desApp[0] = '\0'; \
	pModuleStr->rcvBic12[0] = '\0'; \
	pModuleStr->block2Tid[0] = '\0'; \
	pModuleStr->nameKey[0] = '\0'; \
	pModuleStr->cid[0] = '\0'; \
	pModuleStr->nameKeyFromPA[0] = '\0'; \
	pModuleStr->cidFromPA[0] = '\0'; \
	pModuleStr->orgMTType[0] = '\0'; \
	pModuleStr->orgTrn[0] = '\0'; \
	pModuleStr->trnPA[0] = '\0'; \
	pModuleStr->recvAdd1[0] = '\0'; \
	pModuleStr->recvAdd2[0] = '\0'; \
	pModuleStr->recvAdd3[0] = '\0'; \
	pModuleStr->recvAdd4[0] = '\0'; \
	pModuleStr->chrgAdd1[0] = '\0'; \
	pModuleStr->chrgAdd2[0] = '\0'; \
	pModuleStr->chrgAdd3[0] = '\0'; \
	pModuleStr->chrgAdd4[0] = '\0'; \
	pModuleStr->origAsn[0]  = '\0'; \
	pModuleStr->timeCompleted[0]  = '\0'; \
	pModuleStr->origDept[0]  = '\0'; \
	pModuleStr->charAcct[0]  = '\0'; \
	pModuleStr->acctNum[0]  = '\0'; \
	pModuleStr->msgId[0]  = '\0'; \
	pModuleStr->nameKeyOutputQueue[0] = '\0'; \
	pModuleStr->checksum = false; \
	pModuleStr->useSat = false; \
	pModuleStr->pIsnBIC8Str = NULL; \
	pModuleStr->pIsnLTermStr = NULL; \
	pModuleStr->pPriorityStr = NULL; \
	pModuleStr->pSelLTermStr = NULL; \
	pModuleStr->numberOfIsnBic8s = 0; \
	pModuleStr->firstTime = true; \
	pModuleStr->priority[0] = '\0'; \
	pModuleStr->annualFormat[0] = '\0'; \
	pModuleStr->lTermIndex = -1; \
	pModuleStr->maximumGap = 0; \
	pModuleStr->maximumNumberOfGaps = 0; \
	pModuleStr->maximumSequenceNumber = 99999; \
	pModuleStr->numberOfPriorityDef = 0; \
	pModuleStr->numberOfLTerms = 0; \
	pModuleStr->numberOfBic8 = 0; \
	pModuleStr->prodBic8fileName[0] = '\0'; \
	pModuleStr->bi8ExceptionfileName[0] = '\0'; \
	pModuleStr->pBic8CvtStr = NULL; \
	pModuleStr->pPodBic8Excep  = NULL; \
	pModuleStr->pTandtBic8Excep  = NULL; \
	pModuleStr->numberOfBic8CvtStr = 0; \
	pModuleStr->numberOfBic8Excep = 0; \
	pModuleStr->convertBic8 = false; \
	pModuleStr->numberOfIsnMTType = 0; \
	pModuleStr->pIsnMTTypeStr = NULL; \
	pModuleStr->processGapCheck = INOGAPCHECK; \
	pModuleStr->getGapTable = false; \
	pModuleStr->pGapTable = NULL; \
	pModuleStr->passAreaLength = 1200; \
	pModuleStr->seqNumberLength = 5; \
	pModuleStr->seqNumberStartPos = 5; \
	pModuleStr->pSvcClient = NULL;  \
	pModuleStr->defaultSvcPort = NOSVC; \
	pModuleStr->defaultSvcSvr[0] = '\0'; \
	pModuleStr->editCheckBySwift = true; \
	pModuleStr->processIBR = true; \
	pModuleStr->messageFormat = INORMALFORMAT; \
	pModuleStr->editSvcFailed = false; \
	pModuleStr->passErrMsgToSwf = false; \
	pModuleStr->useWebSvc = false; \
	pModuleStr->svcHandler[0] = '\0'; \
	pModuleStr->svcTFMHandler[0] = '\0'; \
	pModuleStr->svcGapCheckHandler[0] = '\0'; \
	pModuleStr->svcGTMAckHandler[0] = '\0'; \
	pModuleStr->svcCIFHandler[0] = '\0'; \
	pModuleStr->desAppPerMsg[0] = '\0'; \
	pModuleStr->metadfataBuff[0] = '\0'; \
	pModuleStr->desDirectionPerMsg[0] = '\0'; \
	pModuleStr->rcvRepMsg = false; \
	pModuleStr->pMervaTrace = NULL; \
	pModuleStr->pAppLTermStr = NULL; \
	pModuleStr->numberofAppLTerms = 0; \
	pModuleStr->putGapTable = false; \
	pModuleStr->forwardPassArea = false; \
	pModuleStr->asn[0] ='\0'; \
	pModuleStr->processPassArea = false; \
	pModuleStr->currentPassAreaIndex = 0; \
	pModuleStr->numberOfOnDemandMQs = 0; \
	pModuleStr->pGapTableStr = NULL; \
	pModuleStr->pMsgHeaderStr = NULL; \
	pModuleStr->createHeaderBlock = false; \
	pModuleStr->block3Type = IBLOCK3NONE; \
	pModuleStr->senderBic8[0] = '\0'; \
	pModuleStr->validRcvBic8[0] = '\0'; \
	pModuleStr->drainMessage = false; \
	pModuleStr->addPDE = false; \
	pModuleStr->replaceInvalidChar = false; \
	pModuleStr->pAlertEmailStr = NULL; \
	pModuleStr->numberOfAlertEmails = 0; \
	pModuleStr->alertEmailFileName[0] = '\0'; \
	pModuleStr->invalidPassArea = false; \
	pModuleStr->numberOfAsnPrefix = 0; \
	pModuleStr->pAsnPrefixStr = NULL; \
	pModuleStr->numberOfTrnPrefix = 0; \
	pModuleStr->pTrnPrefixStr = NULL; \
	pModuleStr->transformInternalFmt = false; \
	pModuleStr->transformInternalFmtLocal = false; \
	pModuleStr->failToTransform = false; \
	pModuleStr->checkOFAC = false; \
	pModuleStr->mainAppId[0] = '\0'; \
	pModuleStr->gtmAck = false; \
	pModuleStr->firstGTMAck = false; \
	pModuleStr->sendGTMAck = false; \
	pModuleStr->failToGetGTM = false; \
	pModuleStr->supportTEO = false; \
	pModuleStr->pCitTEOStr = NULL; \
	pModuleStr->handleTEO = false; \
	pModuleStr->ibrOnly = false; \
	pModuleStr->pNameKeyStr = NULL; \
	pModuleStr->supportNameKey = false; \
	pModuleStr->numberOfNameKeys = 0;\
	pModuleStr->handleNameKey = false; \
	pModuleStr->pOutSrcStr = NULL; \
	pModuleStr->numberOfOutSrc = 0;\
	pModuleStr->supportOutSrc = false; \
	pModuleStr->assignLT = true; \
	pModuleStr->transformSwiftToSwift = false; \
	pModuleStr->createTag108 = true; \
	pModuleStr->switchToIBR = false; \
	pModuleStr->use1AsIBRFlag = true; \
	pModuleStr->pSwiftIBRStr = NULL; \
	pModuleStr->numberOfSwiftIBRStr = 0; \
	pModuleStr->setSwitchToIBR = false; \
	pModuleStr->cusIndId = '\0'; \
	pModuleStr->cifLookup = false; \
	pModuleStr->trnPrefix[0] = '\0'; \
	pModuleStr->ourSrcCode[0] = '\0'; \
	pModuleStr->handleCIBC = false; \
	pModuleStr->handleOutSrc = false; \
	pModuleStr->supportCIBC = false; \
	pModuleStr->keepSwfHeaderInfo = false; \
	pModuleStr->registerCIFSvc = false; \
	pModuleStr->correlationId = ICORRNORMAL; \
	pModuleStr->block4Only = false; \
	pModuleStr->pSupportOutSrcStr = NULL; \
	pModuleStr->numberOfSupportOutSrc = 0; \
	pModuleStr->noValidation = false; \
	pModuleStr->checkErrStatusInPassarea = false; \
	pModuleStr->handleErrInPassarea = false; \
	pModuleStr->expectedSeq = 0; \
	pModuleStr->bContinue = true; \
	pModuleStr->gapCheckBySvc = false; \
	pModuleStr->numberOfMessagesToDrain = 0; \
	pModuleStr->countOfMsgDrain = 0; \
	pModuleStr->reserveAddress = false; \
	pModuleStr->isFirstMessage = true; \
	pModuleStr->supportGPII = false;

#include "fniGwyBic8Cmp.h"

int mtTypeSwitchIBRComparator ( const void * elem1, const void * elem2 ) {
	int i;
	PSWITCHIBRSTR pSwiftIBRStr1 = (PSWITCHIBRSTR)elem1;
	PSWITCHIBRSTR pSwiftIBRStr2 = (PSWITCHIBRSTR)elem2;

	for (i = 0; i < MTTYPE_LEN; i++) {
		if (pSwiftIBRStr1->mtType[i] > pSwiftIBRStr2->mtType[i]) {
			return 1;
		}
		else if (pSwiftIBRStr1->mtType[i] < pSwiftIBRStr2->mtType[i]) {
			return -1;
		}
	}
	return 0;
}

int mtTypeComparator ( const void * elem1, const void * elem2 ) {
	int i;
	PISNMTTYPESTR pIsnMTTypeStr1 = (PISNMTTYPESTR)elem1;
	PISNMTTYPESTR pIsnMTTypeStr2 = (PISNMTTYPESTR)elem2;

	for (i = 0; i < MTTYPE_LEN; i++) {
		if (pIsnMTTypeStr1->mtType[i] > pIsnMTTypeStr2->mtType[i]) {
			return 1;
		}
		else if (pIsnMTTypeStr1->mtType[i] < pIsnMTTypeStr2->mtType[i]) {
			return -1;
		}
	}
	return 0;
}

int bic8Comparator ( const void * elem1, const void * elem2 ) {
	int i;
	PISNBIC8STR pBIC8Str1 = (PISNBIC8STR)elem1;
	PISNBIC8STR pBIC8Str2 = (PISNBIC8STR)elem2;

	for (i = 0; i < BIC8LEN; i++) {
		if (pBIC8Str1->bic8Name[i] > pBIC8Str2->bic8Name[i]) {
			return 1;
		}
		else if (pBIC8Str1->bic8Name[i] < pBIC8Str2->bic8Name[i]) {
			return -1;
		}
	}
	return 0;
}

int lTermComparator ( const void * elem1, const void * elem2 ) {
	int i;
	PISNLTERMSTR pIsnLtermStr1 = (PISNLTERMSTR)elem1;
	PISNLTERMSTR pIsnLtermStr2 = (PISNLTERMSTR)elem2;

	for (i = 0; i < LTERMLEN; i++) {
		if (pIsnLtermStr1->lTerm[i] > pIsnLtermStr2->lTerm[i]) {
			return 1;
		}
		else if (pIsnLtermStr1->lTerm[i] < pIsnLtermStr2->lTerm[i]) {
			return -1;
		}
	}
	return 0;
}

int asnPrefixComparator ( const void * elem1, const void * elem2 ) {
	int i;

	PASNPREFIXSTR pAsnPrefixStr1 = (PASNPREFIXSTR)elem1;
	PASNPREFIXSTR pAsnPrefixStr2 = (PASNPREFIXSTR)elem2;

	for (i = 0; i < ASNPREFIXLEN - 1; i++) {
		if (pAsnPrefixStr1->asnPrefix[i] > pAsnPrefixStr2->asnPrefix[i]) {
			return 1;
		}
		else if (pAsnPrefixStr1->asnPrefix[i] < pAsnPrefixStr2->asnPrefix[i]) {
			return -1;
		}
	}
	return 0;
}

int trnPrefixComparator ( const void * elem1, const void * elem2 ) {
	int i;

	PTRNPREFIXSTR pTrnPrefixStr1 = (PTRNPREFIXSTR)elem1;
	PTRNPREFIXSTR pTrnPrefixStr2 = (PTRNPREFIXSTR)elem2;

	for (i = 0; i < TRNPREFIXLEN; i++) {
		if (pTrnPrefixStr1->trnPrefix[i] > pTrnPrefixStr2->trnPrefix[i]) {
			return 1;
		}
		else if (pTrnPrefixStr1->trnPrefix[i] < pTrnPrefixStr2->trnPrefix[i]) {
			return -1;
		}
	}
	return 0;
}

int appLTermComparator ( const void * elem1, const void * elem2 ) {
	int i;
	PAPPLTERMSTR pAppLTermStr1 = (PAPPLTERMSTR)elem1;
	PAPPLTERMSTR pAppLTermStr2 = (PAPPLTERMSTR)elem2;

	for (i = 0; i < LTERMLEN - 1; i++) {
		if (pAppLTermStr1->appLTerm[i] > pAppLTermStr2->appLTerm[i]) {
			return 1;
		}
		else if (pAppLTermStr1->appLTerm[i] < pAppLTermStr2->appLTerm[i]) {
			return -1;
		}
	}
	return 0;
}
int selLTermComparator ( const void * elem1, const void * elem2 ) {
	int i;
	PSELLTERMSTR pSelIsnLTermStr1 = (PSELLTERMSTR)elem1;
	PSELLTERMSTR pSelIsnLTermStr2 = (PSELLTERMSTR)elem2;

	for (i = 0; i < LTERMLEN; i++) {
		if (pSelIsnLTermStr1->bic8Name[i] > pSelIsnLTermStr2->bic8Name[i]) {
			return 1;
		}
		else if (pSelIsnLTermStr1->bic8Name[i] < pSelIsnLTermStr2->bic8Name[i]) {
			return -1;
		}
	}
	return 0;
}

int mtLTermComparator ( const void * elem1, const void * elem2 ) {
	int i;
	PMTLTERMSTR pMTLTermStr1 = (PMTLTERMSTR)elem1;
	PMTLTERMSTR pMTLTermStr2 = (PMTLTERMSTR)elem2;

	for (i = 0; i < MTTYPE_LEN; i++) {
		if (pMTLTermStr1->mtType[i] > pMTLTermStr2->mtType[i]) {
			return 1;
		}
		else if (pMTLTermStr1->mtType[i] < pMTLTermStr2->mtType[i]) {
			return -1;
		}
	}
	return 0;
}

int nameKeyComparator ( const void * elem1, const void * elem2 ) {
	int i;
	PNAMEKEYSTR pNameKeyStr1 = (PNAMEKEYSTR)elem1;
	PNAMEKEYSTR pNameKeyStr2 = (PNAMEKEYSTR)elem2;

	for (i = 0; i < NAMEKEYLEN; i++) {
		if (pNameKeyStr1->nameKey[i] > pNameKeyStr2->nameKey[i]) {
			return 1;
		}
		else if (pNameKeyStr1->nameKey[i] < pNameKeyStr2->nameKey[i]) {
			return -1;
		}
	}
	return 0;
}

int outSrcComparator ( const void * elem1, const void * elem2 ) {
	int i;
	POUTSRCSTR pOutSrcStr1 = (POUTSRCSTR)elem1;
	POUTSRCSTR pOutSrcStr2 = (POUTSRCSTR)elem2;

	for (i = 0; i < OUTSRCCODELEN; i++) {
		if (pOutSrcStr1->outSrcCode[i] > pOutSrcStr2->outSrcCode[i]) {
			return 1;
		}
		else if (pOutSrcStr1->outSrcCode[i] < pOutSrcStr2->outSrcCode[i]) {
			return -1;
		}
	}
	return 0;
}

#include "fniGwySetBic8List.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	setup -- Set up initial configuration variables.
// Parameters:	pGwyInit -- point to gateway initial structure.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(PGWINIT pGwyInit) {
	int i;
	CXml xml;
	string xmlValue;
	char* pt;
	string mtTypeDocs[MAX_MTTYPE];
	string mtTypeListDoc;
	string mtType;
	string alertEmailDocs[MAX_ALERTEMAILS];
	string alertEmailListDoc;
	string alertEmail;
	string asnPreFixListDoc;
	string asnPreFixDocs[MAX_ASNPREFIX];
	string asnPrefix;

	string trnPreFixListDoc;
	string trnPreFixDocs[MAX_TRNPREFIX];
	string trnPrefix;

	string switchIBRDefDocs[MAX_SWITCHIBRSTR];
	string switchIBRDefListDoc;

	string bicDefDocs[MAX_SWITCHIBRBICDEF];
	string bicDefListDoc;

	string outSrcCodDocs[MAX_OUTSRCLIST];
	string outSrcListDoc;
	string outSrcCode;

	string priorityDocs[MAX_PRIORITY];
	string priorityListDoc;

	getPGWStr();

	string bmDoc = getXmlDoc();
	getBusinessModuleVars(PBMDEF);
	initBMDef();

	tracing(TRACE_LEVEL_1, "APPISN setup", "started");
	reset();

/*	xmlValue = xml.getValue(bmDoc,APPHOST);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ApplicationHost: " + xmlValue);
		if (xmlValue == "MERVA") {
			pModuleStr->applicationHost = MERVA;
			setCfgNameAndValue(APPHOST, "MERVA");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "MSGRTR") {
			pModuleStr->applicationHost = MSGRTR;
			setCfgNameAndValue(APPHOST, "MSGRTR");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(APPHOST));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ApplicationHost: TAG_NOT_EXISTS");
		reset();
	}
	*/

	outSrcListDoc = xml.getNode(bmDoc,OUTSRCLIST);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != NODE_NOT_EXISTS) {
		pModuleStr->numberOfSupportOutSrc = xml.getNodes(outSrcListDoc,OUTSRCCODE,outSrcCodDocs,MAX_OUTSRCLIST);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pSupportOutSrcStr = (PSUPPORTOUTSRCSTR) malloc(sizeof(SUPPORTOUTSRCSTR) * pModuleStr->numberOfSupportOutSrc);
		for (i = 0; i < pModuleStr->numberOfSupportOutSrc; i++) {
			outSrcCode = xml.getValue(outSrcCodDocs[i],OUTSRCCODE);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			strcpy(pModuleStr->pSupportOutSrcStr[i].outSrcCode,outSrcCode.c_str());
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "OUTSRCLIST: NODE_NOT_EXISTS");
		reset();
	}

	alertEmailListDoc = xml.getNode(bmDoc,ALERTEMAILLIST);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != NODE_NOT_EXISTS) {


		pModuleStr->numberOfAlertEmails = xml.getNodes(alertEmailListDoc,ALERTEMAILADDRESS,alertEmailDocs,MAX_ALERTEMAILS);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pAlertEmailStr = (PALERTEMAILSTR) malloc(sizeof(ALERTEMAILSTR) * pModuleStr->numberOfAlertEmails);
		for (i = 0; i < pModuleStr->numberOfAlertEmails; i++) {
			alertEmail = xml.getValue(alertEmailDocs[i],ALERTEMAILADDRESS);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			strcpy(pModuleStr->pAlertEmailStr[i].alertEmailAddress,alertEmail.c_str());
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ALERTEMAILLIST: NODE_NOT_EXISTS");
		reset();
	}


	switchIBRDefListDoc = xml.getNode(bmDoc,SWITCHIBRDEFLIST);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != NODE_NOT_EXISTS) {
		pModuleStr->numberOfSwiftIBRStr = xml.getNodes(switchIBRDefListDoc,SWITCHIBRDEF,switchIBRDefDocs,MAX_SWITCHIBRSTR);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pSwiftIBRStr = (PSWITCHIBRSTR) malloc(sizeof(SWITCHIBRSTR) * pModuleStr->numberOfSwiftIBRStr);
		for (i = 0; i < pModuleStr->numberOfSwiftIBRStr; i++) {
			mtType = xml.getValue(switchIBRDefDocs[i],MTTYPE);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			strcpy(pModuleStr->pSwiftIBRStr[i].mtType,mtType.c_str());
			pModuleStr->pSwiftIBRStr[i].pBic11Str = NULL;
			bicDefListDoc = xml.getNode(switchIBRDefDocs[i],BICDEFLIST);
			pModuleStr->pSwiftIBRStr[i].numberOfBic11Str = xml.getNodes(bicDefListDoc,BICDEF,bicDefDocs,MAX_SWITCHIBRBICDEF);
			if (pModuleStr->pSwiftIBRStr[i].numberOfBic11Str > 0) {
				pModuleStr->pSwiftIBRStr[i].pBic11Str = (PBIC11STR) malloc(sizeof(BIC11STR) * pModuleStr->pSwiftIBRStr[i].numberOfBic11Str);
				for (int j = 0; j < pModuleStr->pSwiftIBRStr[i].numberOfBic11Str; j++) {
					(pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).sndBic8Name[0] = '\0';
					(pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).sndSubBranch[0] = '\0';
					(pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).desBic8Name[0] = '\0';
					(pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).desSubBranch[0] = '\0';
					(pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).desSubBranch[0] = '\0';
					(pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).desApp[0] = '\0';
					string sndBic8Name = xml.getValue(bicDefDocs[j],SNDBIC8);
					if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
						setStatus(xml.getStatus());
						setErrorMessage(xml.getErrorMessage());
						return;
					}
					if (xml.getStatus() != TAG_NOT_EXISTS) {
						if (strlen(sndBic8Name.c_str()) == BIC8LEN) {
							strcpy((pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).sndBic8Name,sndBic8Name.c_str());
						}
						else {
							setStatus(INVALID_VALUE);
							setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(SNDBIC8));
							return;
						}
					}
					string sndSubBranch = xml.getValue(bicDefDocs[j],SNDSUBBRANCH);
					if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
						setStatus(xml.getStatus());
						setErrorMessage(xml.getErrorMessage());
						return;
					}
					if (xml.getStatus() != TAG_NOT_EXISTS) {
						if (strlen(sndSubBranch.c_str()) == BRANCHLEN) {
							strcpy((pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).sndSubBranch,sndSubBranch.c_str());
						}
						else {
							setStatus(INVALID_VALUE);
							setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(SNDSUBBRANCH));
							return;
						}
					}

					string desBic8Name = xml.getValue(bicDefDocs[j],RCVBIC8);
					if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
						setStatus(xml.getStatus());
						setErrorMessage(xml.getErrorMessage());
						return;
					}
					if (xml.getStatus() != TAG_NOT_EXISTS) {
						if (strlen(desBic8Name.c_str()) == BIC8LEN) {
							strcpy((pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).desBic8Name,desBic8Name.c_str());
						}
						else {
							setStatus(INVALID_VALUE);
							setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(RCVBIC8));
							return;
						}
					}
					string desSubBranch = xml.getValue(bicDefDocs[j],RCVSUBBRANCH);
					if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
						setStatus(xml.getStatus());
						setErrorMessage(xml.getErrorMessage());
						return;
					}
					if (xml.getStatus() != TAG_NOT_EXISTS) {
						if (strlen(desSubBranch.c_str()) == BRANCHLEN) {
							strcpy((pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).desSubBranch,desSubBranch.c_str());
						}
						else {
							setStatus(INVALID_VALUE);
							setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(RCVSUBBRANCH));
							return;
						}
					}
					string desDirection = xml.getValue(bicDefDocs[j],DESDIRECTION);
					if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
						setStatus(xml.getStatus());
						setErrorMessage(xml.getErrorMessage());
						return;
					}
					if (xml.getStatus() != TAG_NOT_EXISTS) {
						if (strlen(desDirection.c_str()) == DESDIRLEN) {
							strcpy((pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).desDirection,desDirection.c_str());
						}
						else {
							setStatus(INVALID_VALUE);
							setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(DESDIRECTION));
							return;
						}
					}
					string desApp = xml.getValue(bicDefDocs[j],DESAPP);
					if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
						setStatus(xml.getStatus());
						setErrorMessage(xml.getErrorMessage());
						return;
					}
					if (xml.getStatus() != TAG_NOT_EXISTS) {
						if (strlen(desApp.c_str()) == DESAPPLEN) {
							strcpy((pModuleStr->pSwiftIBRStr[i].pBic11Str[j]).desApp,desApp.c_str());
						}
						else {
							setStatus(INVALID_VALUE);
							setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(DESAPP));
							return;
						}
					}
				}
			}
		}
		qsort (pModuleStr->pSwiftIBRStr, pModuleStr->numberOfSwiftIBRStr, sizeof(SWITCHIBRSTR), mtTypeSwitchIBRComparator);
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SWITCHIBRDEFLIST: NODE_NOT_EXISTS");
		reset();
	}
	mtTypeListDoc = xml.getNode(bmDoc,SUPPORTEDMTTYPELIST);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != NODE_NOT_EXISTS) {


		pModuleStr->numberOfIsnMTType = xml.getNodes(mtTypeListDoc,MTTYPE,mtTypeDocs,MAX_MTTYPE);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pIsnMTTypeStr = (PISNMTTYPESTR) malloc(sizeof(ISNMTTYPESTR) * pModuleStr->numberOfIsnMTType);
		for (i = 0; i < pModuleStr->numberOfIsnMTType; i++) {
			mtType = xml.getValue(mtTypeDocs[i],MTTYPE);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			strcpy(pModuleStr->pIsnMTTypeStr[i].mtType,mtType.c_str());
		}
		qsort (pModuleStr->pIsnMTTypeStr, pModuleStr->numberOfIsnMTType, sizeof(ISNMTTYPESTR), mtTypeComparator);
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTEDMTTYPELIST: NODE_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,MAINAPPID);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAINAPPID: " + xmlValue);
		if (strlen(xmlValue.c_str()) == APPIDLEN) {
			strcpy(pModuleStr->mainAppId,xmlValue.c_str());
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MAINAPPID));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAINAPPID: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,ASNPREFIX);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ASNPREFIX: " + xmlValue);
		if (strlen(xmlValue.c_str()) == ASNPREFIXLEN) {
			strcpy(pModuleStr->asnPrefix,xmlValue.c_str());
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(ASNPREFIX));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ASNPREFIX: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,SUPPORTGPII);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTGPII: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->supportGPII = true;
			setCfgNameAndValue(SUPPORTGPII, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->supportGPII = false;
			setCfgNameAndValue(SUPPORTGPII, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(SUPPORTGPII));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTGPII: TAG_NOT_EXISTS");
		reset();
	}


	xmlValue = xml.getValue(bmDoc,CHECKERRSTATUS);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CHECKERRSTATUS: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->checkErrStatusInPassarea = true;
			setCfgNameAndValue(CHECKERRSTATUS, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->checkErrStatusInPassarea = false;
			setCfgNameAndValue(CHECKERRSTATUS, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(CHECKERRSTATUS));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CHECKERRSTATUS: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,KEEPSWFHEADERINFO);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "KEEPSWFHEADERINFO: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->keepSwfHeaderInfo = true;
			setCfgNameAndValue(KEEPSWFHEADERINFO, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->keepSwfHeaderInfo = false;
			setCfgNameAndValue(KEEPSWFHEADERINFO, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(KEEPSWFHEADERINFO));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "RCVREPMSG: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,BLOCK4ONLY);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "USE1ASIBRFLAG: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->block4Only = true;
			setCfgNameAndValue(USE1ASIBRFLAG, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->block4Only = false;
			setCfgNameAndValue(USE1ASIBRFLAG, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "USE1ASIBRFLAG: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,USE1ASIBRFLAG);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "USE1ASIBRFLAG: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->use1AsIBRFlag = true;
			setCfgNameAndValue(USE1ASIBRFLAG, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->use1AsIBRFlag = false;
			setCfgNameAndValue(USE1ASIBRFLAG, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "USE1ASIBRFLAG: TAG_NOT_EXISTS");
		reset();
	}
	xmlValue = xml.getValue(bmDoc,SWITCHTOIBR);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SWITCHTOIBR: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->switchToIBR = true;
			setCfgNameAndValue(SWITCHTOIBR, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->switchToIBR = false;
			setCfgNameAndValue(SWITCHTOIBR, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SWITCHTOIBR: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,ASSIGNLT);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ASSIGNLT: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->assignLT = true;
			setCfgNameAndValue(ASSIGNLT, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->assignLT = false;
			setCfgNameAndValue(ASSIGNLT, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ASSIGNLT: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,CORRELATIONID);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CORRELATIONID: " + xmlValue);
		if (xmlValue == USEASN) {
			pModuleStr->correlationId  = ICORRUSEASN;
			setCfgNameAndValue(CORRELATIONID, USEASN);
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(CORRELATIONID));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CORRELATIONID: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,SUPPORTCIBC);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTCIBC: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->supportCIBC = true;
			setCfgNameAndValue(SUPPORTCIBC, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->supportCIBC = false;
			setCfgNameAndValue(SUPPORTCIBC, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTCIBC: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,SUPPORTTEO);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTTEO: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->supportTEO = true;
			pModuleStr->pCitTEOStr = (PCITTEOSTR) malloc(sizeof(CITTEOSTR));
			setCfgNameAndValue(SUPPORTTEO, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->supportTEO = false;
			setCfgNameAndValue(SUPPORTTEO, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTTEO: TAG_NOT_EXISTS");
		reset();
	}
	xmlValue = xml.getValue(bmDoc,CREATETAG108);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CREATETAG108: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->createTag108 = true;
			setCfgNameAndValue(CREATETAG108, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->createTag108 = false;
			setCfgNameAndValue(CREATETAG108, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(CREATETAG108));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "TRANSFORSWIFTTOSWIFT: CREATETAG108");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,TRANSFORSWIFTTOSWIFT);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "TRANSFORSWIFTTOSWIFT: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->transformSwiftToSwift = true;
			pModuleStr->noValidation = false;
			setCfgNameAndValue(TRANSFORSWIFTTOSWIFT, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == NoVALIDATION) {
			pModuleStr->transformSwiftToSwift = true;
			pModuleStr->noValidation = true;
			setCfgNameAndValue(TRANSFORSWIFTTOSWIFT, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->transformSwiftToSwift = false;
			pModuleStr->noValidation = false;
			setCfgNameAndValue(TRANSFORSWIFTTOSWIFT, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(TRANSFORSWIFTTOSWIFT));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "TRANSFORSWIFTTOSWIFT: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,TRANSFORINTERNALFMT);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "TRANSFORINTERNALFMT: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->transformInternalFmt = true;
			setCfgNameAndValue(TRANSFORINTERNALFMT, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->transformInternalFmt = false;
			setCfgNameAndValue(TRANSFORINTERNALFMT, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "Local") {
			pModuleStr->transformInternalFmtLocal = true;
			pModuleStr->transformInternalFmt = false;
			setCfgNameAndValue(TRANSFORINTERNALFMT, "Local");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(TRANSFORINTERNALFMT));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "TRANSFORINTERNALFMT: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,SUPPORTOUTSRC);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTOUTSRC: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->supportOutSrc = true;
			setCfgNameAndValue(SUPPORTOUTSRC, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->supportOutSrc = false;
			setCfgNameAndValue(SUPPORTOUTSRC, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(SUPPORTOUTSRC));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTOUTSRC: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,SUPPORTNAMEKEY);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTNAMEKEY: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->supportNameKey = true;
			setCfgNameAndValue(SUPPORTNAMEKEY, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->supportNameKey = false;
			setCfgNameAndValue(SUPPORTNAMEKEY, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(SUPPORTNAMEKEY));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SUPPORTNAMEKEY: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,CHECKSUM);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CHECKSUM: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->checksum = true;
			setCfgNameAndValue(CHECKSUM, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->checksum = false;
			setCfgNameAndValue(CHECKSUM, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(CHECKSUM));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CHECKSUM: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,PASSAREA);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PASSAREA: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->processPassArea = true;
			setCfgNameAndValue(PASSAREA, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->processPassArea = false;
			setCfgNameAndValue(PASSAREA, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(PASSAREA));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PASSAREA: TAG_NOT_EXISTS");
		reset();
	}

	if (pModuleStr->processPassArea) {
		xmlValue = xml.getValue(bmDoc,NUMBEROFONDEMANDMQS);
		if (xml.getStatus() != SUCCESS)  {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}

		tracing(TRACE_LEVEL_4, "APPISN setup", "NUMBEROFOMQS: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(NUMBEROFONDEMANDMQS));
				return;
			}
		}
		pModuleStr->numberOfOnDemandMQs = atoi(xmlValue.c_str());
	}

	xmlValue = xml.getValue(bmDoc,CONVERTBIC8);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CONVERTBIC8: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->convertBic8 = true;
			setCfgNameAndValue(CONVERTBIC8, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->convertBic8 = false;
			setCfgNameAndValue(CONVERTBIC8, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(CONVERTBIC8));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CONVERTBIC8: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,RESERVEADDRESS);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "RESERVEADDRESS: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->reserveAddress = true;
			setCfgNameAndValue(RESERVEADDRESS, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->reserveAddress = false;
			setCfgNameAndValue(RESERVEADDRESS, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(RESERVEADDRESS));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "RESERVEADDRESS: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,PROCESSGAPCHECK);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}

	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PROCESSGAPCHECK: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->processGapCheck = IUSE1200PASSAREA;

			pModuleStr->getGapTable = true;
			setCfgNameAndValue(PROCESSGAPCHECK, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->processGapCheck = INOGAPCHECK;
			pModuleStr->getGapTable = false;
			setCfgNameAndValue(PROCESSGAPCHECK, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == USEMATADATA) {
			pModuleStr->processGapCheck = IUSEMATADATA;
			pModuleStr->getGapTable = true;
			setCfgNameAndValue(PROCESSGAPCHECK, USEMATADATA);
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == USEBLOCK1SEQNUM) {
			pModuleStr->processGapCheck = IUSEBLOCK1SEQNUM;
			pModuleStr->getGapTable = true;
			setCfgNameAndValue(PROCESSGAPCHECK, USEBLOCK1SEQNUM);
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(PROCESSGAPCHECK));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PROCESSGAPCHECK: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,USEWEBSVC);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "USEWEBSVC: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->useWebSvc = true;
			setCfgNameAndValue(USEWEBSVC, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->useWebSvc = false;
			pModuleStr->getGapTable = false;
			setCfgNameAndValue(USEWEBSVC, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(USEWEBSVC));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "USEWEBSVC: TAG_NOT_EXISTS");
		reset();
	}


	/*
	xmlValue = xml.getValue(bmDoc,HANDLEBLOCK3FORIBR);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "HANDLEBLOCK3FORIBR: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->handleBlock3ForIBR = true;
			setCfgNameAndValue(HANDLEBLOCK3FORIBR, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->handleBlock3ForIBR = false;
			setCfgNameAndValue(HANDLEBLOCK3FORIBR, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(HANDLEBLOCK3FORIBR));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "HANDLEBLOCK3FORIBR: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,LTERMNAME);
	if (xml.getStatus() != SUCCESS) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (strlen(xmlValue.c_str()) == LTERMLEN) {
		strcpy(pModuleStr->lTerm,xmlValue.c_str());
		strncpy(pModuleStr->gateWayBic8.bic8Name,pModuleStr->lTerm,BIC8LEN);
		pModuleStr->gateWayBic8.bic8Name[BIC8LEN] = '\0';
		strncpy(pModuleStr->tid,&(pModuleStr->lTerm[BIC8LEN]),TIDLEN);
		pModuleStr->tid[TIDLEN] = '\0';
	}
	else {
		setStatus(INVALID_VALUE);
		setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(LTERMNAME));
		return;
	}
	xmlValue = xml.getValue(bmDoc,USESAT);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "USESAT: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->useSat = true;
			setCfgNameAndValue(USESAT, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->useSat = false;
			setCfgNameAndValue(USESAT, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(USESAT));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "USESAT: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,CHANGESEQ);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CHANGESEQ: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->changeSeq = true;
			setCfgNameAndValue(CHANGESEQ, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->changeSeq = false;
			setCfgNameAndValue(CHANGESEQ, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(CHANGESEQ));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CHANGESEQ: TAG_NOT_EXISTS");
		reset();
	}
*/

	xmlValue = xml.getValue(bmDoc,RCVREPMSG);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "RCVREPMSG: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->rcvRepMsg = true;
			setCfgNameAndValue(RCVREPMSG, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->rcvRepMsg = false;
			setCfgNameAndValue(RCVREPMSG, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(RCVREPMSG));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "RCVREPMSG: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,NOIBRFORSAMEBIC);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "NOIBRFORSAMEBIC: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->noIBRForSameBIC = true;
			setCfgNameAndValue(NOIBRFORSAMEBIC, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->noIBRForSameBIC = false;
			setCfgNameAndValue(NOIBRFORSAMEBIC, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(NOIBRFORSAMEBIC));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "NOIBRFORSAMEBIC: TAG_NOT_EXISTS");
		reset();
	}
/*
	xmlValue = xml.getValue(bmDoc,MTSHIGHSOURCE);
	if (xml.getStatus() != SUCCESS){
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (strlen(xmlValue.c_str()) == MTS_SOURCE_LEN) {
		strcpy(pModuleStr->highSrc,xmlValue.c_str());
	}
	else {
		setStatus(INVALID_VALUE);
		setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MTSHIGHSOURCE));
		return;
	}
	*/
/*	xmlValue = xml.getValue(bmDoc,LTERMNAME);
	if ((xml.getStatus() != SUCCESS)&& (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		if (strlen(xmlValue.c_str()) == LTERMLEN) {
			strncpy(pModuleStr->gateWayBic8,xmlValue.c_str(),BIC8LEN);
			ModuleStr->gateWayBic8[BIC8LEN] = '\0';
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(LTERMNAME));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "LTERMNAME: TAG_NOT_EXISTS");
		reset();
	}
	*/

/*	xmlValue = xml.getValue(bmDoc,MTSMEDIUMSOURCE);
	if (xml.getStatus() != SUCCESS){
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (strlen(xmlValue.c_str()) == MTS_SOURCE_LEN) {
		strcpy(pModuleStr->mediumSrc,xmlValue.c_str());
	}
	else {
		setStatus(INVALID_VALUE);
		setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MTSMEDIUMSOURCE));
		return;
	}
	xmlValue = xml.getValue(bmDoc,MTSLOWSOURCE);
	if (xml.getStatus() != SUCCESS){
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (strlen(xmlValue.c_str()) == MTS_SOURCE_LEN) {
		strcpy(pModuleStr->lowSrc,xmlValue.c_str());
	}
	else {
		setStatus(INVALID_VALUE);
		setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MTSLOWSOURCE));
		return;
	}


	xmlValue = xml.getValue(bmDoc,MTSIBRSOURCE);
	if (xml.getStatus() != SUCCESS){
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (strlen(xmlValue.c_str()) == MTS_SOURCE_LEN) {
		strcpy(pModuleStr->ibrSrc,xmlValue.c_str());
	}
	else {
		setStatus(INVALID_VALUE);
		setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MTSIBRSOURCE));
		return;
	}
*/

	xmlValue = xml.getValue(bmDoc,BLOCK2TID);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "BLOCK2TID: " + xmlValue);
		if (strlen(xmlValue.c_str()) == TIDLEN) {
			strcpy(pModuleStr->block2Tid,xmlValue.c_str());
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(BLOCK2TID));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "BLOCK2TID: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,APPID);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "APPID: " + xmlValue);
		if (strlen(xmlValue.c_str()) ==APPIDLEN) {
			strcpy(pModuleStr->appId,xmlValue.c_str());
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(APPID));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "APPID: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,MAXIMUMNUMBEROFGAPS);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAXIMUMNUMBEROFGAPS: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MAXIMUMNUMBEROFGAPS));
				return;
			}
		}
		pModuleStr->maximumNumberOfGaps = atoi(xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAXIMUMNUMBEROFGAPS: TAG_NOT_EXISTS");
		reset();
	}
	xmlValue = xml.getValue(bmDoc,PASSAREALENGTH);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PASSAREALENGTH: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(PASSAREALENGTH));
				return;
			}
		}
		pModuleStr->passAreaLength = atoi(xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PASSAREALENGTH: TAG_NOT_EXISTS");
		reset();
	}
	xmlValue = xml.getValue(bmDoc,SEQNUMBERLENGTH);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SEQNUMBERLENGTH: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(SEQNUMBERLENGTH));
				return;
			}
		}
		pModuleStr->seqNumberLength = atoi(xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SEQNUMBERLENGTH: TAG_NOT_EXISTS");
		reset();
	}
	xmlValue = xml.getValue(bmDoc,MAXIMUMNUMBEROFGAPS);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAXIMUMNUMBEROFGAPS: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MAXIMUMNUMBEROFGAPS));
				return;
			}
		}
		pModuleStr->maximumNumberOfGaps = atoi(xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAXIMUMNUMBEROFGAPS: TAG_NOT_EXISTS");
		reset();
	}
	xmlValue = xml.getValue(bmDoc,MAXIMUMGAP);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAXIMUMGAP: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MAXIMUMGAP));
				return;
			}
		}
		pModuleStr->maximumGap = atoi(xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAXIMUMGAP: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,SEQNUMBERSTARTPOS);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SEQNUMBERSTARTPOS: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(SEQNUMBERSTARTPOS));
				return;
			}
		}
		pModuleStr->seqNumberStartPos = atoi(xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SEQNUMBERSTARTPOS: TAG_NOT_EXISTS");
		reset();
	}
	xmlValue = xml.getValue(bmDoc,MAXIMUMSEQNUMBER);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAXIMUMSEQNUMBER: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MAXIMUMSEQNUMBER));
				return;
			}
		}
		pModuleStr->maximumSequenceNumber = atoi(xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MAXIMUMSEQNUMBER: TAG_NOT_EXISTS");
		reset();
	}

	/*
	xmlValue = xml.getValue(bmDoc,IBRSEQFILENAME);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "IBRSEQFILENAME: " + xmlValue);
		strcpy(pModuleStr->ibrSeqFileName,xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "IBRSEQFILENAME: TAG_NOT_EXISTS");
		return;
	}
*/

	xmlValue = xml.getValue(bmDoc,DEFAULTSVCSVR);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "DEFAULTSVCSVR: " + xmlValue);
	/*	pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(DEFAULTSVCPORT));
				return;
			}
		}
		*/
		strcpy(pModuleStr->defaultSvcSvr,xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "DEFAULTSVCSVR: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,EDITCHECKBYSWIFT);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "EDITCHECKBYSWIFT: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->editCheckBySwift = true;
			setCfgNameAndValue(EDITCHECKBYSWIFT, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->editCheckBySwift = false;
			setCfgNameAndValue(USESAT, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(EDITCHECKBYSWIFT));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "EDITCHECKBYSWIFT: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,DRAINMESSAGE);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}

	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CREATEHEADERBLOCK: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->drainMessage = true;
			setCfgNameAndValue(DRAINMESSAGE, "Yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->drainMessage = false;
			setCfgNameAndValue(DRAINMESSAGE, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(DRAINMESSAGE));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "DRAINMESSAGE: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,CREATEHEADERBLOCK);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CREATEHEADERBLOCK: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->createHeaderBlock = true;
			setCfgNameAndValue(EDITCHECKBYSWIFT, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->createHeaderBlock = false;
			setCfgNameAndValue(USESAT, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(CREATEHEADERBLOCK));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "CREATEHEADERBLOCK: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,MESSAGEFORMAT);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MESSAGEFORMAT: " + xmlValue);
		if (xmlValue == NORMALFORMAT) {
			pModuleStr->messageFormat = INORMALFORMAT;
			setCfgNameAndValue(MESSAGEFORMAT, NORMALFORMAT);
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == STDFORMAT) {
			pModuleStr->messageFormat = ISTDFORMAT;
			pModuleStr->correlationId  = ICORRSTANDARD;
			setCfgNameAndValue(MESSAGEFORMAT, STDFORMAT);
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MESSAGEFORMAT));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "MESSAGEFORMAT: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,ANNUALFORMAT);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ANNUALFORMAT: " + xmlValue);
		int len = strlen(xmlValue.c_str());
		if (len != FORMAT_LEN) {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(ANNUALFORMAT));
			return;
		}
		strcpy(pModuleStr->annualFormat,xmlValue.c_str());
	}
	else {
		if (pModuleStr->defaultSvcPort != NOSVC) {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- MIssing TAG: " + toString(ANNUALFORMAT));
			return;
		}
		else {
			tracing(TRACE_LEVEL_4, "APPISN setup", "ANNUALFORMAT: TAG_NOT_EXISTS");
			reset();
		}
	}
	xmlValue = xml.getValue(bmDoc,PASSERRMSGTOSWF);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PASSERRMSGTOSWF: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->passErrMsgToSwf = true;
			setCfgNameAndValue(PASSERRMSGTOSWF, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->passErrMsgToSwf = false;
			setCfgNameAndValue(PASSERRMSGTOSWF, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(PASSERRMSGTOSWF));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PASSERRMSGTOSWF: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,REPLACEINVALIDCHAR);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "REPLACEINVALIDCHAR: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->replaceInvalidChar = true;
			setCfgNameAndValue(REPLACEINVALIDCHAR, "Yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->replaceInvalidChar = false;
			setCfgNameAndValue(REPLACEINVALIDCHAR, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(REPLACEINVALIDCHAR));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "REPLACEINVALIDCHAR: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,ADDPDE);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ADDPDE: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->addPDE = true;
			setCfgNameAndValue(ADDPDE, "Yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->addPDE = false;
			setCfgNameAndValue(ADDPDE, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(ADDPDE));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ADDPDE: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,PROCESSIBR);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PROCESSIBR: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->processIBR = true;
			setCfgNameAndValue(PROCESSIBR, "Yes");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->processIBR = false;
			setCfgNameAndValue(PROCESSIBR, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(PROCESSIBR));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PROCESSIBR: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,FORMATBLOCK3);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}

	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "FORMATBLOCK3: " + xmlValue);
		if (xmlValue == BLOCK3TYPE1) {
			pModuleStr->block3Type = IBLOCK3TYPE1;
			setCfgNameAndValue(FORMATBLOCK3, BLOCK3TYPE1);
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == BLOCK3TYPE2) {
			pModuleStr->block3Type = IBLOCK3TYPE2;
			setCfgNameAndValue(FORMATBLOCK3, BLOCK3TYPE2);
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else if (xmlValue == BLOCK3TYPE3) {
			pModuleStr->block3Type = IBLOCK3TYPE3;
			setCfgNameAndValue(FORMATBLOCK3, BLOCK3TYPE3);
			if (retStatus() != SUCCESS) {
				return;
			}
			trnPreFixListDoc = xml.getNode(bmDoc,GTMTRNPREFIXLIST);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			pModuleStr->numberOfTrnPrefix = xml.getNodes(trnPreFixListDoc,GTMTRNPREFIX,trnPreFixDocs,MAX_TRNPREFIX);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			pModuleStr->pTrnPrefixStr = (PTRNPREFIXSTR) malloc(sizeof(TRNPREFIXSTR) * pModuleStr->numberOfTrnPrefix);
			for (i = 0; i < pModuleStr->numberOfTrnPrefix; i++) {
				trnPrefix = xml.getValue(trnPreFixDocs[i],GTMTRNPREFIX);
				if (xml.getStatus() != SUCCESS) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}
				strcpy(pModuleStr->pTrnPrefixStr[i].trnPrefix,trnPrefix.c_str());
			}
			qsort (pModuleStr->pTrnPrefixStr, pModuleStr->numberOfTrnPrefix, sizeof(TRNPREFIXSTR), trnPrefixComparator);

		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(FORMATBLOCK3));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PROCESSIBR: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,SENDERBIC);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SENDERBIC: " + xmlValue);
		if (strlen(xmlValue.c_str()) != BIC8LEN) {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(SENDERBIC));
			return;
		}
		strcpy(pModuleStr->senderBic8,xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "SENDERBIC: TAG_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,VALIDRCVBIC8);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "VALIDRCVBIC8: " + xmlValue);
		if (strlen(xmlValue.c_str()) != BIC8LEN) {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(VALIDRCVBIC8));
			return;
		}
		strcpy(pModuleStr->validRcvBic8,xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "VALIDRCVBIC8: TAG_NOT_EXISTS");
		reset();
	}

	asnPreFixListDoc = xml.getNode(bmDoc,ASNPREFIXLIST);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != NODE_NOT_EXISTS) {
		pModuleStr->numberOfAsnPrefix = xml.getNodes(asnPreFixListDoc,ASNPREFIX,asnPreFixDocs,MAX_ASNPREFIX);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pAsnPrefixStr = (PASNPREFIXSTR) malloc(sizeof(ASNPREFIXSTR) * pModuleStr->numberOfAsnPrefix);
		for (i = 0; i < pModuleStr->numberOfAsnPrefix; i++) {
			asnPrefix = xml.getValue(asnPreFixDocs[i],ASNPREFIX);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			strcpy(pModuleStr->pAsnPrefixStr[i].asnPrefix,asnPrefix.c_str());
			pModuleStr->pAsnPrefixStr[i].outputModuleIndex = i;
		}
		qsort (pModuleStr->pAsnPrefixStr, pModuleStr->numberOfAsnPrefix, sizeof(ASNPREFIXSTR), asnPrefixComparator);
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "ASNPREFIXLIST: NODE_NOT_EXISTS");
		reset();
	}

	xmlValue = xml.getValue(bmDoc,GAPCHECKBYSVC);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "GAPCHECKBYSVC: " + xmlValue);
		if (xmlValue == "Yes") {
			pModuleStr->gapCheckBySvc = true;
			setCfgNameAndValue(GAPCHECKBYSVC, "yes");
			if (retStatus() != SUCCESS) {
				return;
			}
			if (pModuleStr->asnPrefix[0] == '\0') {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Missing Tag AsnPrefix");
				return;
			}
		}
		else if (xmlValue == "No") {
			pModuleStr->gapCheckBySvc = false;
			setCfgNameAndValue(GAPCHECKBYSVC, "No");
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			setStatus(INVALID_VALUE);
			setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(GAPCHECKBYSVC));
			return;
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "GAPCHECKBYSVC: TAG_NOT_EXISTS");
		reset();
	}
	xmlValue = xml.getValue(bmDoc,NUMOFMSG);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != TAG_NOT_EXISTS) {
		tracing(TRACE_LEVEL_4, "APPISN setup", "NUMOFMSG: " + xmlValue);
		pt = (char *)xmlValue.c_str();
		for (i = 0; i < strlen(pt); i++) {
			if (!isdigit(pt[i])) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(NUMOFMSG));
				return;
			}
		}
		pModuleStr->numberOfMessagesToDrain = atoi(xmlValue.c_str());
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "NUMOFMSG: TAG_NOT_EXISTS");
		reset();
	}

	priorityListDoc = xml.getNode(bmDoc,PRIORITYDEFLIST);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)){
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != NODE_NOT_EXISTS) {
		pModuleStr->numberOfPriorityDef = xml.getNodes(priorityListDoc,PRIORITYDEF,priorityDocs,MAX_PRIORITY);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pPriorityStr = (PPRIOITYSTR) malloc(sizeof(PRIORITYSTR) * pModuleStr->numberOfPriorityDef);

		for (i = 0; i < pModuleStr->numberOfPriorityDef; i++) {
			xmlValue = xml.getValue(priorityDocs[i],MTTYPE);
			if (strlen(xmlValue.c_str()) == MTTYPE_LEN) {
				strcpy((pModuleStr->pPriorityStr[i]).mtType,xmlValue.c_str());
			}
			else {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(MTTYPE));
				return;
			}
			xmlValue = xml.getValue(priorityDocs[i],PRIORITY);
			if (!strcmp(xmlValue.c_str(),HIGH)) {
				(pModuleStr->pPriorityStr[i]).priority = PRIORITYHIGH;
			}
			else if (!strcmp(xmlValue.c_str(),MEDIUM)) {
				(pModuleStr->pPriorityStr[i]).priority = PRIORITYMEDIUM;
			}
			else if (!strcmp(xmlValue.c_str(),LOW)) {
				(pModuleStr->pPriorityStr[i]).priority = PRIORITYLOW;
			}
			else {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(PRIORITY));
				return;
			}
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "PRIORITYDEFLIST: NODE_NOT_EXISTS");
		reset();
	}

	tracing(TRACE_LEVEL_1, "APPISN setup", "ended");
}

void registerSvc(PGWYSTR pGwyStr) {
	string params;
	int retValue;
	int reConnectCount = 0;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	CSvcClient* pSvcClient;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN registerSvc", "started");

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;

	if (pModuleStr->useWebSvc) {
		params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(pModuleStr->annualFormat) + toString(PARAMEND) +
				toString(PARAMSTART) + toString(REMOTEEDITCHK) + toString(PARAMEND) +
				toString(PARAMSEND);
	}
	else {
		params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(pModuleStr->annualFormat) + toString(PARAMEND) + toString(PARAMSEND);
	}

	while (1) {
		retValue = pSvcClient->svcClientRegSvc(EDITCHECK, params, svcClientRequest, svcServerResponse, MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			pModuleStr->editSvcFailed = true;
			break;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				pModuleStr->editSvcFailed = true;
				break;
			}
			else {
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				endPt = strstr(pt,SVCRSPEND);
				if (endPt != NULL) {
					endPt[0] = '\0';
					strcpy(pModuleStr->svcHandler,pt);
				}
				else {
					pModuleStr->editSvcFailed = true;
				}
			}
			else {
				pModuleStr->editSvcFailed = true;
			}
			break;
		}
	}


	tracing(TRACE_LEVEL_1, "APPISN registerSvc", "ended");
	return;
}

void registerGapCheckSvc(PGWYSTR pGwyStr) {
	string params;
	int retValue;
	int reConnectCount = 0;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	CSvcClient* pSvcClient;
	char gapCheckAppId[APPIDLEN+1];

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN registerGapCheckSvc", "started");

	if (pModuleStr->mainAppId[0] != '\0') {
		strcat(gapCheckAppId,pModuleStr->mainAppId);
	}
	else {
		strcat(gapCheckAppId,pModuleStr->appId);
	}
	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;
	params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(gapCheckAppId) + toString(PARAMEND) +
				toString(PARAMSTART) + toString(pModuleStr->asnPrefix) + toString(PARAMEND) +
				toString(PARAMSEND);

	while (1) {

		retValue = pSvcClient->svcClientRegSvc(GAPCHECK, params, svcClientRequest, svcServerResponse, MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN registerGapCheckSvc", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN registerGapCheckSvc", "ended");
				return;
			}
			else {
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				endPt = strstr(pt,SVCRSPEND);
				if (endPt != NULL) {
					endPt[0] = '\0';
					strcpy(pModuleStr->svcGapCheckHandler,pt);
				}
				else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN registerGapCheckSvc", "ended");
					return;
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN registerGapCheckSvc", "ended");
				return;
			}
			break;
		}
	}


	tracing(TRACE_LEVEL_1, "APPISN registerGapCheckSvc", "ended");
	return;
}

void registerTFMSvc(PGWYSTR pGwyStr) {
	string params;
	int retValue;
	int reConnectCount = 0;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	CSvcClient* pSvcClient;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "started");


	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;
	if (pModuleStr->transformInternalFmt) {
		params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(pModuleStr->annualFormat) + toString(PARAMEND) +
					toString(PARAMSTART) + toString(BNYINTERNALTOSWIFTBLOCK4) + toString(PARAMEND) +
					toString(PARAMSEND);
	}
	else if ((pModuleStr->transformSwiftToSwift) &&(!pModuleStr->noValidation)) {
		params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(pModuleStr->annualFormat) + toString(PARAMEND) +
					toString(PARAMSTART) + toString(SWIFTTOSWIFTBLOCK4) + toString(PARAMEND) +
					toString(PARAMSEND);
	}
	else if ((pModuleStr->transformSwiftToSwift) &&(pModuleStr->noValidation)) {
		params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(pModuleStr->annualFormat) + toString(PARAMEND) +
					toString(PARAMSTART) + toString(SWIFTTOSWIFTBLOCK4NV) + toString(PARAMEND) +
					toString(PARAMSEND);
	}


	while (1) {

		retValue = pSvcClient->svcClientRegSvc(TRANSFORM, params, svcClientRequest, svcServerResponse, MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
				return;
			}
			else {
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				endPt = strstr(pt,SVCRSPEND);
				if (endPt != NULL) {
					endPt[0] = '\0';
					strcpy(pModuleStr->svcTFMHandler,pt);
				}
				else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
					return;
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
				return;
			}
			break;
		}
	}


	tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
	return;
}

/* void registerTFMSvc(PGWYSTR pGwyStr) {
	string params;
	int retValue;
	int reConnectCount = 0;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	CSvcClient* pSvcClient;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "started");


	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;
	params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(pModuleStr->annualFormat) + toString(PARAMEND) +
				toString(PARAMSTART) + toString(BNYINTERNALTOSWIFTBLOCK4) + toString(PARAMEND) +
				toString(PARAMSEND);


	while (1) {

		retValue = pSvcClient->svcClientRegSvc(TRANSFORM, params, svcClientRequest, svcServerResponse, MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
				return;
			}
			else {
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				endPt = strstr(pt,SVCRSPEND);
				if (endPt != NULL) {
					endPt[0] = '\0';
					strcpy(pModuleStr->svcTFMHandler,pt);
				}
				else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
					return;
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
				return;
			}
			break;
		}
	}


	tracing(TRACE_LEVEL_1, "APPISN registerTFMSvc", "ended");
	return;
}
*/
void registerCIFSvc(PGWYSTR pGwyStr) {
	string params;
	int retValue;
	int reConnectCount = 0;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	CSvcClient* pSvcClient;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN registerCIFSvc", "started");

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;

	//params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(CIFINFO) + toString(PARAMEND) + toString(PARAMSEND);
	params = "";

	while (1) {
		retValue = pSvcClient->svcClientRegSvc(CIFINFO, params, svcClientRequest, svcServerResponse, MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN registerCIFSvc", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN registerCIFSvc", "ended");
				return;
			}
			else {
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				endPt = strstr(pt,SVCRSPEND);
				if (endPt != NULL) {
					endPt[0] = '\0';
					strncpy(pModuleStr->svcCIFHandler,pt,SVCHANDLER_LEN);
					pModuleStr->svcCIFHandler[SVCHANDLER_LEN] = '\0';
				}
				else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN registerCIFSvc", "ended");
					return;
				}
			}
			else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN registerCIFSvc", "ended");
					return;
			}
			break;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN registerCIFSvc", "ended");
	return;
}

void getCIFInfo(PGWYSTR pGwyStr, string type, string inputValue) {
	string params;
	int retValue;
	int reConnectCount = 0;
	char cifInfo[MAX_CIF_LENGTH+1];
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	CSvcClient* pSvcClient;
	bool afterReconnect = false;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getCIFInfo", "started");

	params = toString(PARAMSSTART) + toString(PARAMSTART) + type + toString(PARAMEND)  + toString(PARAMSTART) + inputValue + toString(PARAMEND) + toString(PARAMSEND);

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;

	while (1) {
		if (afterReconnect) {
			registerCIFSvc(pGwyStr);
			if (retStatus() != SUCCESS) {
				afterReconnect = false;
				break;
			}
		}
		retValue = pSvcClient->svcClientReqSvc(pModuleStr->svcCIFHandler, CIFFETCH, params, svcClientRequest, cifInfo, MAX_CIF_LENGTH);
		if (retValue == FAIL_TO_CONNECT){
			cifInfo[0] = '\0';
			break;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				cifInfo[0] = '\0';
				break;
			}
			else {
				afterReconnect =true;
				continue;
			}
		}
		else {
			char* pt = &cifInfo[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				if (pModuleStr->rcvBic12[0] == '\0') {
					strncpy(pModuleStr->rcvBic12,pt,BIC8LEN);
					pModuleStr->rcvBic12[BIC8LEN] = 'X';
					strncpy(&(pModuleStr->rcvBic12[BIC8LEN+1]),&(pt[BIC8LEN]),BRANCHLEN);
					pModuleStr->rcvBic12[BIC12LEN] = '\0';
				}
				pt = pt + BIC11LEN + 1;
				if (pModuleStr->nameKey[0] == '\0') {
					strncpy(pModuleStr->nameKey,pt,NAMEKEYLEN);
					pModuleStr->nameKey[NAMEKEYLEN] = '\0';
				}
				pt = pt + NAMEKEYLEN + 1;
				if (pModuleStr->cid[0] == '\0') {
					strncpy(pModuleStr->cid,pt,CIDLEN);
					pModuleStr->cid[CIDLEN] = '\0';
				}
			}
			break;
		}
	}
}

void registerGTMAckSvc(PGWYSTR pGwyStr) {
	string params;
	int retValue;
	int reConnectCount = 0;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	CSvcClient* pSvcClient;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN registerGTMAckSvc", "started");


	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;
	params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(RECEIVED) + toString(PARAMEND) + toString(PARAMSEND);

	while (1) {

		retValue = pSvcClient->svcClientRegSvc(GENGTMACK, params, svcClientRequest, svcServerResponse, MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN registerGTMAckSvc", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN registerGTMAckSvc", "ended");
				return;
			}
			else {
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				endPt = strstr(pt,SVCRSPEND);
				if (endPt != NULL) {
					endPt[0] = '\0';
					strcpy(pModuleStr->svcGTMAckHandler,pt);
				}
				else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN registerGTMAckSvc", "ended");
					return;
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN registerGTMAckSvc", "ended");
				return;
			}
			break;
		}
	}


	tracing(TRACE_LEVEL_1, "APPISN registerGTMAckSvc", "ended");

	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	getApplicationId -- Get Application Id.
// Parameters:	msg -- The message may contain the application Id.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void getApplicationId(PGWYSTR pGwyStr, char* msg) {
	char* appidStartPt = NULL;
	char* appidEndPt = NULL;
	char tmpChar;
	char priority;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getApplicationId", "started");

	appidStartPt=strstr(msg,APPLICATIONID);

	if (appidStartPt != NULL) {
		appidStartPt += strlen(APPLICATIONID);
		appidEndPt = NULL;
		appidEndPt=strstr(appidStartPt,"\r\n");
		if ((appidEndPt != NULL) && ((appidEndPt - appidStartPt) >= APPIDLEN)) {
			strncpy(pModuleStr->appId,appidStartPt,APPIDLEN);
			pModuleStr->appId[APPIDLEN] = '\0';
		}
	}

	tracing(TRACE_LEVEL_1, "APPISN getApplicationId", "ended");
}


int getSeqNumber(PGWYSTR pGwyStr) {
	char sSeqNumber[32];
	char* pt;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getSeqNumber", "started");

	if (pModuleStr->supportCIBC) {
		strncpy(sSeqNumber, (char*) &(pGwyStr->inputMessage[FROMSEQPOS]), FROMSEQLEN);
		sSeqNumber[FROMSEQLEN] = '\0';
		tracing(TRACE_LEVEL_1, "APPISN getSeqNumber", "ended");
		return atoi(sSeqNumber);
	}
	if (pModuleStr->processGapCheck == IUSE1200PASSAREA) {
		strncpy(sSeqNumber, (char*) &(pGwyStr->inputMessage[pModuleStr->seqNumberStartPos]), pModuleStr->seqNumberLength);
		sSeqNumber[pModuleStr->seqNumberLength] = '\0';
	}
	else if (pModuleStr->processGapCheck == IUSEMATADATA)  {
		pt = strstr(pGwyStr->inputMessage,METADATA);
		pt = strstr(pt,CORRID);
		pt = pt + strlen(CORRID);
		strncpy(sSeqNumber, (char*) &(pt[pModuleStr->seqNumberStartPos]), pModuleStr->seqNumberLength);
		sSeqNumber[pModuleStr->seqNumberLength] = '\0';
	}
	else if (pModuleStr->processGapCheck == IUSEBLOCK1SEQNUM)  {
		pt = strstr(pGwyStr->inputMessage,BLOCK1);
		strncpy(sSeqNumber, (char*) &(pt[pModuleStr->seqNumberStartPos]), pModuleStr->seqNumberLength);
		sSeqNumber[pModuleStr->seqNumberLength] = '\0';
	}
	tracing(TRACE_LEVEL_1, "APPISN getSeqNumber", "ended");
	return atoi(sSeqNumber);


}
/*
int checkGapOrDuplication(PGWYSTR pGwyStr, int seq, int circular) {

	int idx, idx1;
	int	lowGapIdx, highGapIdx;
	int expectedSeq;
	int* pGapRang;
	int* pGapRang1;
	int numberOfGaps;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "started");
	reset();

	expectedSeq = pModuleStr->pGapTable[1];
	numberOfGaps = pModuleStr->pGapTable[0];

	for (i = 1; i <= numberOfGaps; i++) {

	if (numberOfGaps == 0) {
		return NEWGAP;
	}
	lowGapIdx = 1;
	highGapIdx = numberOfGaps;
	idx = (highGapIdx - lowGapIdx) / 2 + lowGapIdx;
	while (1) {
		if (pModuleStr->pGapTable[idx * 2 + 1] >= pModuleStr->pGapTable[idx * 2]) {
			if (seq > pModuleStr->pGapTable[idx * 2 + 1]) {


				if (idx == numberOfGaps) {
					if (seq < expectedSeq) {
						if (circular == 0) {
							return DUPLICATED;
						}
						else {
							return NEWGAP;
						}
					}
					else {
						if (circular == 0) {
							return NEWGAP;
						}
						else {
							return DUPLICATED;
						}
					}
				}
				idx1 = idx + 1;
				if (seq < pModuleStr->pGapTable[idx1 * 2]) {
					return DUPLICATED;
				}
				lowGapIdx = idx + 1;
				idx = (highGapIdx - lowGapIdx) / 2 + lowGapIdx;
				continue;
			}
			else if (seq < pModuleStr->pGapTable[idx * 2]) {


				if (idx == 1) {
					if (seq < expectedSeq) {
						if ((circular == 0){
							return DUPLICATED;
						}
						if (circular == 2) {
							return NEWGAP;

						}
					}
					else if (circular == 1) {
						return DUPLICATED;
					}
				}
				idx1 = idx - 1;
				if (seq > pModuleStr->pGapTable[idx1 * 2 + 1]) {
					if (seq < expectedSeq) {
						if (circular == 0) {
							return DUPLICATED;
						}
						else {
							return NEWGAP;
						}
					}
					else {
					}
					if (circular == 2) {
						return NEWGAP;
					}
				}
				highGapIdx = highGapIdx -1;
				idx = idx = (highGapIdx - lowGapIdx) / 2 + lowGapIdx;
				continue;
			}
			else {
				return idx;
			}
		}
		else {
			if ((seq > pModuleStr->pGapTable[idx * 2 + 1]) && (seq < pModuleStr->pGapTable[idx * 2])) {
				if (idx == numberOfGaps) {
					return NEWGAP;
				}
				idx1 = idx + 1;
				if (seq < pModuleStr->pGapTable[idx1 * 2]) {
					return DUPLICATED;
				}
				lowGapIdx = idx + 1;
				idx = (highGapIdx - lowGapIdx) / 2 + lowGapIdx;
				continue;
			}
			else if (seq < pModuleStr->pGapTable[idx * 2]) {
				if (idx == 0) {
					return DUPLICATED;
				}
				idx1 = idx - 1;
				if (seq > pModuleStr->pGapTable[idx1 * 2 + 1]) {
					return DUPLICATED;
				}
				highGapIdx = highGapIdx -1;
				idx = idx = (highGapIdx - lowGapIdx) / 2 + lowGapIdx;
				continue;
			}
			else {
				return idx;
			}
		}
	}
	return 0;
}
*/

void sendAlert(PGWYSTR pGwyStr, string subject, string alert) {
	FILE* alertFp;
	string cmd;
	string alertEmail;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "started");

	if (pModuleStr->numberOfAlertEmails > 0) {
		alertFp = fopen(pModuleStr->alertEmailFileName,"w+");
		fprintf(alertFp,"%s\n",alert.c_str());
		fclose(alertFp);

		cmd = "mailx -s \"" + subject + "\" ";

		if (pModuleStr->numberOfAlertEmails > 1) {
			cmd = cmd + " -c \" ";
			for (int i = 1; i < pModuleStr->numberOfAlertEmails; i++) {
				alertEmail = pModuleStr->pAlertEmailStr[i].alertEmailAddress;
				cmd = cmd + alertEmail + " ";
			}
			cmd = cmd + "\" ";
		}
		alertEmail = pModuleStr->pAlertEmailStr[0].alertEmailAddress;
		cmd = cmd + " " + alertEmail;
		cmd = cmd + " < " + toString(pModuleStr->alertEmailFileName);
		system(cmd.c_str());
	}

	tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
}

void processcGapOrDuplication(PGWYSTR pGwyStr, int seq) {
	int expectedSeq;
	int numberOfGaps;
	int* pGapRang;
	int* pGapRang1;
	int checkSeq;
	int i;
	int gap;
	int gap1;
	int gapCase = 0;
	int lastGapIndex;
	int j;
	string errorMsg;
	string subject;



	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "started");
	reset();

	expectedSeq = pModuleStr->pGapTable[1];
	numberOfGaps = pModuleStr->pGapTable[0];
	lastGapIndex = pModuleStr->pGapTable[2];

	if (seq == expectedSeq) {
		gapCase = 0;
		gap = 0;
	}
	else if (seq > expectedSeq) {
		gap = seq - expectedSeq;
		gap1 = expectedSeq + pModuleStr->maximumSequenceNumber - seq;
		if (gap1 < gap) {
			gapCase = 2;
			gap = 0;
		}
		else {
			gapCase = 1;
		}
	}
	else {
		gap = expectedSeq - seq;
		gap1 = pModuleStr->maximumSequenceNumber + seq - expectedSeq;
		if (gap1 < gap) {
			gapCase = 4;
			gap = gap1;
		}
		else {
			gapCase = 3;
			gap = 0;
		}
	}

	if (gap > pModuleStr->maximumGap) {
		errorMsg = pModuleStr->appId;
		errorMsg = errorMsg + ": FNI ISN gateway is down -- sequence gap exceeded the maximum gap limit. Expected Sequence Number = " + passInt("%d",expectedSeq) + " Current Sequence Number = " + passInt("%d",seq);
		subject = pModuleStr->appId;
		subject = subject + ": FNI ISN gateway is down -- sequence gap exceeded the maximum gap limit";
		setStatus(GAPCHECK_EXCEED_MAXGAP);
		setErrorMessage(errorMsg);
		sendAlert(pGwyStr,subject, errorMsg);
		tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
		return;
	}

	if (numberOfGaps == 0) {
		switch (gapCase)
		{
			case 0:
			{
				pModuleStr->pGapTable[1] = (seq == pModuleStr->maximumSequenceNumber) ? 1: seq + 1;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			break;
			case 1:
			{
				pModuleStr->pGapTable[1] = (seq == pModuleStr->maximumSequenceNumber) ? 1: seq + 1;
				numberOfGaps++;
				pModuleStr->pGapTable[0] = numberOfGaps;
				lastGapIndex = 2;
				pModuleStr->pGapTable[2] = lastGapIndex;
				pModuleStr->pGapTable[lastGapIndex * 2] = expectedSeq;
				pModuleStr->pGapTable[lastGapIndex * 2 + 1] = seq - 1;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			break;
			case 2:
			{
				subject = pModuleStr->appId;
				subject = subject + ": " + toString(DUPLICATEDMESSAGE);
				errorMsg = pModuleStr->appId;
				errorMsg = errorMsg + ": " + toString(DUPLICATEDMESSAGE) + ". Expected Sequence Number = " + passInt("%d",expectedSeq) + " Current Sequence Number = " + passInt("%d",seq);
				setStatus(GAPCHECK_DUPLICATE_SEQ);
				setErrorMessage(errorMsg);
				sendAlert(pGwyStr,subject, errorMsg);
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			break;
			case 3:
			{
				subject = pModuleStr->appId;
				subject = subject + ": " + toString(DUPLICATEDMESSAGE);
				errorMsg = pModuleStr->appId;
				errorMsg = errorMsg + ": " + toString(DUPLICATEDMESSAGE) + ". Expected Sequence Number = " + passInt("%d",expectedSeq) + " Current Sequence Number = " + passInt("%d",seq);

				sendAlert(pGwyStr,subject, errorMsg);
				setStatus(GAPCHECK_DUPLICATE_SEQ);
				setErrorMessage(errorMsg);
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			break;
			case 4:
			{
				numberOfGaps = numberOfGaps + 2;
				pModuleStr->pGapTable[1] = (seq == pModuleStr->maximumSequenceNumber) ? 1: seq + 1;
				pModuleStr->pGapTable[0] = numberOfGaps;
				lastGapIndex = 2;
				pModuleStr->pGapTable[2] = lastGapIndex;
				pModuleStr->pGapTable[lastGapIndex * 2] = 1;
				pModuleStr->pGapTable[lastGapIndex * 2 + 1] = seq - 1;
				pModuleStr->pGapTable[(lastGapIndex + 1) * 2] = expectedSeq;
				pModuleStr->pGapTable[(lastGapIndex + 1) * 2 + 1] = pModuleStr->maximumSequenceNumber;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			break;
		}
	}
	switch (gapCase)
	{
		case 0:
		{
			int tableIdx;
			int newExpectedSeq = (seq == pModuleStr->maximumSequenceNumber) ? 1: seq + 1;

			if (newExpectedSeq == 1) {
				tableIdx = 2;
				pModuleStr->pGapTable[2] = 0;
			}
			else if (lastGapIndex == 0) {
				tableIdx = 2;
			}
			else {
				tableIdx = lastGapIndex + 1;
			}
			int newNumberGaps = numberOfGaps;
			for (i = tableIdx; i <= numberOfGaps + 1; i++) {
				if (newExpectedSeq >= pModuleStr->pGapTable[i * 2]) {
					newNumberGaps--;
					continue;
				}
				break;
			}
			if (i > tableIdx) {
				int idx = tableIdx;
				for (j = i ; j <= (numberOfGaps + 1); j++) {
					pModuleStr->pGapTable[idx * 2 + 1] = pModuleStr->pGapTable[j * 2 + 1];
					pModuleStr->pGapTable[idx * 2] = pModuleStr->pGapTable[j * 2];
					idx++;
				}
				numberOfGaps = newNumberGaps;
				pModuleStr->pGapTable[0] = numberOfGaps;
			}
			pModuleStr->pGapTable[1] = newExpectedSeq;
			tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
			return;
		}
		break;
		case 1:
		{
			if (((numberOfGaps  + 1) == lastGapIndex) && (expectedSeq != 1))  {
				lastGapIndex++;
				numberOfGaps++;
				pModuleStr->pGapTable[lastGapIndex * 2 ] = expectedSeq;
				pModuleStr->pGapTable[lastGapIndex * 2 + 1] = seq - 1;
				pModuleStr->pGapTable[0] = numberOfGaps;
				pModuleStr->pGapTable[1] = (seq == pModuleStr->maximumSequenceNumber) ? 1: seq + 1;
				pModuleStr->pGapTable[2] = lastGapIndex;
				return;
			}
			else {
				if (expectedSeq  == 1) {
					lastGapIndex = 2;
				}
				else if (lastGapIndex == 0) {
					lastGapIndex = 2;
				}
				else {
					lastGapIndex++;
				}

				if ( (seq + 1) < pModuleStr->pGapTable[lastGapIndex * 2]) {

					for (i = (numberOfGaps + 2); i > lastGapIndex; i--) {
						int n = i - 1;
						pModuleStr->pGapTable[i * 2 + 1] = pModuleStr->pGapTable[n * 2 + 1];
						pModuleStr->pGapTable[i * 2] = pModuleStr->pGapTable[n * 2];
					}
					pModuleStr->pGapTable[lastGapIndex * 2 ] = expectedSeq;
					pModuleStr->pGapTable[lastGapIndex * 2 + 1] = seq - 1;
					numberOfGaps++;
					pModuleStr->pGapTable[0] = numberOfGaps;
					pModuleStr->pGapTable[1] = (seq == pModuleStr->maximumSequenceNumber) ? 1: seq + 1;
					pModuleStr->pGapTable[2] = lastGapIndex;
					tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
					return;
				}

				pModuleStr->pGapTable[lastGapIndex * 2 ] = expectedSeq;
				pModuleStr->pGapTable[lastGapIndex * 2 + 1] = seq - 1;

				for (i = lastGapIndex + 1; i <= (numberOfGaps + 1); i++) {
					if ((seq + 1) >= pModuleStr->pGapTable[i * 2]) {
						continue;
					}
					break;
				}


				int newNumberGaps = lastGapIndex - 1;
				if (i <= (numberOfGaps + 1)) {
					int n = lastGapIndex;
					for (j = i; j <= numberOfGaps + 1; j++) {
						n++;
						pModuleStr->pGapTable[n * 2 + 1] = pModuleStr->pGapTable[j * 2 + 1];
						pModuleStr->pGapTable[n * 2] = pModuleStr->pGapTable[j * 2];
						newNumberGaps++;
					}
				}
				numberOfGaps = newNumberGaps;


				pModuleStr->pGapTable[0] = numberOfGaps;
				pModuleStr->pGapTable[1] = (seq == pModuleStr->maximumSequenceNumber) ? 1: seq + 1;
				pModuleStr->pGapTable[2] = lastGapIndex;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
		}
		break;
		case 2:
		{
			for (i = lastGapIndex + 1; i <= numberOfGaps + 1; i++) {

				if (seq > pModuleStr->pGapTable[i * 2 + 1]) {
					continue;
				}
				break;
			}

			if (i == (numberOfGaps + 2)) {
				subject = pModuleStr->appId;
				subject = subject + ": " + toString(DUPLICATEDMESSAGE);
				errorMsg = pModuleStr->appId;
				errorMsg = errorMsg + ": " + toString(DUPLICATEDMESSAGE) + ". Expected Sequence Number = " + passInt("%d",expectedSeq) + " Current Sequence Number = " + passInt("%d",seq);
				sendAlert(pGwyStr,subject, errorMsg);
				setStatus(GAPCHECK_DUPLICATE_SEQ);
				setErrorMessage(errorMsg);
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			if (seq < pModuleStr->pGapTable[i * 2]) {
				subject = pModuleStr->appId;
				subject = subject + ": " + toString(DUPLICATEDMESSAGE);
				errorMsg = pModuleStr->appId;
				errorMsg = errorMsg + ": " + toString(DUPLICATEDMESSAGE) + ". Expected Sequence Number = " + passInt("%d",expectedSeq) + " Current Sequence Number = " + passInt("%d",seq);
				sendAlert(pGwyStr,subject, errorMsg);
				setStatus(GAPCHECK_DUPLICATE_SEQ);
				setErrorMessage(errorMsg);
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			if (pModuleStr->pGapTable[i * 2] == pModuleStr->pGapTable[i * 2 + 1]) {
				for (j = i; j <= numberOfGaps + 1; j++ ) {
					int idx = j + 1;
					pModuleStr->pGapTable[j * 2] = pModuleStr->pGapTable[idx * 2];
					pModuleStr->pGapTable[j * 2 + 1] = pModuleStr->pGapTable[idx * 2 + 1];
				}
				numberOfGaps--;
				pModuleStr->pGapTable[0] = numberOfGaps;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			if (seq == pModuleStr->pGapTable[i * 2 + 1]) {
				pModuleStr->pGapTable[i * 2 + 1] = seq - 1;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			if (seq == pModuleStr->pGapTable[i * 2]) {
				pModuleStr->pGapTable[i * 2] = seq + 1;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			int upSeq = pModuleStr->pGapTable[i * 2 + 1];

			pModuleStr->pGapTable[i * 2 + 1] = seq - 1;
			int idx;
			numberOfGaps++;
			for (j = numberOfGaps + 1; j >= i + 1; j--) {
				idx = j - 1;
				pModuleStr->pGapTable[j * 2] = pModuleStr->pGapTable[idx * 2];
				pModuleStr->pGapTable[j * 2 + 1] = pModuleStr->pGapTable[idx * 2 + 1];
			}
			idx = i + 1;
			pModuleStr->pGapTable[idx * 2 + 1] = upSeq;
			pModuleStr->pGapTable[idx * 2] = seq + 1;
			pModuleStr->pGapTable[0] = numberOfGaps;
			tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
			return;
		}
		break;
		case 3:
		{
			for (i = 2; i <= lastGapIndex; i++) {
				if (seq > pModuleStr->pGapTable[i * 2 + 1]) {
					continue;
				}
				break;
			}
			if (i == (lastGapIndex + 1)) {
				subject = pModuleStr->appId;
				subject = subject + ": " + toString(DUPLICATEDMESSAGE);
				errorMsg = pModuleStr->appId;
				errorMsg = errorMsg + ": " + toString(DUPLICATEDMESSAGE) + ". Expected Sequence Number = " + passInt("%d",expectedSeq) + " Current Sequence Number = " + passInt("%d",seq);
				sendAlert(pGwyStr,subject, errorMsg);
				setStatus(GAPCHECK_DUPLICATE_SEQ);
				setErrorMessage(errorMsg);
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			if (seq < pModuleStr->pGapTable[i * 2]) {
				subject = pModuleStr->appId;
				subject = subject + ": " + toString(DUPLICATEDMESSAGE);
				errorMsg = pModuleStr->appId;
				errorMsg = errorMsg + ": " + toString(DUPLICATEDMESSAGE) + ". Expected Sequence Number = " + passInt("%d",expectedSeq) + " Current Sequence Number = " + passInt("%d",seq);
				sendAlert(pGwyStr,subject, errorMsg);
				setStatus(GAPCHECK_DUPLICATE_SEQ);
				setErrorMessage(errorMsg);
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			if (pModuleStr->pGapTable[i * 2] == pModuleStr->pGapTable[i * 2 + 1]) {
				for (j = i; j <= numberOfGaps + 1; j++ ) {
					int idx = j + 1;
					pModuleStr->pGapTable[j * 2] = pModuleStr->pGapTable[idx * 2];
					pModuleStr->pGapTable[j * 2 + 1] = pModuleStr->pGapTable[idx * 2 + 1];
				}
				numberOfGaps--;
				lastGapIndex--;
				pModuleStr->pGapTable[0] = numberOfGaps;
				pModuleStr->pGapTable[2] = lastGapIndex;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			if (seq == pModuleStr->pGapTable[i * 2 + 1]) {
				pModuleStr->pGapTable[i * 2 + 1] = seq - 1;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			if (seq == pModuleStr->pGapTable[i * 2]) {
				pModuleStr->pGapTable[i * 2] = seq + 1;
				tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
				return;
			}
			int upSeq = pModuleStr->pGapTable[i * 2 + 1];
			pModuleStr->pGapTable[i * 2 + 1] = seq - 1;
			int idx;
			numberOfGaps++;
			lastGapIndex++;
			for (j = numberOfGaps + 1; j >= i + 1; j--) {
				idx = j - 1;
				pModuleStr->pGapTable[j * 2] = pModuleStr->pGapTable[idx * 2];
				pModuleStr->pGapTable[j * 2 + 1] = pModuleStr->pGapTable[idx * 2 + 1];
			}
			idx = i + 1;
			pModuleStr->pGapTable[idx * 2 + 1] = upSeq;
			pModuleStr->pGapTable[idx * 2] = seq + 1;
			pModuleStr->pGapTable[0] = numberOfGaps;
			pModuleStr->pGapTable[2] = lastGapIndex;
			tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
			return;
		}
		break;
		case 4:
		{
			int tableIndex;
			numberOfGaps = lastGapIndex;
			pModuleStr->pGapTable[(numberOfGaps + 1) * 2 ] = expectedSeq;
			pModuleStr->pGapTable[(numberOfGaps + 1) * 2 + 1] = pModuleStr->maximumSequenceNumber;
			lastGapIndex = 2;

			if (seq > 1) {
				pModuleStr->pGapTable[(lastGapIndex) * 2 ] = 1;
				pModuleStr->pGapTable[(lastGapIndex) * 2 + 1] = seq - 1;
				tableIndex = lastGapIndex + 1;
			}
			else {
				lastGapIndex = 0;
				tableIndex = 2;
			}


			for (i = tableIndex; i <= numberOfGaps + 1; i++) {
				if ((seq + 1) >= pModuleStr->pGapTable[i * 2]) {
					continue;
				}
				break;
			}
			int newNumberGaps = 1;
			if (lastGapIndex == 0) {
				newNumberGaps = 0;
			}
			int n = tableIndex;
			for (j = i; j <= numberOfGaps + 1; j++) {
				pModuleStr->pGapTable[n * 2 + 1] = pModuleStr->pGapTable[j * 2 + 1];
				pModuleStr->pGapTable[n * 2] = pModuleStr->pGapTable[j * 2];
				newNumberGaps++;
				n++;
			}
			numberOfGaps = newNumberGaps;

			pModuleStr->pGapTable[1] = (seq == pModuleStr->maximumSequenceNumber) ? 1: seq + 1;


			pModuleStr->pGapTable[0] = numberOfGaps;
			pModuleStr->pGapTable[2] = lastGapIndex;
			tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
			return;
		}
		break;
	}
	tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
	return;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	setOFACState -- Set OFAC State.
// Parameters:	msg -- Set OFAC state
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void setOFACState(PGWYSTR pGwyStr) {
	char* ofacPt;
	char* pMetaData;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN setOFACState", "started");

	pModuleStr->checkOFAC = false;
	if (pModuleStr->messageFormat == ISTDFORMAT) {
		pMetaData = strstr(pGwyStr->inputMessage,METADATA);
		if (pMetaData != NULL) {
			ofacPt = strstr(pMetaData,OFACIND);
			if (ofacPt[strlen(OFACIND)] == 'Y') {
				pModuleStr->checkOFAC = true;
			}
		}
	}
}

void checkOutSrc(PGWYSTR pGwyStr) {
	char* pt1;
	char* pt;
	char* pBlock2;
	char* pBlock4;
	char* pMetaData;
	char  tmpChar;
	char toAddress[BIC11LEN+1];
	char strBlock4[20000];
	char header[2048];
	int i;
	POUTSRCSTR pOutSrcStr;
	OUTSRCSTR outSrcStr;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN checkOutSrc", "started");
	pModuleStr->handleOutSrc = false;
	if (pModuleStr->messageFormat == ISTDFORMAT) {
		pMetaData = strstr(pGwyStr->inputMessage,METADATA);
		if (pMetaData != NULL) {
			pt = strstr(pMetaData,OUTSRC);
			if (pt != NULL) {

				pt = pt + strlen(OUTSRC);
				pt1 = strstr(pt,"}");
				pt1[0] = '\0';
				strcpy(pModuleStr->ourSrcCode,&(pt[STDOUTSRCCODEPOS]));
				if (!strcmp(pModuleStr->ourSrcCode,"004")) {
					strcpy(pModuleStr->ourSrcCode,"003");
				}
				pt1[0] = '}';
				strcpy(outSrcStr.outSrcCode,pModuleStr->ourSrcCode);
				bool checkOutSrcTable = true;
				if (pModuleStr->numberOfSupportOutSrc > 0) {
					bool findOutSrc = false;
					for (i = 0; i < pModuleStr->numberOfSupportOutSrc; i++) {
						if (!strcmp(pModuleStr->ourSrcCode, (pModuleStr->pSupportOutSrcStr[i]).outSrcCode)) {
							findOutSrc = true;
							break;
						}
					}
					if (!findOutSrc) {
						checkOutSrcTable = false;
						strcpy(pModuleStr->errMsg,OUTSRCERRCODE);
						strcat(pModuleStr->errMsg,pModuleStr->ourSrcCode);
						strcat(pModuleStr->errMsg,"}");
						pModuleStr->ourSrcCode[0] = '\0';
						pModuleStr->handleOutSrc = false;
					}
				}
				if (checkOutSrcTable) {
					pOutSrcStr = (POUTSRCSTR) bsearch (&outSrcStr,
													pModuleStr->pOutSrcStr,
													pModuleStr->numberOfOutSrc,
													sizeof (OUTSRCSTR),
													outSrcComparator);

					if (pOutSrcStr != NULL){
						pModuleStr->handleOutSrc = true;
						pBlock2 = strstr(pGwyStr->inputMessage,"{2:");
						strncpy(toAddress,&pBlock2[B2ILTPOS],BIC8LEN);
						toAddress[BIC8LEN] = '\0';
						strncat(toAddress,&pBlock2[B2ILTPOS + BIC8LEN + 1],BRANCHLEN);
						toAddress[BIC11LEN] = '\0';
						pt = &pBlock2[B2ILTPOS];
						tmpChar = pt[0];
						pt[0] = '\0';
						strcpy(header,pGwyStr->inputMessage);
						pt[0] = tmpChar;
						if (!strcmp(pModuleStr->ourSrcCode,"001")) {
							strcat(header,"IRVTUS3N");
							strcpy(pModuleStr->rcvBic12,pOutSrcStr->outSrcBic);
							strcat(pModuleStr->rcvBic12,"AXXX");
							pModuleStr->handleCIBC = true;
						}
						else {
							strcat(header,pOutSrcStr->outSrcBic);
						}

						strcat(header,"XXXXN}");
						strcat(header,"{3:{113:OBNY}{108:");
						strcat(header,toAddress);
						strcat(header,"}}");
						pBlock4 = strstr(pGwyStr->inputMessage, "{4:");
						strcpy(strBlock4,pBlock4);
						strcpy(pGwyStr->inputMessage,header);
						strcat(pGwyStr->inputMessage,strBlock4);
						tracing(TRACE_LEVEL_1, "APPISN checkOutSrc", "ended");
						return;
					}
					else {
						strcpy(pModuleStr->errMsg,OUTSRCERRCODE);
						strcat(pModuleStr->errMsg,pModuleStr->ourSrcCode);
						strcat(pModuleStr->errMsg,"}");
						pModuleStr->ourSrcCode[0] = '\0';
						pModuleStr->handleOutSrc = false;
					}
				}
			}
			else {
				pModuleStr->ourSrcCode[0] = '\0';
			}
		}
	}
	else {
		char outSrcInd[SENDINGBANKLEN + 1];
		strncpy(outSrcInd,&(pGwyStr->inputMessage[SENDINGBANKPOS]),SENDINGBANKLEN);
		outSrcInd[SENDINGBANKLEN] = '\0';
		if (!strncmp(outSrcInd,"OUT",3)) {
			strncpy(outSrcStr.outSrcCode,&(pGwyStr->inputMessage[OUTSRCCODEPOS]),OUTSRCCODELEN);
			outSrcStr.outSrcCode[OUTSRCCODELEN] = '\0';
			strcpy(pModuleStr->ourSrcCode,outSrcStr.outSrcCode);
			bool checkOutSrcTable = true;
			if (pModuleStr->numberOfSupportOutSrc > 0) {
				bool findOutSrc = false;
				for (i = 0; i < pModuleStr->numberOfSupportOutSrc; i++) {
					if (!strcmp(pModuleStr->ourSrcCode, (pModuleStr->pSupportOutSrcStr[i]).outSrcCode)) {
						findOutSrc = true;
						break;
					}
				}
				if (!findOutSrc) {
					checkOutSrcTable = false;
					strcpy(pModuleStr->errMsg,OUTSRCERRCODE);
					strcat(pModuleStr->errMsg,pModuleStr->ourSrcCode);
					strcat(pModuleStr->errMsg,"}");
					pModuleStr->ourSrcCode[0] = '\0';
					pModuleStr->handleOutSrc = false;
				}
			}
			if (checkOutSrcTable) {
				pOutSrcStr = (POUTSRCSTR) bsearch (&outSrcStr,
												pModuleStr->pOutSrcStr,
												pModuleStr->numberOfOutSrc,
												sizeof (OUTSRCSTR),
												outSrcComparator);

				if (pOutSrcStr != NULL){
					strcpy(pModuleStr->ourSrcCode,outSrcStr.outSrcCode);
					strcpy(pModuleStr->outSrcBic,pOutSrcStr->outSrcBic);
					pModuleStr->handleOutSrc = true;
				}
				else {
					strcpy(pModuleStr->errMsg,OUTSRCERRCODE);
					strcat(pModuleStr->errMsg,pModuleStr->ourSrcCode);
					strcat(pModuleStr->errMsg,"}");
					pModuleStr->ourSrcCode[0] = '\0';
					pModuleStr->handleOutSrc = false;
				}
			}
		}
		else {
			pModuleStr->ourSrcCode[0] = '\0';
			pModuleStr->handleOutSrc = false;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN checkOutSrc", "ended");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	setNameKeyParameters -- Set name key prameters.
// Parameters:	pGwyStr -- Global pointer
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void setNameKeyParameters(PGWYSTR pGwyStr) {
	char* pt;
	char* pt1;
	char* pBlock2;
	char* pBlock4;
	char* pMetaData;
	char  tmpChar;
	char toAddress[BIC11LEN+1];
	char strBlock4[20000];
	char header[2048];
	POUTSRCSTR pOutSrcStr;
	OUTSRCSTR outSrcStr;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN setNameKeyParameters", "started");
	if (!pModuleStr->handleOutSrc) {
		pBlock2 = strstr(pGwyStr->inputMessage,"{2:");
		strncpy(pModuleStr->mtType,&(pBlock2[B2IMTPOS]),MTTYPELEN);
		strncpy(pModuleStr->rcvBic12,&(pBlock2[B2ILTPOS]),BIC12LEN);
		pModuleStr->rcvBic12[BIC12LEN] = '\0';
		pModuleStr->mtType[MTTYPELEN] = '\0';
		pMetaData = strstr(pGwyStr->inputMessage,METADATA);
		if (pMetaData != NULL) {
			pt = strstr(pMetaData,MNAMEKEY);
			if (pt != NULL) {
				pt = pt + strlen(MNAMEKEY);
				pt1 = strstr(pt,"}");
				pt1[0] = '\0';
				strcpy(pModuleStr->nameKey,pt);
				pt1[0] = '}';
			}
			else {
				pModuleStr->nameKey[0] = '\0';
			}
			pt = strstr(pMetaData,MASNPREFIX);
			if (pt != NULL) {
				pt = pt + strlen(MASNPREFIX);
				pt1 = strstr(pt,"}");
				pt1[0] = '\0';
				strcpy(pModuleStr->trnPrefix,pt);
				pt1[0] = '}';
			}
			else {
				pModuleStr->trnPrefix[0] = '\0';
			}
			pt = strstr(pMetaData,CID);
			if (pt != NULL) {
				pt = pt + strlen(CID);
				pt1 = strstr(pt,"}");
				pt1[0] = '\0';
				strcpy(pModuleStr->cid,pt);
				pt1[0] = '}';
			}
			else {
				pModuleStr->cid[0] = '\0';
			}
			pt = strstr(pMetaData,CIFLOOKUP);
			if (pt != NULL) {
				pt = pt + strlen(CIFLOOKUP);
				if (pt[0] == 'Y') {
					pModuleStr->cifLookup = true;
					pModuleStr->rcvBic12[0] = '\0';
				}
				else {
					pModuleStr->cifLookup = false;
				}
			}
			else {
				pModuleStr->cifLookup = false;
			}
		}
		if ((pModuleStr->nameKey[0] == '\0') && (pModuleStr->cid[0] != '\0')) {
			getCIFInfo(pGwyStr, "CID", pModuleStr->cid);
		}
		else if ((pModuleStr->nameKey[0] != '\0') && (pModuleStr->rcvBic12[0] == '\0')) {
			getCIFInfo(pGwyStr, "NAMEKEY", pModuleStr->nameKey);
		}
	}
	else {
		pModuleStr->cifLookup = false;
		pModuleStr->cid[0] = '\0';
		pModuleStr->trnPrefix[0] = '\0';
		pModuleStr->nameKey[0] = '\0';
	}
	tracing(TRACE_LEVEL_1, "APPISN setNameKeyParameters", "ended");
	return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	getCorrelationData -- Get Correlation Data.
// Parameters:	msg -- The message contains the correlation data.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void getCorrelationData(PGWYSTR pGwyStr, char* msg) {
	char* corrStartPt = NULL;
	char* pMetaData;
	char* corrEndPt = NULL;
	char tmpChar;
	char priority;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getCorrelationData", "started");

	reset();
	if (pModuleStr->messageFormat == ISTDFORMAT) {
		pMetaData = strstr(msg,METADATA);
		if (pMetaData != NULL) {
			corrStartPt = strstr(pMetaData,CORRID);
			if (corrStartPt != NULL) {
				corrStartPt += strlen(CORRID);
				corrEndPt = strstr(corrStartPt,"}");
				if (corrEndPt != NULL) {
					corrEndPt[0] = '\0';
					strcpy(pModuleStr->correlationData,corrStartPt);
					corrEndPt[0] = '}';

				}
				else {
					setStatus(INVALID_DATA_FORMAT);
					setErrorMessage("APPISN: Invalid data format");
					return;
				}
			}
			else {
				setStatus(INVALID_DATA_FORMAT);
				setErrorMessage("APPISN: Invalid data format");
				return;
			}
		}
		else {
			setStatus(INVALID_DATA_FORMAT);
			setErrorMessage("APPISN: Invalid data format");
			return;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN getCorrelationData", "ended");
}

int findPriority(PGWYSTR pGwyStr, char* mtType) {
	bool found = true;
	int i;
	int j;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "SWFAPPISN findPriority", "started");

	for (i = 0; i < pModuleStr->numberOfPriorityDef; i++) {
		found = true;
		for (j = 0; j < MTTYPE_LEN; j++) {
			if ((pModuleStr->pPriorityStr[i]).mtType[j] == 'X') {
				continue;
			}
			else if (mtType[j] == (pModuleStr->pPriorityStr[i]).mtType[j]) {
				continue;
			}
			else {
				found = false;
				break;
			}
		}
		if (found) {
			return (pModuleStr->pPriorityStr[i]).priority;
		}
	}
	return PRIORITYLOW;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	getPriority -- Get Priority.
// Parameters:	lTerm -- The Logical Terminal.
//              mtType -- The message type.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void getPriority(PGWYSTR pGwyStr, char* lTerm, char* mtType, bool ibr, char cPriority) {
	char* priorityStartPt = NULL;
	char* priorityEndPt = NULL;
	char tmpChar;
	int priority;
	PISNLTERMSTR pIsnLTermStr = NULL;
	ISNLTERMSTR isnLTermStr;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "SWFAPPISN getPriority", "started");

	reset();

	strcpy(isnLTermStr.lTerm,lTerm);
	pIsnLTermStr = (PISNLTERMSTR) bsearch (&isnLTermStr,
						pModuleStr->pIsnLTermStr,
						pModuleStr->numberOfLTerms,
						sizeof (ISNLTERMSTR),
						lTermComparator);

	if (pIsnLTermStr != NULL) {
		if (ibr) {
			if (cPriority == 'U') {
				strcpy(pModuleStr->src,pIsnLTermStr->ibrHSrc);
				strcpy(pModuleStr->priority,"I");
			}
			else {
				priority = findPriority(pGwyStr, mtType);
				if (priority == PRIORITYHIGH) {
					strcpy(pModuleStr->src,pIsnLTermStr->ibrHSrc);
					strcpy(pModuleStr->priority,"I");
				}
				else if (priority == PRIORITYMEDIUM) {
					strcpy(pModuleStr->src,pIsnLTermStr->ibrMSrc);
					strcpy(pModuleStr->priority,"I");
				}
				else if (priority == PRIORITYLOW) {
					strcpy(pModuleStr->src,pIsnLTermStr->ibrSrc);
					strcpy(pModuleStr->priority,"I");
				}
			}
		}
		else {
			if (cPriority == 'U') {
				strcpy(pModuleStr->src,pIsnLTermStr->highSrc);
				strcpy(pModuleStr->priority,"H");
			}
			else {
				priority = findPriority(pGwyStr, mtType);
				if (priority == PRIORITYHIGH) {
					strcpy(pModuleStr->src,pIsnLTermStr->highSrc);
					strcpy(pModuleStr->priority,"H");
				}
				else if (priority == PRIORITYMEDIUM) {
					strcpy(pModuleStr->src,pIsnLTermStr->mediumSrc);
					strcpy(pModuleStr->priority,"M");
				}
				else if (priority == PRIORITYLOW) {
					strcpy(pModuleStr->src,pIsnLTermStr->lowSrc);
					strcpy(pModuleStr->priority,"L");
				}
			}
		}
	}
	else {
		strcpy(pModuleStr->src,"ERR");
		strcpy(pModuleStr->priority,"L");
		strcpy(pModuleStr->errMsg,INVALIDLT);
		//strcpy(pModuleStr->errCode,INVALIDLTERRCODE);
	}
	tracing(TRACE_LEVEL_1, "SWFAPPISN getPriority", "ended");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	getPriority -- Get Priority.
// Parameters:	msg -- The message contains priority.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

/*void getPriority(PGWYSTR pGwyStr, char* msg) {
	char* priorityStartPt = NULL;
	char* priorityEndPt = NULL;
	char tmpChar;
	char priority[32];

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getPriority", "started");

	if (pModuleStr->applicationHost == MSGRTR) {
		tracing(TRACE_LEVEL_1, "APPISN getPriority", "PRIORITY_DATA = " + toString(PRIORITY_DATA));
		priorityStartPt=strstr(msg,PRIORITY_DATA);
		if (priorityStartPt != NULL) {
			tracing(TRACE_LEVEL_1, "APPISN getPriority", "priorityStartPt != NULL");
			priorityStartPt += strlen(PRIORITY_DATA);
			tracing(TRACE_LEVEL_1, "APPISN getPriority", "priorityStartPt = " + toString(priorityStartPt));
			priorityEndPt = NULL;
			priorityEndPt=strstr(priorityStartPt,"\r\n");
			if (priorityEndPt != NULL) {
				tracing(TRACE_LEVEL_1, "APPISN getPriority", "priorityEndPt != NULL priorityEndPt  - priorityStartPt = " + passInt("%d",priorityEndPt - priorityStartPt));
				tmpChar = priorityEndPt[0];
				priorityEndPt[0] = '\0';
				strcpy(priority,priorityStartPt);
				priorityEndPt[0] = tmpChar;
				tracing(TRACE_LEVEL_1, "APPISN getPriority", "priority = " + toString(priority));
				if (!strcmp(priority,HIGH)) {
					strcpy(pModuleStr->src,pModuleStr->highSrc);
					strcpy(pModuleStr->priority,"H");
				}
				else if (!strcmp(priority,MEDIUM)) {
					strcpy(pModuleStr->src,pModuleStr->mediumSrc);
					strcpy(pModuleStr->priority,"M");
				}
				else if (!strcmp(priority,LOW)) {
					strcpy(pModuleStr->src,pModuleStr->lowSrc);
					strcpy(pModuleStr->priority,"L");
				}
				else {
					strcpy(pModuleStr->src,pModuleStr->lowSrc);
					strcpy(pModuleStr->priority,"L");
				}
			}
			else {
				strcpy(pModuleStr->src,pModuleStr->lowSrc);
				strcpy(pModuleStr->priority,"L");
			}
		}
		else {
			strcpy(pModuleStr->src,pModuleStr->lowSrc);
			strcpy(pModuleStr->priority,"L");
		}
	}

	tracing(TRACE_LEVEL_1, "APPISN getPriority", "ended");
}
*/
char* findEndBlock4(char* pBlock4) {
	char* pBlock4End = NULL;
	char *pt, *pLeft, *pLeft1, *pRight, *pLeft2;
	int nLeft;
	char tmpChar;

	nLeft = 1;
	pLeft = pBlock4;
	while (1) {
		pt = &pLeft[1];
		pLeft1 = strstr(pt, "{");

		if (pLeft1 != NULL) {
			tmpChar = pLeft1[0];
			pLeft1[0] = '\0';
			pLeft2 = pLeft;
			while (1) {
				pRight = strstr(pLeft2+ 1, "}");
				if (pRight != NULL) {
					nLeft--;
					if (nLeft == 0) {
						break;
					}
					else {
						pLeft2 = pRight;
						continue;
					}
				}
				else {
					break;
				}
			}
			pLeft1[0] = tmpChar;
			if (nLeft == 0) {
				pBlock4End = pRight + 1;
				break;
			}
		}
		else {
			pLeft2 = pLeft;
			while (1) {
				pRight = strstr(pLeft2 + 1, "}");
				if (pRight != NULL) {
					nLeft--;
					if (nLeft == 0) {
						break;
					}
					else {
						pLeft2 = pRight;
						continue;
					}
				}
				else {
					break;
				}
			}
			if (nLeft == 0) {
				pBlock4End = pRight + 1;
				break;
			}
		}
		if (nLeft != 0) {
			pLeft = pLeft1;
			nLeft++;
		}
	}
	return pBlock4End;
}

void fetchSeqNum(PGWYSTR pGwyStr) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	char sSeqNum[64];

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN fetchSeqNum", "started");
	string params = "";

	int retValue;
	int reConnectCount = 0;
	bool afterReconnect = false;

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;

	while (1) {
		if (afterReconnect) {
			reset();
			registerTFMSvc(pGwyStr);
			if (retStatus() != SUCCESS){
				return;
			}
		}

		retValue = pSvcClient->svcClientReqSvc(pModuleStr->svcGapCheckHandler, FETCHOP, params, svcClientRequest, svcServerResponse,MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN fetchSeqNum", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN fetchSeqNum", "ended");
				return;
			}
			else {
				afterReconnect =true;
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				if (!strncmp(pt,FMTSUCCESS,strlen(FMTSUCCESS))) {
					pt = &pt[strlen(FMTSUCCESS)];
					endPt = strstr(pt,SVCRSPEND);
					if (endPt != NULL) {
						endPt[0] = '\0';
						strcpy(sSeqNum,pt);
						pModuleStr->expectedSeq = atoi(sSeqNum);
					}
					else {
						setStatus(SVCREMOTE_FAIL_READ);
						setErrorMessage("Invalid return format from Svc Server");
						tracing(TRACE_LEVEL_1, "APPISN fetchSeqNum", "ended");
						return;
					}
				}
				else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN fetchSeqNum", "ended");
					return;
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN fetchSeqNum", "ended");
				return;
			}
			break;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN fetchSeqNum", "ended");
}

void saveSeqNum(PGWYSTR pGwyStr) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	char sSeqNum[64];

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN saveSeqNum", "started");
	string params = "";

	int retValue;
	int reConnectCount = 0;
	bool afterReconnect = false;

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;

	sprintf(sSeqNum,"%d",pModuleStr->expectedSeq);
	params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(sSeqNum) + toString(PARAMEND) + toString(PARAMSEND);

	while (1) {
		if (afterReconnect) {
			reset();
			registerTFMSvc(pGwyStr);
			if (retStatus() != SUCCESS){
				return;
			}
		}

		retValue = pSvcClient->svcClientReqSvc(pModuleStr->svcGapCheckHandler, SAVEOP, params, svcClientRequest, svcServerResponse,MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN saveSeqNum", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN saveSeqNum", "ended");
				return;
			}
			else {
				afterReconnect =true;
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				if (!strncmp(pt,FMTSUCCESS,strlen(FMTSUCCESS))) {
				}
				else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN saveSeqNum", "ended");
					return;
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN saveSeqNum", "ended");
				return;
			}
			break;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN saveSeqNum", "ended");
}

void checkSeqNum(PGWYSTR pGwyStr, int iSeqNum) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	char sSeqNum[64];

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN checkSeqNum", "started");
	string params = "";

	int retValue;
	int reConnectCount = 0;
	bool afterReconnect = false;

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;
	sprintf(sSeqNum,"%d",iSeqNum);
	params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(sSeqNum) + toString(PARAMEND) + toString(PARAMSEND);

	while (1) {
		if (afterReconnect) {
			reset();
			registerTFMSvc(pGwyStr);
			if (retStatus() != SUCCESS){
				return;
			}
		}

		retValue = pSvcClient->svcClientReqSvc(pModuleStr->svcGapCheckHandler, CHECKOP, params, svcClientRequest, svcServerResponse,MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN checkSeqNum", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN checkSeqNum", "ended");
				return;
			}
			else {
				afterReconnect =true;
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			char* pt1;
			int i;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				if (!strncmp(pt,FMTSUCCESS,strlen(FMTSUCCESS))) {
					pt = &pt[strlen(FMTSUCCESS)];
					endPt = strstr(pt,SVCRSPEND);
					if (endPt != NULL) {
						endPt[0] = '\0';
						strcpy(sSeqNum,pt);
						if (!strcmp(sSeqNum,STOP)) {
							pModuleStr->bContinue = false;
						}
						else {
							endPt = strstr(sSeqNum,":");
							if (endPt != NULL) {
								endPt[0] = '\0';
								for (i = 0; i < strlen(sSeqNum); i++) {
									pt1 = &(sSeqNum[i]);
									if (isblank(pt1[0])) {
										pt1[0] = '\0';
										break;
									}
								}
								pModuleStr->expectedSeq = atoi(sSeqNum);
								pModuleStr->bContinue = true;
							}
						}
					}
					else {
						setStatus(SVCREMOTE_FAIL_READ);
						setErrorMessage("Invalid return format from Svc Server");
						tracing(TRACE_LEVEL_1, "APPISN checkSeqNum", "ended");
						return;
					}
				}
				else {
					setStatus(SVCREMOTE_FAIL_READ);
					setErrorMessage(svcServerResponse);
					tracing(TRACE_LEVEL_1, "APPISN checkSeqNum", "ended");
					return;
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN checkSeqNum", "ended");
				return;
			}
			break;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN checkSeqNum", "ended");
}

void createGapTable(PGWYSTR pGwyStr) {
	char* pt;
	char sGapData[18];
	int i = 0;
	int m;
	int iGapCheck;

	getBusinessModuleVars(PBMDEF);

	tracing(TRACE_LEVEL_1, "APPISN createGapTable", "started");
	if (pModuleStr->pGapTableStr[0] == '\0') {
		pModuleStr->pGapTable[0] = 0;
		pModuleStr->pGapTable[1] = 1;
		pModuleStr->pGapTable[2] = 0;
		pModuleStr->pGapTable[3] = 0;
	}
	else {
		pt = pModuleStr->pGapTableStr;
		strncpy(sGapData,pt,10);
		sGapData[10] = '\0';

		sscanf(sGapData,"%05X%05X",&(pModuleStr->pGapTable[0]),&(pModuleStr->pGapTable[1]));
		pt = pt + 10;
		strncpy(sGapData,pt,10);
		sGapData[10] = '\0';

		sscanf(sGapData,"%05X%05X",&(pModuleStr->pGapTable[2]),&(pModuleStr->pGapTable[3]));

		for (i = 2; i <= pModuleStr->pGapTable[0] + 1; i++) {
			pt = pt + 10;
			strncpy(sGapData,pt,10);
			sGapData[10] = '\0';
			sscanf(sGapData,"%05X%05X",&(pModuleStr->pGapTable[i*2]),&(pModuleStr->pGapTable[i*2 +1]));
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN createGapTable", "ended");
}

void putGapTable(PGWYSTR pGwyStr) {
	char* pt;
	char sGapData[18];
	int i = 0;
	int m;
	int iGapCheck;

	getBusinessModuleVars(PBMDEF);

	tracing(TRACE_LEVEL_1, "APPISN putGapTable", "started");

	sprintf(pModuleStr->pGapTableStr,"%05X%05X",pModuleStr->pGapTable[0],pModuleStr->pGapTable[1]);
	pModuleStr->pGapTable[3] = 0;
	sprintf(sGapData,"%05X%05X",pModuleStr->pGapTable[2],pModuleStr->pGapTable[3]);
	strcat(pModuleStr->pGapTableStr,sGapData);

	for (i = 2; i <= (pModuleStr->pGapTable[0] + 1); i++) {
		sprintf(sGapData,"%05X%05X",pModuleStr->pGapTable[i*2],pModuleStr->pGapTable[i*2 +1]);
		strcat(pModuleStr->pGapTableStr,sGapData);
	}
	FILE* gapTableFt = fopen(pModuleStr->gapTableFileName,"w+");
	fprintf(gapTableFt,"%s",pModuleStr->pGapTableStr);
	fclose(gapTableFt);
	tracing(TRACE_LEVEL_1, "APPISN putGapTable", "ended");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	bmInitialize -- Initialize the business tranformation module.
// Parameters:	pBmInit -- The structure contains the point to the trace and the business module
//						   xml configuration segment.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void bmInitialize(PGWINIT pGwyInit) {
	string fniHomeDir;
	CEnv env;
	CXml xml;

	PISNBIC8STR pIsnBIC8Str;
	string bic8Docs[MAX_BIC8S];
	string lTermDocs[MAX_BIC8S];
	string priorityDocs[MAX_PRIORITY];
	string bic8Name;
	string bic8ListDoc;
	string lTermListDoc;
	string priorityListDoc;
	string xmlCfgName;
	string xmlDoc;
	string ibrSeqFilePath;
	FILE* fp;
	int i;
	int j;
	int n;
	PISNBIC8STR pIsnBIC8StrOwn;
	string xmlValue;
	string mtType;
	char bic8[BIC8LEN + 1];
	PMTLTERMSTR pMTLTermStr = NULL;
	string appDefListDoc;

	string appDocs[MAX_APPS];

	string gatewayName;
	getPGWStr();

	tracing(TRACE_LEVEL_1, "APPISN bmInitialize", "started");

	createBusinessModuleVars(BMDEF, PBMDEF);
	getBusinessModuleVars(PBMDEF);
	env.getEnv();
	if (env.getStatus() != SUCCESS){
        setStatus(env.getStatus());
        setErrorMessage(env.getErrorMessage());
		tracing(TRACE_LEVEL_1, "APPISN bmInitialize", "ended");
		return;
	}
	else {
		fniHomeDir = env.getFniHome();
	}
	reset();
	setup(pGwyInit);

	gatewayName = (pGwyInit->pGwyStr)->gatewayName;

	if (pModuleStr->processGapCheck != INOGAPCHECK) {
		pModuleStr->pGapTable = (int*) malloc(sizeof(int) * (pModuleStr->maximumSequenceNumber + 10) * 2);
		pModuleStr->pGapTable[0] = 0;
		pModuleStr->pGapTable[1] = 0;
	}

	pModuleStr->pMsgHeaderStr = (PMSGHEADERSTR)malloc(sizeof(MSGHEADERSTR));

	xmlCfgName = env.getFniHome() + "/prod/cfg/fniMasterConfig.xml";
	xmlDoc = xml.readXmlFromFile(xmlCfgName);
	if (xml.getStatus() != SUCCESS) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	bic8ListDoc = xml.getNode(xmlDoc,IBRBIC8LIST);
	if (xml.getStatus() != SUCCESS) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	pModuleStr->numberOfIsnBic8s = xml.getNodes(bic8ListDoc,IBRBIC8NAME,bic8Docs,MAX_BIC8S);
	if (xml.getStatus() != SUCCESS) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	pModuleStr->pIsnBIC8Str = (PISNBIC8STR) malloc(sizeof(ISNBIC8STR) * pModuleStr->numberOfIsnBic8s);
	for (i = 0; i < pModuleStr->numberOfIsnBic8s; i++) {
		bic8Name = xml.getValue(bic8Docs[i],IBRBIC8NAME);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		strcpy(pModuleStr->pIsnBIC8Str[i].bic8Name,bic8Name.c_str());
	}
	qsort (pModuleStr->pIsnBIC8Str, pModuleStr->numberOfIsnBic8s, sizeof(ISNBIC8STR), bic8Comparator);



	if (pModuleStr->supportOutSrc) {
		string outSrcListDoc;
		string outSrcDocs[MAX_OUTSRC];
		string outSrcCode;
		string outSrcBic;

		outSrcListDoc = xml.getNode(xmlDoc,OUTSRCDEFLIST);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->numberOfOutSrc = xml.getNodes(outSrcListDoc,OUTSRCDEF,outSrcDocs,MAX_OUTSRC);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pOutSrcStr = (POUTSRCSTR) malloc(sizeof(OUTSRCSTR) * pModuleStr->numberOfOutSrc);
		for (i = 0; i < pModuleStr->numberOfOutSrc; i++) {
			outSrcCode = xml.getValue(outSrcDocs[i],OUTSRCCODE);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			strcpy(pModuleStr->pOutSrcStr[i].outSrcCode,outSrcCode.c_str());

			outSrcBic = xml.getValue(outSrcDocs[i],OUTSRCRCVBIC);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			strcpy(pModuleStr->pOutSrcStr[i].outSrcBic,outSrcBic.c_str());
		}
		qsort (pModuleStr->pOutSrcStr, pModuleStr->numberOfOutSrc, sizeof(OUTSRCSTR), outSrcComparator);
	}



	appDefListDoc = xml.getNode(xmlDoc,APPDEFLIST);
	if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}
	if (xml.getStatus() != NODE_NOT_EXISTS) {
		int numberofApps = xml.getNodes(appDefListDoc,APPDEF,appDocs,MAX_APPS);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		for (int i = 0; i < numberofApps; i++) {
			xmlValue = xml.getValue(appDocs[i],APPNAME);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			/*
			if (strlen(xmlValue.c_str()) != APPIDLEN) {
				setStatus(INVALID_VALUE);
				setErrorMessage("APPISN bmInitialize -- Invalid value " + xmlValue + " for tag " + toString(APPNAME));
				return;
			}

			*/


			tracing(TRACE_LEVEL_4, "APPISN bmInitialize", "APPNAME = " + xmlValue);
			if (((pModuleStr->mainAppId[0] != '\0') && (!strcmp(xmlValue.c_str(),pModuleStr->mainAppId))) || (!strcmp(xmlValue.c_str(),pModuleStr->appId))) {
//			if (!strcmp(xmlValue.c_str(),pModuleStr->appId)) {
				string appLTermListDoc = xml.getNode(appDocs[i],APPLTERMLIST);
				if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}

				if (xml.getStatus() != NODE_NOT_EXISTS) {
					string appLTermDocs[MAX_APPLTERMS];
					int numberofAppLTerms;
					numberofAppLTerms = xml.getNodes(appLTermListDoc,APPLTERM,appLTermDocs,MAX_APPLTERMS);
					pModuleStr->pAppLTermStr = (PSELLTERMSTR) malloc(sizeof(SELLTERMSTR) * numberofAppLTerms);

					pModuleStr->numberofAppLTerms = 0;
					for (int j = 0; j < numberofAppLTerms; j++) {
						xmlValue = xml.getValue(appLTermDocs[j],APPLTERM);

						if (xml.getStatus() != SUCCESS) {
							setStatus(xml.getStatus());
							setErrorMessage(xml.getErrorMessage());
							return;
						}
						if (strlen(xmlValue.c_str()) != LTERMLEN) {
							setStatus(INVALID_VALUE);
							setErrorMessage("APPISN setup -- Invalid value " + xmlValue + " for tag " + toString(APPLTERM));
							return;
						}
						bool found = false;
						int n;

						for (n = 0; n < pModuleStr->numberofAppLTerms; n++) {
							if (!strncmp(pModuleStr->pAppLTermStr[n].bic8Name,xmlValue.c_str(),BIC8LEN)) {
								found = true;
								break;
							}
						}
						if (found) {
							int m = pModuleStr->pAppLTermStr[n].pMTLTermStr[0].numberOfLTerms;
							strcpy(pModuleStr->pAppLTermStr[n].pMTLTermStr[0].lTermStr[m].lTerm,xmlValue.c_str());
							pModuleStr->pAppLTermStr[n].pMTLTermStr[0].numberOfLTerms++;
						}
						else{
							strncpy(pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].bic8Name,xmlValue.c_str(),BIC8LEN);
							pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].bic8Name[BIC8LEN] = '\0';
							pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].numberOfMTLTs = 1;
							pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].pMTLTermStr = (PMTLTERMSTR) malloc(sizeof(MTLTERMSTR));
							strcpy(pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].pMTLTermStr[0].mtType,"XXX");
							pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].pMTLTermStr[0].currentLTIdx = 0;
							strcpy(pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].pMTLTermStr[0].lTermStr[0].lTerm,xmlValue.c_str());

							pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].pMTLTermStr[0].numberOfLTerms = 1;
							pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].pMTLTermStr[0].destBIC11[0] = '\0';
							pModuleStr->pAppLTermStr[pModuleStr->numberofAppLTerms].pMTLTermStr[0].lastMtType[0] = '\0';
							pModuleStr->numberofAppLTerms++;
						}
					}
					qsort (pModuleStr->pAppLTermStr, pModuleStr->numberofAppLTerms, sizeof(SELLTERMSTR), selLTermComparator);
				}
			}
		}
	}
	else {
		tracing(TRACE_LEVEL_4, "APPISN setup", "APPDEFLIST: TAG_NOT_EXISTS");
		reset();
	}

	/*pIsnBIC8StrOwn = (PISNBIC8STR) bsearch (&(pModuleStr->gateWayBic8),
							pModuleStr->pIsnBIC8Str,
							pModuleStr->numberOfIsnBic8s,
							sizeof (ISNBIC8STR),
							bic8Comparator);

	if (pIsnBIC8StrOwn != NULL) {
		pModuleStr->ibrForSenderBic = true;
	}
	else {
		pModuleStr->ibrForSenderBic = false;
	}
	*/
	tracing(TRACE_LEVEL_4, "SWFAPPISN bmInitialize", "Before getNode LTERMDEFLIST");

	lTermListDoc = xml.getNode(xmlDoc,LTERMDEFLIST);
	if (xml.getStatus() != SUCCESS) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}

	pModuleStr->numberOfLTerms = xml.getNodes(lTermListDoc,LTERMDEF,lTermDocs,MAX_BIC8S);

	tracing(TRACE_LEVEL_4, "SWFAPPISN bmInitialize", "numberOfLTerms: " + passInt("%d",pModuleStr->numberOfLTerms));

	if (xml.getStatus() != SUCCESS) {
		setStatus(xml.getStatus());
		setErrorMessage(xml.getErrorMessage());
		return;
	}

	pModuleStr->pIsnLTermStr = (PISNLTERMSTR) malloc(sizeof(ISNLTERMSTR) * pModuleStr->numberOfLTerms);


	pModuleStr->pSelLTermStr = (PSELLTERMSTR) malloc(sizeof(SELLTERMSTR) * pModuleStr->numberOfLTerms);
	pModuleStr->numberOfBic8 = 0;

	for (i = 0; i < pModuleStr->numberOfLTerms; i++) {
		xmlValue = xml.getValue(lTermDocs[i],LTERMNAME);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		strcpy(pModuleStr->pIsnLTermStr[i].lTerm,xmlValue.c_str());

		mtType = xml.getValue(lTermDocs[i],MTTYPE);


		strncpy(bic8,pModuleStr->pIsnLTermStr[i].lTerm,BIC8LEN);
		bic8[BIC8LEN] = '\0';
		bool found = false;
		int bic8Idx = 0;
		for (j = 0; j < pModuleStr->numberOfBic8; j++) {
			if (!strcmp(bic8,pModuleStr->pSelLTermStr[j].bic8Name)) {
				found = true;
				bic8Idx = j;
				break;
			}
		}
		if (!found) {
			strcpy(pModuleStr->pSelLTermStr[pModuleStr->numberOfBic8].bic8Name,bic8);
			pModuleStr->pSelLTermStr[pModuleStr->numberOfBic8].pMTLTermStr = (PMTLTERMSTR) malloc(sizeof(MTLTERMSTR) * MAXMTLTERMLIST);

			(pModuleStr->pSelLTermStr[pModuleStr->numberOfBic8].pMTLTermStr) -> destBIC11[0] = '\0';

			pModuleStr->pSelLTermStr[pModuleStr->numberOfBic8].numberOfMTLTs = 0;
			int n = pModuleStr->pSelLTermStr[pModuleStr->numberOfBic8].numberOfMTLTs;
			pMTLTermStr = &(pModuleStr->pSelLTermStr[pModuleStr->numberOfBic8].pMTLTermStr[n]);

			strcpy(pMTLTermStr->mtType,mtType.c_str());
			pMTLTermStr->numberOfLTerms = 0;
			strcpy(pMTLTermStr->lTermStr[pMTLTermStr->numberOfLTerms].lTerm,xmlValue.c_str());
			pMTLTermStr->numberOfLTerms++;
			pModuleStr->pSelLTermStr[pModuleStr->numberOfBic8].numberOfMTLTs++;
			pModuleStr->numberOfBic8++;
		}
		else {
			int mtIdx;
			bool found1 = false;
			for (n = 0; n < pModuleStr->pSelLTermStr[bic8Idx].numberOfMTLTs; n++) {
				pMTLTermStr = &(pModuleStr->pSelLTermStr[bic8Idx].pMTLTermStr[n]);
				if (!strcmp(mtType.c_str(),pMTLTermStr->mtType)) {
					found1 = true;
					mtIdx = n;
					break;
				}
			}
			if (found1) {
				pMTLTermStr = &(pModuleStr->pSelLTermStr[bic8Idx].pMTLTermStr[mtIdx]);
				strcpy(pMTLTermStr->lTermStr[pMTLTermStr->numberOfLTerms].lTerm,xmlValue.c_str());
				pMTLTermStr->numberOfLTerms++;
			}
			else {
				mtIdx = (pModuleStr->pSelLTermStr[bic8Idx]).numberOfMTLTs;
				pMTLTermStr = &(pModuleStr->pSelLTermStr[bic8Idx].pMTLTermStr[mtIdx]);
				strcpy(pMTLTermStr->mtType,mtType.c_str());

				strcpy(pMTLTermStr->lTermStr[0].lTerm,xmlValue.c_str());
				pMTLTermStr->destBIC11[0] = '\0';
				pMTLTermStr->lastMtType[0] = '\0';
				pMTLTermStr->numberOfLTerms = 1;
				pModuleStr->pSelLTermStr[bic8Idx].numberOfMTLTs++;
			}
		}
		xmlValue = xml.getValue(lTermDocs[i],MTSHIGHSOURCE);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		strcpy(pModuleStr->pIsnLTermStr[i].highSrc,xmlValue.c_str());

		xmlValue = xml.getValue(lTermDocs[i],MTSLOWSOURCE);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		strcpy(pModuleStr->pIsnLTermStr[i].lowSrc,xmlValue.c_str());

		xmlValue = xml.getValue(lTermDocs[i],MTSMEDIUMSOURCE);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		strcpy(pModuleStr->pIsnLTermStr[i].mediumSrc,xmlValue.c_str());

		xmlValue = xml.getValue(lTermDocs[i],MTSIBRSOURCE);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		strcpy(pModuleStr->pIsnLTermStr[i].ibrSrc,xmlValue.c_str());

		xmlValue = xml.getValue(lTermDocs[i],MTSIBRHSOURCE);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		strcpy(pModuleStr->pIsnLTermStr[i].ibrHSrc,xmlValue.c_str());

		xmlValue = xml.getValue(lTermDocs[i],MTSIBRMSOURCE);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		strcpy(pModuleStr->pIsnLTermStr[i].ibrMSrc,xmlValue.c_str());
/*		xmlValue = xml.getValue(lTermDocs[i],MTSERRSOURCE);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		*/
		strcpy(pModuleStr->pIsnLTermStr[i].errSrc,DEFAULTERRORCODE);
	}
	qsort (pModuleStr->pIsnLTermStr, pModuleStr->numberOfLTerms, sizeof(ISNLTERMSTR), lTermComparator);
	qsort (pModuleStr->pSelLTermStr, pModuleStr->numberOfBic8, sizeof(SELLTERMSTR), selLTermComparator);

	for (j = 0; j < pModuleStr->numberOfBic8; j++) {
		if (pModuleStr->pSelLTermStr[j].numberOfMTLTs > 1) {
			pMTLTermStr = (pModuleStr->pSelLTermStr[j]).pMTLTermStr;
			qsort (pMTLTermStr, pModuleStr->pSelLTermStr[j].numberOfMTLTs, sizeof(MTLTERMSTR), mtLTermComparator);
		}
	}

	if (pModuleStr->pPriorityStr == NULL) {
		priorityListDoc = xml.getNode(xmlDoc,PRIORITYDEFLIST);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}

		pModuleStr->numberOfPriorityDef = xml.getNodes(priorityListDoc,PRIORITYDEF,priorityDocs,MAX_PRIORITY);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pPriorityStr = (PPRIOITYSTR) malloc(sizeof(PRIORITYSTR) * pModuleStr->numberOfPriorityDef);

		for (i = 0; i < pModuleStr->numberOfPriorityDef; i++) {
			xmlValue = xml.getValue(priorityDocs[i],MTTYPE);
			if (strlen(xmlValue.c_str()) == MTTYPE_LEN) {
				strcpy((pModuleStr->pPriorityStr[i]).mtType,xmlValue.c_str());
			}
			else {
				setStatus(INVALID_VALUE);
				setErrorMessage("SWFAPPISN bmInitialize -- Invalid value " + xmlValue + " for tag " + toString(MTTYPE));
				return;
			}
			xmlValue = xml.getValue(priorityDocs[i],PRIORITY);
			if (!strcmp(xmlValue.c_str(),HIGH)) {
				(pModuleStr->pPriorityStr[i]).priority = PRIORITYHIGH;
			}
			else if (!strcmp(xmlValue.c_str(),MEDIUM)) {
				(pModuleStr->pPriorityStr[i]).priority = PRIORITYMEDIUM;
			}
			else if (!strcmp(xmlValue.c_str(),LOW)) {
				(pModuleStr->pPriorityStr[i]).priority = PRIORITYLOW;
			}
			else {
				setStatus(INVALID_VALUE);
				setErrorMessage("SWFAPPISN bmInitialize -- Invalid value " + xmlValue + " for tag " + toString(PRIORITY));
				return;
			}
		}
	}

	for (i = 0; i < pModuleStr->numberOfBic8; i++) {
		if (pModuleStr->pSelLTermStr[i].numberOfMTLTs > 1) {
			for (j = 0; j < pModuleStr->pSelLTermStr[i].numberOfMTLTs; j++) {
				pMTLTermStr = &((pModuleStr->pSelLTermStr[i]).pMTLTermStr[j]);
			}
		}
	}
/*	if (pModuleStr->ibrSeqFileName[0] != '\0') {
		ibrSeqFilePath = pModuleStr->ibrSeqFileName;
		sprintf(pModuleStr->ibrSeqFileName,"%s/persistent/%s",fniHomeDir.c_str(),ibrSeqFilePath.c_str());
		fp = fopen(pModuleStr->ibrSeqFileName,"r+");
		if (fp != NULL) {
			fscanf(fp,"%d",&(pModuleStr->ibrSeqNumber));
			fclose(fp);
		}
		else {
			pModuleStr->ibrSeqNumber = 0;
		}
	}
	else {
		pModuleStr->ibrSeqNumber = 0;
	}
*/
	if (pModuleStr->convertBic8) {
		reset();
		setProBic8List(pGwyStr);
		if (retStatus() != SUCCESS) {
			return;
		}
	}
	if (pModuleStr->defaultSvcSvr[0] != '\0') {
		string svcServerDoc[MAX_SVCSERVER];
		string svcServerListDoc;

		svcServerListDoc = xml.getNode(xmlDoc,SVCSERVERLIST);
		if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != NODE_NOT_EXISTS)) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		if (xml.getStatus() != NODE_NOT_EXISTS) {
			string svcClientName = gatewayName + "|" + toString(pModuleStr->annualFormat);
			CSvcClient* pSvcClient= new CSvcClient(svcClientName);
			string hostName;
			string sPort;
			string svcSvr;
			int port;
			int numberOfSvcServer = xml.getNodes(svcServerListDoc,SVCSERVERDEF,svcServerDoc,MAX_SVCSERVER);
			tracing(TRACE_LEVEL_1, "APPISN bmInitialize", "numberOfSvcServer =  " + passInt("%d",numberOfSvcServer));
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			for (i = 0; i < numberOfSvcServer; i++) {
				hostName = xml.getValue(svcServerDoc[i],HOSTNAME);
				if (xml.getStatus() != SUCCESS) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}
				sPort = xml.getValue(svcServerDoc[i],PORT);
				if (xml.getStatus() != SUCCESS) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}
				port = atoi(sPort.c_str());
				svcSvr = xml.getValue(svcServerDoc[i],SERVER);
				if (!strcmp(pModuleStr->defaultSvcSvr,(const char*)svcSvr.c_str())) {
				//if (port == pModuleStr->defaultSvcPort) {
					pModuleStr->defaultSvcPort = port;
					pSvcClient->setConnection((char *) hostName.c_str(), port, DEFAULT_CONNECTION);
					if (pSvcClient->getStatus() != SUCCESS) {
						if (!pModuleStr->editCheckBySwift) {
							setStatus(pSvcClient->getStatus());
							setErrorMessage(pSvcClient->getErrorMessage());
							return;
						}
						else {
							pModuleStr->defaultSvcPort = NOSVC;
						}
					}
				}
				else {
					pSvcClient->setConnection((char *) hostName.c_str(), port, BACKUP_CONNECTION);
					if (pSvcClient->getStatus() != SUCCESS) {
						if (!pModuleStr->editCheckBySwift) {
							setStatus(pSvcClient->getStatus());
							setErrorMessage(pSvcClient->getErrorMessage());
							return;
						}
						else {
							pModuleStr->defaultSvcPort = NOSVC;
						}
					}
				}

			}
			pModuleStr->pSvcClient = (void*) pSvcClient;

			pSvcClient->init();
			if (pSvcClient->getStatus() != SUCCESS) {
				if ((pModuleStr->transformInternalFmt) || (pModuleStr->transformSwiftToSwift)) {
					tracing(TRACE_LEVEL_1, "SWFACK bmInitialize", "after pSvcClient->init  fail error message =  " + pSvcClient->getErrorMessage());
					setStatus(pSvcClient->getStatus());
					setErrorMessage(pSvcClient->getErrorMessage());
					return;
				}
				pModuleStr->editSvcFailed = true;
				pModuleStr->processIBR = false;
				tracing(TRACE_LEVEL_1, "SWFACK bmInitialize", "after pSvcClient->init  fail error message =  " + pSvcClient->getErrorMessage());
			}
			else {
				registerSvc(pGwyStr);
				if ((pModuleStr->transformInternalFmt) || (pModuleStr->transformSwiftToSwift)) {
					reset();
					if (pModuleStr->editSvcFailed) {
						tracing(TRACE_LEVEL_1, "SWFACK bmInitialize", "after registerSvc fail error message =  " + pSvcClient->getErrorMessage());
						setStatus(pSvcClient->getStatus());
						setErrorMessage(pSvcClient->getErrorMessage());
						return;
					}
					else {
						registerTFMSvc(pGwyStr);
						if (retStatus() != SUCCESS){
							return;
						}
					}
				}
				if (pModuleStr->processGapCheck != INOGAPCHECK) {
					if (pModuleStr->gapCheckBySvc) {
						registerGapCheckSvc(pGwyStr);
						if (retStatus() != SUCCESS){
							return;
						}
					}
				}
				/* if (pModuleStr->pTrnPrefixStr != NULL) {
						registerGTMAckSvc(pGwyStr);
						if (retStatus() != SUCCESS){
							return;
						}
				}
				*/
			}

			/*if (pSvcClient->getStatus() != SUCCESS) {
				if (!pModuleStr->editCheckBySwift) {
					setStatus(pSvcClient->getStatus());
					setErrorMessage(pSvcClient->getErrorMessage());
					return;
				}
				else {
					pModuleStr->defaultSvcPort = NOSVC;
				}
			}
			*/
		}
		else {
			pModuleStr->defaultSvcPort = NOSVC;
		}
	}

	if (pModuleStr->processGapCheck != INOGAPCHECK) {
		reset();
		if (pModuleStr->gapCheckBySvc) {
			fetchSeqNum(pGwyStr);
			if (retStatus() != SUCCESS) {
				return;
			}
		}
		else {
			string gapTableFileName = xmlCfgName = env.getFniHome() + "/persistent/" + pModuleStr->appId + "_GapTable.txt";

			strcpy(pModuleStr->gapTableFileName,gapTableFileName.c_str());
			pModuleStr->pGapTableStr = (char*) malloc((pModuleStr->maximumSequenceNumber + 20) * 10 *  sizeof(char));

			FILE* gapTableFt = fopen(pModuleStr->gapTableFileName,"r");
			if (gapTableFt == NULL) {
				pModuleStr->pGapTableStr[0] = '\0';
				createGapTable(pGwyStr);
			}
			else {
				fscanf(gapTableFt,"%s",pModuleStr->pGapTableStr);
				fclose(gapTableFt);
				createGapTable(pGwyStr);
			}
		}
	}
	if (pModuleStr->numberOfAlertEmails > 0) {
		string alertEmailFileName = env.getFniHome() + "/prod/log/" + pModuleStr->appId + "_GapErrorMsg.log";
		strcpy(pModuleStr->alertEmailFileName,alertEmailFileName.c_str());
	}

	if (pModuleStr->supportNameKey) {
		string nameKeyListDoc;
		string nameKeyDocs[MAX_NAMEKEYS];
		string nameKey;
		string mtType;
		string nameKeyAsn;
		string customerCode;
		string outputQueue;
		string nameKeyTrn;
		string desApp;
		string rowDefListDoc;

		xmlCfgName = env.getFniHome() + "/prod/cfg/fniNameKeyTable.xml";
		xmlDoc = xml.readXmlFromFile(xmlCfgName);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		nameKeyListDoc = xml.getNode(xmlDoc,NAMEKEYDEFLIST);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->numberOfNameKeys = xml.getNodes(nameKeyListDoc,NAMEKEYDEF,nameKeyDocs,MAX_NAMEKEYS);
		if (xml.getStatus() != SUCCESS) {
			setStatus(xml.getStatus());
			setErrorMessage(xml.getErrorMessage());
			return;
		}
		pModuleStr->pNameKeyStr = (PNAMEKEYSTR) malloc(sizeof(NAMEKEYSTR) * pModuleStr->numberOfNameKeys);
		for (i = 0; i < pModuleStr->numberOfNameKeys; i++) {
			string rowDocs[MAX_ROWS];
			strcpy(pModuleStr->pNameKeyStr[i].nameKey,"XXXXXXXXXXXXXXX");

			nameKey = xml.getValue(nameKeyDocs[i],NAMEKEY);
			if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			if (xml.getStatus() != TAG_NOT_EXISTS) {
				if (strlen(nameKey.c_str()) == NAMEKEYLEN) {
					strcpy(pModuleStr->pNameKeyStr[i].nameKey,nameKey.c_str());
				}
				else {
					setStatus(INVALID_VALUE);
					setErrorMessage("APPISN bmInitialize -- Invalid value " + nameKey + " for tag " + toString(NAMEKEY));
					return;
				}
			}
			rowDefListDoc = xml.getNode(nameKeyDocs[i],ROWDEFLIST);
			pModuleStr->pNameKeyStr[i].numberOfRows = xml.getNodes(rowDefListDoc,ROWDEF,rowDocs,MAX_ROWS);
			if (xml.getStatus() != SUCCESS) {
				setStatus(xml.getStatus());
				setErrorMessage(xml.getErrorMessage());
				return;
			}
			pModuleStr->pNameKeyStr[i].pNameKeyRowStr = (PNAMEKEYROWSTR) malloc(sizeof(NAMEKEYROWSTR) * pModuleStr->pNameKeyStr[i].numberOfRows);

			for (j = 0; j < pModuleStr->pNameKeyStr[i].numberOfRows; j++) {
				(pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).mtType[0] = '\0';
				(pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).nameKeyAsn[0] = '\0';
				(pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).customerCode[0] = '\0';
				(pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).outputQueue[0] = '\0';
				(pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).nameKeyTrn[0] = '\0';

				mtType = xml.getValue(rowDocs[j],MTTYPE);
				if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}
				if (xml.getStatus() != TAG_NOT_EXISTS) {
					if (strlen(mtType.c_str()) == MTTYPE_LEN) {
						strcpy((pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).mtType,mtType.c_str());
					}
					else {
						setStatus(INVALID_VALUE);
						setErrorMessage("APPISN bmInitialize -- Invalid value " + mtType + " for tag " + toString(MTTYPE));
						return;
					}
				}
				nameKeyAsn = xml.getValue(rowDocs[j],NAMEKEYASN);
				if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}
				if (xml.getStatus() != TAG_NOT_EXISTS) {
					if (strlen(nameKeyAsn.c_str()) == NAMEKEYASNLEN) {
						strcpy((pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).nameKeyAsn,nameKeyAsn.c_str());
					}
					else {
						setStatus(INVALID_VALUE);
						setErrorMessage("APPISN bmInitialize -- Invalid value " + nameKeyAsn + " for tag " + toString(NAMEKEYASN));
						return;
					}
				}

				customerCode = xml.getValue(rowDocs[j],CUSTCODE);
				if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}
				if (xml.getStatus() != TAG_NOT_EXISTS) {
					if (strlen(customerCode.c_str()) == CUSTCODELEN) {
						strcpy((pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).customerCode,customerCode.c_str());
					}
					else {
						setStatus(INVALID_VALUE);
						setErrorMessage("APPISN bmInitialize -- Invalid value " + customerCode + " for tag " + toString(CUSTCODE));
						return;
					}
				}

				outputQueue = xml.getValue(rowDocs[j],OUTPUTQUE);
				if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}
				if (xml.getStatus() != TAG_NOT_EXISTS) {
					strcpy((pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).outputQueue,outputQueue.c_str());
				}
				nameKeyTrn = xml.getValue(rowDocs[j],NAMEKEYTRN);
				if ((xml.getStatus() != SUCCESS) && (xml.getStatus() != TAG_NOT_EXISTS)) {
					setStatus(xml.getStatus());
					setErrorMessage(xml.getErrorMessage());
					return;
				}
				if (xml.getStatus() != TAG_NOT_EXISTS) {
					if (strlen(nameKeyTrn.c_str()) == NAMEKEYTRNLEN) {
						strcpy((pModuleStr->pNameKeyStr[i].pNameKeyRowStr[j]).nameKeyTrn,nameKeyTrn.c_str());
					}
					else {
						setStatus(INVALID_VALUE);
						setErrorMessage("APPISN bmInitialize -- Invalid value " + nameKeyTrn + " for tag " + toString(NAMEKEYTRN));
						return;
					}
				}
			}
		}
		qsort (pModuleStr->pNameKeyStr, pModuleStr->numberOfNameKeys, sizeof(NAMEKEYSTR), nameKeyComparator);
	}
	tracing(TRACE_LEVEL_1, "APPISN bmInitialize", "ended");
}

void assignLT(PGWYSTR pGwyStr,char* srcBic8, char* mtType, char* desBic11, char* retLTerm, char* field97, char* field25) {
	char lTerm[LTERMLEN + 1];
	SELLTERMSTR selLTermStr;
	PSELLTERMSTR pSelLTermStr;

	SELLTERMSTR appLTermStr;
	PSELLTERMSTR pAppLTermStr;

	int i, j, m, n;
	bool found;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "started");

	strcpy(appLTermStr.bic8Name,srcBic8);

	pAppLTermStr = (PSELLTERMSTR) bsearch (&appLTermStr,
						pModuleStr->pAppLTermStr,
						pModuleStr->numberofAppLTerms,
						sizeof (SELLTERMSTR),
						selLTermComparator);
	if (pAppLTermStr != NULL) {

		if ((pAppLTermStr->pMTLTermStr[0]).destBIC11[0] == '\0') {
			pAppLTermStr->pMTLTermStr[0].currentLTIdx = 0;
			strcpy(retLTerm,(pAppLTermStr->pMTLTermStr[0]).lTermStr[(pAppLTermStr->pMTLTermStr[0]).currentLTIdx].lTerm);
			strcpy((pAppLTermStr->pMTLTermStr[0]).destBIC11, desBic11);
			strcpy((pAppLTermStr->pMTLTermStr[0]).lastMtType, mtType);
			tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
			return;
		}
		if ((!strcmp(desBic11,(pAppLTermStr->pMTLTermStr[0]).destBIC11)) && (!strcmp(mtType,(pAppLTermStr->pMTLTermStr[0]).lastMtType))) {
			strcpy(retLTerm,(pAppLTermStr->pMTLTermStr[0]).lTermStr[(pAppLTermStr->pMTLTermStr[0]).currentLTIdx].lTerm);
			tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
			return;
		}
		(pAppLTermStr->pMTLTermStr[0]).currentLTIdx = ((pAppLTermStr->pMTLTermStr[0]).currentLTIdx + 1) % (pAppLTermStr->pMTLTermStr[0]).numberOfLTerms;
		strcpy((pAppLTermStr->pMTLTermStr[0]).destBIC11,desBic11);
		strcpy((pAppLTermStr->pMTLTermStr[0]).lastMtType,mtType);
		strcpy(retLTerm,(pAppLTermStr->pMTLTermStr[0]).lTermStr[(pAppLTermStr->pMTLTermStr[0]).currentLTIdx].lTerm);
		tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
		return;
	}

	strcpy(selLTermStr.bic8Name,srcBic8);

	pSelLTermStr = (PSELLTERMSTR) bsearch (&selLTermStr,
												pModuleStr->pSelLTermStr,
												pModuleStr->numberOfBic8,
												sizeof (SELLTERMSTR),
												selLTermComparator);
	if (pSelLTermStr != NULL) {
		if (pSelLTermStr->numberOfMTLTs == 1) {
			if ((pSelLTermStr->pMTLTermStr[0]).numberOfLTerms == 1) {
				strcpy(retLTerm,(pSelLTermStr->pMTLTermStr[0]).lTermStr[0].lTerm);
				tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
				return;
			}
			else {
				if ((pSelLTermStr->pMTLTermStr[0]).destBIC11[0] == '\0') {
					(pSelLTermStr->pMTLTermStr[0]).currentLTIdx = 0;
					strcpy(retLTerm,(pSelLTermStr->pMTLTermStr[0]).lTermStr[(pSelLTermStr->pMTLTermStr[0]).currentLTIdx].lTerm);
					strcpy((pSelLTermStr->pMTLTermStr[0]).destBIC11, desBic11);
					strcpy((pSelLTermStr->pMTLTermStr[0]).lastMtType, mtType);
					tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
					return;
				}
				if ((!strcmp(desBic11,(pSelLTermStr->pMTLTermStr[0]).destBIC11)) && (!strcmp(mtType,(pSelLTermStr->pMTLTermStr[0]).lastMtType))) {
					strcpy(retLTerm,(pSelLTermStr->pMTLTermStr[0]).lTermStr[(pSelLTermStr->pMTLTermStr[0]).currentLTIdx].lTerm);
					return;
				}
				(pSelLTermStr->pMTLTermStr[0]).currentLTIdx = ((pSelLTermStr->pMTLTermStr[0]).currentLTIdx + 1) %
				(pSelLTermStr->pMTLTermStr[0]).numberOfLTerms;
				strcpy(retLTerm,(pSelLTermStr->pMTLTermStr[0]).lTermStr[(pSelLTermStr->pMTLTermStr[0]).currentLTIdx].lTerm);
				strcpy((pSelLTermStr->pMTLTermStr[0]).destBIC11, desBic11);
				strcpy((pSelLTermStr->pMTLTermStr[0]).lastMtType, mtType);
				tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
				return;
			}
			tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
			return;
		}
		else {
			for (i = 0; i < pSelLTermStr->numberOfMTLTs; i++) {
				found = true;
				for (j = 0; j < MTTYPE_LEN; j++) {
					if ((pSelLTermStr->pMTLTermStr[i]).mtType[j] == 'X') {
						continue;
					}
					else if (mtType[j] == (pSelLTermStr->pMTLTermStr[i]).mtType[j]) {
						continue;
					}
					else {
						found = false;
						break;
					}
				}
				if (found) {
					if ((pSelLTermStr->pMTLTermStr[i]).numberOfLTerms == 1) {
						strcpy(retLTerm,(pSelLTermStr->pMTLTermStr[i]).lTermStr[0].lTerm);
						tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
						return;
					}
					else {
						if ((pSelLTermStr->pMTLTermStr[i]).destBIC11[0] == '\0') {
							(pSelLTermStr->pMTLTermStr[i]).currentLTIdx = 0;
							strcpy(retLTerm,(pSelLTermStr->pMTLTermStr[i]).lTermStr[(pSelLTermStr->pMTLTermStr[i]).currentLTIdx].lTerm);
							strcpy((pSelLTermStr->pMTLTermStr[i]).destBIC11, desBic11);
							strcpy((pSelLTermStr->pMTLTermStr[i]).lastMtType, mtType);
							tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
							return;
						}
						if ((!strcmp(desBic11,(pSelLTermStr->pMTLTermStr[i]).destBIC11)) && (!strcmp(mtType,(pSelLTermStr->pMTLTermStr[i]).lastMtType))) {
							strcpy(retLTerm,(pSelLTermStr->pMTLTermStr[i]).lTermStr[(pSelLTermStr->pMTLTermStr[i]).currentLTIdx].lTerm);
							tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
							return;
						}
						(pSelLTermStr->pMTLTermStr[i]).currentLTIdx = ((pSelLTermStr->pMTLTermStr[i]).currentLTIdx + 1) %
						(pSelLTermStr->pMTLTermStr[i]).numberOfLTerms;
						strcpy(retLTerm,(pSelLTermStr->pMTLTermStr[i]).lTermStr[(pSelLTermStr->pMTLTermStr[i]).currentLTIdx].lTerm);
						strcpy((pSelLTermStr->pMTLTermStr[i]).destBIC11, desBic11);
						strcpy((pSelLTermStr->pMTLTermStr[i]).lastMtType, mtType);
						tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
						return;
					}
				}
			}
		}
	}
	else {
		strcpy(retLTerm,srcBic8);
		strcat(retLTerm,"A");
		tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "ended");
		return;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	appendEditResults -- append edit results.
// Parameters:	editResults -- The buf contains the edit results.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void appendEditResults(PGWYSTR pGwyStr, char* editResults) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	int len = strlen(ERRCODE);

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN appendEditResults", "started");
	if (pModuleStr->passErrMsgToSwf) {
		editMsgStart = strstr(editResults,ERRCODE);
		while (editMsgStart != NULL) {
			strncpy(editMsgStart,VLERROR,len);
			editMsgStart += len;
			editMsgStart = strstr(editResults,ERRCODE);
		}
	}
	else {
		strcat(pGwyStr->outputMessage,EDITCHKFAIL);
	}
	tracing(TRACE_LEVEL_1, "APPISN appendEditResults", "ended");
	strcat(pGwyStr->outputMessage,editResults);

}
void addSBlock(PGWYSTR pGwyStr, char* editResults) {
	char* sBlock = "{S:";
	char* sSource = "{SRC:";
	char* sMsgtrace = "{MSGTRACE:";
	char* sEnd = "}";
	char* sAppId = "{APP:";
	char* sPrio = "{PRIO:";
	char* sErrMsg = "{ERRMSG:";
	char* sErrCode = "{ERRCODE:";
	char* sOrgMTSTrn = "{ORGMTSTRN:";
	char* sDte = "{DTE:";
	char* sMrvTrc = "{MRVTRC:";
	char* sASN = "{ASN:";
	char* sORIGASN = "{ORIGASN:";
	char* sTIMECMPLT = "{TIMECMPLT:";
	char* sCKOFAC = "{CKOFAC:";
	char* sBNYTRN = "{BNYTRN:";
	char* sCUSTID = "{CUSTID:";
	char* sRCVADD1 = "{RCVADD1:";
	char* sRCVADD2 = "{RCVADD2:";
	char* sDESAPP = "{DESAPP:";
	char* sOrgRcvBIC = "{ORGRCVBIC:";
	char* sSOURCEAPP = "{SOURCEAPP:";
	char* sDESOUTPUTQ = "{DESOUTPUTQ:";
	char* sDESDIR = "{DESDIRECTION:";
	char* sMTTYPE = "{MTTYPE:";
	char* sTRN = "{TRN:";
	char* sCID = "{CID:";
	char* sNAMEKEY = "{NAMEKEY:";
	char* sACCNUM = "{ACCNUM:";
	char* sTRNPA = "{TRNPA:";
	char* sORIGDEPT = "{ORIGDEPT:";
	char* sCHRGACCT = "{CHRGACCT:";
	char* sRECVADD1 = "{RECVADD1:";
	char* sRECVADD2 = "{RECVADD2:";
	char* sRECVADD3 = "{RECVADD3:";
	char* sRECVADD4 = "{RECVADD4:";
	char* sCHRGADD1 = "{CHRGADD1:";
	char* sCHRGADD2 = "{CHRGADD2:";
	char* sCHRGADD3 = "{CHRGADD3:";
	char* sCHRGADD4 = "{CHRGADD4:";
	char* sMSGID= "{MSGID:";
	char* sOUTSRCCODE= "{OUTSRCCODE:";


	char tmpChar;

	getBusinessModuleVars(PBMDEF);

	tracing(TRACE_LEVEL_1, "APPISN addSBlock", "started");

	strcat(pGwyStr->outputMessage,sBlock);
	strcat(pGwyStr->outputMessage,sMsgtrace);
	strcat(pGwyStr->outputMessage,pModuleStr->correlationData);
	strcat(pGwyStr->outputMessage,sEnd);

	strcat(pGwyStr->outputMessage,sSource);
	strcat(pGwyStr->outputMessage,pModuleStr->src);
	strcat(pGwyStr->outputMessage,sEnd);
	if ((pModuleStr->appId[0] != '\0') || (pModuleStr->mainAppId[0] != '\0')) {
		strcat(pGwyStr->outputMessage,sAppId);
		if (pModuleStr->mainAppId[0] != '\0') {
			strcat(pGwyStr->outputMessage,pModuleStr->mainAppId);
		}
		else {
			strcat(pGwyStr->outputMessage,pModuleStr->appId);
		}
		strcat(pGwyStr->outputMessage,sEnd);
	}

	strcat(pGwyStr->outputMessage,sPrio);
	strcat(pGwyStr->outputMessage,pModuleStr->priority);
	strcat(pGwyStr->outputMessage,sEnd);

	if (pModuleStr->processPassArea) {
		strcat(pGwyStr->outputMessage,sASN);
		strcat(pGwyStr->outputMessage,pModuleStr->asn);
		strcat(pGwyStr->outputMessage,sEnd);
		if (pModuleStr->invalidPassArea) {
			strcat(pGwyStr->outputMessage, INVALIDPASSAREA);
		}
	}
	if (pModuleStr->origAsn[0] != '\0') {
		strcat(pGwyStr->outputMessage,sORIGASN);
		strcat(pGwyStr->outputMessage,pModuleStr->origAsn);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->timeCompleted[0] != '\0') {
		strcat(pGwyStr->outputMessage,sTIMECMPLT);
		strcat(pGwyStr->outputMessage,pModuleStr->timeCompleted);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->msgId[0] != '\0') {
		strcat(pGwyStr->outputMessage,sMSGID);
		strcat(pGwyStr->outputMessage,pModuleStr->msgId);
		strcat(pGwyStr->outputMessage,sEnd);
	}

	if (pModuleStr->origDept[0] != '\0') {
		strcat(pGwyStr->outputMessage,sORIGDEPT);
		strcat(pGwyStr->outputMessage,pModuleStr->origDept);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->charAcct[0] != '\0') {
		strcat(pGwyStr->outputMessage,sCHRGACCT);
		strcat(pGwyStr->outputMessage,pModuleStr->charAcct);
		strcat(pGwyStr->outputMessage,sEnd);
	}

	if (pModuleStr->acctNum[0] != '\0') {
		strcat(pGwyStr->outputMessage,sACCNUM);
		strcat(pGwyStr->outputMessage,pModuleStr->acctNum);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->trnPA[0] != '\0') {
		strcat(pGwyStr->outputMessage,sTRNPA);
		strcat(pGwyStr->outputMessage,pModuleStr->trnPA);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->recvAdd1[0] != '\0') {
		strcat(pGwyStr->outputMessage,sRECVADD1);
		strcat(pGwyStr->outputMessage,pModuleStr->recvAdd1);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->recvAdd2[0] != '\0') {
		strcat(pGwyStr->outputMessage,sRECVADD2);
		strcat(pGwyStr->outputMessage,pModuleStr->recvAdd2);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->recvAdd3[0] != '\0') {
		strcat(pGwyStr->outputMessage,sRECVADD3);
		strcat(pGwyStr->outputMessage,pModuleStr->recvAdd3);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->recvAdd4[0] != '\0') {
		strcat(pGwyStr->outputMessage,sRECVADD4);
		strcat(pGwyStr->outputMessage,pModuleStr->recvAdd4);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->chrgAdd1[0] != '\0') {
		strcat(pGwyStr->outputMessage,sCHRGADD1);
		strcat(pGwyStr->outputMessage,pModuleStr->chrgAdd1);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->chrgAdd2[0] != '\0') {
		strcat(pGwyStr->outputMessage,sCHRGADD2);
		strcat(pGwyStr->outputMessage,pModuleStr->chrgAdd2);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->chrgAdd3[0] != '\0') {
		strcat(pGwyStr->outputMessage,sCHRGADD3);
		strcat(pGwyStr->outputMessage,pModuleStr->chrgAdd3);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->chrgAdd4[0] != '\0') {
		strcat(pGwyStr->outputMessage,sCHRGADD4);
		strcat(pGwyStr->outputMessage,pModuleStr->chrgAdd4);
		strcat(pGwyStr->outputMessage,sEnd);
	}

	if (pModuleStr->cidFromPA[0] != '\0') {
		strcat(pGwyStr->outputMessage,sCID);
		strcat(pGwyStr->outputMessage,pModuleStr->cidFromPA);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->nameKeyFromPA[0] != '\0') {
		strcat(pGwyStr->outputMessage,sNAMEKEY);
		strcat(pGwyStr->outputMessage,pModuleStr->nameKeyFromPA);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->handleOutSrc) {
		strcat(pGwyStr->outputMessage,sOUTSRCCODE);
		strcat(pGwyStr->outputMessage,pModuleStr->ourSrcCode);
		strcat(pGwyStr->outputMessage,sEnd);
	}

	if (pModuleStr->checkOFAC) {
		strcat(pGwyStr->outputMessage,sCKOFAC);
		strcat(pGwyStr->outputMessage,"Y");
		strcat(pGwyStr->outputMessage,sEnd);
	}
	else {
		strcat(pGwyStr->outputMessage,sCKOFAC);
		strcat(pGwyStr->outputMessage,"N");
		strcat(pGwyStr->outputMessage,sEnd);
	}

	if (pModuleStr->rcvRepMsg) {
		if (pModuleStr->orgMtsTrn[0] != '\0') {
			strcat(pGwyStr->outputMessage,sOrgMTSTrn);
			strcat(pGwyStr->outputMessage,pModuleStr->orgMtsTrn);
			strcat(pGwyStr->outputMessage,sEnd);
		}
		if ((!strcmp(pModuleStr->mrvRsp,MRVRSPDEL)) || (!strcmp(pModuleStr->mrvRsp,MRVRSPERR))) {
			strcat(pGwyStr->outputMessage,sDte);
			strcat(pGwyStr->outputMessage,"D");
			strcat(pGwyStr->outputMessage,sEnd);
		}
		else if (!strcmp(pModuleStr->mrvRsp,MRVRSPNEW)) {
			strcat(pGwyStr->outputMessage,sDte);
			strcat(pGwyStr->outputMessage,"T");
			strcat(pGwyStr->outputMessage,sEnd);
		}
		if (pModuleStr->pMervaTrace != NULL) {
			char* pt = pModuleStr->pMervaTrace;

			while (pt[0] != '\0') {
				char* pEnd = strstr(pt,"\r\n");
				char* pEnd1;
				char* pt1;
				if (pEnd != NULL) {
					pEnd1 = pEnd - 1;
					pt1 = pEnd + 2;
					//
					// remove trailing blanks
					//
					while ((isblank(pEnd1[0])) && (pEnd1 != pt)) {
						pEnd = pEnd1;
						pEnd1--;
					}
					if (pEnd1 != pt) {
						tmpChar = pEnd[0];
						pEnd[0] = '\0';
						strcat(pGwyStr->outputMessage,sMrvTrc);
						strcat(pGwyStr->outputMessage,pt);
						strcat(pGwyStr->outputMessage,sEnd);
						pEnd[0] =tmpChar;
					}
					pt = pt1;
				}
				 else {
					pEnd = pt + strlen(pt);
					pEnd1 = pEnd - 1;
					//
					// remove trailing blanks
					//
					while ((isblank(pEnd1[0])) && (pEnd1 != pt)) {
						pEnd = pEnd1;
						pEnd1--;
					}
					if (pEnd1 != pt) {
						tmpChar = pEnd[0];
						pEnd[0] = '\0';
						strcat(pGwyStr->outputMessage,sMrvTrc);
						strcat(pGwyStr->outputMessage,pt);
						strcat(pGwyStr->outputMessage,sEnd);
						pEnd[0] =tmpChar;
					}
					pt = pt + strlen(pt);
				 }
			}
		}
	}
	if (pModuleStr->errMsg[0] != '\0') {
		if (pModuleStr->orgMTType[0] != '\0') {
			strcat(pGwyStr->outputMessage,sMTTYPE);
			strcat(pGwyStr->outputMessage,pModuleStr->orgMTType);
			strcat(pGwyStr->outputMessage,sEnd);
			pModuleStr->orgMTType[0] = '\0';
		}
		if (pModuleStr->orgTrn[0] != '\0') {
			strcat(pGwyStr->outputMessage,sTRN);
			strcat(pGwyStr->outputMessage,pModuleStr->orgTrn);
			strcat(pGwyStr->outputMessage,sEnd);
			pModuleStr->orgTrn[0] = '\0';
		}
		strcat(pGwyStr->outputMessage,pModuleStr->errMsg);
		pModuleStr->errMsg[0] = '\0';
	}
	else if ((editResults[0] != '\0') && (strcmp(editResults, EDITSUCCESS) != 0)) {
		appendEditResults(pGwyStr, editResults);
	}

	if (pModuleStr->handleTEO) {
		strcat(pGwyStr->outputMessage,sBNYTRN);
		strcat(pGwyStr->outputMessage,(pModuleStr->pCitTEOStr)->bnyTRn);
		strcat(pGwyStr->outputMessage,sEnd);
		strcat(pGwyStr->outputMessage,sCUSTID);
		strcat(pGwyStr->outputMessage,(pModuleStr->pCitTEOStr)->custId);
		strcat(pGwyStr->outputMessage,sEnd);
		strcat(pGwyStr->outputMessage,sRCVADD1);
		strcat(pGwyStr->outputMessage,(pModuleStr->pCitTEOStr)->rcvAdd1);
		strcat(pGwyStr->outputMessage,sEnd);
		strcat(pGwyStr->outputMessage,sRCVADD2);
		strcat(pGwyStr->outputMessage,(pModuleStr->pCitTEOStr)->rcvAdd2);
		strcat(pGwyStr->outputMessage,sEnd);
		strcat(pGwyStr->outputMessage,sDESAPP);
		strcat(pGwyStr->outputMessage,pModuleStr->desApp);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->setSwitchToIBR) {
		strcat(pGwyStr->outputMessage,sSOURCEAPP);
		strcat(pGwyStr->outputMessage,pModuleStr->appId);
		strcat(pGwyStr->outputMessage,sEnd);
		strcat(pGwyStr->outputMessage,sOrgRcvBIC);
		strcat(pGwyStr->outputMessage,pModuleStr->rcvBic12);
		strcat(pGwyStr->outputMessage,sEnd);
		if (pModuleStr->desAppPerMsg[0] != '\0') {
			strcat(pGwyStr->outputMessage,sDESAPP);
			strcat(pGwyStr->outputMessage,pModuleStr->desAppPerMsg);
			strcat(pGwyStr->outputMessage,sEnd);
		}
		if (pModuleStr->desDirectionPerMsg[0] != '\0') {
			strcat(pGwyStr->outputMessage,sDESDIR);
			strcat(pGwyStr->outputMessage,pModuleStr->desDirectionPerMsg);
			strcat(pGwyStr->outputMessage,sEnd);
		}
	}
	if (pModuleStr->handleCIBC) {
		strcat(pGwyStr->outputMessage,sDESAPP);
		strcat(pGwyStr->outputMessage,"CIBC");
		strcat(pGwyStr->outputMessage,sEnd);
		strcat(pGwyStr->outputMessage,sOrgRcvBIC);
		strcat(pGwyStr->outputMessage,pModuleStr->rcvBic12);
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if (pModuleStr->handleNameKey) {
		strcat(pGwyStr->outputMessage,sOrgRcvBIC);
		strcat(pGwyStr->outputMessage,pModuleStr->rcvBic12);
		strcat(pGwyStr->outputMessage,sEnd);
		strcat(pGwyStr->outputMessage,sDESOUTPUTQ);
		strcat(pGwyStr->outputMessage,pModuleStr->nameKeyOutputQueue);
		strcat(pGwyStr->outputMessage,sEnd);
		if (!strcmp(pModuleStr->rcvBic12,"XXXXXXXXXXXX")) {
			strcpy(pModuleStr->errMsg,BADSWFADDRESS);
			strcat(pGwyStr->outputMessage,pModuleStr->errMsg);
			pModuleStr->errMsg[0] = '\0';
		}
	}
	if (pModuleStr->failToTransform) {
		strcat(pGwyStr->outputMessage,pModuleStr->errMsg);
		pModuleStr->errMsg[0] = '\0';
	}
	strcat(pGwyStr->outputMessage,sEnd);
	tracing(TRACE_LEVEL_1, "APPISN addSBlock", "ended");
}

void getRepMsgInfo(PGWYSTR pGwyStr) {
	char* pt;
	char* pMsgEnd;
	char tmpChar;

	getBusinessModuleVars(PBMDEF);

	tracing(TRACE_LEVEL_1, "APPISN getRepMsgInfo", "started");

	pt = strstr(pGwyStr->inputMessage,MRVCORRID);
	if (pt != NULL) {
		pMsgEnd = strstr(pt,"\r\n");
		tmpChar = pMsgEnd[0];
		pMsgEnd[0] = '\0';
		pt = pt + strlen(MRVCORRID);
		strcpy(pModuleStr->correlationData,pt);
		pMsgEnd[0] = tmpChar;
	}
	else {
		pModuleStr->correlationData[0] = '\0';
	}

	pt = strstr(pGwyStr->inputMessage,MRVDE);
	if (pt != NULL) {
		pMsgEnd = strstr(pt,"\r\n");
		tmpChar = pMsgEnd[0];
		pMsgEnd[0] = '\0';
		pt = pt + strlen(MRVDE);
		strcpy(pModuleStr->mrvRsp,pt);
		pMsgEnd[0] = tmpChar;
		pt = strstr(pGwyStr->inputMessage,APPDE);
		if (pt != NULL) {
			pMsgEnd = strstr(pt,"\r\n");
			tmpChar = pMsgEnd[0];
			pMsgEnd[0] = '\0';
			pt = pt + strlen(APPREP);
			strcpy(pModuleStr->appId,pt);
			pMsgEnd[0] = tmpChar;
		}
		else {
			strcpy(pModuleStr->mrvRsp,MRVRSPDEL);
		}
		pt = strstr(pGwyStr->inputMessage,MRVTRAC);
		if (pt != NULL){
			pModuleStr->pMervaTrace = pt + strlen(MRVTRAC);
		}
		else {
			pModuleStr->pMervaTrace = NULL;
		}
	}
	else {
		pt = strstr(pGwyStr->inputMessage,MTSTRN);
		if (pt != NULL) {
			pMsgEnd = strstr(pt,"\r\n");
			tmpChar = pMsgEnd[0];
			pMsgEnd[0] = '\0';
			pt = pt + strlen(MTSTRN);
			strcpy(pModuleStr->orgMtsTrn,pt);
			pMsgEnd[0] = tmpChar;
		}
		else {
			pModuleStr->orgMtsTrn[0] = '\0';
			strcpy(pModuleStr->mrvRsp,MRVRSPDEL);
		}

		pt = strstr(pGwyStr->inputMessage,APPREP);
		if (pt != NULL) {
			pMsgEnd = strstr(pt,"\r\n");
			tmpChar = pMsgEnd[0];
			pMsgEnd[0] = '\0';
			pt = pt + strlen(APPREP);
			strcpy(pModuleStr->appId,pt);
			pMsgEnd[0] = tmpChar;
		}
		else {
			strcpy(pModuleStr->mrvRsp,MRVRSPDEL);
		}


		pt = strstr(pGwyStr->inputMessage,MRVRESP);
		if (pt != NULL) {
			pMsgEnd = strstr(pt,"\r\n");
			tmpChar = pMsgEnd[0];
			pMsgEnd[0] = '\0';
			pt = pt + strlen(MRVRESP);
			strcpy(pModuleStr->mrvRsp,pt);
			pMsgEnd[0] = tmpChar;
		}
		else {
			strcpy(pModuleStr->mrvRsp,MRVRSPDEL);
		}
		pt = strstr(pGwyStr->inputMessage,MRVTRAC);


		if (pt != NULL){
			pModuleStr->pMervaTrace = pt + strlen(MRVTRAC);
		}
		else {
			pModuleStr->pMervaTrace = NULL;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	transformInternalToSwiftLocal -- Tansform messages from internal format to Swift format.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void transformInternalToSwiftLocal(PGWYSTR pGwyStr) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	char swiftMsg[20000];
	char* pt;
	char sLineNum[3];
	char tmpBuf[128];
	int swiftMsgPos;
	int i;
	int lineNum;
	int preLineNum;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN transformInternalToSwiftLocal", "started");
	pt = &(pGwyStr->inputMessage[PASSAREALEN]);
	strncpy(sLineNum,&(pt[3]),2);
	sLineNum[2] = '\0';
	lineNum = atoi(sLineNum);
	preLineNum = lineNum;
	swiftMsg[0] = '\0';
	swiftMsgPos = 0;
	while(pt[0] != '\0') {
		tmpBuf[0] = '\0';
		if (lineNum <= preLineNum) {
			if (isblank(pt[2])) {
				strcat(tmpBuf,":");
				strncat(tmpBuf,pt,2);
				tmpBuf[3] = '\0';
				strcat(tmpBuf,":");
				swiftMsgPos = 4;
			}
			else {
				strcat(tmpBuf,":");
				strncat(tmpBuf,pt,3);
				tmpBuf[4] = '\0';
				strcat(tmpBuf,":");
				swiftMsgPos = 5;
			}
		}
		strncat(tmpBuf,&(pt[5]),35);
		tmpBuf[swiftMsgPos + 35] = '\0';
		for (i = swiftMsgPos + 34; i >= swiftMsgPos; i--) {
			if (!isblank(pt[i])) {
				break;
			}
		}
		tmpBuf[i+1] = '\0';
		strcat(swiftMsg,tmpBuf);
		strcat(swiftMsg,"\r\n");
		pt = pt + 40;
		if (pt[0] != '\0') {
			strncpy(sLineNum,&(pt[3]),2);
			sLineNum[2] = '\0';
			preLineNum = lineNum;
			lineNum = atoi(sLineNum);
		}
	}
	pGwyStr->inputMessage[PASSAREALEN] = '\0';
	strcat(pGwyStr->inputMessage,swiftMsg);
	tracing(TRACE_LEVEL_1, "APPISN transformInternalToSwiftLocal", "ended");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	transformInternalToSwift -- Tansform messages from internal format to Swift format.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void transformInternalToSwift(PGWYSTR pGwyStr) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	char* pMetaData = NULL;
	char* pMetaData1 = NULL;
	char* pMetaDataEnd = NULL;

	char tmpChar;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN transformInternalToSwift", "started");
	if (pModuleStr->handleNameKey) {
		pModuleStr->cusIndId = pGwyStr->inputMessage[CUSTINDPOS];
		pGwyStr->inputMessage[CUSTINDPOS] = 'Y';
	}
	pModuleStr->metadfataBuff[0] = '\0';
	if (pModuleStr->supportGPII) {
		pMetaData = strstr(pGwyStr->inputMessage,METADATA);
		if (pMetaData != NULL) {
			pMetaData1 = pMetaData - 2;
			tmpChar = pMetaData1[0];
			pMetaData1[0] = '\0';
			pMetaDataEnd = strstr(pMetaData,"}}");
			if (pMetaDataEnd != NULL) {
				pMetaDataEnd[1] = '\0';
				pMetaData = pMetaData + strlen(METADATA);
				strcpy(pModuleStr->metadfataBuff,pMetaData);
			}
		}
	}

	string params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(CDATASTART) + toString(pGwyStr->inputMessage) + toString(CDATAEND) + toString(PARAMEND) + toString(PARAMSEND);
	pModuleStr->orgTrn[0] = '\0';

	int retValue;
	int reConnectCount = 0;
	bool afterReconnect = false;

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;

	while (1) {
		if (afterReconnect) {
			reset();
			registerTFMSvc(pGwyStr);
			if (retStatus() != SUCCESS){
				return;
			}
		}

		retValue = pSvcClient->svcClientReqSvc(pModuleStr->svcTFMHandler, TRANSFORMOP, params, svcClientRequest, svcServerResponse,MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN transformInternalToSwift", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN transformInternalToSwift", "ended");
				return;
			}
			else {
				afterReconnect =true;
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				if (!strncmp(pt,FMTSUCCESS,strlen(FMTSUCCESS))) {
					pt = &pt[strlen(FMTSUCCESS)];
					strncpy(pModuleStr->rcvBic12,pt,BIC8LEN);
					pModuleStr->rcvBic12[BIC8LEN] = 'X';
					strncpy(&(pModuleStr->rcvBic12[BIC8LEN+1]),&(pt[BIC8LEN]),BRANCHLEN);
					pModuleStr->rcvBic12[BIC12LEN] = '\0';
					pt = pt + BIC11LEN + 1;
					strncpy(pModuleStr->nameKey,pt,NAMEKEYLEN);
					pModuleStr->nameKey[NAMEKEYLEN] = '\0';
					pt = pt + NAMEKEYLEN + 1;
					strncpy(pModuleStr->cid,pt,CIDLEN);
					pModuleStr->cid[CIDLEN] = '\0';
					pt = pt + CIDLEN;
					endPt = strstr(pt,SVCRSPEND);
					if (endPt != NULL) {
						endPt[0] = '\0';
						pGwyStr->inputMessage[PASSAREALEN] = '\0';
						strcat(pGwyStr->inputMessage,pt);
 						break;
					}
				}
				else {
					pModuleStr->failToTransform = true;
					char mtType[MTTYPELEN + 1];
					char rcvBIC8[BIC8LEN + 1];
					char rcvSBch[SBCHLEN + 1];
					bool findBlank = false;
					char* pt1;
					int i;

					strncpy(pModuleStr->orgMTType,&(pGwyStr->inputMessage[MTTYPEPOS]),MTTYPELEN);
					pModuleStr->orgMTType[MTTYPELEN] = '\0';
					strncpy(pModuleStr->orgTrn,&(pGwyStr->inputMessage[ORGTRNPOS]),ORGTRNSEQLEN);
					pModuleStr->orgTrn[ORGTRNSEQLEN] = '\0';
					strcpy(mtType,pModuleStr->orgMTType);
					strncpy(&mtType[1],"98",2);
					strncpy(rcvBIC8,&(pGwyStr->inputMessage[HB2BIC8POS]),BIC8LEN);
					rcvBIC8[BIC8LEN] = '\0';
					findBlank = false;
					for (i = 0; i < BIC8LEN; i++) {
						if (isblank(rcvBIC8[i])) {
							findBlank = true;
							break;
						}
					}
					if (findBlank) {
						strcpy(rcvBIC8,"IRVTUS3N");
					}
					strncpy(rcvSBch,&(pGwyStr->inputMessage[HB2SBCHPOS]),SBCHLEN);
					rcvSBch[SBCHLEN] = '\0';
					findBlank = false;
					for (i = 0; i < SBCHLEN; i++) {
						if (isblank(rcvSBch[i])) {
							findBlank = true;
							break;
						}
					}
					if (findBlank) {
						strcpy(rcvSBch,"XXX");
					}
					strcpy(pModuleStr->errMsg,TRANSFORMERR);
					pt = &pt[strlen(FMTFAILURE)];
					pt1 = strstr(pt,"|");
					if (pt1 != NULL) {
						pt = pt1 + 1;
						endPt = strstr(pt,SVCRSPEND);
						if (endPt != NULL) {
							endPt[0] = '\0';
							strcpy(pGwyStr->inputMessage, "{1:F01IRVTUS3NAXXX0000000000}{2:I");
							strcat(pGwyStr->inputMessage,mtType);
							strcat(pGwyStr->inputMessage,rcvBIC8);
							strcat(pGwyStr->inputMessage,"X");
							strcat(pGwyStr->inputMessage,rcvSBch);
							strcat(pGwyStr->inputMessage,"N}{4:\r\n");
							strcat(pGwyStr->inputMessage,pt);
							strcat(pGwyStr->inputMessage,"\r\n");
							break;
						}
					}
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN transformInternalToSwift", "ended");
				return;
			}
			break;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN transformInternalToSwift", "ended");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	transformSwiftToSwift -- Tansform messages from Swift format to Swift format.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void transformSwiftToSwift(PGWYSTR pGwyStr) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];
	char* pBlock4;
	char* pBlock4End;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN transformSwiftToSwift", "started");

	pBlock4 = strstr(pGwyStr->inputMessage,"{4:");
	pBlock4 = pBlock4 + 5;
	pBlock4End = strstr(pBlock4,"-}");
	if (pBlock4End == NULL) {
		strcpy(pModuleStr->errMsg,STOSERRCODE);
		strcat(pModuleStr->errMsg,"Invalid Message Format");
		strcat(pModuleStr->errMsg,"}");
		pModuleStr->failToTransform = true;
		tracing(TRACE_LEVEL_1, "APPISN transformSwiftToSwift", "Invalid Message Format");
		tracing(TRACE_LEVEL_1, "APPISN transformSwiftToSwift", "ended");
		return;
	}
	pModuleStr->failToTransform = false;

	pBlock4End[0] = '\0';

	string params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(CDATASTART) + toString(pBlock4) + toString(CDATAEND) + toString(PARAMEND) + toString(PARAMSEND);
	pBlock4End[0] = '-';

	int retValue;
	int reConnectCount = 0;
	bool afterReconnect = false;

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;

	while (1) {
		if (afterReconnect) {
			reset();
			registerTFMSvc(pGwyStr);
			if (retStatus() != SUCCESS){
				return;
			}
		}

		retValue = pSvcClient->svcClientReqSvc(pModuleStr->svcTFMHandler, TRANSFORMOP, params, svcClientRequest, svcServerResponse,MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN transformSwiftToSwift", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN transformSwiftToSwift", "ended");
				return;
			}
			else {
				afterReconnect =true;
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				if (!strncmp(pt,FMTSUCCESS,strlen(FMTSUCCESS))) {
					pt = &pt[strlen(FMTSUCCESS)] + TRANSFORMSKIPLEN;
					endPt = strstr(pt,SVCRSPEND);
					if (endPt != NULL) {
						endPt[0] = '\0';
						pBlock4[0] = '\0';
						strcat(pBlock4,pt);
						strcat(pBlock4,"-}");
 						break;
					}
				}
				else {
					pt = &pt[strlen(FMTFAILURE)];
					pModuleStr->failToTransform = true;
					strcpy(pModuleStr->errMsg,STOSERRCODE);
					endPt = strstr(pt,SVCRSPEND);
					if (endPt != NULL) {
						endPt[0] = '\0';
						strcat(pModuleStr->errMsg,pt);
						strcat(pModuleStr->errMsg,"}");
						break;
					}
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN transformSwiftToSwift", "ended");
				return;
			}
			break;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN transformSwiftToSwift", "ended");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	Create GTM Ack Message -- Create GTM Ack Message
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void createGTMAckMsg(PGWYSTR pGwyStr) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];


	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN createGTMAckMsg", "started");

	string params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(CDATASTART) + toString(pModuleStr->asn) + toString(CDATAEND) + toString(PARAMEND) + toString(PARAMSEND);

	int retValue;
	int reConnectCount = 0;
	bool afterReconnect = false;

	pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;

	while (1) {
		if (afterReconnect) {
			reset();
			registerGTMAckSvc(pGwyStr);
			if (retStatus() != SUCCESS){
				return;
			}
		}
		retValue = pSvcClient->svcClientReqSvc(pModuleStr->svcGTMAckHandler, GENGTMACKOP, params, svcClientRequest, svcServerResponse,MAX_SVC_BUF);
		if (retValue == FAIL_TO_CONNECT){
			setStatus(pSvcClient->getStatus());
			setErrorMessage(pSvcClient->getErrorMessage());
			tracing(TRACE_LEVEL_1, "APPISN createGTMAckMsg", "ended");
			return;
		}
		else if (retValue == RECONNECT_SUCCESS) {
			reConnectCount++;
			if (reConnectCount > 1) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				tracing(TRACE_LEVEL_1, "APPISN createGTMAckMsg", "ended");
				return;
			}
			else {
				afterReconnect =true;
				continue;
			}
		}
		else {
			char* pt = &svcServerResponse[strlen(SVCRSPSTART)];
			char* endPt = NULL;
			if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
				pt = &pt[strlen(SVCSUCCESS)];
				if (!strncmp(pt,FMTSUCCESS,strlen(FMTSUCCESS))) {
					pt = &pt[strlen(FMTSUCCESS)];
					endPt = strstr(pt,SVCRSPEND);
					if (endPt != NULL) {
						endPt[0] = '\0';
						strcpy(pModuleStr->gtmAckMsg,pt);
 						break;
					}
				}
				else {
					pModuleStr->failToGetGTM = true;
					strcpy(pModuleStr->errMsg,GETGTMERR);
				}
			}
			else {
				setStatus(SVCREMOTE_FAIL_READ);
				setErrorMessage(svcServerResponse);
				tracing(TRACE_LEVEL_1, "APPISN createGTMAckMsg", "ended");
				return;
			}
			break;
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN createGTMAckMsg", "ended");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	getEditResults -- Get Priority.
// Parameters:	editResults -- The buf contains the edit results.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void getEditResults(PGWYSTR pGwyStr, char* editResults, char* lTerm, char* mtType, char cPriority) {
	CSvcClient* pSvcClient;
	char* editMsgStart;
	char svcClientRequest[MAX_SVC_BUF];
	char svcServerResponse[MAX_SVC_BUF];

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getEditResults", "started");

	editResults[0] = '\0';
	if (pModuleStr->defaultSvcPort != NOSVC) {
		pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;
		if (pModuleStr->editSvcFailed) {
			//pSvcClient->init();
			//if (pSvcClient->getStatus() != SUCCESS) {
			if (!pModuleStr->editCheckBySwift) {
				pSvcClient->disconnectSvcServer();
				if (!pModuleStr->editCheckBySwift) {
					strcpy(editResults,EDITSVCFAIL);
					pModuleStr->editSvcFailed = true;
					//if (strcmp(pModuleStr->src,pModuleStr->ibrSrc)) {
						//getPriority(pGwyStr, pGwyStr->inputMessage);
					getPriority(pGwyStr, lTerm, mtType, false, cPriority);
					//}
				}
			}
			else {
				//getPriority(pGwyStr, pGwyStr->inputMessage);
				getPriority(pGwyStr, lTerm, mtType, false, cPriority);
				editResults[0] = '\0';
			}
			//}
			/*else {
				pModuleStr->editSvcFailed = false;
			}
			*/
		}
		if (!pModuleStr->editSvcFailed) {

			editMsgStart = strstr(pGwyStr->outputMessage,MERVABLOCK1);
			string params = toString(PARAMSSTART) + toString(PARAMSTART) + toString(CDATASTART) + toString(editMsgStart) + toString(CDATAEND) + toString(PARAMEND) + toString(PARAMSEND);

			int retValue;
			int reConnectCount = 0;
			bool afterReconnect = false;

			while (1) {
				if (afterReconnect) {
					registerSvc(pGwyStr);
					if (pModuleStr->editSvcFailed) {
						afterReconnect = false;
						break;
					}
				}

				retValue = pSvcClient->svcClientReqSvc(pModuleStr->svcHandler, EDITCHECKOP, params, svcClientRequest, editResults,MAX_EDIT_LENGTH);
				if (retValue == FAIL_TO_CONNECT){
					break;
				}
				else if (retValue == RECONNECT_SUCCESS) {
					reConnectCount++;
					if (reConnectCount > 1) {
						pModuleStr->editSvcFailed = true;
						break;
					}
					else {
						afterReconnect =true;
						continue;
					}
				}
				else {
					break;
				}
			}
			//pSvcClient->editCheck(editMsgStart,editResults,MAX_EDIT_LENGTH);
			if (pSvcClient->getStatus() != SUCCESS) {
				pSvcClient->disconnectSvcServer();
				if ((!pModuleStr->editCheckBySwift) || (pModuleStr->ibrOnly)) {
					strcpy(editResults,EDITSVCFAIL);
					pModuleStr->editSvcFailed = true;
					getPriority(pGwyStr, lTerm, mtType, false, cPriority);

					pModuleStr->editSvcFailed = true;
					tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after pSvcClient->editCheck  fail errormsg = " + pSvcClient->getErrorMessage());
				}
				else {
					pModuleStr->processIBR = false;

					getPriority(pGwyStr, lTerm, mtType, false, cPriority);
					//getPriority(pGwyStr, pGwyStr->inputMessage);
					tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after allow swift edit check pSvcClient->editCheck  fail errormsg = " + pSvcClient->getErrorMessage());
					editResults[0] = '\0';
					pModuleStr->editSvcFailed = true;
				}
			}
			else {
				tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after pSvcClient->editCheck  SUCCESS");
				tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after pSvcClient->editCheck  editResults = " + toString(editResults));
				pModuleStr->editSvcFailed = false;
				char* pt = &editResults[strlen(SVCRSPSTART)];
				char* endPt = NULL;
				if (!strncmp(pt,SVCSUCCESS,strlen(SVCSUCCESS))) {
					pt = &pt[strlen(SVCSUCCESS)];
					endPt = strstr(pt,SVCRSPEND);
					if (endPt != NULL) {
						endPt[0] = '\0';
						strcpy(editResults,pt);
					}
					else {
						pModuleStr->editSvcFailed = true;
						if ((!pModuleStr->editCheckBySwift) || (pModuleStr->ibrOnly)) {
							strcpy(editResults,EDITSVCFAIL);
							pModuleStr->editSvcFailed = true;
							getPriority(pGwyStr, lTerm, mtType, false, cPriority);
							pModuleStr->editSvcFailed = true;
							tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after pSvcClient->editCheck  fail errormsg = " + pSvcClient->getErrorMessage());
						}
						else {
							pModuleStr->processIBR = false;
							//getPriority(pGwyStr, pGwyStr->inputMessage);
							getPriority(pGwyStr, lTerm, mtType, false, cPriority);
							tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after allow swift edit check pSvcClient->editCheck  fail errormsg = " + pSvcClient->getErrorMessage());
							editResults[0] = '\0';
							pModuleStr->editSvcFailed = true;
						}
					}
				}
				else {
					pModuleStr->editSvcFailed = true;
					if ((!pModuleStr->editCheckBySwift) || (pModuleStr->ibrOnly)) {
						strcpy(editResults,EDITSVCFAIL);
						pModuleStr->editSvcFailed = true;
						getPriority(pGwyStr, lTerm, mtType, false, cPriority);
						pModuleStr->editSvcFailed = true;
						tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after pSvcClient->editCheck  fail errormsg = " + pSvcClient->getErrorMessage());
					}
					else {
						pModuleStr->processIBR = false;
						//getPriority(pGwyStr, pGwyStr->inputMessage);
						getPriority(pGwyStr, lTerm, mtType, false, cPriority);
						tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after allow swift edit check pSvcClient->editCheck  fail errormsg = " + pSvcClient->getErrorMessage());
						editResults[0] = '\0';
						pModuleStr->editSvcFailed = true;
					}
				}
				if (strcmp(editResults, EDITSUCCESS)) {
					if (pModuleStr->passErrMsgToSwf) {
						//getPriority(pGwyStr, pGwyStr->inputMessage);
						getPriority(pGwyStr, lTerm, mtType, false, cPriority);
					}
				}
			}
		}

	}
	tracing(TRACE_LEVEL_1, "APPISN getEditResults", "ended");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	getEditResults -- Get Priority.
// Parameters:	editResults -- The buf contains the edit results.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*void getEditResults(PGWYSTR pGwyStr, char* editResults, char* lTerm, char* mtType, char cPriority) {
	CSvcClient* pSvcClient;
	char* editMsgStart;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getEditResults", "started");

	editResults[0] = '\0';
	if (pModuleStr->defaultSvcPort != NOSVC) {
		pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;
		if (pModuleStr->editSvcFailed) {
			if (!pModuleStr->editCheckBySwift) {
				strcpy(editResults,EDITSVCFAIL);
				pModuleStr->editSvcFailed = true;
			}
			else {
				//getPriority(pGwyStr, lTerm, mtType, false, cPriority);
				editResults[0] = '\0';
			}
		}
		if (!pModuleStr->editSvcFailed) {
			editMsgStart = strstr(pGwyStr->outputMessage,MERVABLOCK1);
			pSvcClient->editCheck(editMsgStart,editResults,MAX_EDIT_LENGTH);
			if (pSvcClient->getStatus() != SUCCESS) {
				pSvcClient->disconnectSvcServer();
				if (!pModuleStr->editCheckBySwift) {
					strcpy(editResults,EDITSVCFAIL);
					pModuleStr->editSvcFailed = true;
					tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after pSvcClient->editCheck  fail errormsg = " + pSvcClient->getErrorMessage());
				}
				else {
					pModuleStr->processIBR = false;
					getPriority(pGwyStr, lTerm, mtType, false, cPriority);
					tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after allow swift edit check pSvcClient->editCheck  fail errormsg = " + pSvcClient->getErrorMessage());
					editResults[0] = '\0';
					pModuleStr->editSvcFailed = true;
				}
			}
			else {
				tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after pSvcClient->editCheck  SUCCESS");
				tracing(TRACE_LEVEL_1, "SWFACK getEditResults", "after pSvcClient->editCheck  editResults = " + toString(editResults));
				pModuleStr->editSvcFailed = false;
				if (strcmp(editResults, EDITSUCCESS)) {
					if (pModuleStr->passErrMsgToSwf) {
						getPriority(pGwyStr, lTerm, mtType, false, cPriority);
					}
				}
			}
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN getEditResults", "ended");
}
*/

void getGapTable(PGWYSTR pGwyStr) {
	char* pt;
	char sGapData[5];
	int i = 0;
	int m;

	getBusinessModuleVars(PBMDEF);

	tracing(TRACE_LEVEL_1, "APPISN getGapTable", "started");

	pt = pGwyStr->inputMessage;
	while (pt[0] != '\0') {
		strncpy(sGapData,pt,5);
		sGapData[4] = '\0';
		sscanf (sGapData,"%05X",&m);
		pt = pt + 4;
		pModuleStr->pGapTable[i] = m;
		i++;
	}
	tracing(TRACE_LEVEL_1, "APPISN getGapTable", "ended");
}


/*int getSeqNumber(PGWYSTR pGwyStr) {

	int i, j, m, n;
	bool found;
	char sAsnNumber[ASNNUM_LEN+1];
	int asnNUmber;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "SWFAPPISN assignLT", "started");

	strncpy(sAsnNumber, &(pGwyStr->inputMessage[ASNNUMPOS]),ASNNUM_LEN);
	sAsnNumber[ASNNUM_LEN]= '\0';
	asnNumber = atoi(sAsnNumber);

	return asnNUmber;
}
*/

void getAsn(PGWYSTR pGwyStr) {
	char* pt;
	int i;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getAsn", "started");

	strncpy(pModuleStr->asn, &(pGwyStr->inputMessage[ASNPOS]),ASN_LEN);
	pModuleStr->asn[ASN_LEN]= '\0';

	pModuleStr->origAsn[0] = '\0';
	if (!isblank(pGwyStr->inputMessage[ORGASNPOS])) {
		strncpy(pModuleStr->origAsn, (char*) &(pGwyStr->inputMessage[ORGASNPOS]), ORIGASNLEN);
		pModuleStr->origAsn[ORIGASNLEN] = '\0';
	}
	pModuleStr->timeCompleted[0] = '\0';
	if (!isblank(pGwyStr->inputMessage[TIMECOMPLETEDPOS])) {
		strncpy(pModuleStr->timeCompleted, (char*) &(pGwyStr->inputMessage[TIMECOMPLETEDPOS]), TIMECOMPLETEDLEN);
		pModuleStr->timeCompleted[TIMECOMPLETEDLEN] = '\0';
	}

	pModuleStr->origDept[0] = '\0';
	if (!isblank(pGwyStr->inputMessage[ORIGDEPTPOS])) {
		strncpy(pModuleStr->origDept, (char*) &(pGwyStr->inputMessage[ORIGDEPTPOS]), ORIGDEPTLEN);
		pModuleStr->origDept[ORIGDEPTLEN] = '\0';
	}

	pModuleStr->charAcct[0] = '\0';
	if (!isblank(pGwyStr->inputMessage[CHRGACCTPOS])) {
		strncpy(pModuleStr->charAcct, (char*) &(pGwyStr->inputMessage[CHRGACCTPOS]), CHRGACCTLEN);
		pModuleStr->charAcct[CHRGACCTLEN] = '\0';
	}

	pModuleStr->msgId[0] = '\0';
	if (!isblank(pGwyStr->inputMessage[MSGIDPOS])) {
		strncpy(pModuleStr->msgId, (char*) &(pGwyStr->inputMessage[MSGIDPOS]), MSGIDLEN);
		pModuleStr->msgId[MSGIDLEN] = '\0';
	}

	pModuleStr->trnPA[0] = '\0';
	if (!isblank(pGwyStr->inputMessage[ORGTRNPOS])) {
		strncpy(pModuleStr->trnPA, (char*) &(pGwyStr->inputMessage[ORGTRNPOS]), ORGTRNSEQLEN);
		pModuleStr->trnPA[ORGTRNSEQLEN] = '\0';
	}

	pModuleStr->acctNum[0] = '\0';
	if (!isblank(pGwyStr->inputMessage[ACCTNUMPOS])) {
		strncpy(pModuleStr->acctNum, (char*) &(pGwyStr->inputMessage[ACCTNUMPOS]), ACCTNUMLEN);
		pModuleStr->acctNum[ACCTNUMLEN] = '\0';
	}
	if (pModuleStr->reserveAddress) {
		pModuleStr->recvAdd1[0] = '\0';
		pModuleStr->recvAdd2[0] = '\0';
		pModuleStr->recvAdd3[0] = '\0';
		pModuleStr->recvAdd4[0] = '\0';
		pModuleStr->chrgAdd1[0] = '\0';
		pModuleStr->chrgAdd2[0] = '\0';
		pModuleStr->chrgAdd3[0] = '\0';
		pModuleStr->chrgAdd4[0] = '\0';
		if (!isblank(pGwyStr->inputMessage[RECVADDPOS])) {
			strncpy(pModuleStr->recvAdd1, (char*) &(pGwyStr->inputMessage[RECVADDPOS]), ADDRESSLEN);
			pModuleStr->recvAdd1[ADDRESSLEN] = '\0';
			strncpy(pModuleStr->recvAdd2, (char*) &(pGwyStr->inputMessage[RECVADDPOS  + ADDRESSLEN]), ADDRESSLEN);
			pModuleStr->recvAdd2[ADDRESSLEN] = '\0';
			strncpy(pModuleStr->recvAdd3, (char*) &(pGwyStr->inputMessage[RECVADDPOS  + 2*ADDRESSLEN]), ADDRESSLEN);
			pModuleStr->recvAdd3[ADDRESSLEN] = '\0';
			strncpy(pModuleStr->recvAdd4, (char*) &(pGwyStr->inputMessage[RECVADDPOS  + 3*ADDRESSLEN]), ADDRESSLEN);
			pModuleStr->recvAdd4[ADDRESSLEN] = '\0';
			for (i = ADDRESSLEN - 1; i>= 0; i--) {
				if (!isblank(pModuleStr->recvAdd1[i])) {
					break;
				}
				else {
					pModuleStr->recvAdd1[i] = '\0';
				}
			}
			for (i = ADDRESSLEN - 1; i>= 0; i--) {
				if (!isblank(pModuleStr->recvAdd2[i])) {
					break;
				}
				else {
					pModuleStr->recvAdd2[i] = '\0';
				}
			}
			for (i = ADDRESSLEN - 1; i>= 0; i--) {
				if (!isblank(pModuleStr->recvAdd3[i])) {
					break;
				}
				else {
					pModuleStr->recvAdd3[i] = '\0';
				}
			}
			for (i = ADDRESSLEN - 1; i>= 0; i--) {
				if (!isblank(pModuleStr->recvAdd4[i])) {
					break;
				}
				else {
					pModuleStr->recvAdd4[i] = '\0';
				}
			}
		}
		if (!isblank(pGwyStr->inputMessage[CHRGADDPOS])) {
			strncpy(pModuleStr->chrgAdd1, (char*) &(pGwyStr->inputMessage[CHRGADDPOS]), ADDRESSLEN);
			pModuleStr->chrgAdd1[ADDRESSLEN] = '\0';
			strncpy(pModuleStr->chrgAdd2, (char*) &(pGwyStr->inputMessage[CHRGADDPOS  + ADDRESSLEN]), ADDRESSLEN);
			pModuleStr->chrgAdd2[ADDRESSLEN] = '\0';
			strncpy(pModuleStr->chrgAdd3, (char*) &(pGwyStr->inputMessage[CHRGADDPOS  + 2*ADDRESSLEN]), ADDRESSLEN);
			pModuleStr->chrgAdd3[ADDRESSLEN] = '\0';
			strncpy(pModuleStr->chrgAdd4, (char*) &(pGwyStr->inputMessage[CHRGADDPOS  + 3*ADDRESSLEN]), ADDRESSLEN);
			pModuleStr->chrgAdd4[ADDRESSLEN] = '\0';
			for (i = ADDRESSLEN - 1; i>= 0; i--) {
				if (!isblank(pModuleStr->chrgAdd1[i])) {
					break;
				}
				else {
					pModuleStr->chrgAdd1[i] = '\0';
				}
			}
			for (i = ADDRESSLEN - 1; i>= 0; i--) {
				if (!isblank(pModuleStr->chrgAdd2[i])) {
					break;
				}
				else {
					pModuleStr->chrgAdd2[i] = '\0';
				}
			}
			for (i = ADDRESSLEN - 1; i>= 0; i--) {
				if (!isblank(pModuleStr->chrgAdd3[i])) {
					break;
				}
				else {
					pModuleStr->chrgAdd3[i] = '\0';
				}
			}
			for (i = ADDRESSLEN - 1; i>= 0; i--) {
				if (!isblank(pModuleStr->chrgAdd4[i])) {
					break;
				}
				else {
					pModuleStr->chrgAdd4[i] = '\0';
				}
			}
		}
	}

	pModuleStr->nameKeyFromPA[0] = '\0';
	pModuleStr->cidFromPA[0] = '\0';
	if (!isblank(pGwyStr->inputMessage[NAMEKEYCIDINDPOS])) {
		if (pGwyStr->inputMessage[NAMEKEYCIDINDPOS] == 'N') {
			if (strncmp(&(pGwyStr->inputMessage[NAMEKEYPOS]), "NOTONCIF", strlen("NOTONCIF"))) {
				strncpy(pModuleStr->nameKeyFromPA, (char*) &(pGwyStr->inputMessage[NAMEKEYPOS]), NAMEKEYLEN);
				pModuleStr->nameKeyFromPA[NAMEKEYLEN] = '\0';
			}
		}
		else if (pGwyStr->inputMessage[NAMEKEYCIDINDPOS] == 'C') {
			strncpy(pModuleStr->cidFromPA, (char*) &(pGwyStr->inputMessage[NAMEKEYPOS]), CIDLEN);
			pModuleStr->cidFromPA[CIDLEN] = '\0';
		}
	}


	pt = &(pGwyStr->inputMessage[REJECTPOS]);

	if ((pModuleStr->transformInternalFmt) || (pModuleStr->transformInternalFmtLocal)) {
		if (pt[0] == 'I') {
			pModuleStr->invalidPassArea = false;
		}
		else {
			pModuleStr->invalidPassArea = true;
		}
	}
	else {
		if (pt[0] == 'S') {
			pModuleStr->invalidPassArea = false;
		}
		else {
			pModuleStr->invalidPassArea = true;
		}
	}

	tracing(TRACE_LEVEL_1, "APPISN getAsn", "ended");
	return;
}

void setPassArea(PGWYSTR pGwyStr) {
	char tmpChar;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "SWFAPPISN setPassArea", "started");

	strcpy(pGwyStr->outputMessage,"PASSAREA");
	strcat(pGwyStr->outputMessage,"|");
	strcat(pGwyStr->outputMessage,PASSAREALENSTR);
	strcat(pGwyStr->outputMessage,"|");
	strcat(pGwyStr->outputMessage,pModuleStr->correlationData);
	strcat(pGwyStr->outputMessage,"\r\n");
	tmpChar = pGwyStr->inputMessage[PASSAREALEN];
	pGwyStr->inputMessage[PASSAREALEN] = '\0';
	strcat(pGwyStr->outputMessage,pGwyStr->inputMessage);
	pGwyStr->inputMessage[PASSAREALEN] = tmpChar;

	tracing(TRACE_LEVEL_1, "APPISN setPassArea", "ended");
}


void setupTEO(PGWYSTR pGwyStr) {

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN setupTEO", "started");

	pModuleStr->handleTEO = false;
	pModuleStr->ibrOnly = false;
	if ((pGwyStr->inputMessage[SRFLAGPOS] == 'M') || (pGwyStr->inputMessage[FSINDPOS] == 'E')) {
//	if (pGwyStr->inputMessage[SRFLAGPOS] == 'M') {
		strncpy((pModuleStr->pCitTEOStr) ->bnyTRn,&(pGwyStr->inputMessage[BNYTRNPOS]),BNYTRNLEN);
		(pModuleStr->pCitTEOStr) -> bnyTRn[BNYTRNLEN] = '\0';
		strncpy((pModuleStr->pCitTEOStr) -> custId,&(pGwyStr->inputMessage[CUSTIDPOS]),CUSTIDLEN);
		(pModuleStr->pCitTEOStr) -> custId[CUSTIDLEN] = '\0';
		strncpy((pModuleStr->pCitTEOStr) -> rcvAdd1,&(pGwyStr->inputMessage[RCVADD1POS]),RCVADD1LEN);
		(pModuleStr->pCitTEOStr) -> rcvAdd1[RCVADD1LEN] = '\0';
		strncpy((pModuleStr->pCitTEOStr) -> rcvAdd2,&(pGwyStr->inputMessage[RCVADD2POS]),RCVADD2LEN);
		(pModuleStr->pCitTEOStr) -> rcvAdd2[RCVADD2LEN] = '\0';
		pModuleStr->handleTEO = true;
		pModuleStr->ibrOnly = true;
		strcpy(pModuleStr->desApp,TEO);
	}
	tracing(TRACE_LEVEL_1, "APPISN setupTEO", "ended");
	return;
}

void setupNameKey(PGWYSTR pGwyStr) {
	NAMEKEYSTR nameKeyStr;
	PNAMEKEYSTR pNameKeyStr;
	char mtType[MTTYPELEN + 1];
	char nameKeyAsn[ORGASNLEN + 1];
	char nameKeyTrn[ORGTRNLEN + 1];
	bool invalidBIC = false;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN setupNameKey", "started");

	pModuleStr->handleNameKey = false;
	pModuleStr->ibrOnly = false;

	if (pModuleStr->messageFormat == ISTDFORMAT)  {
		if (pModuleStr->nameKey[0] == '\0') {
			tracing(TRACE_LEVEL_1, "APPISN setupNameKey", "ended");
			return;
		}
	}
	strcpy(nameKeyStr.nameKey,"XXXXXXXXXXXXXXX");
	pNameKeyStr = (PNAMEKEYSTR) bsearch (&nameKeyStr,
									pModuleStr->pNameKeyStr,
									pModuleStr->numberOfNameKeys,
									sizeof (NAMEKEYSTR),
									nameKeyComparator);
	if (pNameKeyStr != NULL){
		if (pModuleStr->messageFormat == ISTDFORMAT)  {
			strcpy(nameKeyTrn,pModuleStr->trnPrefix);
		}
		else {
			strncpy(nameKeyTrn, &(pGwyStr->inputMessage[ORGTRNPOS]),ORGTRNLEN);
			nameKeyTrn[ORGASNLEN] = '\0';
		}

		if (pModuleStr->messageFormat == ISTDFORMAT)  {
			strcpy(mtType,pModuleStr->mtType);
		}
		else {
			strncpy(mtType, &(pGwyStr->inputMessage[MTTYPEPOS]),MTTYPELEN);
			mtType[MTTYPELEN] = '\0';
		}

		for (int i = 0; i < pNameKeyStr->numberOfRows; i++) {
			bool matchTrn = false;
			if ((pNameKeyStr->pNameKeyRowStr[i]).nameKeyTrn[0] == '\0') {
				matchTrn = true;
			}
			else {
				if (!strcmp((pNameKeyStr->pNameKeyRowStr[i]).nameKeyTrn,nameKeyTrn)) {
					matchTrn = true;
				}
			}
			if (matchTrn) {
				if ((pNameKeyStr->pNameKeyRowStr[i]).mtType[0] == '\0') {
					pModuleStr->handleNameKey = true;
					pModuleStr->ibrOnly = true;
					strcpy(pModuleStr->nameKeyOutputQueue,(pNameKeyStr->pNameKeyRowStr[i]).outputQueue);
					break;
				}
				else if (!strcmp((pNameKeyStr->pNameKeyRowStr[i]).mtType,mtType)) {
					pModuleStr->handleNameKey = true;
					pModuleStr->ibrOnly = true;
					strcpy(pModuleStr->nameKeyOutputQueue,(pNameKeyStr->pNameKeyRowStr[i]).outputQueue);
					break;
				}
			}
		}
	}
	if (!pModuleStr->handleNameKey) {
		if (pModuleStr->nameKey[0] != '\0') {
			strcpy(nameKeyStr.nameKey,pModuleStr->nameKey);
		}
		else {
			strncpy(nameKeyStr.nameKey,&(pGwyStr->inputMessage[NAMEKEYPOS]),NAMEKEYLEN);
			nameKeyStr.nameKey[NAMEKEYLEN] = '\0';
		}

		if (strcmp(nameKeyStr.nameKey,"XXXXXXXXXXXXXXX")) {
			pNameKeyStr = (PNAMEKEYSTR) bsearch (&nameKeyStr,
												pModuleStr->pNameKeyStr,
												pModuleStr->numberOfNameKeys,
												sizeof (NAMEKEYSTR),
												nameKeyComparator);
			if (pNameKeyStr != NULL){
				if (pModuleStr->messageFormat == ISTDFORMAT)  {
					strcpy(nameKeyAsn,pModuleStr->trnPrefix);
				}
				else {
					strncpy(nameKeyAsn, &(pGwyStr->inputMessage[ORGASNPOS]),ORGASNLEN);
					nameKeyAsn[ORGASNLEN] = '\0';
				}
				if (pModuleStr->messageFormat == ISTDFORMAT)  {
					strcpy(mtType,pModuleStr->mtType);
				}
				else {
					strncpy(mtType, &(pGwyStr->inputMessage[MTTYPEPOS]),MTTYPELEN);
					mtType[MTTYPELEN] = '\0';
				}
				if ((pModuleStr->messageFormat != ISTDFORMAT) && (pGwyStr->inputMessage[SRFLAGPOS] == 'E')) {
					pModuleStr->handleNameKey = true;
					pModuleStr->ibrOnly = true;
					strcpy(pModuleStr->nameKeyOutputQueue,EDIMGOUT);
				}
				if ((pModuleStr->messageFormat == ISTDFORMAT) || ((pModuleStr->messageFormat != ISTDFORMAT) && (pGwyStr->inputMessage[SRFLAGPOS] != 'E'))) {
					for (int i = 0; i < pNameKeyStr->numberOfRows; i++) {
						bool matchAsn = false;
						if ((pNameKeyStr->pNameKeyRowStr[i]).nameKeyAsn[0] == '\0') {
							matchAsn = true;
						}
						else {
							if (!strcmp((pNameKeyStr->pNameKeyRowStr[i]).nameKeyAsn,nameKeyAsn)) {
								matchAsn = true;
							}
						}
						if (matchAsn) {
							if ((pNameKeyStr->pNameKeyRowStr[i]).mtType[0] == '\0') {
								pModuleStr->handleNameKey = true;
								pModuleStr->ibrOnly = true;
								strcpy(pModuleStr->nameKeyOutputQueue,(pNameKeyStr->pNameKeyRowStr[i]).outputQueue);
								break;
							}
							else if (!strcmp((pNameKeyStr->pNameKeyRowStr[i]).mtType,mtType)) {
								pModuleStr->handleNameKey = true;
								pModuleStr->ibrOnly = true;
								strcpy(pModuleStr->nameKeyOutputQueue,(pNameKeyStr->pNameKeyRowStr[i]).outputQueue);
								break;
							}
						}
					}
				}
			}
		}
	}
	if (pModuleStr->handleNameKey) {
		if (pModuleStr->messageFormat == ISTDFORMAT)  {
			char* pBlock2 = strstr(pGwyStr->inputMessage,"{2:");
			//strncpy(pModuleStr->rcvBic12,&(pBlock2[B2ILTPOS]),BIC12LEN);
			strncpy(&(pBlock2[B2ILTPOS]),"IRVTUS3NAXXX",BIC12LEN);
		}
		else if ((pModuleStr->cusIndId != 'b') && (pModuleStr->cusIndId != 'B') && (pModuleStr->cusIndId != ' ')) {
			strncpy(pModuleStr->rcvBic12,&(pGwyStr->inputMessage[SWFADDRESSPOS]),BIC8LEN);
			pModuleStr->rcvBic12[BIC8LEN] = 'X';
			strncpy(&(pModuleStr->rcvBic12[BIC8LEN+1]),&(pGwyStr->inputMessage[SWFADDRESSPOS + BIC8LEN]),BRANCHLEN);
			pModuleStr->rcvBic12[BIC12LEN] = '\0';
		}
		int i;
		bool findBlank = false;
		for (i = 0; i < BIC8LEN; i++) {
			if (isblank(pModuleStr->rcvBic12[i])) {
				findBlank = true;
				break;
			}
		}
		if (findBlank) {
			strcpy(pModuleStr->rcvBic12,"XXXXXXXXXXXX");
		}
		findBlank = false;
		for (i = BIC8LEN + 1; i < BIC12LEN; i++) {
			if (isblank(pModuleStr->rcvBic12[i])) {
				findBlank = true;
				break;
			}
		}
		if (findBlank) {
			strncpy(&(pModuleStr->rcvBic12[BIC8LEN+1]),"XXX",BRANCHLEN);
		}
	}
	tracing(TRACE_LEVEL_1, "APPISN setupNameKey", "ended");
	return;
}

void switchToIBR(PGWYSTR pGwyStr) {
	char* pBlock2;
	int i;
	char mtType[MTTYPE_LEN + 1];
	char sndBic8Name[BIC8LEN + 1];
	char sndSubBranch[BRANCHLEN + 1];
	char desBic8Name[BIC8LEN + 1];
	char desSubBranch[BRANCHLEN + 1];
	char desApp[DESAPPLEN+1];
	char desDirection[DESDIRLEN+1];
	SWITCHIBRSTR switchIBRStr;
	PSWITCHIBRSTR pSwiftIBRStr;
	PBIC11STR pBic11Str;
	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN switchToIBR", "started");

	pModuleStr->setSwitchToIBR = false;
	pModuleStr->desAppPerMsg[0] = '\0';
	pModuleStr->desDirectionPerMsg[0] = '\0';

	if (pModuleStr->numberOfSwiftIBRStr == 0) {
		strncpy(pModuleStr->rcvBic12,&(pGwyStr->inputMessage[B1BIC8POS]),BIC12LEN);
		pModuleStr->rcvBic12[BIC12LEN] = '\0';
		strncpy(&(pGwyStr->inputMessage[B1BIC8POS]),"IRVTUS3NAXXX",BIC12LEN);

		pBlock2 = strstr(pGwyStr->inputMessage, "{2:");
		if (pBlock2 != NULL) {
			strncpy(&(pBlock2[B2ILTPOS]),"IRVTUS3N",BIC8LEN);
		}
		pModuleStr->setSwitchToIBR = true;
	}
	else {
		pBlock2 = strstr(pGwyStr->inputMessage, "{2:");
		strncpy(switchIBRStr.mtType, &(pBlock2[B2MTTYPEPOS]),MTTYPELEN);
		switchIBRStr.mtType[MTTYPELEN] = '\0';
		pSwiftIBRStr = (PSWITCHIBRSTR) bsearch (&switchIBRStr,
										pModuleStr->pSwiftIBRStr,
										pModuleStr->numberOfSwiftIBRStr,
										sizeof (SWITCHIBRSTR),
										mtTypeSwitchIBRComparator);
		if (pSwiftIBRStr != NULL) {
			strncpy(sndBic8Name,&(pGwyStr->inputMessage[B1BIC8POS]),BIC8LEN);
			sndBic8Name[BIC8LEN] = '\0';

			bool findFlag = false;
			pBic11Str = pSwiftIBRStr->pBic11Str;
			strncpy(sndSubBranch,&(pGwyStr->inputMessage[B1BIC8POS + BIC8LEN + 1]),BRANCHLEN);
			sndSubBranch[BRANCHLEN] = '\0';
			for (i = 0; i < pSwiftIBRStr->numberOfBic11Str; i++) {
				if (pBic11Str[i].sndBic8Name[0] != '\0') {
					if (strcmp(sndBic8Name,pBic11Str[i].sndBic8Name)) {
						continue;
					}
				}
				if (pBic11Str[i].sndSubBranch[0] != '\0') {
					if (strcmp(sndSubBranch,pBic11Str[i].sndSubBranch)) {
						continue;
					}
				}
				if (pBic11Str[i].desBic8Name[0] != '\0') {
					desBic8Name[0] = '\0';
					if (pBlock2 != NULL) {
						strncpy(desBic8Name,&(pBlock2[B2ILTPOS]),BIC8LEN);
						desBic8Name[BIC8LEN] = '\0';
					}
					if (strcmp(desBic8Name,pBic11Str[i].desBic8Name)) {
						continue;
					}
				}
				if (pBic11Str[i].desSubBranch[0] != '\0') {
					desSubBranch[0] = '\0';
					if (pBlock2 != NULL) {
						strncpy(desSubBranch,&(pBlock2[B2ILTPOS + BIC8LEN + 1]),BRANCHLEN);
						desSubBranch[BRANCHLEN] = '\0';
					}
					if (strcmp(desSubBranch,pBic11Str[i].desSubBranch)) {
						continue;
					}
				}

				findFlag = true;
				if (pBic11Str[i].desDirection[0] != '\0') {
					strcpy(pModuleStr->desDirectionPerMsg,pBic11Str[i].desDirection);
				}
				if (pBic11Str[i].desApp[0] != '\0') {
					strcpy(pModuleStr->desAppPerMsg,pBic11Str[i].desApp);
				}
				break;
			}
			if (findFlag) {
				strncpy(pModuleStr->rcvBic12,&(pBlock2[B2ILTPOS]),BIC12LEN);
				pModuleStr->rcvBic12[BIC12LEN] = '\0';
				strncpy(&(pGwyStr->inputMessage[B1BIC8POS]),sndBic8Name,BIC8LEN);
				strncpy(&(pGwyStr->inputMessage[B1BIC8POS + BIC8LEN]),"AXXX",4);
				if (pBlock2 != NULL) {
					strncpy(&(pBlock2[B2ILTPOS]),sndBic8Name,BIC8LEN);
					strncpy(&(pBlock2[B2ILTPOS + BIC8LEN]),"X",1);
					strncpy(&(pBlock2[B2ILTPOS + BIC8LEN + 1]),sndSubBranch,BRANCHLEN);
				}
				pModuleStr->setSwitchToIBR = true;
			}
			else {
				pModuleStr->setSwitchToIBR = false;
			}
		}
		else {
			pModuleStr->setSwitchToIBR = false;
		}
	}

	tracing(TRACE_LEVEL_1, "APPISN switchToIBR", "ended");
}

void setupCIBC(PGWYSTR pGwyStr) {
	CTime currentTime;
	char strBlock4[20000];
	char header[2048];
	char* pt;
	char* ptEnd;
	int len;
	char tmpChar;
	char* sBlock = "{S:";
	char* sSource = "{SRC:";
	char* sMsgtrace = "{MSGTRACE:";
	char* sEnd = "}";
	char* sAppId = "{APP:";
	char* sPrio = "{PRIO:";
	char* sSrcSeq = "{SOURCEREFERENCE:";
	char* sErrCode = "{ERRCODE:";
	char* sOrgMTSTrn = "{ORGMTSTRN:";
	char* sDte = "{DTE:";
	char* sMrvTrc = "{MRVTRC:";
	char* sFROMSEQ = "{FROMSEQ:";
	char* sOrgRcvBIC = "{ORGRCVBIC:";
	char* sSOURCEAPP = "{SOURCEAPP:";
	char* sDESOUTPUTQ = "{DESOUTPUTQ:";
	char* sDESDIR = "{DESDIRECTION:";
	char* sFromTime = "{FROMTIME:";
	char* sMTSHDR = "{H:{TYP:SWF}}";
	char* sOUTSRCCODE = "{OUTSRCCODE:";

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN setupCIBC", "started");

	strcpy(header,sMTSHDR);
	if (pModuleStr->convertBic8) {
		strcat(header,"{1:F01IRVTUS30AXXX0000000000}");
	}
	else {
		strcat(header,"{1:F01IRVTUS3NAXXX0000000000}");
	}
	strcat(header,"{2:I");
	len = strlen(header);
	strncat(header,&(pGwyStr->inputMessage[CIBCMTTYPEPOS]),CIBCMTTYPELEN);
	len += CIBCMTTYPELEN;
	header[len] = '\0';
	if (pModuleStr->convertBic8) {
		strcat(header,"IRVTUS30AXXXN}{3:{113:OBNY}{108:");
	}
	else {
		strcat(header,"IRVTUS3NAXXXN}{3:{113:OBNY}{108:");
	}
	len = strlen(header);
	strncat(header,&(pGwyStr->inputMessage[FROMADDRPOS]),BIC8LEN);
	len += BIC8LEN;
	header[len] = '\0';
	strncat(header,&(pGwyStr->inputMessage[FROMADDRPOS + BIC8LEN + 1]),BRANCHLEN);
	len += BRANCHLEN;
	header[len] = '\0';
	strcat(header,"}}{4:\r\n");
	len = strlen(header);
	strcpy(pGwyStr->outputMessage,header);
	pt = &(pGwyStr->inputMessage[MSGTEXTPOS]);
	int m = 0;
	char* pt1 = pt;
	while (1) {
		if (pt1[0] != '-') {
			strBlock4[m++] = pt1[0];
			pt1++;
		}
		else if (pt1[1] != '\3') {
			char* pt2 = &(pt1[1]);
			if (strncmp(pt2,PDE,PDELEN)){
				strBlock4[m++] = pt1[0];
				pt1++;
			}
			else {
				int j = 0;
				bool fidPDE = false;
				char pdeBuf[512];
				pt2 = pt2 + PDELEN;
				while (1) {
					if (pt2[0] != '\3') {
						pdeBuf[j++] = pt2[0];
						pt2++;
					}
					else {
						pdeBuf[j] = '\0';
						strBlock4[m] = '\0';
						strcat(pGwyStr->outputMessage,strBlock4);
						strcat(pGwyStr->outputMessage,"-}{5:{PDE:");
						strcat(pGwyStr->outputMessage,pdeBuf);
						strcat(pGwyStr->outputMessage,"}}{S:");
						fidPDE = true;
						break;
					}
				}
				if (fidPDE) {
					break;
				}
			}
		}
		else {
			strBlock4[m] = '\0';
			strcat(pGwyStr->outputMessage,strBlock4);
			strcat(pGwyStr->outputMessage,"-}{5:}{S:");
			break;
		}
	}

/*	ptEnd = strstr(pt,MSGENDPDE);
	if (ptEnd == NULL) {
		ptEnd = strstr(pt,MSGEND);
		if (ptEnd != NULL) {
			tmpChar = ptEnd[0];
			ptEnd[0] = '\0';
			strcat(pGwyStr->outputMessage,pt);
			strcat(pGwyStr->outputMessage,"-}{5:}{S:");
			ptEnd[0] = tmpChar;

		}
	}
	else {
		tmpChar = ptEnd[0];
		ptEnd[0] = '\0';
		strcat(pGwyStr->outputMessage,pt);
		strcat(pGwyStr->outputMessage,"-}{5:{PDE:");
		ptEnd[0] = tmpChar;
		pt = ptEnd;
		ptEnd = strstr(pt,MSGENDAPDE);
		if (ptEnd != NULL) {
			tmpChar = ptEnd[0];
			ptEnd[0] = '\0';
			strcat(pGwyStr->outputMessage,pt);
			strcat(pGwyStr->outputMessage,sEnd);
			strcat(pGwyStr->outputMessage,sEnd);
		}
	}
	*/

	string dateTimeStr = currentTime.getDateTimeStr();
	sprintf(header,"CIBC%s",dateTimeStr.c_str());
	strcat(pGwyStr->outputMessage,sMsgtrace);
	strcat(pGwyStr->outputMessage,header);
	strcat(pGwyStr->outputMessage,sEnd);
	strcat(pGwyStr->outputMessage,sAppId);
	strcat(pGwyStr->outputMessage,"CIBC");
	strcat(pGwyStr->outputMessage,sEnd);
	strcat(pGwyStr->outputMessage,sSOURCEAPP);
	strcat(pGwyStr->outputMessage,"CIBC");
	strcat(pGwyStr->outputMessage,sEnd);
	strcat(pGwyStr->outputMessage,sOUTSRCCODE);
	strcat(pGwyStr->outputMessage,"001");
	strcat(pGwyStr->outputMessage,sEnd);
	strcat(pGwyStr->outputMessage,sSource);
	strcat(pGwyStr->outputMessage,"RUA");
	strcat(pGwyStr->outputMessage,sEnd);
	strncpy(header,&(pGwyStr->inputMessage[SRCREFPOS]),SRCREFLEN);
	header[SRCREFLEN] = '\0';
	strcat(pGwyStr->outputMessage,sSrcSeq);
	strcat(pGwyStr->outputMessage,header);
	strcat(pGwyStr->outputMessage,sEnd);
	strncpy(header,&(pGwyStr->inputMessage[TOADDRPOS]),TOADDRLEN);
	header[TOADDRLEN] = '\0';
	strcat(pGwyStr->outputMessage,sOrgRcvBIC);
	strcat(pGwyStr->outputMessage,header);
	strcat(pGwyStr->outputMessage,sEnd);
	strncpy(header,&(pGwyStr->inputMessage[FROMSEQPOS]),FROMSEQLEN);
	header[FROMSEQLEN] = '\0';
	strcat(pGwyStr->outputMessage,sFROMSEQ);
	strcat(pGwyStr->outputMessage,header);
	strcat(pGwyStr->outputMessage,sEnd);
	strncpy(header,&(pGwyStr->inputMessage[FROMTIMESTAMPPOS]),FROMTIMESTAMPLEN);
	header[FROMTIMESTAMPLEN] = '\0';
	strcat(pGwyStr->outputMessage,sFromTime);
	strcat(pGwyStr->outputMessage,header);
	strcat(pGwyStr->outputMessage,sEnd);
	strcat(pGwyStr->outputMessage,sEnd);

	tracing(TRACE_LEVEL_1, "APPISN setupCIBC", "ended");
	return;
}


void createHeaderBlock(PGWYSTR pGwyStr) {
	char tmpChar;
	char* pBlock4;
	char* pBlock3;
	char* pBlock2;
	char header[2048];
	int len;
	char subBranch[SBCHLEN + 1];
	bool isBlank;
	char* pBlock1;
	char strBlock4[20000];
	char block3Buf[TAG108LEN + 1];
	bool hasBlock3;
	char allBlock3Buf[256];
	char* pt;
	OUTSRCSTR outSrcStr;
	POUTSRCSTR pOutSrcStr;
	char bic12[SWFADDRESSLEN + 1];
	char tBic12[BIC12LEN + 1];
	int msgLen;
	char bic8[BIC8LEN + 1];
	bool usePassArea = false;
	char tmpBuf[256];
	char* pt1;
	char* pMetaData = NULL;
	char* pMetaDataEnd = NULL;
	char* pMetaData1 = NULL;


	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN createHeaderBlock", "started");

	pMetaData = NULL;
	pMetaDataEnd = NULL;
	pMetaData1 = NULL;

	if (pModuleStr->handleOutSrc) {
		strcpy(header,"{1:F01");
		strcpy(pModuleStr->senderBic8,"IRVTUS3N");
		strcat(header,pModuleStr->senderBic8);
		strcat(header,"AXXX0000000000}");
		len = strlen(header);
		strcat(header,"{2:I");
		len = len + IBLK2LEN;
		strncat(header,&(pGwyStr->inputMessage[MTTYPEPOS]),MTTYPELEN);
		len = len + MTTYPELEN;
		header[len] = '\0';
		if (!strcmp(pModuleStr->ourSrcCode,"001")) {
			strcat(header,"IRVTUS3N");
			strcpy(pModuleStr->rcvBic12,pModuleStr->outSrcBic);
			strcat(pModuleStr->rcvBic12,"AXXX");
			pModuleStr->handleCIBC = true;
		}
		else {
			strcat(header,pModuleStr->outSrcBic);
		}
		strcat(header,"XXXXN}");
		strcat(header,"{3:{113:OBNY}{108:");
		strncpy(bic12,&(pGwyStr->inputMessage[SWFADDRESSPOS]),SWFADDRESSLEN);
		bic12[SWFADDRESSLEN] = '\0';
		for (int j = SWFADDRESSLEN - 1; j >= 0; j--) {
			if (isblank(bic12[j])) {
				bic12[j] = '\0';
			}
			else {
				break;
			}
		}
		strcat(header,bic12);
		strcat(header,"}}");
		if ((pModuleStr->transformInternalFmt) || (pModuleStr->transformInternalFmtLocal)) {
			strcpy(strBlock4,"{4:\r\n");
			strcat(strBlock4,&(pGwyStr->inputMessage[PASSAREALEN]));
			msgLen = strlen(strBlock4);
			if (msgLen >= 2) {
				if ((strBlock4[msgLen - 2] == '\r') && (strBlock4[msgLen - 1] == '\n')) {
					strcat(strBlock4,"-}{5:}");
				}
				else {
					strcat(strBlock4,"\r\n-}{5:}");
				}
			}
			else {
				strcat(strBlock4,"\r\n-}{5:}");
			}
			//strcat(strBlock4,"\r\n-}{5:}");
			pGwyStr->inputMessage[PASSAREALEN] = '\0';
			strcpy(&(pGwyStr->inputMessage[PASSAREALEN]),header);
			strcat(pGwyStr->inputMessage,strBlock4);
		}
		else {
			pBlock4 = strstr(&(pGwyStr->inputMessage[PASSAREALEN]), "{4:");
			strcpy(strBlock4,pBlock4);
			pGwyStr->inputMessage[PASSAREALEN] = '\0';
			strcpy(&(pGwyStr->inputMessage[PASSAREALEN]),header);
			strcat(pGwyStr->inputMessage,strBlock4);
		}
		tracing(TRACE_LEVEL_1, "APPISN createHeaderBlock", "ended");
		return;
	}

	if (pModuleStr->keepSwfHeaderInfo) {
		pBlock1 = strstr(pGwyStr->inputMessage,"{1:");
		pBlock2 = strstr(pGwyStr->inputMessage,"{2:");
	}

	strcpy(header,"{1:F01");
	if (pModuleStr->senderBic8[0] == '\0') {
		strcpy(pModuleStr->senderBic8,"IRVTUS3N");
	}
	strcat(header,pModuleStr->senderBic8);
	strcat(header,"A");

	len = strlen(header);
	if (pModuleStr->keepSwfHeaderInfo) {
		strncpy(subBranch,&(pBlock1[B1BIC8POS + BIC8LEN + 1]),SBCHLEN);
		subBranch[SBCHLEN] = '\0';
	}
	else {
		strncpy(subBranch,&(pGwyStr->inputMessage[HB1SBCHPOS]),SBCHLEN);
		subBranch[SBCHLEN] = '\0';
		isBlank = true;
		for (int i = 0; i < SBCHLEN; i++) {
			if (!isblank(subBranch[i])) {
				isBlank = false;
				break;
			}
		}
		if (isBlank) {
			strcpy(subBranch,"XXX");
		}
	}
	strcat(header,subBranch);

	len = len + SBCHLEN;
	header[len] = '\0';
	strcat(header,"0000000000}");
	len = len + SESSSEQLEN;

	if (pModuleStr->keepSwfHeaderInfo) {
		pt = strstr(pBlock2,"}");
		pt[0] = '\0';
		strcat(header,pBlock2);
		strcat(header,"}");
		len = strlen(header);
		pt[0] = '}';
	}
	else {
		strcat(header,"{2:I");
		len = len + IBLK2LEN;

		if (pModuleStr->checkErrStatusInPassarea) {
			pModuleStr->handleErrInPassarea = false;
			pModuleStr->failToTransform = false;
			if (!strncmp(&(pGwyStr->inputMessage[ERRSTATUSPOS]), CASFMTERR, strlen(CASFMTERR))) {
				char mtType[MTTYPELEN + 1];
				pModuleStr->handleErrInPassarea = true;
				pModuleStr->failToTransform = true;
				strncpy(pModuleStr->orgMTType,&(pGwyStr->inputMessage[MTTYPEPOS]),MTTYPELEN);
				pModuleStr->orgMTType[MTTYPELEN] = '\0';
				strcpy(mtType,pModuleStr->orgMTType);
				strncpy(&mtType[1],"98",2);
				strncat(header,mtType,MTTYPELEN);
				strcpy(pModuleStr->errMsg,TRANSFORMERR);
			}
			else {
				strncat(header,&(pGwyStr->inputMessage[MTTYPEPOS]),MTTYPELEN);
			}
		}
		else {
			strncat(header,&(pGwyStr->inputMessage[MTTYPEPOS]),MTTYPELEN);
		}
		len = len + MTTYPELEN;
		header[len] = '\0';

		strncpy(subBranch,&(pGwyStr->inputMessage[HB2SBCHPOS]),SBCHLEN);
		subBranch[3] = '\0';

		if (pModuleStr->ibrOnly) {
			strcat(header,"IRVTUS3N");
			len = len + BIC8LEN;
			header[len] = '\0';
			strcat(header,"X");
			len = len + 1;
			strncpy(subBranch,&(pGwyStr->inputMessage[HB2SBCHPOS]),SBCHLEN);
			subBranch[SBCHLEN] = '\0';
			isBlank = true;
			for (int i = 0; i < SBCHLEN; i++) {
				if (!isblank(subBranch[i])) {
					isBlank = false;
					break;
				}
			}
			if (isBlank) {
				strcpy(subBranch,"XXX");
			}
			strcat(header,subBranch);
			len = len + SBCHLEN;
		}
		else {
			strncpy(tBic12,&(pGwyStr->inputMessage[HB2BIC8POS]),BIC8LEN);
			tBic12[BIC8LEN] = 'X';
			tBic12[BIC8LEN + 1] = '\0';
			strncpy(subBranch,&(pGwyStr->inputMessage[HB2SBCHPOS]),SBCHLEN);
			subBranch[SBCHLEN] = '\0';
			strcat(tBic12,subBranch);
			if ((pGwyStr->inputMessage[CUSTINDPOS] == 'S') || (pGwyStr->inputMessage[CUSTINDPOS] == 'Y')) {
				isBlank = true;
				for (int i = 0; i < SBCHLEN; i++) {
					if (!isblank(subBranch[i])) {
						isBlank = false;
						break;
					}
				}
				if (isBlank) {
					tBic12[BIC8LEN + 1] = '\0';
					strcat(tBic12,"XXX");
				}
			}
			else {
				isBlank = false;
				for (int i = 0; i < BIC12LEN; i++) {
					if (isblank(tBic12[i])) {
						isBlank = true;
						break;
					}
				}
				if (isBlank) {
					if ((pModuleStr->rcvBic12[0] != '\0') && (strcmp(pModuleStr->rcvBic12,"XXXXXXXXXXXX"))) {
						strcpy(tBic12,pModuleStr->rcvBic12);
					}
					else {
						isBlank = true;
						for (int i = 0; i < SBCHLEN; i++) {
							if (!isblank(subBranch[i])) {
								isBlank = false;
								break;
							}
						}
						if (isBlank) {
							tBic12[BIC8LEN + 1] = '\0';
							strcat(tBic12,"XXX");
						}
					}
				}
			}
			strcat(header,tBic12);
			len = len + BIC12LEN;
		}
		strcat(header,"N}");
		len = len + 2;

	}
	if (pModuleStr->block3Type == IBLOCK3TYPE1) {
		if (pModuleStr->createTag108) {
			strcat(header,"{3:{108:");
			len = len + 8;
			strncat(header, &(pGwyStr->inputMessage[TAG108TYP1POS]),TAG108LEN);
			len = len + TAG108LEN;
			header[len] = '\0';
			strcat(header,"}}");
			len = len + 2;
		}
	}
	else if ((pModuleStr->block3Type == IBLOCK3TYPE2)||(pModuleStr->block3Type == IBLOCK3TYPE3)) {
		hasBlock3 = false;
		allBlock3Buf[0] = '\0';
		pBlock3 = strstr(pGwyStr->inputMessage,BLOCK3);
		if (pModuleStr->block3Type == IBLOCK3TYPE3) {
			pt = NULL;
			if (pBlock3 != NULL)  {
				pt = strstr(pBlock3,"{113:GTM");
			}
			if (pt == NULL) {
				TRNPREFIXSTR trnPrefixStr;
				PTRNPREFIXSTR pTrnPrefixStr;

				strncpy(trnPrefixStr.trnPrefix, &(pGwyStr->inputMessage[TAG108TYP1POS]),TRNPREFIXLEN);
				trnPrefixStr.trnPrefix[TRNPREFIXLEN] = '\0';
				tracing(TRACE_LEVEL_1, "APPISN createHeaderBlock", "trnPrefix = " + toString(trnPrefixStr.trnPrefix));

				pTrnPrefixStr = (PTRNPREFIXSTR) bsearch (&trnPrefixStr,
										pModuleStr->pTrnPrefixStr,
										pModuleStr->numberOfTrnPrefix,
										sizeof (TRNPREFIXSTR),
										trnPrefixComparator);

				if (pTrnPrefixStr != NULL){
					strcat(allBlock3Buf,"{3:");
					hasBlock3 = true;
					strcat(allBlock3Buf,"{113:GTM }");
				}
			}
		}
		if (pBlock3 != NULL)  {
			pt = strstr(pBlock3,"{108:");
			if (pt == NULL) {
				strncpy(block3Buf, &(pGwyStr->inputMessage[B3T108POS]),TAG108LEN);
				block3Buf[TAG108LEN] = '\0';
				for (int j = TAG108LEN - 1; j >= 0; j--) {
					if (isblank(block3Buf[j])) {
						block3Buf[j] = '\0';
					}
					else {
						break;
					}
				}
				if (block3Buf[0] != '\0') {
					if (hasBlock3) {
						strcat(allBlock3Buf,"{108:");
						hasBlock3 = true;
					}
					else {
						strcat(allBlock3Buf,"{3:{108:");
						hasBlock3 = true;
					}
					strcat(allBlock3Buf, block3Buf);
					strcat(allBlock3Buf, "}");
				}
				else {
					strncat(block3Buf, &(pGwyStr->inputMessage[TAG108TYP1POS]),TAG108LEN);
					block3Buf[TAG108LEN] = '\0';
					for (int j = TAG108LEN - 1; j >= 0; j--) {
						if (isblank(block3Buf[j])) {
							block3Buf[j] = '\0';
						}
						else {
							break;
						}
					}
					if (block3Buf[0] != '\0') {
						if (hasBlock3) {
							strcat(allBlock3Buf,"{108:");
							hasBlock3 = true;
						}
						else {
							strcat(allBlock3Buf,"{3:{108:");
							hasBlock3 = true;
						}
						strcat(allBlock3Buf, block3Buf);
						strcat(allBlock3Buf, "}");
					}
				}
			}
		}
		if (pBlock3 != NULL) {
			pBlock4 = strstr(pGwyStr->inputMessage,"{4:");
			if (!hasBlock3) {
				strcat(allBlock3Buf,"{3:");
			}
			pt = pBlock4 - 1;
			tmpChar = pt[0];
			pt[0] = '\0';
			strcat(allBlock3Buf,&pBlock3[strlen(BLOCK3)]);
			pt[0] = tmpChar;
			hasBlock3 = true;
		}
		pt = strstr(allBlock3Buf,"{108:");
		if (pt == NULL) {
			if (pModuleStr->createTag108) {
				strncpy(block3Buf, &(pGwyStr->inputMessage[B3T108POS]),TAG108LEN);
				block3Buf[TAG108LEN] = '\0';
				for (int j = TAG108LEN - 1; j >= 0; j--) {
					if (isblank(block3Buf[j])) {
						block3Buf[j] = '\0';
					}
					else {
						break;
					}
				}
				if (block3Buf[0] != '\0') {
					if (hasBlock3) {
						strcat(allBlock3Buf,"{108:");
						hasBlock3 = true;
					}
					else {
						strcat(allBlock3Buf,"{3:{108:");
						hasBlock3 = true;
					}
					strcat(allBlock3Buf, block3Buf);
					strcat(allBlock3Buf, "}");
				}
				else {
					strncat(block3Buf, &(pGwyStr->inputMessage[TAG108TYP1POS]),TAG108LEN);
					block3Buf[TAG108LEN] = '\0';
					for (int j = TAG108LEN - 1; j >= 0; j--) {
						if (isblank(block3Buf[j])) {
							block3Buf[j] = '\0';
						}
						else {
							break;
						}
					}
					if (block3Buf[0] != '\0') {
						if (hasBlock3) {
							strcat(allBlock3Buf,"{108:");
							hasBlock3 = true;
						}
						else {
							strcat(allBlock3Buf,"{3:{108:");
							hasBlock3 = true;
						}
						strcat(allBlock3Buf, block3Buf);
						strcat(allBlock3Buf, "}");
					}
				}
			}
		}
		pt = strstr(allBlock3Buf,"{103:");
		if (pt == NULL) {
			strncpy(block3Buf, &(pGwyStr->inputMessage[B3T103POS]),TAG103LEN);
			block3Buf[TAG103LEN] = '\0';
			for (int j = TAG103LEN - 1; j >= 0; j--) {
				if (isblank(block3Buf[j])) {
					block3Buf[j] = '\0';
				}
				else {
					break;
				}
			}
			if (block3Buf[0] != '\0') {
				if (allBlock3Buf[0] == '\0') {
					strcat(allBlock3Buf,"{3:{103:");
					strcat(allBlock3Buf, block3Buf);
					strcat(allBlock3Buf, "}");
				}
				else {
					pt1 = &(allBlock3Buf[3]);
					strcpy(tmpBuf,pt1);
					pt1 [0] = '\0';
					strcat(allBlock3Buf,"{103:");
					strcat(allBlock3Buf, block3Buf);
					strcat(allBlock3Buf, "}");
					strcat(allBlock3Buf, tmpBuf);
				}
				hasBlock3 = true;
			}
		}
		pt = strstr(allBlock3Buf,"{113:");
		if (pt == NULL) {
			strncpy(block3Buf, &(pGwyStr->inputMessage[B3T113POS]),TAG113LEN);
			block3Buf[TAG113LEN] = '\0';
			isBlank = true;
			for (int j = 0; j < TAG113LEN; j++) {
				if (!isblank(block3Buf[j])) {
					isBlank = false;
					break;
				}
			}
			if (!isBlank) {
				if (hasBlock3) {
					pt1 = strstr(allBlock3Buf,"{108:");
					if (pt1 != NULL) {
						strcpy(tmpBuf,pt1);
						pt1 [0] = '\0';
						strcat(allBlock3Buf,"{113:");
						strcat(allBlock3Buf, block3Buf);
						strcat(allBlock3Buf, "}");
						strcat(allBlock3Buf, tmpBuf);
					}
					else {
						strcat(allBlock3Buf,"{113:");
						strcat(allBlock3Buf, block3Buf);
						strcat(allBlock3Buf, "}");
					}
					hasBlock3 = true;
				}
				else {
					strcat(allBlock3Buf,"{113:");
					strcat(allBlock3Buf, block3Buf);
					strcat(allBlock3Buf, "}");
					hasBlock3 = true;
				}
			}
		}

		pt = strstr(allBlock3Buf,"{119:");
		if (pt == NULL) {
			strncpy(block3Buf, &(pGwyStr->inputMessage[B3T119POS]),TAG119LEN);
			block3Buf[TAG119LEN] = '\0';
			for (int j = TAG119LEN - 1; j >= 0; j--) {
				if (isblank(block3Buf[j])) {
					block3Buf[j] = '\0';
				}
				else {
					break;
				}
			}
			if (block3Buf[0] != '\0') {
				if (hasBlock3) {
					strcat(allBlock3Buf,"{119:");
					hasBlock3 = true;
				}
				else {
					strcat(allBlock3Buf,"{3:{119:");
					hasBlock3 = true;
				}
				strcat(allBlock3Buf, block3Buf);
				strcat(allBlock3Buf, "}");
			}
		}
/*		pMetaData == NULL;
		pMetaDataEnd = NULL;
		if (pModuleStr->supportGPII) {
			pMetaData = strstr(pGwyStr->inputMessage,METADATA);
			if (pMetaData != NULL) {
				pMetaDataEnd = strstr(pMetaData,"}}");
			}
		}

		pModuleStr->metadfataBuff[0] = '\0';
		*/
		if (hasBlock3) {
			if (pModuleStr->metadfataBuff[0] == '\0') {
				strcat(header, allBlock3Buf);
				len = len + strlen(allBlock3Buf);
				strcat(header,"}");
				len = len + 1;
			}
			else {
				strcat(allBlock3Buf,pModuleStr->metadfataBuff);
				strcat(header, allBlock3Buf);
				len = len + strlen(allBlock3Buf);
				strcat(header,"}");
				len = len + 1;
			}
		}
		else {
			if (pModuleStr->metadfataBuff[0] == '\0') {
				strcpy(allBlock3Buf,pModuleStr->metadfataBuff);
				strcat(header, allBlock3Buf);
				len = len + strlen(allBlock3Buf);
				strcat(header,"}");
				len = len + 1;
			}
		}
	}


	if ((pModuleStr->transformInternalFmt) || (pModuleStr->transformInternalFmtLocal)) {
		strcpy(strBlock4,"{4:\r\n");
		strcat(strBlock4,&(pGwyStr->inputMessage[PASSAREALEN]));
		msgLen = strlen(strBlock4);
		if (msgLen >= 2) {
			if ((strBlock4[msgLen - 2] == '\r') && (strBlock4[msgLen - 1] == '\n')) {
				strcat(strBlock4,"-}{5:}");
			}
			else {
				strcat(strBlock4,"\r\n-}{5:}");
			}
		}
		else {
			strcat(strBlock4,"\r\n-}{5:}");
		}
		pGwyStr->inputMessage[PASSAREALEN] = '\0';
		strcpy(&(pGwyStr->inputMessage[PASSAREALEN]),header);
		strcat(pGwyStr->inputMessage,strBlock4);
	}
	else if (!pModuleStr->block4Only) {
		pBlock4 = strstr(&(pGwyStr->inputMessage[PASSAREALEN]), "{4:");
		strcpy(strBlock4,pBlock4);
		pGwyStr->inputMessage[PASSAREALEN] = '\0';
		if (pModuleStr->failToTransform) {
			strcpy(pGwyStr->inputMessage,header);
			strcat(pGwyStr->inputMessage,strBlock4);
		}
		else {
			strcpy(&(pGwyStr->inputMessage[PASSAREALEN]),header);
			strcat(pGwyStr->inputMessage,strBlock4);
		}
	}
	else {
		pBlock4 = &(pGwyStr->inputMessage[PASSAREALEN]);
		strcpy(strBlock4,"{4:\r\n");
		strcat(strBlock4,pBlock4);
		pGwyStr->inputMessage[PASSAREALEN] = '\0';
		if (pModuleStr->failToTransform) {
			strcpy(pGwyStr->inputMessage,header);
			strcat(pGwyStr->inputMessage,strBlock4);
		}
		else {
			strcpy(&(pGwyStr->inputMessage[PASSAREALEN]),header);
			strcat(pGwyStr->inputMessage,strBlock4);
		}
		strcat(pGwyStr->inputMessage,"-}{5:}");
	}

	pt = strstr(pGwyStr->inputMessage,"{113:GTM");
	if (pt != NULL) {
		/*if (!pModuleStr->firstGTMAck) {
			pModuleStr->firstGTMAck = true;
			registerGTMAckSvc(pGwyStr);
		}
		*/
		pModuleStr->gtmAck = false;
	}

	tracing(TRACE_LEVEL_1, "APPISN createHeaderBlock", "ended");
}


void replaceInvalidChar(PGWYSTR pGwyStr, char* pBlock4) {
	char* pt;
	char* pt1;
	char* pt2;
	bool loop = true;
	bool isBlank = false;
	bool isZero = false;
	char msgBuf[20000];
	char tmpBuf[12000];
	char* pLineEnd;
	bool newLine = false;
	int j = 0;
	int m =0;
	char tmpChar;
	int mutilLineTag = 0;
	int len;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "SWFAPPISN replaceInvalidChar", "started");

	pt = pBlock4 + 1;
	pt1 = pt + 1;
	if ((pt[2] != '\r') && (pt[3] != '\n')) {
		msgBuf[j++] = '4';
		msgBuf[j++] = ':';
		msgBuf[j++] = '\r';
		msgBuf[j++] = '\n';
		pt = pt + 2;
		pt1 = pt + 1;
	}
	while (loop) {
		if ((pt[0] == '-') && (pt1[0] == '}')) {
			msgBuf[j++] = '-';
			msgBuf[j++] = '}';
			msgBuf[j] = '\0';
			pt = pt + 2;
			strcpy(tmpBuf,pt);
			pt1 = pBlock4 + 1;
			strcpy(pt1,msgBuf);
			strcat(pt1,tmpBuf);
			break;
		}
		if (newLine) {
			pt1 = pt;
			isBlank = true;
			while (isBlank) {
				if ((pt1[0] == '\r') && (pt1[1] == '\n')) {
					break;
				}
				else if (pt1[0] == '\r') {
					isBlank = false;
					break;
				}
				else if (isblank(pt1[0])) {
					pt1++;
					continue;
				}
				else if (!isprint(pt1[0])) {
					pt1++;
					continue;
				}
				else {
					isBlank = false;
					break;
				}
			}
			if (isBlank) {
				pt = pt1 + 2;
				pt1 = pt + 1;
				if (mutilLineTag == 1) {
					mutilLineTag = 2;
				}
				continue;
			}
			else {
				pt1 = pt + 1;
			}
			if (!strncmp(pt,":61:",4)) {
				mutilLineTag = 1;
			}
			else if (pt[0] == ':') {
				mutilLineTag = 0;
			}
			if (isblank(pt[0]) && (mutilLineTag == 2)) {
				msgBuf[j++] = '.';
				msgBuf[j++] = '\r';
				msgBuf[j++] = '\n';
				mutilLineTag = 0;
			}
			if ((!strncmp(pt,":62M:",4)) ||(!strncmp(pt,":19A:",4))){
				pt1 = strstr(pt,",");
				pt1 = pt1 + 1;
				tmpChar = pt1[0];
				pt1[0] = '\0';
				msgBuf[j] = '\0';
				strcat(msgBuf,pt);
				j = j + strlen(pt);
				pt1[0] = tmpChar;
				pt = strstr(pt1,"\r\n");
				if ((pt1[0] != '\r') && (pt1[1] != '\r') && (pt1[1] != '0')) {
					msgBuf[j++] = pt1[0];
					msgBuf[j++] = pt1[1];
				}
				else if ((pt1[0] != '\r') && (pt1[0] != '0')) {
					msgBuf[j++] = pt1[0];
				}
				newLine = true;
				msgBuf[j++] = '\r';
				msgBuf[j++] = '\n';
				pt = pt + 2;
				pt1 = pt + 1;
				continue;
			}
			/* else if (!strncmp(pt,":32A:",4)) {
				pt1 = &pt[14];
				tmpChar = pt1[0];
				pt1[0] = '\0';
				msgBuf[j] = '\0';
				strcat(msgBuf,pt);
				j = j + strlen(pt);
				pt1[0] = tmpChar;
				pt = strstr(pt1,"\r\n");
				pt[0] = '\0';
				while(1) {
					if ((pt1[0] != '0') || (pt1 == pt)){
						break;
					}
					pt1++;
				}
				len = strlen(pt1);
				if (len > 2) {
					msgBuf[j] = '\0';
					strncat(msgBuf,pt1, len-2);
					j = j + len-2;
					msgBuf[j] = '\0';
					strcat(msgBuf,",");
					j = j + 1;
					msgBuf[j] = '\0';
					strcat(msgBuf,&(pt1[len-2]));
					j = j + 2;
				}
				msgBuf[j++] = '\r';
				msgBuf[j++] = '\n';
				pt = pt + 2;
				pt1 = pt + 1;
				continue;
			}
			*/
			else if ((!strncmp(pt,":93B:",4)) || (!strncmp(pt,":90B:",4)) || (!strncmp(pt,":36B:",4))) {
				pt1 = strstr(pt,",");
				pt1 = pt1 + 1;
				tmpChar = pt1[0];
				pt1[0] = '\0';
				msgBuf[j] = '\0';
				strcat(msgBuf,pt);
				j = j + strlen(pt);
				pt1[0] = tmpChar;
				pt = strstr(pt1,"\r\n");
				pt1--;
				pt2 = pt - 1;
				isZero = true;
				pt[0] = '\0';
				while (pt2 != pt1) {
					if (pt2[0] == '0') {
						pt2--;
						continue;
					}
					break;
				}
				pt[0] = '\r';
				if (pt1 != pt2) {
					pt1++;
					pt2++;
					tmpChar = pt2[0];
					pt2[0] = '\0';
					msgBuf[j] = '\0';
					strcat(msgBuf,pt1);
					j = j + strlen(pt1);
					pt2[0] = tmpChar;
				}
				newLine = true;
				msgBuf[j++] = '\r';
				msgBuf[j++] = '\n';
				pt = pt + 2;
				pt1 = pt + 1;
				continue;
			}
			else if ((pt[0] != ':') && (pt[0] == '-')) {
				msgBuf[j++] = '(';
				pt++;
				pt1 = pt + 1;
				newLine = false;
				continue;
			}
			else if (pt[0] == ':') {
				msgBuf[j++] = pt[0];
				pt++;
				pt1 = pt + 1;
				while ((pt[0] != ':') && !((pt[0] == '\r') && (pt[1] == '\n'))) {
					msgBuf[j++] = pt[0];
					pt++;
					pt1 = pt + 1;
				}
				if (pt[0] == ':') {
					msgBuf[j++] = pt[0];
					pt++;
					pt1 = pt + 1;
					if (pt[0] == '-') {
						msgBuf[j++] = '(';
						pt++;
						pt1 = pt + 1;
						newLine = false;
						continue;
					}
					newLine = false;
					continue;
				}
				if ((pt[0] == '\r') && (pt[1] == '\n')) {
					newLine = true;
					msgBuf[j++] = '\r';
					msgBuf[j++] = '\n';
					pt = pt + 2;
					pt1 = pt + 1;
					continue;
				}
			}
		}
		if ((pt[0] == '\r') && (pt[1] == '\n')) {
			newLine = true;
			msgBuf[j++] = '\r';
			msgBuf[j++] = '\n';
			pt = pt + 2;
			pt1 = pt + 1;
			continue;
		}
		else {
			newLine = false;
		}
		pt1 = pt;
		isBlank = true;
		while (isBlank) {
			if ((pt1[0] == '\r')&& (pt1[1] == '\n')){
				break;
			}
			else if (pt1[0] == '\r') {
				isBlank = false;
				break;
			}
			else if (isblank(pt1[0])) {
				pt1++;
				continue;
			}
			else if (!isprint(pt1[0])) {
				if ((int) pt1[0] == 0xa8) {
					isBlank = false;
					break;
				}
				else if ((int) pt1[0] == 0xdd) {
					isBlank = false;
					break;
				}
				else {
					pt1++;
					continue;
				}
			}
			else if ((pt1[0] == '@') || (pt1[0] == '!') || (pt1[0] == '#') || (pt1[0] == '$') || (pt1[0] == '%') || (pt1[0] == '^') || (pt1[0] == '&') || (pt1[0] == '*')
					|| (pt1[0] == '|') || (pt1[0] == '~') || (pt1[0] == '`') || (pt1[0] == '<') || (pt1[0] == '>') || (pt1[0] == '=')) {
				pt1++;
				continue;
			}
			else {
				isBlank = false;
				break;
			}
		}
		if (isBlank) {
			newLine = true;
			msgBuf[j++] = '\r';
			msgBuf[j++] = '\n';
			pt = pt1 + 2;
			pt1 = pt + 1;
			continue;
		}
		else {
			pt1 = pt + 1;
		}

		if (pt[0] == '_') {
			msgBuf[j++] = '-';
		}
		else if (pt[0] == '\r') {
			msgBuf[j++] = '\r';
		}
		else if (!isprint(pt[0])) {
			if ((int) pt[0] == 0xdd) {
				msgBuf[j++] = ')';
			}
			else if ((int) pt[0] == 0xa8) {
				msgBuf[j++] = '(';
			}
			else {
				msgBuf[j++] = ' ';
			}
		}
		else if (pt[0] == '{') {
			msgBuf[j++] = '(';
		}
		else if (pt[0] == '}') {
			msgBuf[j++] = ')';
		}
		else if (pt[0] == '[') {
			msgBuf[j++] = '(';
		}
		else if (pt[0] == ']') {
			msgBuf[j++] = ')';
		}
		else if (pt[0] == ';') {
			msgBuf[j++] = ',';
		}
		else if (pt[0] == '\\') {
			msgBuf[j++] = '/';
		}
		else if (pt[0] == '\"') {
			msgBuf[j++] = '\'';
		}
		else if ((pt[0] == '@') || (pt[0] == '!') || (pt[0] == '#') || (pt[0] == '$') || (pt[0] == '%') || (pt[0] == '^') || (pt[0] == '&') || (pt[0] == '*')
				|| (pt[0] == '|') || (pt[0] == '~') || (pt[0] == '`') || (pt[0] == '<') || (pt[0] == '>') || (pt[0] == '=')) {
			msgBuf[j++] = ' ';
		}
		else {
			msgBuf[j++] = pt[0];
		}
		pt++;
		pt1 = pt + 1;
	}
	tracing(TRACE_LEVEL_1, "APPISN replaceInvalidChar", "ended");
}

int getOutputMoudleIndex(PGWYSTR pGwyStr) {
	char* pt;
	char asnPreFix[ASNPREFIXLEN + 1];
	ASNPREFIXSTR asnPrefixStr;
	PASNPREFIXSTR pAsnPrefixStr;

	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN getOutputMoudleIndex", "started");

	strncpy(asnPrefixStr.asnPrefix, &(pGwyStr->inputMessage[ASNPOS]),ASNPREFIXLEN);
	asnPrefixStr.asnPrefix[ASNPREFIXLEN] = '\0';
	tracing(TRACE_LEVEL_1, "APPISN getOutputMoudleIndex", "asnPreFix = " + toString(asnPrefixStr.asnPrefix));

	pAsnPrefixStr = (PASNPREFIXSTR) bsearch (&asnPrefixStr,
									pModuleStr->pAsnPrefixStr,
									pModuleStr->numberOfAsnPrefix,
									sizeof (ASNPREFIXSTR),
									asnPrefixComparator);

	if (pAsnPrefixStr != NULL){
		tracing(TRACE_LEVEL_1, "APPISN getOutputMoudleIndex", "ended");
		strcpy(pGwyStr->outputMessage,pGwyStr->inputMessage);
		return pAsnPrefixStr->outputModuleIndex;
	}
	else {
		strcpy(pGwyStr->outputMessage,pGwyStr->inputMessage);
		tracing(TRACE_LEVEL_1, "APPISN getOutputMoudleIndex", "ended");
		return pModuleStr->numberOfAsnPrefix;
	}
	tracing(TRACE_LEVEL_1, "APPISN getOutputMoudleIndex", "ended");
	return pModuleStr->numberOfAsnPrefix;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	bmProcess -- Tramsform the CHIP message.
// Parameters:	pMsgStr -- The structure contains the input messages and output messages as well as
//						   the instractions to gateway about what should be done next.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void bmProcess(PGWYSTR pGwyStr)
{
	CAuth auth;
	char* outputMsg;
	char* header = "{H:{TYP:SWF}}";
	char* sBlock = "{S:";
	char* sSource = "{SRC:";
	char* sMsgtrace = "{MSGTRACE:";
	char* sEnd = "}";
	char* sAppId = "{APP:";
	char* sPrio = "{PRIO:";
	char* sEndEnd = "}";
	char* msgStart;
	char* pData;
	char sMsgLen[32];
	char sSeq[32];
	char szChecksum[12+1];
	char *pBlock2, *pBlock4, *pBlock5, *pBlock3;
	char *pBlock2End, *pBlock3End;
	char *pOutBlock2 = NULL;
	char *pEnd, *pTNG, *pCHK, *pCHKNext;
	char* pBlock4End;
	char *pt, *pLeft, *pLeft1, *pRight, *pLeft2;
	int nLeft;
	char  *p20f;
	int msgLen;
	char tmpCh;
	char tmpChar;
	bool noBlock4 = false;
	bool noBlock5 = false;
	char* tmpBlock4 = "";
	char  iType[MTTYPE_LEN+1];
	char* pBlock1;
	char gpaOrFin[GPAORFINLEN + 1];
	PISNBIC8STR pIsnBIC8Str;
	PBIC8STR pBic8Str;
	ISNBIC8STR IsnBIC8Str;
	int totalBic8 = 0;
	int i;
	CLTEnv* plTEnv;
	CTime currentTime;
	int lTermIndex;
	PSWFSTR pSwfStr;
	bool sendIBRToSwift = false;
	char seqNumber[SEQNUMBELEN + 1];
	char *pBlock5Next;
	char desBic11[BIC11LEN+1];
	char srcBic8[BIC8LEN+1];
	char retBic8[BIC8LEN+1];
	char retLTerm[LTERMLEN+1];
	char cPriority;
	char field97[FIELDLEN+1];
	char field25[FIELDLEN+1];
	char* pTagStart = NULL;
	char* pTagEnd = NULL;
	ISNMTTYPESTR isnMTTypeStr;
	PISNMTTYPESTR pIsnMTTypeStr;
	int appSeqNumber;
	int expectedSeq;
	char editResults[MAX_EDIT_LENGTH+1];
	char* batchStart;
	char* batchEnd;


	getBusinessModuleVars(PBMDEF);

	tracing(TRACE_LEVEL_1, "APPISN bmProcess", "started");

	if (pModuleStr->isFirstMessage) {
		if (pGwyStr->backoutAndRetry) {
			pGwyStr->backoutAndRetry = false;
		}
		pModuleStr->isFirstMessage = false;
	}

	if (pModuleStr->numberOfAsnPrefix > 0) {
		pGwyStr->currentOutputMoudleIndex = getOutputMoudleIndex(pGwyStr);
		tracing(TRACE_LEVEL_1, "APPISN bmProcess", "Split the traffic based on ASN Prefix OutputMoudleIndex = " + passInt("%d",pGwyStr->currentOutputMoudleIndex));
		pGwyStr->gwInstruction = 1;
		tracing(TRACE_LEVEL_1, "APPISN bmProcess", "ended");
		return;
	}

	if (pModuleStr->drainMessage) {
		appSeqNumber = getSeqNumber(pGwyStr);
		expectedSeq = pModuleStr->expectedSeq;
		if (appSeqNumber != expectedSeq) {
			strcpy(pGwyStr->outputMessage,pGwyStr->inputMessage);
			if (pModuleStr->numberOfMessagesToDrain > 0) {
				pModuleStr->countOfMsgDrain++;
				if (pModuleStr->countOfMsgDrain >= pModuleStr->numberOfMessagesToDrain) {
					pGwyStr->gwInstruction = GW_WRITE_AND_EXIT;
					pGwyStr->currentOutputMoudleIndex = 0;
					pModuleStr->countOfMsgDrain = 0;
					return;
				}
				else {
					pGwyStr->gwInstruction = 1;
					pGwyStr->currentOutputMoudleIndex = 0;
					return;
				}
			}
			else {
				pGwyStr->gwInstruction = 1;
				pGwyStr->currentOutputMoudleIndex = 0;
				return;
			}
		}
		else {
			pGwyStr->currentOutputMoudleIndex = 0;
			pGwyStr->gwInstruction = GW_NO_WRITE_AND_EXIT;
			return;
		}
	}

	if (pModuleStr->rcvRepMsg) {
		getRepMsgInfo(pGwyStr);
	}
	if (pModuleStr->sendGTMAck) {
		pGwyStr->currentOutputMoudleIndex = 1 + pModuleStr->numberOfOnDemandMQs;
		pGwyStr->gwInstruction = 1;
		strcpy(pGwyStr->outputMessage,pModuleStr->gtmAckMsg);
		pModuleStr->sendGTMAck = false;
		tracing(TRACE_LEVEL_4, "APPISN bmProcess", "OutputMsg is\n" + toString(pGwyStr->outputMessage));
		tracing(TRACE_LEVEL_1, "APPISN bmProcess", "ended");
		return;
	}
	if (pModuleStr->forwardPassArea){
		pGwyStr->currentOutputMoudleIndex = 1 + pModuleStr->currentPassAreaIndex;
		if (pModuleStr->gtmAck) {
			pModuleStr->sendGTMAck = true;
			pModuleStr->gtmAck = false;
			pGwyStr->gwInstruction = 2;
			createGTMAckMsg(pGwyStr);
		}
		else {
			pGwyStr->gwInstruction = 1;
		}
		setPassArea(pGwyStr);
		pModuleStr->currentPassAreaIndex = (pModuleStr->currentPassAreaIndex + 1) % pModuleStr->numberOfOnDemandMQs;
		pModuleStr->forwardPassArea = false;
		tracing(TRACE_LEVEL_4, "APPISN bmProcess", "OutputMsg is\n" + toString(pGwyStr->outputMessage));
		tracing(TRACE_LEVEL_1, "APPISN bmProcess", "ended");
		return;
	}

	if (pModuleStr->supportCIBC) {
		if (pModuleStr->processGapCheck != INOGAPCHECK) {
			appSeqNumber = getSeqNumber(pGwyStr);
			if (!pGwyStr->backoutAndRetry) {
				if (pModuleStr->expectedSeq != appSeqNumber) {
					reset();
					pModuleStr->bContinue = true;
					checkSeqNum(pGwyStr, appSeqNumber);
					if (retStatus() != SUCCESS) {
						return;
					}
					if (!pModuleStr->bContinue) {
						string errorMsg = pModuleStr->appId;
						errorMsg = errorMsg + ": FNI ISN gateway is down -- sequence gap exceeded the maximum gap limit. Expected Sequence Number = " + passInt("%d",pModuleStr->expectedSeq) + " Current Sequence Number = " + passInt("%d",appSeqNumber);
						string subject = pModuleStr->appId;
						subject = subject + ": FNI ISN gateway is down -- sequence gap exceeded the maximum gap limit";
						setStatus(GAPCHECK_EXCEED_MAXGAP);
						setErrorMessage(errorMsg);
						sendAlert(pGwyStr,subject, errorMsg);
						pModuleStr->bContinue = true;
						tracing(TRACE_LEVEL_1, "APPISN bmProcess", "ended");
						return;
					}
				}
				else {
					pModuleStr->expectedSeq = pModuleStr->expectedSeq % pModuleStr->maximumSequenceNumber + 1;
				}
			}
		}
		setupCIBC(pGwyStr);
		pGwyStr->currentOutputMoudleIndex = 0;
		pGwyStr->gwInstruction = 1;
		if (pModuleStr->processGapCheck != INOGAPCHECK) {
			if (!pGwyStr->backoutAndRetry) {
				if (pModuleStr->gapCheckBySvc) {
					saveSeqNum(pGwyStr);
				}
			}
		}
		if (pGwyStr->backoutAndRetry) {
			pGwyStr->backoutAndRetry = false;
		}
		tracing(TRACE_LEVEL_4, "APPISN bmProcess", "OutputMsg is\n" + toString(pGwyStr->outputMessage));
		tracing(TRACE_LEVEL_1, "APPISN bmProcess", "ended");
		return;
	}


	char subBranch[4];
	strncpy(subBranch,&(pGwyStr->inputMessage[HB2SBCHPOS]),SBCHLEN);
	subBranch[3] = '\0';

	editResults[0] = '\0';
	pModuleStr->rcvBic12[0] = '\0';
	if (pModuleStr->processPassArea) {
		pModuleStr->cusIndId = pGwyStr->inputMessage[CUSTINDPOS];
		getAsn(pGwyStr);
	}
	if (pModuleStr->supportTEO) {
		setupTEO(pGwyStr);
		if (pModuleStr->handleTEO) {
			appSeqNumber = getSeqNumber(pGwyStr);
			if (!pGwyStr->backoutAndRetry) {
				if (!pModuleStr->gapCheckBySvc) {
					reset();
					processcGapOrDuplication(pGwyStr, appSeqNumber);
					if (retStatus() != SUCCESS) {
						return;
					}
				}
				else {
					if (pModuleStr->expectedSeq != appSeqNumber) {
						reset();
						pModuleStr->bContinue = true;
						checkSeqNum(pGwyStr, appSeqNumber);
						if (retStatus() != SUCCESS) {
							return;
						}
						if (!pModuleStr->bContinue) {
							string errorMsg = pModuleStr->appId;
							errorMsg = errorMsg + ": FNI ISN gateway is down -- sequence gap exceeded the maximum gap limit. Expected Sequence Number = " + passInt("%d",pModuleStr->expectedSeq) + " Current Sequence Number = " + passInt("%d",appSeqNumber);
							string subject = pModuleStr->appId;
							subject = subject + ": FNI ISN gateway is down -- sequence gap exceeded the maximum gap limit";
							setStatus(GAPCHECK_EXCEED_MAXGAP);
							setErrorMessage(errorMsg);
							sendAlert(pGwyStr,subject, errorMsg);
							pModuleStr->bContinue = true;
							tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
							return;
						}
					}
					else {
						pModuleStr->expectedSeq = pModuleStr->expectedSeq % pModuleStr->maximumSequenceNumber + 1;
					}
				}
			}
			strcpy(pGwyStr->outputMessage,pGwyStr->inputMessage);
			pGwyStr->currentOutputMoudleIndex = 1 + pModuleStr->numberOfOnDemandMQs;
			pGwyStr->gwInstruction = 1;
			tracing(TRACE_LEVEL_4, "APPISN bmProcess", "OutputMsg is\n" + toString(pGwyStr->outputMessage));
			tracing(TRACE_LEVEL_1, "APPISN bmProcess", "ended");
			if (pModuleStr->processGapCheck != INOGAPCHECK) {
				if (!pGwyStr->backoutAndRetry) {
					if (pModuleStr->gapCheckBySvc) {
						saveSeqNum(pGwyStr);
					}
					else {
						putGapTable(pGwyStr);
					}
				}
			}
			if (pGwyStr->backoutAndRetry) {
				pGwyStr->backoutAndRetry = false;
			}
			return;
		}
	}
	if (pModuleStr->messageFormat != ISTDFORMAT)  {
		if ((!pModuleStr->rcvRepMsg) && (pModuleStr->correlationId  != ICORRUSEASN)) {
			string dateTimeStr = currentTime.getDateTimeStr();
			sprintf(pModuleStr->correlationData,"%s%s",pModuleStr->appId,dateTimeStr.c_str());
		}
		else if (pModuleStr->correlationId  == ICORRUSEASN) {
			strcpy(pModuleStr->correlationData, pModuleStr->asn);
		}
		else if (pModuleStr->correlationData[0] == '\0') {
			string dateTimeStr = currentTime.getDateTimeStr();
			sprintf(pModuleStr->correlationData,"%s%s",pModuleStr->appId,dateTimeStr.c_str());
		}
	}

	if (pModuleStr->validRcvBic8[0] != '\0') {
		pBlock2 = strstr(pGwyStr->inputMessage, "{2:");
		if (pBlock2 != NULL) {
			strncpy(desBic11,&pBlock2[B2ILTPOS],BIC8LEN);
			desBic11[BIC8LEN] = '\0';
			if (pModuleStr->convertBic8) {
				getNewBic8(pGwyStr, desBic11, retBic8, true);
				strcpy(desBic11,retBic8);
			}
			if (strcmp(pModuleStr->validRcvBic8,desBic11)) {
				pGwyStr->gwInstruction = 1;
				strcpy(pGwyStr->outputMessage,header);
				strcat(pGwyStr->outputMessage,pGwyStr->inputMessage);
				pBlock4End = strstr(pGwyStr->outputMessage,"-}");
				if (pBlock4End == NULL) {
					strcat(pGwyStr->outputMessage,"-}");
				}
				pBlock5 = strstr(pGwyStr->outputMessage,"{5:");
				if (pBlock5 == NULL) {
					strcat(pGwyStr->outputMessage,"{5:}");
				}
				strcpy(pModuleStr->src,DEFAULTERRORCODE);
				strcpy(pModuleStr->errMsg,INVALIDBIC);
				strcat(pModuleStr->errMsg,desBic11);
				strcat(pModuleStr->errMsg,"}");
				strcpy(pModuleStr->priority,"L");
				editResults[0] = '\0';
				addSBlock(pGwyStr,editResults);
				pModuleStr->failToTransform = false;
				return;
			}
		}
	}

	if (pModuleStr->processGapCheck != INOGAPCHECK) {

		appSeqNumber = getSeqNumber(pGwyStr);
		if (!pGwyStr->backoutAndRetry) {
			if (!pModuleStr->gapCheckBySvc) {
				reset();
				processcGapOrDuplication(pGwyStr, appSeqNumber);
				if (retStatus() != SUCCESS) {
					return;
				}
			}
			else {
				if (pModuleStr->expectedSeq != appSeqNumber) {
					reset();
					pModuleStr->bContinue = true;
					checkSeqNum(pGwyStr, appSeqNumber);
					if (retStatus() != SUCCESS) {
						return;
					}
					if (!pModuleStr->bContinue) {
						string errorMsg = pModuleStr->appId;
						errorMsg = errorMsg + ": FNI ISN gateway is down -- sequence gap exceeded the maximum gap limit. Expected Sequence Number = " + passInt("%d",pModuleStr->expectedSeq) + " Current Sequence Number = " + passInt("%d",appSeqNumber);
						string subject = pModuleStr->appId;
						subject = subject + ": FNI ISN gateway is down -- sequence gap exceeded the maximum gap limit";
						setStatus(GAPCHECK_EXCEED_MAXGAP);
						setErrorMessage(errorMsg);
						sendAlert(pGwyStr,subject, errorMsg);
						pModuleStr->bContinue = true;
						tracing(TRACE_LEVEL_1, "APPISN processcGapOrDuplication", "ended");
						return;
					}
				}
				else {
					pModuleStr->expectedSeq = pModuleStr->expectedSeq % pModuleStr->maximumSequenceNumber + 1;

				}
			}
		}
	}
	pModuleStr->handleOutSrc = false;
	pModuleStr->handleCIBC = false;
	if (pModuleStr->supportOutSrc) {
		checkOutSrc(pGwyStr);
	}
	if (pModuleStr->messageFormat == ISTDFORMAT) {
		if (pModuleStr->supportNameKey)  {
			if (!pModuleStr->registerCIFSvc) {
				registerCIFSvc(pGwyStr);
				if (retStatus() != SUCCESS) {
					return;
				}
				pModuleStr->registerCIFSvc = true;
			}
			setNameKeyParameters(pGwyStr);
		}
	}

	if (pModuleStr->transformInternalFmt) {
		transformInternalToSwift(pGwyStr);
		if (retStatus() != SUCCESS){
			return;
		}

	}
	else if (pModuleStr->transformInternalFmtLocal) {
		transformInternalToSwiftLocal(pGwyStr);
		if (retStatus() != SUCCESS){
			return;
		}
	}
	else if (pModuleStr->transformSwiftToSwift) {
		transformSwiftToSwift(pGwyStr);
		if (retStatus() != SUCCESS){
			return;
		}
	}

	if ((pModuleStr->failToTransform) && (pModuleStr->transformInternalFmt)) {
		pGwyStr->gwInstruction = 1;
		strcpy(pGwyStr->outputMessage,header);
		strcat(pGwyStr->outputMessage,pGwyStr->inputMessage);
		pBlock4End = strstr(pGwyStr->outputMessage,"-}");
		if (pBlock4End == NULL) {
			strcat(pGwyStr->outputMessage,"-}");
		}
		pBlock5 = strstr(pGwyStr->outputMessage,"{5:");
		if (pBlock5 == NULL) {
			strcat(pGwyStr->outputMessage,"{5:}");
		}
		strcpy(pModuleStr->src,DEFAULTERRORCODE);
		strcpy(pModuleStr->priority,"L");
		editResults[0] = '\0';
		addSBlock(pGwyStr,editResults);
		pModuleStr->failToTransform = false;
		if (pModuleStr->processGapCheck != INOGAPCHECK) {
			if (!pGwyStr->backoutAndRetry) {
				if (pModuleStr->gapCheckBySvc) {
					saveSeqNum(pGwyStr);
				}
				else {
					putGapTable(pGwyStr);
				}
			}
		}
		if (pGwyStr->backoutAndRetry) {
			pGwyStr->backoutAndRetry = false;
		}
		return;
	}
	if ((pModuleStr->processPassArea) && (pModuleStr->rcvBic12[0] == '\0')) {
		if ((pModuleStr->cusIndId == 'b') || (pModuleStr->cusIndId == 'B') || (pModuleStr->cusIndId != ' ')) {
			if (!pModuleStr->registerCIFSvc) {
				registerCIFSvc(pGwyStr);
				if (retStatus() != SUCCESS) {
					return;
				}
				pModuleStr->registerCIFSvc = true;
			}
			if (pGwyStr->inputMessage[NMKYCIDINDPOS] == 'C') {
				strncpy(pModuleStr->cid,&(pGwyStr->inputMessage[NAMEKEYPOS]), CIDLEN);
				pModuleStr->cid[CIDLEN] = '\0';
				getCIFInfo(pGwyStr, "CID", pModuleStr->cid);
			}
			else {
				strncpy(pModuleStr->nameKey,&(pGwyStr->inputMessage[NAMEKEYPOS]), NAMEKEYLEN);
				pModuleStr->nameKey[NAMEKEYLEN] = '\0';
				getCIFInfo(pGwyStr, "NAMEKEY", pModuleStr->nameKey);
			}
		}
	}
	if (pModuleStr->supportNameKey) {
		setupNameKey(pGwyStr);
	}

	strncpy(subBranch,&(pGwyStr->inputMessage[HB2SBCHPOS]),SBCHLEN);
	subBranch[3] = '\0';

	field97[0] = '\0';
	field25[0] = '\0';

	if (pModuleStr->createHeaderBlock) {
		createHeaderBlock(pGwyStr);
	}
	else if (pModuleStr->switchToIBR) {
		switchToIBR(pGwyStr);
	}

	if (pModuleStr->failToTransform) {
		pGwyStr->gwInstruction = 1;
		strcpy(pGwyStr->outputMessage,header);
		strcat(pGwyStr->outputMessage,pGwyStr->inputMessage);
		pBlock4End = strstr(pGwyStr->outputMessage,"-}");
		if (pBlock4End == NULL) {
			strcat(pGwyStr->outputMessage,"-}");
		}
		pBlock5 = strstr(pGwyStr->outputMessage,"{5:");
		if (pBlock5 == NULL) {
			strcat(pGwyStr->outputMessage,"{5:}");
		}
		strcpy(pModuleStr->src,DEFAULTERRORCODE);
		strcpy(pModuleStr->priority,"L");
		editResults[0] = '\0';
		addSBlock(pGwyStr,editResults);
		pModuleStr->failToTransform = false;
		if (pModuleStr->processGapCheck != INOGAPCHECK) {
			if (!pGwyStr->backoutAndRetry) {
				if (pModuleStr->gapCheckBySvc) {
					saveSeqNum(pGwyStr);
				}
				else {
					putGapTable(pGwyStr);
				}
			}
			else {
				pGwyStr->backoutAndRetry = false;
			}
		}
		if (pGwyStr->backoutAndRetry) {
			pGwyStr->backoutAndRetry = false;
		}
		return;
	}

	msgStart = strstr(pGwyStr->inputMessage,BLOCK1);


	if (msgStart == NULL) {
		pGwyStr->gwInstruction = 1;
		strcpy(pGwyStr->outputMessage,header);
		strcat(pGwyStr->outputMessage,pGwyStr->inputMessage);
		strcpy(pModuleStr->src,DEFAULTERRORCODE);
		strcpy(pModuleStr->priority,"L");
		strcpy(pModuleStr->errMsg,MISSINGBLOCK1);
		//strcpy(pModuleStr->errCode,MISSINGBLOCK1ERRCODE);
		addSBlock(pGwyStr,editResults);
		return;
	}

	if (pModuleStr->use1AsIBRFlag) {
		if (msgStart[BIC8POS] == '1') {
			sendIBRToSwift = true;
			msgStart[BIC8POS] = '0';
		}
	}

	strncpy(gpaOrFin,&msgStart[3],3);
	gpaOrFin[GPAORFINLEN] = '\0';


	strncpy(srcBic8,&msgStart[B1BIC8POS],BIC8LEN);
	srcBic8[BIC8LEN] = '\0';

	if (pModuleStr->convertBic8) {
		getNewBic8(pGwyStr, srcBic8, retBic8, true);
		strcpy(srcBic8,retBic8);
		strncpy(&msgStart[B1BIC8POS],srcBic8,BIC8LEN);
	}

	pBlock2 = strstr(pGwyStr->inputMessage, "{2:");
	if (pBlock2 == NULL) {
		pGwyStr->gwInstruction = 1;
		strcpy(pGwyStr->outputMessage,header);
		strcat(pGwyStr->outputMessage,pGwyStr->inputMessage);
		strcpy(pModuleStr->src,DEFAULTERRORCODE);
		strcpy(pModuleStr->priority,"L");
		strcpy(pModuleStr->errMsg,MISSINGBLOCK2);
		//strcpy(pModuleStr->errCode,MISSINGBLOCK2ERRCODE);
		addSBlock(pGwyStr,editResults);
		return;
	}
	pBlock3 = strstr(pGwyStr->inputMessage, "{3:");
	if (pBlock3 != NULL) {
		char* pTag103 = strstr(pBlock3,"{103:");
		if (pTag103 != NULL) {
			sendIBRToSwift = true;
		}
	}
	if (pModuleStr->use1AsIBRFlag) {
		if (pBlock2[B2BIC8POS] == '1') {
			sendIBRToSwift = true;
			pBlock2[B2BIC8POS] = '0';
		}
	}

	cPriority = pBlock2[PRIORITYPOS];
	strncpy(desBic11,&pBlock2[B2ILTPOS],BIC8LEN);
	desBic11[BIC8LEN] = '\0';
	if (pModuleStr->convertBic8) {
		getNewBic8(pGwyStr, desBic11, retBic8, true);
		strcpy(desBic11,retBic8);
		strncpy(&pBlock2[B2ILTPOS],desBic11,BIC8LEN);
	}
	strncat(desBic11,&pBlock2[B2ILTPOS + LTERMLEN],BRANCHLEN);
	desBic11[BIC11LEN] = '\0';

	iType[MTTYPE_LEN] = '\0';
	strncpy(iType,&pBlock2[4],MTTYPE_LEN);
	iType[MTTYPE_LEN] = '\0';
	pTagStart = strstr(pGwyStr->inputMessage,TAG97);
	if (pTagStart != NULL) {
		pTagEnd = strstr(pTagStart,"\r\n");
		tmpChar = pTagEnd[0];
		pTagEnd[0] = '\0';
		strcpy(field97,pTagStart);
		pTagEnd[0] = tmpChar;
	}
	else {
		pTagStart = strstr(pGwyStr->inputMessage,TAG25);
		if (pTagStart != NULL) {
			pTagEnd = strstr(pTagStart,"\r\n");
			tmpChar = pTagEnd[0];
			pTagEnd[0] = '\0';
			strcpy(field25,pTagStart);
			pTagEnd[0] = tmpChar;
		}
	}

	if (!pModuleStr->switchToIBR) {
		assignLT(pGwyStr,srcBic8, iType, desBic11, retLTerm, field97, field25);
		if (pModuleStr->assignLT) {
			strncpy(&msgStart[B1BIC8POS],retLTerm, LTERMLEN);
		}
		else {
			strncpy(retLTerm, &msgStart[B1BIC8POS],LTERMLEN);
			retLTerm[LTERMLEN] = '\0';
		}
	}
	else {
		if (pModuleStr->assignLT) {
			msgStart[B1BIC8POS + BIC8LEN] = 'A';
		}
		pModuleStr->processIBR = true;
		strncpy(retLTerm,&msgStart[B1BIC8POS],BIC8LEN);
		retLTerm[BIC8LEN] = 'A';
		retLTerm[BIC8LEN + 1] = '\0';
		sendIBRToSwift = false;
	}

	//
	// find bic8
	//
	strncpy(IsnBIC8Str.bic8Name, &pBlock2[B2ILTPOS], BIC8LEN);

	IsnBIC8Str.bic8Name[BIC8LEN] = '\0';

	if ((sendIBRToSwift) || (!pModuleStr->processIBR)) {
		sendIBRToSwift = false;
		getPriority(pGwyStr, retLTerm, iType, false, cPriority);
	}
	else {

		pIsnBIC8Str = (PISNBIC8STR) bsearch (&IsnBIC8Str,
									pModuleStr->pIsnBIC8Str,
									pModuleStr->numberOfIsnBic8s,
									sizeof (ISNBIC8STR),
									bic8Comparator);

		if (pIsnBIC8Str != NULL){
			getPriority(pGwyStr, retLTerm, iType, true, cPriority);

		}
		else {
			getPriority(pGwyStr, retLTerm, iType, false, cPriority);
		}
	}
	strcpy(isnMTTypeStr.mtType, iType);
	if (pModuleStr->pIsnMTTypeStr != NULL) {
		pIsnMTTypeStr = (PISNMTTYPESTR) bsearch (&isnMTTypeStr,
										pModuleStr->pIsnMTTypeStr,
										pModuleStr->numberOfIsnMTType,
										sizeof (ISNMTTYPESTR),
										mtTypeComparator);
		if (pIsnMTTypeStr == NULL){
			pGwyStr->gwInstruction = 1;
			strcpy(pGwyStr->outputMessage,header);
			strcat(pGwyStr->outputMessage,pGwyStr->inputMessage);
			strcpy(pModuleStr->errMsg,INVALIDMTTYPE);
			addSBlock(pGwyStr,editResults);
			return;
		}
	}
	if (pModuleStr->messageFormat == ISTDFORMAT) {
		getCorrelationData(pGwyStr, msgStart);
		if (retStatus() != SUCCESS) {
			return;
		}
		setOFACState(pGwyStr);
	}
	pBlock4 = strstr(msgStart, "{4:");
	if (pBlock4 == NULL) {
		noBlock4 = true;
	}
	else if (pModuleStr->replaceInvalidChar) {
		replaceInvalidChar(pGwyStr,pBlock4);
	}

	pBlock5 = strstr(msgStart, "{5:");
	if (pBlock5 == NULL) {
		if (!noBlock4) {
			//
			// find pBlock4End with string "-}" if it is a FIN message
			//
			if (!strcmp(gpaOrFin,"F01")) {
				pBlock4End = strstr(pBlock4,"-}");
				if (pBlock4End == NULL) {
					pBlock4End = findEndBlock4(pBlock4);
				}
				else {
					pBlock4End = pBlock4End + 2;
				}
			}
			else {
				pBlock4End = findEndBlock4(pBlock4);
			}
			//pBlock4End = strstr(pBlock4,"-}");
		}
		else {
			pBlock4End = strstr(pBlock2, "}");
			pBlock4End = pBlock4End + 1;
		}
	}
	else {
			pBlock4End = pBlock5;
	}
	tmpCh = pBlock4End[0];
	*pBlock4End = '\0';
	if (!noBlock4) {
		char* pVerticalBar;
		char* pStart;
		pStart = pBlock4;
		while ((pVerticalBar = strchr(pStart, '|')) != NULL) {
			*pVerticalBar = '!';
			pStart = pVerticalBar+1;
		}
	}
	if (!noBlock4) {
		auth.createChecksum(pBlock2+7, pBlock4, szChecksum);
	}
	else {
		auth.createChecksum(pBlock2+7, tmpBlock4, szChecksum);
	}

	strcpy(pGwyStr->outputMessage,header);

	strcat(pGwyStr->outputMessage,msgStart);

	pBlock4End[0] = tmpCh;
	if (pBlock5 != NULL) {
		pEnd = strstr(pBlock5, "}}");
		if (pEnd != NULL) {
			pBlock5Next = strstr(pBlock5 + 1,"{");
			pEnd[1] = '\0';
			if ((pBlock5Next != NULL) && (pBlock5Next < pEnd)) {
				pCHK = strstr(pBlock5, "{CHK");
				if (pCHK != NULL) {
					pCHKNext = strstr(pCHK,"}") + 1;
					*pCHK = '\0';
					strcat(pGwyStr->outputMessage,pBlock5);
					//strcat(pGwyStr->outputMessage,"{CHK:");
					//strcat(pGwyStr->outputMessage,szChecksum);
					//strcat(pGwyStr->outputMessage,sEnd);
					strcat(pGwyStr->outputMessage,pCHKNext);
				}
				else {
					pBlock5Next[0] = '\0';
					strcat(pGwyStr->outputMessage,pBlock5);
					//strcat(pGwyStr->outputMessage,"{CHK:");
					//strcat(pGwyStr->outputMessage,szChecksum);
					//strcat(pGwyStr->outputMessage,sEnd);
					pBlock5Next[0] = '{';
					strcat(pGwyStr->outputMessage,pBlock5Next);
				}
				if (pModuleStr->addPDE) {
					strcat(pGwyStr->outputMessage,"{PDE:}");
				}
				strcat(pGwyStr->outputMessage,sEnd);
			}
			else {
				strcat(pGwyStr->outputMessage,pBlock5);
				if (pModuleStr->addPDE) {
					strcat(pGwyStr->outputMessage,"{PDE:}");
				}
				strcat(pGwyStr->outputMessage,sEnd);
			}
		}
		else {
			pEnd = strstr(pBlock5, "}");
			if (pEnd != NULL) {
				pEnd[0] = '\0';
				strcat(pGwyStr->outputMessage,pBlock5);
				if (pModuleStr->addPDE) {
					strcat(pGwyStr->outputMessage,"{PDE:}");
				}
				strcat(pGwyStr->outputMessage,sEnd);
			}
			else {
				pEnd = pBlock5 + 3;
				pEnd[0] = '\0';
				strcat(pGwyStr->outputMessage,pBlock5);
				if (pModuleStr->addPDE) {
					strcat(pGwyStr->outputMessage,"{PDE:}");
				}
				strcat(pGwyStr->outputMessage,sEnd);
			}
		}
	}
	else {
		strcat(pGwyStr->outputMessage,"{5:");
		if (pModuleStr->addPDE) {
			strcat(pGwyStr->outputMessage,"{PDE:}");
		}
		strcat(pGwyStr->outputMessage,sEnd);
	}
	if ((!pModuleStr->switchToIBR) && (!pModuleStr->handleNameKey) && (!pModuleStr->failToTransform) && (!pModuleStr->handleCIBC)) {
		getEditResults(pGwyStr, editResults, retLTerm, iType, cPriority);
	}
/*	if (pModuleStr->defaultSvcPort != NOSVC) {
		CSvcClient* pSvcClient = (CSvcClient*) pModuleStr->pSvcClient;
		char* editMsgStart = strstr(pGwyStr->outputMessage,MERVABLOCK1);
		pSvcClient->editCheck(editMsgStart,editResults,MAX_EDIT_LENGTH);
		if (pSvcClient->getStatus() != SUCCESS) {
			if (!pModuleStr->editCheckBySwift) {
				setStatus(pSvcClient->getStatus());
				setErrorMessage(pSvcClient->getErrorMessage());
				return;
			}
			else {
				pModuleStr->defaultSvcPort = NOSVC;
				pModuleStr->processIBR = false;
				getPriority(pGwyStr, retLTerm, iType, false, cPriority);
			}
		}
	}
	*/
	reset();
	addSBlock(pGwyStr,editResults);

	if (pModuleStr->block2Tid[0] != '\0') {
		pBlock2 = strstr(pGwyStr->outputMessage,"{2:");
		if (pBlock2 != NULL) {
			pBlock2[TIDPOS] = pModuleStr->block2Tid[0];
		}
	}


	if (pModuleStr->processPassArea) {
			pGwyStr->gwInstruction = 1;
			pGwyStr->currentOutputMoudleIndex = 0;
			pModuleStr->forwardPassArea = false;
	}
	else {
		if (pModuleStr->gtmAck) {
			pModuleStr->sendGTMAck = true;
			pModuleStr->gtmAck = false;
			pGwyStr->gwInstruction = 2;
			createGTMAckMsg(pGwyStr);
		}
		else {
			pGwyStr->gwInstruction = 1;
			pModuleStr->sendGTMAck = false;
			pModuleStr->gtmAck = false;
		}
		pGwyStr->currentOutputMoudleIndex = 0;
		pModuleStr->putGapTable = false;
		pModuleStr->forwardPassArea = false;
	}
	if (pModuleStr->processGapCheck != INOGAPCHECK) {
		if (!pGwyStr->backoutAndRetry) {
			if (pModuleStr->gapCheckBySvc) {
				saveSeqNum(pGwyStr);
			}
			else {
				putGapTable(pGwyStr);
			}
		}
		else {
			pGwyStr->backoutAndRetry = false;
		}
	}
    if (pGwyStr->backoutAndRetry) {
		pGwyStr->backoutAndRetry = false;
	}
	tracing(TRACE_LEVEL_4, "APPISN bmProcess", "OutputMsg is\n" + toString(pGwyStr->outputMessage));
	tracing(TRACE_LEVEL_1, "APPISN bmProcess", "ended");
	return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function:	bmCleanup -- Clean up the module.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void bmCleanup(PGWYSTR pGwyStr)
{
	CLTEnv* plTEnv;
	PISNBIC8STR pIsnBIC8Str;
	PISNLTERMSTR pIsnLTermStr;
	PSELLTERMSTR pSelLTermStr;
	PMTLTERMSTR pMTLTermStr;
	PPRIOITYSTR pPriorityStr;

	PBIC8CVTSTR pBic8CvtStr;
	PBIC8ECPSTR pPodBic8Excep;
	PBIC8ECPSTR pTandtBic8Excep;
	PISNMTTYPESTR pIsnMTTypeStr;
	PSELLTERMSTR pAppLTermStr;
	PASNPREFIXSTR pAsnPrefixStr;
	PTRNPREFIXSTR pTrnPrefixStr;
	PCITTEOSTR pCitTEOStr;
	PNAMEKEYSTR pNameKeyStr;
	POUTSRCSTR pOutSrcStr;
	PSWITCHIBRSTR pSwiftIBRStr;

	int * pGapTable;
	CSvcClient* pSvcClient;

	int j;


	getBusinessModuleVars(PBMDEF);
	tracing(TRACE_LEVEL_1, "APPISN bmCleanup", "started");
	reset();

	if (pModuleStr->pIsnBIC8Str != NULL) {
		pIsnBIC8Str = (PISNBIC8STR) pModuleStr->pIsnBIC8Str;
		free(pIsnBIC8Str);
		pModuleStr->pIsnBIC8Str = NULL;
	}
	if (pModuleStr->pIsnLTermStr != NULL) {
		pIsnLTermStr = (PISNLTERMSTR) pModuleStr->pIsnLTermStr;
		free(pIsnLTermStr);
		pModuleStr->pIsnLTermStr = NULL;
	}
	if (pModuleStr->pPriorityStr != NULL) {
		pPriorityStr = (PPRIOITYSTR) pModuleStr->pPriorityStr;
		free(pPriorityStr);
		pModuleStr->pPriorityStr = NULL;
	}

	if (pModuleStr->pSelLTermStr != NULL) {
		for (j = 0; j < pModuleStr->numberOfBic8; j++) {
			pMTLTermStr = (PMTLTERMSTR) (pModuleStr->pSelLTermStr[j]).pMTLTermStr;
			if (pMTLTermStr != NULL) {
				free(pMTLTermStr);
				(pModuleStr->pSelLTermStr[j]).pMTLTermStr = NULL;
			}
		}
		free(pModuleStr->pSelLTermStr);
		pModuleStr->pSelLTermStr = NULL;
	}
	if (pModuleStr->pBic8CvtStr != NULL) {
		pBic8CvtStr = (PBIC8CVTSTR) pModuleStr->pBic8CvtStr;
		free(pBic8CvtStr);
		pModuleStr->pBic8CvtStr = NULL;
	}

	if (pModuleStr->pPodBic8Excep != NULL) {
		pPodBic8Excep = (PBIC8ECPSTR) pModuleStr->pPodBic8Excep;
		free(pPodBic8Excep);
		pModuleStr->pPodBic8Excep = NULL;
	}

	if (pModuleStr->pTandtBic8Excep != NULL) {
		pTandtBic8Excep = (PBIC8ECPSTR) pModuleStr->pTandtBic8Excep;
		free(pTandtBic8Excep);
		pModuleStr->pTandtBic8Excep = NULL;
	}
	if (pModuleStr->pIsnMTTypeStr != NULL) {
		pIsnMTTypeStr = (PISNMTTYPESTR) pModuleStr->pIsnMTTypeStr;
		free(pIsnMTTypeStr);
		pModuleStr->pIsnMTTypeStr = NULL;
	}
	if (pModuleStr->pGapTable != NULL) {
		pGapTable = (int *) pModuleStr->pGapTable;
		free(pGapTable);
		pModuleStr->pGapTable = NULL;
	}
	if (pModuleStr->pSvcClient != NULL) {
		pSvcClient= (CSvcClient*) pModuleStr->pSvcClient;
		free(pSvcClient);
		pModuleStr->pSvcClient = NULL;
	}

	if (pModuleStr->pAppLTermStr != NULL) {
		pAppLTermStr= (PSELLTERMSTR) pModuleStr->pAppLTermStr;
		for (j = 0; j < pModuleStr->numberofAppLTerms; j++) {
			pMTLTermStr = (PMTLTERMSTR) (pModuleStr->pAppLTermStr[j]).pMTLTermStr;
			if (pMTLTermStr != NULL) {
				free(pMTLTermStr);
				(pModuleStr->pAppLTermStr[j]).pMTLTermStr = NULL;
			}
		}
		free(pAppLTermStr);
		pModuleStr->pAppLTermStr = NULL;
	}
	 if (pModuleStr->pGapTableStr != NULL) {
		 free(pModuleStr->pGapTableStr);
		 pModuleStr->pGapTableStr = NULL;
	}
	if (pModuleStr->pMsgHeaderStr != NULL) {
		 free(pModuleStr->pMsgHeaderStr);
		 pModuleStr->pMsgHeaderStr = NULL;
	}

	if (pModuleStr->pAlertEmailStr != NULL) {
		 free(pModuleStr->pMsgHeaderStr);
		 pModuleStr->pMsgHeaderStr = NULL;
	}

	if (pModuleStr->pAsnPrefixStr != NULL) {
		pAsnPrefixStr = (PASNPREFIXSTR) pModuleStr->pAsnPrefixStr;
		free(pAsnPrefixStr);
		pModuleStr->pAsnPrefixStr = NULL;
	}
	if (pModuleStr->pTrnPrefixStr != NULL) {
		pTrnPrefixStr = (PTRNPREFIXSTR) pModuleStr->pTrnPrefixStr;
		free(pTrnPrefixStr);
		pModuleStr->pTrnPrefixStr = NULL;
	}
	if (pModuleStr->pCitTEOStr != NULL) {
		pCitTEOStr = (PCITTEOSTR) pModuleStr->pCitTEOStr;
		free(pCitTEOStr);
		pModuleStr->pCitTEOStr = NULL;
	}
	if (pModuleStr->pNameKeyStr != NULL) {
		pNameKeyStr = (PNAMEKEYSTR) pModuleStr->pNameKeyStr;
		free(pNameKeyStr);
		pModuleStr->pNameKeyStr = NULL;
	}
	if (pModuleStr->pOutSrcStr != NULL) {
		pOutSrcStr = (POUTSRCSTR) pModuleStr->pOutSrcStr;
		free(pOutSrcStr);
		pModuleStr->pOutSrcStr = NULL;
	}
	if (pModuleStr->pSwiftIBRStr != NULL) {
		pSwiftIBRStr = (PSWITCHIBRSTR) pModuleStr->pSwiftIBRStr;
		for (int i = 0; i < pModuleStr->numberOfSwiftIBRStr; i++) {
			PBIC11STR pBic11Str = (PBIC11STR) pModuleStr->pSwiftIBRStr[i].pBic11Str;
			free(pBic11Str);
			pModuleStr->pSwiftIBRStr[i].pBic11Str = NULL;
		}
		free(pSwiftIBRStr);
		pModuleStr->pSwiftIBRStr = NULL;
	}
	removeModuleVars();
	tracing(TRACE_LEVEL_1, "APPISN bmCleanup", "ended");
}
