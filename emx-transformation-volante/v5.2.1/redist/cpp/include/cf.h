/****************************************************************************r
 *
 *                    DATE:        ~M~/~D~/~Y~
 *                    CATALOG:     ~C~
 *                    SOURCE FILE: ~F~
 *                    RELEASE:     ~R~.~L~
 *                    SYS REL:     ~V~
 *
 *****************************************************************************/

#ifndef ID__cf
#define ID__cf

/*
 User include for Canonical APIs
*/

#if defined( __TANDEM ) && !(defined _OSS_TARGET )
#include <cftdm.h>
#endif
#ifdef __CSCLIB
#include <csclib.h>
#else
#include <limits.h>
#include <stdio.h>
#include <string.h>
#endif
#ifdef __cplusplus
#include <iostream>
#include <strstream>
#endif

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

#include <taglmt.h>
#include <CFtypes.h>
#include <CFlatency.h>

/* prefix:
	CFD_ for private define
	CFG_ for general define
	CFE_ for error define
	CFM_ for warning define
	CFO_ for options define
*/

#define	CF_N_UTCTIMESTAMP_S	17
#define	CF_N_UTCTIMESTAMP_MS	21
#define	CF_N_UTCTIMESTAMP_NS	27
#define CF_N_UTCTIMEONLY_S	8
#define	CF_N_UTCTIMEONLY_MS	12
#define CF_N_UTCDATE		8
#define	CF_N_MONTHYEAR		6
#define CF_N_DIGIT_UTCTIMESTAMP_S	14
#define CF_N_DIGIT_UTCTIMESTAMP_MS	17
#define CF_N_DIGIT_UTCTIMEONLY_S	6
#define CF_N_DIGIT_UTCTIMEONLY_MS	9

/* repeating group related */
#define     CFD_MAX_NEST_GROUP_DEPTH    3

/* Message related */

#define CFD_BODY_LEN_DIGITS_CANONICAL	6
#define CFD_BODY_LEN_DIGITS_FIX			5
#define CFD_MAX_MSG_SIZE				999999
#define CFD_LENGTH_TAG_DELIM				1
#define CFD_LENGTH_EQUAL_SIGN				1
#define CFD_OFFSET_VERSION_TAG_VALUE_CANONICAL_MSG	6
#define CFD_LENGTH_VERSION_TAG_VALUE_CANONICAL_MSG	14
#define CFD_LENGTH_CHKSUM_TAG				2  /* not include '=' */
#define CFD_LENGTH_CHKSUM_TAG_VALUE			3  /* <nnn> */
#define CFD_LENGTH_LONG_CHKSUM_TAG_VALUE		6  /* <nnnnnn> */
#define CFD_LENGTH_CHKSUM_TAG_VALUE_PAIR		(CFD_LENGTH_CHKSUM_TAG+CFD_LENGTH_EQUAL_SIGN+\
							CFD_LENGTH_CHKSUM_TAG_VALUE+CFD_LENGTH_TAG_DELIM) /* 7 <10=nnn\001> */
#define CFD_LENGTH_CHKSUM_TAG_VALUE_DELIM		(CFD_LENGTH_CHKSUM_TAG_VALUE+CFD_LENGTH_TAG_DELIM) /* 4 <nnn\001> */
							
#define CFD_LENGTH_LONG_CHKSUM_TAG_VALUE_PAIR		(CFD_LENGTH_CHKSUM_TAG+CFD_LENGTH_EQUAL_SIGN+\
							CFD_LENGTH_LONG_CHKSUM_TAG_VALUE+CFD_LENGTH_TAG_DELIM) /* 10 <10=nnnnnn\001> */
#define CFD_LENGTH_LONG_CHKSUM_TAG_VALUE_DELIM		(CFD_LENGTH_LONG_CHKSUM_TAG_VALUE+CFD_LENGTH_TAG_DELIM) /* 7 <nnnnnn\001> */
										
#define CFD_N_MIN_ORDERED_TAGS_PER_MSG			3
#define CFD_N_REQUIRED_TAG_PER_MSG			8

#define CFD_GROUP_MASK_TAG_TYPE				0x3

#define CFD_MINLENGTH_FIX_MSG				60
#define CFD_MINLENGTH_CANONICAL_MSG			86

#define CFD_CHECKSUM_MASK				0xff
#define CFD_LONG_CHECKSUM_MASK				0x7ffff	

/* Tag related */
#define CFD_LENGTH_CANONICAL_TAG			5
#define CFD_SIZE_TAG_DELIMITER				1
#define CFD_OFFSET_TAG_VALUE_CANONICAL_TAG		(CFD_LENGTH_CANONICAL_TAG+1) /* + '=' */
#define CFD_SIZE_MIN_TAG_VALUE_PAIR			(CFD_OFFSET_TAG_VALUE_CANONICAL_TAG+CFD_SIZE_TAG_DELIMITER)
#define CFD_N_BIT_PER_BIT_FIELD_TAG			16

#define CFD_N_BITSHIFT_MASK_BIT_TAG			0x10	/* from 0000FFFF to FFFF0000 */
#define CFD_MAX_MSGTYPE_NAME_LENGTH			50
#define CFD_MAX_GROUP_NAME_LENGTH			50
#define CFD_TOTAL_DEFINED_MSG				11
#define CFD_REQUIRE_MSG_TAG_BIT				0x80
#define CFD_OPTIONAL_MSG_TAG_BIT			0x40

/*FIX protocol definition begin*/
#define CFD_STANDARD_MSG_NBR_FIX	46
#define CFD_STANDARD_MSG_NBR_CANONICAL	1

/*Decimal range*/
#define CFD_MIN_DECIMAL					    0
#define CFD_MAX_DECIMAL					    15

#ifdef __cplusplus
typedef unsigned char BitField;
#else
typedef unsigned int BitField;
#endif

typedef unsigned int Field32bits;

typedef struct MsgVersionAttribsField_def
{
	Field32bits no_leading_0: 1;
	Field32bits no_RPG_failure: 1;
	Field32bits bit_2: 1;
	Field32bits bit_3: 1;
	Field32bits bit_4: 1;
	Field32bits bit_5: 1;
	Field32bits bit_6: 1;
	Field32bits bit_7: 1;
	Field32bits bit_8: 1;
	Field32bits bit_9: 1;
	Field32bits bit_10: 1;
	Field32bits bit_11: 1;
	Field32bits bit_12: 1;
	Field32bits bit_13: 1;
	Field32bits bit_14: 1;
	Field32bits bit_15: 1;
	Field32bits bit_16: 1;
	Field32bits bit_17: 1;
	Field32bits bit_18: 1;
	Field32bits bit_19: 1;
	Field32bits bit_20: 1;
	Field32bits bit_21: 1;
	Field32bits bit_22: 1;
	Field32bits bit_23: 1;
	Field32bits bit_24: 1;
	Field32bits bit_25: 1;
	Field32bits bit_26: 1;
	Field32bits bit_27: 1;
	Field32bits bit_28: 1;
	Field32bits bit_29: 1;
	Field32bits bit_30: 1;
	Field32bits bit_31: 1;
} MsgVersionAttribsField;

struct TagData
{
	/*
		At least 8 bits must be provided due to
		compilier limitation.
	*/
	BitField tag_type: 8;	
	BitField tag_group: 3;
};

typedef struct
{
	BitField        required:1;
	BitField        optional:1;
	BitField        repeatable:1;
	BitField        group_header:1;
	BitField        group_level:4;

}       TagMsgInfo;
					
typedef struct
{
	int		tag_num;
	TagMsgInfo	tag_msg_info;

}	MsgTag;

typedef struct
{
	TagMsgInfo tag_msg_info;
	short count;

}	MsgTagInfo;

typedef struct MessageTypeIDIndex_def
{
	const char	*MsgType;
	const char	*SubType;

	MsgTag*  tag_list;
	unsigned short  tag_list_len;
	const int *relational_tag;
}   MessageTypeIDIndex;

typedef struct MessageTypeInfo_def
{
	const char	*MsgType;
	int			MsgID;
	union
	{
		MsgTag*  tag_list;
		const struct MessageTypeInfo_def* SubTypeList;
	} List;

	unsigned short  tag_list_len;
	unsigned short  sub_type_list_len;
#ifdef never
	int (*ck_special_rules)(struct _IncomingCanonical *ic, int *tag_num);
#endif
	const int *relational_tag;

}   MessageTypeInfo;

typedef struct
{
	int	primary_tag;
	int	tag_value;
	int	length;
	int	offset;
} BitFieldTagData;

typedef unsigned char  CS_BOOL;  

typedef struct {
	int stx_internal_struct_num;
	int stx_struct_tagnum;
} STRUCT_TAG_XREF;

#define TEST_ARRAY_SIZE	(1024)

union local_tag_value_t
{
	int tv_int;
	double tv_float;
	char tv_char;
	char tv_string[1000];
	char tv_data[1000];
};


#define DELIM     '\001'
#define SEPARATOR '='

#define FIX_BodyLengthOffset        	12
#define FIX_BodyLengthTagOffset        	10
#define FIX_BodyLengthDelta		(FIX_BodyLengthOffset+CFD_BODY_LEN_DIGITS_FIX+CFD_LENGTH_TAG_DELIM)
#define CANONICAL_BodyLengthOffset	27
#define CANONICAL_BodyLengthTagOffset	21
#define CANONICAL_BodyMinLength     	78
#define CANONICAL_BodyLengthDelta	(CANONICAL_BodyLengthOffset+CFD_BODY_LEN_DIGITS_CANONICAL+CFD_LENGTH_TAG_DELIM)
#define FIX_BodyLengthDelta2 (FIX_BodyLengthDelta-CFD_BODY_LEN_DIGITS_FIX)
#define CANONICAL_BodyLengthDelta2	(CANONICAL_BodyLengthDelta-CFD_BODY_LEN_DIGITS_CANONICAL)

/* TANDEM DEFINES BEGIN */

#define REPEAT_TAGNUM			25000
#define	OPTIONS_TAGNUM			25001

#define FFD_CuponRate FFD_CouponRate

/* options for CF_PrintStructure */
#define CFPS_NO_NEWLINE	0x0001

/* values for choice parameter of CF_EditMsg() */
#define	CFEM_INSERT		1
#define	CFEM_UPDATE		2
#define	CFEM_DELETE		3
#define	CFEM_ADD_TO_HEADER	4
#define	CFEM_ADD_TO_BODY	5
#define	CFEM_FIX_CHECKSUM_AND_LENGTH	6
#define	CFEM_ADD_UPDATE		7

/* options bits */

#define	CFO_DONT_ALLOW_UNDEFINED_TAGS	0x0001
#define CFO_LAST_FIELD					0x0002	/* CF_PutNextField,CF_aPutNextStructField,CF_PutList,CF_PutStructList */
#define CFO_FIX_CHECKSUM_AND_LENGTH		0x0002	/* used by CF_EditMsg only */
#define	CFO_LOAD_FROM_BUFFER			0x0002	/* used only by CF_LoadStructureList */
#define	CFO_HEADER_FIELDS_ONLY			0x0002	/* used only by CF_xParseMsg */
#define	CFO_DUMP_TABLES					0x0002	/* (for internal use only) */
#define	CFO_ADD_CHECKSUM				0x0002	/* used only by CF_CreateMsg */
#define CFO_VALIDATE					0x0008
#define CFO_ORDERED_FIELDS_ONLY				0x0010	/* used only by CF_aParseMsg */
#define	CFO_FULL_VALIDATION   				0x0020	/* used only by CF_aParseMsg */
#define	CFO_SKIP_VALIDATION   				0x0040	/* used only by CF_aParseMsg */
#define	CFO_SEARCH_MSG         				0x0080	/* used only by CF_aParseMsg */
#define	CFO_FIND_MSG_LEN	   			0x0200	/* used only by CF_aParseMsg */
#define	CFO_FIX_RPG_VALIDATION			0x0400	/* FIX repeating group validation */
#define	CFO_NO_FIX_RPG_VALIDATION		0x0800	/* no FIX repeating group validation */

#define CFO_INPUT						0x0010	/* used by CF_Init only */
#define CFO_LOAD_PUBLISHED_STRUCTURES	0x0010	/* used by CF_LoadStructureList only */
#define CFO_ZERO_CHECKSUM				0x0010	/* CF_PutNextField,CF_aPutNextStructField,CF_PutList,CF_PutStructList */
#define CFO_BLK_FIRST_MSG               0x0010  /* used by CF_CreateMsg only */
#define CFO_BLK_NEXT_MSG                0x0020  /* used by CF_CreateMsg only */
#define CFO_BLK_LAST_MSG                0x0040  /* used by CF_CreateMsg and CF_BlockMsgOutUpdate */
#define CFO_BLK_RESET                   0x0080  /* used by CF_BlockMsgInUpdate */
#define CFO_BLK_ADD_MSG                 0x0100  /* used by CF_BlockMsgOutUpdate */
#define CFO_OUTPUT						0x0020	/* used by CF_Init only */
#define CFO_LOAD_FROM_FILE				0x0020	/* used by CF_LoadStructureList only */
#define	CFO_ZERO_FILL					0x0020	/* used by CF_EditMsg only */
#define	CFO_BULK_LOAD					0x0020	/* used by CF_aPutNextStructField */

#define CFO_ORIGINAL_FORM				0x0040

/*  CFO_NO_NULL_TERMINATION:  When this option is set, retrieved STRING type tags returned from CF_GetField, 
    CF_GetNextField, CF_GetRepeatField, and CF_GetList are not NULL terminated.  In addition, CF_PutNextField, 
    CF_PutNextStructField, CF_PutList and CF_PutStructList will not expect STRING type tags to be NULL terminated. 
    This option also applies if CFO_ORIGINAL_FORM is specified when calling any one of these APIs.
*/
#define CFO_NO_NULL_TERMINATION			0x0080
#define	CFO_DONT_ALLOW_UNDEFINED_STANDARD_TAGS	0x0100
#define	CFO_INSERT_AFTER_TAG			0x0200
#define CFO_NO_OUTBUF				0x0400	/* used by CF_EditMsg only */
#define	CFO_APPEND_TO_HEADER			0x0800
#define CFO_TAG_LIST				0x1000	/* used by CF_EditMsg only */
#define CFO_TAG					0x0001
#define CFO_INSTANCE				0x0004
#define CFO_GROUP				0x0008

/* used by CF_aParseMsg or CF_CreateMsg only */
#define CFO_NBO_CONVERSION			0x0008	/* by default, value of structs will not be converted to
							   network byte order. */
#define CFO_TAG_INSTANCE_DELIMITER		0x0080

#define CFO_MSG_TYPE_VALIDATION                 0x1000
#define CFO_CHECKSUM_VALIDATION                 0x1000
#define CFO_NO_CHECKSUM_VALIDATION		0x0200
#define CFO_NO_MSG_TYPE_VALIDATION              0x2000
#define CFO_DONT_ALLOW_ZERO_TAG_LENGTH		0x4000
#define CFO_DONT_ALLOW_UNDEFINED_MSGTYPE	0x0004

/* used by CF_aGetNextField only */
#define CFO_NO_BIT_TAG				0x0080

/* used by CF_FormatMsg only */
#define CFO_FORMAT_PARSE	0x1
#define CFO_FORMAT_PRETTY	0x2
#define CFO_FORMAT_NO_NL	0x4

/* used by CF_SearchTag only */
#define CFO_START_FROM_RIGHT	0x1
#define CFO_SEARCH_DELIMITER	0x2
#define CFO_RETURN_TAG_VALUE	0x4
#define CFO_RETURN_TAG_AS_INT	0x8

/* used by CF_SearchMsg only */
#define CFO_PARTIAL_MSG			0x1

/* used by Latency API only */
#define CFO_DONT_CREATE_BLOB	0x1

#define TTI_HEADER_TAG                  1
#define TTI_BODY_TAG                    2
#define TTI_TRAILER_TAG                 3
#define TTI_LAST_HEADER_TAG             4
#define TTI_LAST_BODY_TAG               5

#define FIX_4_1_VERSION_ID			1
#define	FIX_4_2_VERSION_ID			2
#define CANONICAL_1_00_VERSION_ID		3
#define	FIX_4_3_VERSION_ID			4

#define FIX_4_1_VERSION				"FIX.4.1"
#define	FIX_4_2_VERSION				"FIX.4.2"
#define	FIX_4_3_VERSION				"FIX.4.3"
#define	CANONICAL_1_00_VERSION		"Canonical.1.00"


/* strip off the last 2 digits [error sub_code, see CFE2_... values] */
#define CFE_DIVISOR	100
#define	CFE_ERROR(n)	(((n)/CFE_DIVISOR)*CFE_DIVISOR)


#define CF_BLOCKING                (1)
#define CF_NO_BLOCKING             (0)

/*
	Here we define the return codes for Canonical API routines.
	Use CFE_ERROR() before doing a comparison against these codes.
*/

enum CF_DRANGEINDICATOR
{
		MIN_DECIMAL,
		MAX_DECIMAL	
};

enum{
CFE_NO_MORE_TAGS								= -300,
CFE_AT_END										= -400,
CFE_MISSING_EQUAL_SIGN							= -500,
CFE_RAWDATALENGTH_RAWDATA_PAIR					= -600,
CFE_ZERO_TAG_LENGTH								= -700,
CFE_MISSING_DELIMITER							= -800,
CFE_FIRST_TAG_NOT_BEGINSTRING					= -900,
CFE_SECOND_TAG_NOT_BODYLENGTH					= -1000,
CFE_THIRD_TAG_NOT_MSGTYPE						= -1100,
CFE_NO_ROOM_FOR_TAG								= -1200,
CFE_CANT_SET_DUP_TAG_LIST						= -1300,
CFE_CANT_SET_TAG_FIELD							= -1400,
CFE_CANT_FIND_TAG								= -1500,
CFE_INIT_FAILED									= -2700,
CFE_CHECKSUM_NOT_LAST_TAG						= -2800,
CFE_INVALID_CHECKSUM_TAG_LENGTH					= -2900,
CFE_CHECKSUM_NOT_3ASCII_DIGITS					= -3000,
CFE_INVALID_CHECKSUM							= -3100,
CFE_INVALID_BODYLENGTH							= -3200,
CFE_NULL_DELIMITER_POINTER						= -3300,        /* message being parsed doesn't have first 2 tags present */
CFE_INIT_WAS_NOT_CALLED							= -3400,
CFE_FIRST_TAG_NOT_MSGTYPE						= -3500,
CFE_CREATEMSG_NOT_CALLED						= -3600,
CFE_UNDEFINED_TAG_TYPE							= -3700,
CFE_TAG_SEQUENCE_OVERFLOW						= -3800,
CFE_BUFFER_OVERFLOW								= -3900,
CFE_INPUT_ONLY									= -4000,
CFE_OUTPUT_ONLY									= -4100,
CFE_DUPLICATE									= -4200,
CFE_STRING_TOO_LONG								= -4300,
CFE_OVERFLOW									= -4400,
CFE_HEADER_FIELD_IN_BODY						= -4600,
CFE_HEADER_FIELD_IN_TRAILER						= -4700,
CFE_BODY_FIELD_IN_TRAILER						= -4800,
CFE_RAWLEN_OVERFLOW								= -4900,
CFE_INVALID_BUF_LEN								= -5000,
CFE_UNSUPPORTED_VERSION							= -5100,
CFE_INVALID_VERSION								= -5200,
CFE_FIRST_TAG_NOT_CFT_CANONICALVERSION			= -5700,
CFE_SECOND_TAG_NOT_CFT_BODYLENGTH				= -5800,
CFE_FOURTH_TAG_NOT_CFT_SIACMSGTYPE				= -5900,
CFE_FIRST_TAG_NOT_SIACMSGTYPE					= -6000,
CFE_UNDEFINED_TAG_IN_FIRST_3_TAG_POSITIONS		= -6100,
CFE_UNDEFINED_TAG_IN_LAST_TAG_POSITION			= -6200,
CFE_DUPLICATE_VERSION							= -6300,
CFE_ALLOCATION_FAILURE							= -6400,
CFE_NULL_HANDLE									= -6500,
CFE_NOROOM										= -6600,
CFE_INVALID_STRUCTID							= -6700,
CFE_INVALID_TAGNUM								= -6800,
CFE_RECURSIVE_DEPTH_LIMIT						= -6900,
CFE_STRUCT_MODE									= -7000,
CFE_EMPTY_STRUCT								= -7100,
CFE_CANT_SET_TAGNUM								= -7200,
CFE_CANT_GET_TAGNUM								= -7300,
CFE_CANT_SET_STRUCTNUM							= -7400,
CFE_CANT_GET_STRUCTNUM							= -7500,
CFE_NULL_CF_STRUCTURE_POINTER					= -7600,
CFE_CANT_OPEN_FILE								= -7700,
CFE_CANT_FIND_VERSION							= -7800,
CFE_INVALID_CHOICE								= -7900,
CFE_INVALID_OPTION								= -8000,
CFE_UNEXPECTED_REPEAT_TAG						= -8100,
CFE_UNEXPECTED_VERSION_TAG						= -8200,
CFE_UNEXPECTED_BODYLENGTH_TAG					= -8300,
CFE_INVALID_REPEAT_TAG							= -8400,
CFE_MAX_ISN_SIZE								= -8500,
CFE_UNEXPECTED_CHECKSUM_TAG						= -8600,
CFE_CANT_SET_STRUCT_TAG_FIELD					= -8700,
CFE_CANT_FIND_STRUCT_TAG						= -8800,
CFE_CANT_CLOSE_FILE								= -8900,
CFE_INVALID_TIMESTAMP							= -9000,
CFE_MISSING_OPTIONS_TAG							= -9100,
CFE_DUPLICATE_OPTIONS_TAG						= -9200,
CFE_INVALID_REPEAT_VALUE						= -9300,
CFE_INVALID_DAY_OF_MONTH						= -9400,
CFE_UNEXPECTED_OPTIONS_TAG						= -9500,
CFE_UNEXPECTED_STRUCTURE_TAG					= -9600,
CFE_THIRD_TAG_NOT_OPTIONS_TAG					= -9700,
CFE_INVALID_STRUCTURE_DEFINITION				= -9800,
CFE_CANT_READ_FILE								= -9900,
CFE_INVALID_STRUCT_TAGNUM						= -10000,
CFE_NO_STRUCTURE_DEFINITION_LINES				= -10100,
CFE_INSERT_NODUP_ERROR							= -10200,
CFE_NULL_POINTER								= -10300,
CFE_UNDEFINED_TAG_IN_FIRST_4_TAG_POSITIONS		= -10400,
CFE_CANT_CONVERT_DOUBLE							= -10500,
CFE_CONVERSION_OVERFLOW							= -10600,
CFE_FIRM_SPECIFIC_TAG							= -10700,	/* tags used in FIX.4.1 and FIX.4.2 messages must be < 10000 */
CFE_UNEXPECTED_WHITESPACE_CHAR					= -10800,
CFE_FINISHED_PARSING_HEADER						= -11000,
CFE_INVALID_GROUP								= -11100,
CFE_MISSING_REQUIRED_TAGS						= -11300,
CFE_PUT_TAG_ERROR								= -11400,
CFE_STRTOUL_ERROR								= -11500,
CFE_PUT_STRUCT_TAG_ERROR						= -11600,
CFE_DUPLICATE_HEADER_TAG						= -11800,
CFE_TAG_GET_ERROR								= -11900,
CFE_TAG_SET_ERROR								= -12000,
CFE_TAG_SET_STRUCT_ERROR						= -12100,
CFE_DUPLICATE_TRAILER_TAG						= -12200,
CFE_MISSING_TRAILING_DELIMETER					= -12300,
CFE_TAGNUM_INVALID_DIGIT						= -12400,
CFE_TAGNUM_STRTOUL_ERROR						= -12500,
CFE_MISSING_BUFEND_DELIMETER					= -12600,
CFE_CKSUM_INVALID_DIGIT							= -12700,
CFE_CKSUM_STRTOUL_ERROR							= -12800,
CFE_INVALID_DIGIT								= -12900,
CFE_CKSUM_CONVERSION_ERROR						= -13000,
CFE_TAGNUM_CONVERSION_ERROR						= -13100,
CFE_INVALID_NESTED_STRUCT_LENGTH				= -13200,
CFE_INVALID_NESTED_STRUCT_TYPE					= -13300,
CFE_INVALID_NESTED_STRUCT_NUM					= -13400,
CFE_INVALID_NESTED_STRUCT_TAGNUM				= -13500,
CFE_INVALID_PARSE								= -13600,
CFE_PARTIAL_MESSAGE								= -13700,
CFE_BODYLENGTH_CONVERSION_ERROR					= -13800,
CFE_OPTIONS_CONVERSION_ERROR					= -13900,
CFE_NON_BLK_MSG                                 = -14000,
CFE_BLK_NOT_FOR_FIX                             = -14100,
CFE_BLK_OPTION_INVALID							= -14200,
CFE_NULL_CF_STATUS_POINTER                      = -14300,
CFE_OPTIONS_TAG_OVERFLOW						= -14400,
CFE_SMID_EMITTER_ERROR                          = -14500,
CFE_SMID_INSTANCE_ERROR                         = -14600,
CFE_SMID_SUBJECT_ERROR                          = -14700,
CFE_SMID_SEQUENCE_ERROR                         = -14800,
CFE_SMID_INVALID_ITEM_ID                        = -14900,
CFE_SMID_NOT_SMID_TAG                           = -15000,
CFE_NOT_CANONICAL_MSG							= -15100,
CFE_CANT_ADD_BIT_FIELD_TAG                      = -15200,
CFE_CANT_EDIT_BLK_MSG                           = -15300,
CFE_SMID_EIS_ERROR								= -15400,
CFE_CK_SMID_FIELD_ERROR							= -15500,
CFE_LAST_FIELD_NOT_CALLED						= -15600,
CFE_INVALID_OPTION_FIRST_BLK_MSG				= -15700,
CFE_INVALID_OPTION_BLK_MSG						= -15800,
CFE_MISSING_REQUIRED_BODY_TAGS                  = -15900,
CFE_INVALID_TAG_FOR_CURRENT_MSGTYPE             = -16000,
CFE_MUTULEXCLUSIVE_TAG_FOUND					= -16100,
CFE_TAG_REPEATED_OUTSIDE_GROUP					= -16200,
CFE_MISSING_CONDITIONAL_BODY_TAG				= -16300,
CFE_UNDEFINED_MSG_TYPE							= -16400,
CFE_MSG_TYPE_IS_TOO_LONG						= -16500,
CFE_NO_BIT_TAG_FOUND							= -16600,
CFE_INVALIDE_BIT_TAG_POSITION					= -16700,
CFE_PRIMARY_TAG_VALUE_BUFFER_OVERFLOW			= -16800,
CFE_PRIMARY_TAG_VALUE_CONVERSION_ERROR			= -16900,
CFE_PRIMARY_TAG_NOT_BIT_FIELD_TYPE				= -17000,
CFE_SMID_SEPARATOR_NOT_FOUND					= -17100,
CFE_INVALID_COLUMN_SIZE							= -17200,
CFE_CHECKSUM_NOT_FOUND							= -17300,
CFE_UNKNOWN_MESSAGE								= -17400,
CFE_CANT_UPDATE_OR_DELETE_LIST					= -17500,
CFE_CANT_DELETE_REQUIRED_TAG					= -17600,
CFE_INVALID_INSERT_POSITION						= -17700,
CFE_BUF_SIZE_IS_TOO_BIG							= -17800,
CFE_INVALID_TAG_FOR_GROUP						= -17900,
CFE_DUPLIDATE_TAG_IN_GROUP						= -18000,
CFE_NESTED_GROUP_INCOMPLETE						= -18100,
CFE_NO_OPEN_GROUP								= -18200,
CFE_GROUP_NOT_FOUND								= -18300,
CFE_INSTANCE_NOT_FOUND							= -18400,
CFE_DUPLICATE_GROUP								= -18500,
CFE_NESTED_GROUP_NOT_FOUND						= -18600,
CFE_NESTED_INSTANCE_NOT_FOUND					= -18700,
CFE_INVALID_GROUP_ID							= -18800,
CFE_MISSING_GROUP_END							= -18900,
CFE_MAX_NEST_LEVEL_EXCEED						= -19000,
CFE_UNKNOWN_GROUP								= -19100,
CFE_INVALID_NESTED_GROUP						= -19200,
CFE_CANT_DELETE_LAST_INSTANCE					= -19300,
CFE_INSTANCE_NBR_REQUIRED						= -19400,
CFE_GROUP_NAME_TOO_LONG    			 			= -19400, /* needed only for backward compatible */
CFE_FULL_VALIDATION_REQUIRED					= -19500,
CFE_LEADING_ZERO_NOT_ALLOWED					= -19600,
CFE_FIRST_TAG_IN_GROUP_REQUIRED					= -19700,
CFE_MISSING_SUB_TYPE							= -19800,
CFE_TOO_MANY_GROUP_INSTANCE                     = -19900,

/* used by Java native interfaces 20000 - 21000 */
CFE_NULL_OBJECT_POINTER				= -20000,
CFE_INVALID_DETAIL_OBJECT			= -20001,
CFE_INVALID_OUTGOING_OBJECT			= -20002,
CFE_RETURN_OBJ_CREATION_FAILURE			= -20003,
CFE_UNKNOWN_FIELD_TYPE				= -20004,

/*   */
CFE_GET_CLOCKTIME_FAILURE						= -21100,

CFE_INTERNAL_MSGTYPE_TABLE_ERROR		= -29999,
CFE_MISC_ERROR					= -30000
};


enum{
CFE2_ALLOCATION_FAILURE							= -1,
CFE2_UNEXPECTED_WHITESPACE						= -2,
CFE2_RANGE_ERROR								= -3,
CFE2_MISSING_DELIMITER							= -4,
CFE2_INVALID_CHARACTER							= -5,
CFE2_INVALID_TAG_TYPE							= -6,
CFE2_RAWLEN_OVERFLOW							= -7,
CFE2_BUFFER_OVERFLOW							= -8,
CFE2_CANT_CONVERT_DOUBLE						= -9,
CFE2_STRTOL_ERROR								= -10,
CFE2_STRTOUL_ERROR								= -11,
CFE2_STRTOD_ERROR								= -12,
CFE2_INVALID_DAY_OF_MONTH						= -13,
CFE2_INVALID_FLOAT_CHARACTER					= -14,
CFE2_INVALID_BOOLEAN_CHARACTER					= -15,
CFE2_WITHIN_STRUCTURE							= -16,
CFE2_RAWLENGTH_ERROR							= -17,
CFE2_UNPRINTABLE_CHARACTER						= -18,
CFE2_INVALID_INT_CHARACTER						= -19,
CFE2_ZERO_TAG_LENGTH							= -20,
CFE2_INT_CONVERSION_ERROR						= -21,
CFE2_INVALID_LENGTH						= -22,
CFE2_INVALID_SMID                                               = -23,
CFE2_INVALID_FORMAT						= -24,
CFE2_EMITTER_FORMAT_ERROR					= -25,
CFE2_INSTANCE_FORMAT_ERROR					= -26,
CFE2_SUBJECT_FORMAT_ERROR					= -27,
CFE2_SUBJECT_LENGTH_ERROR					= -28,
CFE2_SEQUENCE_LENGTH_ERROR					= -29,
CFE2_POSITIVE_VALUE_REQUIRED					= -30,
CFE2_NEGATIVE_VALUE_NOT_ALLOWED					= -31,

CFE2_CK_DATE_TIME_ERROR						= -70	/* -70 to -99 reserved for ck_date_time error location values */
};

enum 
{
	SMID_EMITTER_INVALID_LENGTH				= -2,
	SMID_SUBJECT_INVALID_LENGTH				= -3,
	SMID_INSTANCE_INVALID_VALUE				= -4
};

enum {
DTE_UTCTIMESTAMP_INVALID_LENGTH					= -2,
DTE_UTCTIMESTAMP_FORMAT_ERROR					= -3,
DTE_UTCTIMESTAMP_RANGE_ERROR					= -4,
DTE_UTCTIMEONLY_INVALID_LENGTH					= -5,
DTE_UTCTIMEONLY_FORMAT_ERROR					= -6,
DTE_UTCTIMEONLY_RANGE_ERROR					= -7,
DTE_UTCDATE_INVALID_LENGTH					= -8,
DTE_UTCDATE_FORMAT_ERROR					= -9,
DTE_UTCDATE_RANGE_ERROR						= -10,
DTE_MONTHYEAR_INVALID_LENGTH					= -11,
DTE_MONTHYEAR_FORMAT_ERROR					= -12,
DTE_MONTHYEAR_RANGE_ERROR					= -13
};

/* warning return codes CFW_... ( >0 ) */
enum
{
CFW_OVERFLOW					= 100,
CFW_UNDEFINED_TAG				= 200,
CFW_LAST_MESSAGE				= 300,
CFW_BLK_FIRST_MSG                               = 400,
CFW_BLK_NEXT_MSG                                = 500,
CFW_BLK_LAST_MSG                                = 600,
CFW_NON_BLK_MSG                                 = 700,
CFW_PARTIAL_MESSAGE				= 800,
CFW_BUFFER_OVERFLOW				= 900

};

/* General define */

#define CFG_SEV_TRACE	0
#define CFG_SEV_INFO	1
#define CFG_SEV_WARN	2
#define CFG_SEV_ERROR	3
#define CFG_SEV_FATAL	4

#define CFG_PRI_LOW	1
#define CFG_PRI_MEDIUM	2
#define CFG_PRI_HIGH	3

#define CFG_STAT_SUCCESS	0
#define CFG_STAT_FAILURE	1

#define CFG_SMID_EID	1
#define CFG_SMID_INST	2
#define CFG_SMID_SUBJ	3
#define CFG_SMID_SEQ	4
#define CFG_SMID_EIS	5 /* emitter:instance:subject */
#define CFG_SMID_EISS   6 /* emitter:instance:subject:sequence */

#define CFG_MINSMIDLENGTH       13
#define CFG_MAXSMIDLENGTH	60
#define CFG_EMITTERLENGTH	6
#define CFG_INSTANCELENGTH	2
#define CFG_MINSUBJECTLENGTH	1
#define CFG_MAXSUBJECTLENGTH    40
#define CFG_MINSEQUENCELENGTH	1
#define CFG_MAXSEQUENCELENGTH   9
#define CFG_MINSMIDINSTANCE	0
#define CFG_MAXSMIDINSTANCE     99
#define CFG_MINSMIDSEQUENCE     0
#define CFG_MAXSMIDSEQUENCE     999999999
#define CFG_INSTANCE_OFFSET     (CFG_EMITTERLENGTH+1)
#define CFG_SUBJECT_OFFSET      (2+CFG_EMITTERLENGTH+CFG_INSTANCELENGTH)
#define SMID_F_S   ':'	/* SMID field separate */


/*** Field value related definitions ***/

#define CF_TRUE		"Y"
#define CF_FALSE	"N"

#define N_ERROR_DETAIL_INFO	5
#define EDET_LINE_SIZE	80


/* TANDEM DEFINES END */

/* TANDEM STRUCTS BEGIN */


struct INTERNAL_STRUCTNUM
{
	int struct_tagnum;
	unsigned internal_struct_num;
};


struct ErrorDetailInfo
{
	int code1;
	char code1_text[EDET_LINE_SIZE];
	int code2;
	char code2_text[EDET_LINE_SIZE];
};

struct ErrorDetail
{
	int line;
	char file[EDET_LINE_SIZE];
	int return_code;
	char return_code_text[EDET_LINE_SIZE];
	int aux_code;
	char aux_code_text[EDET_LINE_SIZE];
	int n_actual_occurrences;
	int n_filled_in_occurrences;
	struct ErrorDetailInfo error_detail_info[N_ERROR_DETAIL_INFO];
};


/* TANDEM STRUCTS END */

#define TG_NOT_DEFINED	0x0
#define	TG_HEADER_TAG	0x1
#define	TG_BODY_TAG		0x2
#define	TG_TRAILER_TAG	0x3
#define TG_REQUIRED_TAG	0x4



#ifndef __cplusplus
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
struct cf_handle*
CF_Init(
    unsigned int options,
    unsigned max_msg_length,
    int *error );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_cleanup(
    struct cf_handle* handle,
    unsigned int options );
#endif

#ifdef __cplusplus
class ExtractItem;
#else
typedef struct _ExtractItem2 ExtractItem;
#endif



struct _ExtractItem
{
    int tag_num;
    unsigned repeat;
    void *buf;
    unsigned buf_len;
	unsigned *rtn_buf_len;
    ExtractItem *next;
    int result;
};

struct _ExtractItem2
{
	struct _ExtractItem ei_data;
};


#ifdef __cplusplus
class ExtractItem
{
public:
    ExtractItem();
    ExtractItem(
    	int tag_num,
        unsigned repeat,
        void *buf,
        unsigned buf_len,
		unsigned *rtn_buf_len,
        ExtractItem *item = (ExtractItem*)NULL);
        ~ExtractItem();
#endif
	void
	ExtractItem__constructor(
		ExtractItem *ei,
		int tag_num,
		unsigned repeat,
		void *buf,
		unsigned buf_len,
		unsigned *rtn_buf_len,
		ExtractItem *item );
#ifndef C_INLINE
	int
	ExtractItem__GetResult(
		ExtractItem *ei );
	void
	ExtractItem__SetResult(
		ExtractItem *ei,
		int result2 );
	void
	ExtractItem__Set_next(
		ExtractItem *ei,
		ExtractItem *next );
		ExtractItem *
		ExtractItem__Get_next(
		ExtractItem *ei );
	void
	ExtractItem__Set_tag_num(
		ExtractItem *ei,
		int tag_num );
	int
	ExtractItem__Get_tag_num(
		ExtractItem *ei );
	void
	ExtractItem__Set_repeat(
		ExtractItem *ei,
		unsigned repeat );
	unsigned
	ExtractItem__Get_repeat(
		ExtractItem *ei );
	void
	ExtractItem__Set_buf_len(
		ExtractItem *ei,
		unsigned buf_len );
	unsigned
	ExtractItem__Get_buf_len(
		ExtractItem *ei );
	void
	ExtractItem__Set_buf(
		ExtractItem *ei,
		void *buf );
	void *
	ExtractItem__Get_buf(
		ExtractItem *ei );
	void
	ExtractItem__Set_rtn_buf_len(
		ExtractItem *ei,
		unsigned *rtn_buf_len );
	unsigned *
	ExtractItem__Get_rtn_buf_len(
		ExtractItem *ei );
#endif
#ifdef __cplusplus
private:
	struct _ExtractItem ei_data;
};
#endif



struct _ExtractList
{
    int GetNext_flag;
    int GetNext_flag2;
    ExtractItem *list;
    ExtractItem *current;   /* for GetNext call */
    ExtractItem *current2;  /* for GetNext call */
    ExtractItem *at_end;
    int result;
};

#ifndef __cplusplus
typedef struct _ExtractList ExtractList;
#endif


#ifdef __cplusplus

class ExtractList
{
	friend class IncomingCanonical;
	friend class OutgoingCanonical;
friend int insert_update_tag(
	unsigned choice,
	unsigned int options,
	unsigned char *dup_check_tbl,
	struct TagData *tagdata_p,
	char *inbuf,
	unsigned inbuf_len,
	unsigned max_inbuf_len,
	unsigned *rtn_inbuf_len,
	char *outbuf,
	unsigned max_outbuf_len,
	unsigned *rtn_outbuf_len,
	char *buf,
	char *buf_end,
	int tag_num,
	void *field,
	unsigned length,
	unsigned version );

friend int add_instance(
	int options,
	char **buf,
	int buf_len,
	int *max_buf_len,
	int *rtn_buf_len,
	int group_id,
	void *field,
	int length,
	int version,
	char    *orig_buf );

public:
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    ExtractList();
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    ~ExtractList();
#else
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_ExtractList_Init(
		struct _ExtractList **el);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_ExtractList_Cleanup(
		struct _ExtractList *el);
#endif
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_append(
#ifndef __cplusplus
		struct _ExtractList *el,
#endif
		int tag_num,
		unsigned repeat,        /* 1,2 ... */
		void *buf,
		unsigned buf_len,
		unsigned *rtn_buf_len);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_GetNextResult(
#ifndef __cplusplus
		struct _ExtractList *el,
#endif
		int *result_p );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void
	CF_display(
#ifndef __cplusplus
		struct _ExtractList *el
#endif
		);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	void
	ExtractList__remove(
		struct _ExtractList *el);
#ifdef __cplusplus
private:
#endif
	int
	CF_GetResult(
#ifndef __cplusplus
		struct _ExtractList *el
#endif
		);
	void
	ExtractList__constructor(
		struct _ExtractList *el);
	void
	ExtractList__destructor(
			struct _ExtractList *el);
	int
	ExtractList__Init(
		struct _ExtractList *el);
	int
	ExtractList__GetNext(
		struct _ExtractList *el,
		ExtractItem *item, 
		int *at_end );
	int
	ExtractList__SetResult(
		struct _ExtractList *el,
		int result2 );
	int
	ExtractList__is_empty(
		struct _ExtractList *el);
#ifdef never
/* not currently used */
    int
    ExtractList__insert(
        int tag_num,
        unsigned repeat,        /* 1,2 ... */
        void *buf,
        unsigned buf_len );
#endif

#ifdef __cplusplus
	struct _ExtractList el_data;
};

#endif

#ifdef __cplusplus

#define	_ExtractList__constructor( el)\
	(el)->ExtractList__constructor( (struct _ExtractList*)NULL)
#define	_CF_append( el, tag_num, repeat, buf, buf_len, rtn_buf_len )\
	(el)->CF_append( tag_num, repeat, buf, buf_len, rtn_buf_len )
#define	_CF_GetResult( el)\
	(el)->CF_GetResult( )
#define	_CF_GetNextResult( el, result_p )\
	(el)->CF_GetNextResult( result_p )
#define	_CF_display( el)\
	(el)->CF_display( )
#define	_ExtractList__Init( el)\
	(el)->ExtractList__Init( (struct _ExtractList*)NULL)
#define	_ExtractList__GetNext( el, item, at_end )\
	(el)->ExtractList__GetNext( (struct _ExtractList*)NULL, item, at_end )
#define	_ExtractList__remove( el)\
	(el)->ExtractList__remove( (struct _ExtractList*)NULL)
#define	_ExtractList__SetResult( el, result2 )\
	(el)->ExtractList__SetResult( (struct _ExtractList*)NULL, result2 )
#define	_ExtractList__is_empty( el)\
	(el)->ExtractList__is_empty( (struct _ExtractList*)NULL)

#else

#define	_ExtractList__constructor( el)\
	ExtractList__constructor( el)
#define	_CF_append( el, tag_num, repeat, buf, buf_len, rtn_buf_len )\
	CF_append( el, tag_num, repeat, buf, buf_len, rtn_buf_len )
#define	_CF_GetResult( el)\
	CF_GetResult( el)
#define	_CF_GetNextResult( el, result_p )\
	CF_GetNextResult( el, result_p )
#define	_CF_display( el)\
	CF_display( el)
#define	_ExtractList__Init( el)\
	ExtractList__Init( el)
#define	_ExtractList__GetNext( el, item, at_end )\
	ExtractList__GetNext( el, item, at_end )
#define	_ExtractList__remove( el)\
	ExtractList__remove( el)
#define	_ExtractList__SetResult( el, result2 )\
	ExtractList__SetResult( el, result2 )
#define	_ExtractList__is_empty( el)\
	ExtractList__is_empty( el)

#endif


#ifdef __cplusplus
class TagList;
#else
typedef struct _TagList TagList;
#endif


/******************************************************
Start Repeating group related defines 
******************************************************/
#ifdef __cplusplus
class Tag;
#else
typedef struct _Tag Tag;
#endif

typedef struct DecimalRangeDef
{
	unsigned short		min;
	unsigned short		max;
} DecimalRange;
	

typedef struct NestGroupDef
{
	unsigned short		start_index;
	unsigned short		count;
	struct NestGroupDef	*next;
} NestGroup;

typedef struct
{
   	unsigned short  max_count;
   	unsigned short  current_count;
  	unsigned int    parse_id;

	NestGroup *begin;
	NestGroup *current;       /* for GetNext call */
	NestGroup *end;

} NestGroupList;
					
typedef struct
{
	unsigned int		parse_id;
	union Group_elem
	{
		Tag		*tag;
		NestGroup	*group;
	} elem;
} GroupElement;
												
typedef struct GroupDefinition_def
{
	int		group_id;
	char	        group_name[50];
	const MsgTag*	defined_tag_list;
	unsigned short	defined_tag_nbr;
	unsigned short	required_tag_nbr;
	unsigned short	nest_group_nbr;
	int 		*relational_tag;

} GroupDefinition;

typedef struct
{
	int				groupId;
	unsigned int	parse_id;
	unsigned short	startPos;
	unsigned short	groupSize;
   	unsigned short  max_instance;
   	unsigned short  instance_count;
	unsigned short	elemListLen;
	NestGroupList	*nest_list;
	GroupElement	*group_elem_list;

} _IncomingGroup;

typedef struct
{
	int 		group_id;
	int 		instance_count;
	int 		instance_nbr;
	short		startIndex;
	int		current_tag_index;
	unsigned int    required_tag_count;
	unsigned char*  map;
} OutgoingGroup;

typedef struct
{
	int 		group_id;
	short		startIndex;
	short 		count;
} MsgGroup;

union ushort_char2
{
    unsigned short usc2_ushort;
    char usc2_char2[2];
};


struct tag_value_t4
{
	unsigned short struct_repeat;
	unsigned short struct_n_tags;
	unsigned short struct_size;
};

union tag_value_t
{
    int tv_int;
    double tv_float;
	struct tag_value_t4 tv_int_array;
};

struct tag_value_t3
{
    union tag_value_t tv_value;
    char *tv_string;
};

union tag_value_t2
{
    char *tv_string;
    TagList *tv_dup_tag_list;
	_IncomingGroup *group;
    unsigned tv_value_idx;
};


struct _Tag
{
    unsigned parse_id;
    union tag_value_t2 tag_value;
    BitField tag_type: 5;
    BitField undefined_tag_bit: 1;             /* 1=last field within field group */
    BitField last_field_bit: 1;             /* 1=last field within field group */
    BitField field_group: 2;        /* 1=header, 2=body, 3=trailer */
    BitField dup_tag_list_bit: 1;
    BitField group_list_bit: 1;
	BitField within_struct_bit: 1;
	BitField int_array_bit: 1;

	unsigned sequence;		/* sequence within message */
	TagMsgInfo msg_info;
	unsigned short count;
};

#ifndef __cplusplus
struct _IncomingCanonical;
#endif

/********************************************************/

#ifdef __cplusplus
class StructDef;
#else
typedef struct _StructDef StructDef;
#endif

#ifdef __cplusplus
class Tag
{
public:
    Tag();
    ~Tag();         /* NOTE: DO NOT!! PUT CODE FOR DESTRUCTOR HERE. */
#endif
    void
    Tag__constructor(
        struct _Tag *tg);
	void
	Tag__destructor(
		Tag *tp );
#ifndef C_INLINE
    void
    Tag__set_tag_type(
        struct _Tag *tg,
        unsigned short tag_type );
    void
    Tag__set_sequence(
        struct _Tag *tg,
        unsigned short sequence );
    void
    Tag__set_msg_info(
        struct _Tag *tg,
        TagMsgInfo msg_info );
    void
    Tag__set_count(
        struct _Tag *tg,
        unsigned short count );
        union tag_value_t2
        Tag__get_tag_value2(
        struct _Tag *tg);
    void
    Tag__set_parse_id(
        struct _Tag *tg,
        unsigned int parse_id );
    unsigned int
    Tag__get_parse_id(
        struct _Tag *tg);
    void
    Tag__set_tag_value2(
        struct _Tag *tg,
        union tag_value_t2 tag_value2);
    unsigned short
    Tag__get_tag_type(
        struct _Tag *tg);
    unsigned short
    Tag__get_sequence(
        struct _Tag *tg);
    TagMsgInfo
    Tag__get_msg_info(
        struct _Tag *tg);
    unsigned short
    Tag__get_count(
        struct _Tag *tg);
    unsigned int
    Tag__get_field_group(
        struct _Tag *tg);
    void
    Tag__set_field_group(
        struct _Tag *tg,
        unsigned int field_group );
    unsigned int
    Tag__get_undefined_tag_bit(
        struct _Tag *tg);
    void
    Tag__set_undefined_tag_bit(
        struct _Tag *tg,
        unsigned int undefined_tag_bit );
    unsigned int
    Tag__get_last_field_bit(
        struct _Tag *tg);
    void
    Tag__set_last_field_bit(
        struct _Tag *tg,
        unsigned int last_field_bit );
	unsigned int
	Tag__get_within_struct_bit(
		struct _Tag *tg);
    void
    Tag__set_within_struct_bit(
        struct _Tag *tg,
        unsigned int within_struct_bit );
	unsigned int
	Tag__get_int_array_bit(
		struct _Tag *tg);
    void
    Tag__set_int_array_bit(
        struct _Tag *tg,
        unsigned int int_array_bit );
    TagList *
    Tag__get_dup_tag_list(
        struct _Tag *tg);
#endif	
	void
	Tag__set_msg_type_info(
		struct _Tag *tg, 
		TagMsgInfo msg_info);
	CS_BOOL
	Tag__ck_tag_presence(
		struct _Tag *tg);
	int
	Tag__chk_updt_msg_type_info(
		CS_BOOL msgChk,
        struct _Tag *tg,
		int tag_num,
		int *groupIndex);
    int
	Tag__chk_reset_msg_type_info(
		struct _Tag *tg);
    void
    Tag__set_tag_len(
		struct tag_value_t3 *tv,
        struct _Tag *tg,
        unsigned short tag_len );
    int
    Tag__set_dup_tag_list(
        struct _Tag *tg,
        TagList *dup_tag_list2 );
    unsigned short
    Tag__get_tag_len(
		struct tag_value_t3 *tv,
        struct _Tag *tg);
    unsigned short
    Tag__get_tag_len2(
		struct tag_value_t3 *tv,
        struct _Tag *tg);
	int
	Tag__get(
		struct _IncomingCanonical *ic,
		struct _Tag *tg,
		unsigned int ic_options,
		unsigned int options,
		void **buf,             /* array */
		unsigned *max_buf_len,  /* array */
		unsigned *rtn_buf_len,  /* array */
		unsigned offset,
		unsigned count );
#ifdef __cplusplus
    int
	Tag__get2(
		struct _IncomingCanonical *ic,
		CF_TagData &tagData);
#endif
	int
	Tag__get_with_Conversion(
		struct _IncomingCanonical *ic,
		struct _Tag *tg,
		unsigned int ic_options,
		unsigned int options,
		void **buf,             /* array */
		unsigned *max_buf_len,  /* array */
		unsigned *rtn_buf_len,  /* array */
		unsigned offset,
		unsigned count );
	int
	Tag__set(
        struct _IncomingCanonical *ic,
		unsigned options,
		int tag_num,
        struct _Tag *tg,
        unsigned int parse_id,
        unsigned short tag_type,
        char *tag,
        unsigned int field_group,
		char **p,
		char *buf_end);
	int
	Tag__set_no_Conversion(
		struct _IncomingCanonical *ic,
		unsigned options,
		struct _Tag *tg,
		unsigned int parse_id,
		unsigned short tag_type,
		char *tag,
		unsigned int field_group,
		char **pp,
		char *buf_end);
	int
	Tag__set_struct(
		struct _IncomingCanonical *ic,
		StructDef *sd,
		unsigned short blk_repeat,
		unsigned short blk_seq,
		struct _Tag *tg,
		unsigned int parse_id,
		unsigned short tag_type,
		char **p_seg1,
		unsigned int field_group,
		char *buf_end);
    void
    Tag__print_tag(
        struct _Tag *tg,
		struct tag_value_t3 *tv,
        unsigned short tag_type,
        unsigned tag_len,
		unsigned offset);
#ifdef __cplusplus
private:
#endif
#ifndef C_INLINE
    void
    Tag__set_last_field_bit2(
        struct _Tag *tg,
        unsigned int last_field_bit );
    void
    Tag__set_undefined_tag_bit2(
        struct _Tag *tg,
        unsigned int undefined_tag_bit );
    void
    Tag__set_field_group2(
        struct _Tag *tg,
        unsigned int field_group );
    void
    Tag__set_parse_id2(
        struct _Tag *tg,
        unsigned int parse_id );
    void
    Tag__set_tag_type2(
        struct _Tag *tg,
        unsigned short tag_type );
    void
    Tag__set_within_struct_bit2(
        struct _Tag *tg,
        unsigned int within_struct_bit );
    void
    Tag__set_int_array_bit2(
        struct _Tag *tg,
        unsigned int int_array_bit );
    TagList *
    Tag__get_dup_tag_list2(
        struct _Tag *tg);
    unsigned short
    Tag__get_tag_type2(
        struct _Tag *tg);
	int
	Tag__get_orig(
		struct _IncomingCanonical *ic,
		struct _Tag *tg,
		struct tag_value_t3 *tv,
		unsigned int ic_options,
		unsigned int options,
		char *buf,
		unsigned buf_size,
		unsigned *rtn_buf_len,
		unsigned offset,
		unsigned count );

#endif

#ifdef __cplusplus
    struct _Tag tg_data;
};
#endif


struct tag_array_item
{
	Tag *tp;
	unsigned offset;
	unsigned blk_count;
};



#ifdef __cplusplus
class TagItem;
#else
typedef struct _TagItem2 TagItem;
#endif


struct _TagItem
{
    Tag tag;
    int tag_num;
    TagItem *next;
};


struct _TagItem2
{
	struct _TagItem ti_data;
};


#ifdef __cplusplus
class TagItem
{
public:
    TagItem();
    TagItem(
        int tag_num2,
        TagItem *item = (TagItem*)NULL);
    ~TagItem();
#endif
	void
	TagItem__constructor(
		TagItem *ti,
		int tag_num2,
		TagItem *item);
#ifndef C_INLINE
	void
	TagItem__Set_next(
		TagItem *ti,
		TagItem *next );
	TagItem *
	TagItem__Get_next( TagItem *ti );
	void
	TagItem__Set_tag_num(
		TagItem *ti,
		int tag_num );
	int
	TagItem__Get_tag_num(
		TagItem *ti );
	Tag *
	TagItem__Get_tag_ptr( TagItem *ti );
#endif
#ifdef __cplusplus
private:
    struct _TagItem ti_data;
};
#endif


struct _TagList
{
	unsigned rtn_repeat;	/* returned value from IncomingCanonical__get_new_tag_ptr_and_type */
	unsigned parse_id;		/* if given parse_id matches this one no unused slots exist on list */
	unsigned count2;
	unsigned parse_id_current;	/* parse_id associated with current pointer */
	unsigned total_tag_count;	/* includes bulk loaded tags */

    unsigned count;
    int GetNext_flag;
    TagItem *list;
    TagItem *current;       /* for GetNext call */
    TagItem *at_end;
};


#ifdef __cplusplus
class TagList
{
public:
    TagList();
    ~TagList();
#endif
	void
	TagList__destructor(
		struct _TagList *tl);
    int
    TagList__append(
        struct _TagList *tl,
        int tag_num,
        TagItem **item,
        unsigned *rtn_repeat );
#ifdef never
/* not currently used */
#ifdef __cplusplus
    int
    GetNext(
        TagItem &item );
#endif
#endif
	int
	TagList__FindItem(
		struct _IncomingCanonical *ic,
		struct _TagList *tl,
		unsigned int parse_id,
		int tag_num,
		TagItem **tip,
		struct tag_array_item *tag_array,
		unsigned max_tp,
		unsigned *n_tp,
		unsigned repeat,
		unsigned count );
    int
    TagList__FindUnused(
        struct _TagList *tl,
        unsigned int parse_id,
        TagItem **tip,
        unsigned *rtn_repeat );
    void
    TagList__remove(
        struct _TagList *tl );
    void
    TagList__display(
		struct _IncomingCanonical *ic,
        struct _TagList *tl,
        unsigned int parse_id );
    void
    TagList__xdisplay(
		struct _IncomingCanonical *ic,
        struct _TagList *tl,
        unsigned int parse_id );
#ifndef C_INLINE
    int
    TagList__is_empty(
        struct _TagList *tl);
	unsigned
	TagList__get_count(
		struct _TagList *tl);
	unsigned
	TagList__get_parse_id(
		struct _TagList *tl);
	void
	TagList__set_parse_id(
		struct _TagList *tl,
		unsigned parse_id);
	unsigned
	TagList__get_rtn_repeat(
		struct _TagList *tl);
	void
	TagList__set_rtn_repeat(
		struct _TagList *tl,
		unsigned rtn_repeat);
	unsigned
	TagList__get_total_tag_count(
		struct _TagList *tl);
	void
	TagList__set_total_tag_count(
		struct _TagList *tl,
		unsigned total_tag_count);
#endif
#ifdef never
/* not currently used */
    int
    TagList__insert(
        struct _TagList *tl,
        int tag_num,
        TagItem **item );
    void
    xremove();
#endif
#ifdef __cplusplus
private:
	void
	TagList__constructor(
		struct _TagList *tl);

	struct _TagList tl_data;
};
#endif




struct _TagNum
{
	int tagnum;		/* tag #0 is used to indicate a structure */
	int structnum;	/* the structure number is associated with the tag #0 */
	int struct_tagnum;
};

struct _StructDef
{
	unsigned short n_tags;		/* number of array elements in use */
	unsigned short n_tagnum;	/* number of elements in allocated tagnum array */
	struct _TagNum *tagnum;		/* in this array tag #0 is used to indicate a structure */
	unsigned short flags;		/* see below for values */
	unsigned version;			/* i.e. CANONICAL_1_00_ID */
	int struct_tag_num;			/* tag# associated with this structure */
};


#ifdef __cplusplus
class StructDef
{
public:
	StructDef();
	~StructDef();
#endif
#ifndef C_INLINE
	unsigned
	StructDef__GetVersion(
		struct _StructDef *sd);
	void
	StructDef__SetVersion(
		struct _StructDef *sd,
		unsigned version);
	unsigned short
	StructDef__get_n_tags(
		struct _StructDef *sd
	);
	void
	StructDef__set_n_tags(
		struct _StructDef *sd,
		unsigned short n_tags);
	int
	StructDef__get_struct_tag_num(
		struct _StructDef *sd
	);
	void
	StructDef__set_struct_tag_num(
		struct _StructDef *sd,
		int struct_tag_num);
	unsigned short
	StructDef__get_flags(
		struct _StructDef *sd
	);
	void
	StructDef__set_flags(
		struct _StructDef *sd,
		unsigned short flags);
	int
	StructDef__get_tagnum(
		struct _StructDef *sd,
		unsigned index);
	void
	StructDef__set_tagnum(
		struct _StructDef *sd,
		unsigned index,
		int tagnum);
	int
	StructDef__get_structnum(
		struct _StructDef *sd,
		unsigned index);
	void
	StructDef__set_structnum(
		struct _StructDef *sd,
		unsigned index,
		int structnum);
	int
	StructDef__get_struct_tagnum(
		struct _StructDef *sd,
		unsigned index);
	void
	StructDef__set_struct_tagnum(
		struct _StructDef *sd,
		unsigned index,
		int struct_tagnum);
	void
	StructDef__set_tagnum_p(
		struct _StructDef *sd,
		struct _TagNum *tagnum_p);
	unsigned short
	StructDef__get_n_tagnum(
		struct _StructDef *sd
	);
	void
	StructDef__set_n_tagnum(
		struct _StructDef *sd,
		unsigned short n_tagnum);
	struct _StructDef
	StructDef__get_sd_data(
		struct _StructDef *sd
	);
	void
	StructDef__set_sd_data(
		struct _StructDef *sd,
		struct _StructDef sd_data);
#endif

	int
	StructDef__destructor(
		struct _StructDef *sd);
#ifdef __cplusplus
private:
#endif
	int
	StructDef__constructor(
		struct _StructDef *sd);

#ifdef __cplusplus
	struct _StructDef sd_data;
};
#endif


struct _CF_Structure
{
	unsigned n_structdef_array;		/* # of array entries in use */
	unsigned structdef_array_size;	/* size of allocated structdef array */
	StructDef *structdef_array;		/* pointer to allocated structdef array */
	int n_struct_tag_xref_array;
	STRUCT_TAG_XREF *struct_tag_xref_array;

};

#ifndef __cplusplus
typedef struct _CF_Structure	CF_Structure;
#endif

typedef struct
{
	int status;
	int offset;
	int msg_len;
	int msg_count;
} CF_ParseStatus;


#ifdef __cplusplus
class CF_Structure
{
friend class OutgoingCanonical;
friend class IncomingCanonical;
public:
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	CF_Structure(
		unsigned array_size = N_STRUCTDEF_ARRAY);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	~CF_Structure();
#else
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_Structure_Init(
		struct _CF_Structure **cfs,
		unsigned array_size);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_Structure_Cleanup(
		struct _CF_Structure *cfs);
#endif
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_Structure_constructor(
		struct _CF_Structure *cfs,
		unsigned array_size);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_Structure_destructor(
		struct _CF_Structure *cfs);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PrintStructure(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		unsigned struct_num);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_LoadStructure(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		char *struct_def,
		unsigned *rtn_struct_num,
		unsigned version);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_LoadStructureList(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		char *file_name,
		char *structdef_buffer,
		struct INTERNAL_STRUCTNUM *isn,
		unsigned max_isn_size,
		unsigned *rtn_isn_size,
		unsigned line_size);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_LoadExtractListFromStructure(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		unsigned struct_num,
		ExtractList *el,
		int pass,
		unsigned version,
		unsigned tag_len_array[TEST_ARRAY_SIZE],
		unsigned *n_tag_num_array ,
		int tag_num_array[TEST_ARRAY_SIZE],
		unsigned tag_repeat_array[TEST_ARRAY_SIZE],
		union local_tag_value_t newbuf_array[TEST_ARRAY_SIZE],
		unsigned rtn_buf_len[TEST_ARRAY_SIZE]
		);
#ifdef __cplusplus
private:
#endif
	int
	CF_Structure_constructor2(
		struct _CF_Structure *cfs,
		unsigned array_size,
		StructDef **sd,
		STRUCT_TAG_XREF **stx);
	char*
	sgets(
		char *s,
		int n,
		char **stream );
		unsigned
		cf_get_max_line_size(
		char *s);
	int
	CF_LoadStructuresFromFile(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		char *file_name,
		struct INTERNAL_STRUCTNUM *isn,
		unsigned max_isn_size,
		unsigned *rtn_isn_size,
		unsigned line_size);
	int
	CF_LoadStructuresFromTable(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		char *user_structdef_string,
		struct INTERNAL_STRUCTNUM *isn,
		unsigned max_isn_size,
		unsigned *rtn_isn_size);
	int
	CF_LoadStructuresFromFile2(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		struct INTERNAL_STRUCTNUM *isn,
		unsigned max_isn_size,
		unsigned *rtn_isn_size,
		unsigned line_size,
		FILE *fp,
		char *line_buf,
		char *structdef_string);
	int
	CF_DefineStructure(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		int struct_tag_num,
		unsigned *rtn_struct_num,
		unsigned version,
		unsigned tag_count);
	int
	CF_AddTag2Structure(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		int tagnum,
		unsigned struct_num
		);
	int
	CF_AddStructure2Structure(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		unsigned struct_num_to_add,
		unsigned struct_num,
		int struct_tagnum);
	int
	CF_Structure__get_struct_num(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned int options,
		int struct_tag_num,
		unsigned *rtn_struct_num,
		unsigned version);
	int
	CF_Structure__set_NonRepeatingIntsOnly(
#ifndef __cplusplus
		struct _CF_Structure *cfs,
#endif
		unsigned struct_num
		);

#ifdef __cplusplus
	struct _CF_Structure cfs_data;
};
#endif


struct tag_seq
{
	unsigned short tag_num;
	Tag *tp;
	unsigned short repeat;
};

struct _IncomingCanonical
{
	int last_int;
    unsigned max_msg_length;
    unsigned int parse_id;
    unsigned next_field;
    unsigned n_version_array;                       /* # entries in version_array */
    unsigned version_array[N_VERSION_ARRAY];
    TagList unknown_tag_list;
	char *buf;
	char *blk_buf;
    unsigned int blk_msg_cnt;
    unsigned int blk_flag;
	unsigned buf_len;
	unsigned blk_len;
    char *new_buf;
    unsigned new_buf_len;
    unsigned int options;
	struct ErrorDetail error_detail;
	unsigned n_required_tags;

    Tag *tag_array_standard;
	Tag *tag_array_user;
	Tag *tag_array_siac;
	Tag *tag_array_siac2;
		
	const struct TagData *CF_TagTypeDef_standard_p;
    const struct TagData *CF_TagTypeDef_user_p;
    const struct TagData *CF_TagTypeDef_siac_p;
    const struct TagData *CF_TagTypeDef_siac_p2;

	struct tag_seq *new_tag_seq;
	unsigned max_tag_seq;
    unsigned n_tag_seq;

	struct tag_value_t3 *new_tag_value_t3;
	unsigned max_tag_value_t3;
	unsigned n_tag_value_t3;

	struct tag_value_t4 tag_value_t4;
	unsigned tag_index;
	unsigned struct_count;
	unsigned offset;
	unsigned int_array_bit;
	int valid_parse;
	unsigned char *dup_check_tbl;
	const MessageTypeInfo *msg_info;
	int current_bit_field;
	unsigned int cfmo_options;
	unsigned short bit_offset;
	short sys_endian_flag;
	CS_BOOL bit_tag_mode;
	CS_BOOL nbo_conversion;
	CS_BOOL waitSubType;

    /**  RPG **/
	_IncomingGroup	*group_set;
	int		group_nest_level;
	int	group_index;
	int	group_nbr;
	int	instance_index;
	int	group_tag_index;
	/**  RPG **/
    const MsgVersionAttribsField  *version_attribs;
	int versionId;

#ifdef __TANDEM
		struct tag_array_item tag_array[CF_GET_REPEAT_FIELD_TAG_ARRAY_SIZE];
#endif
};

#ifndef __cplusplus
typedef struct _IncomingCanonical IncomingCanonical;
#endif

#ifdef __cplusplus
#define	_IncomingCanonical__get_options( ic )\
		(ic)->IncomingCanonical__get_options( ic )
#else
#define	_IncomingCanonical__get_options( ic )\
		IncomingCanonical__get_options( ic )
#endif

#ifdef __cplusplus
#define CF_ParseMsg(options,buf,buf_len)\
	CF_aParseMsg(options,buf,buf_len,(CF_Structure*)NULL,(CF_ParseStatus*)NULL)
#define CF_xParseMsg(options,buf,buf_len,cfs)\
    CF_aParseMsg(options,buf,buf_len,cfs,(CF_ParseStatus*)NULL)
#else
#define CF_ParseMsg(handle,options,buf,buf_len)\
	CF_aParseMsg(handle,options,buf,buf_len,(CF_Structure*)NULL,(CF_ParseStatus*)NULL)
#define CF_xParseMsg(handle,options,buf,buf_len,cfs)\
    CF_aParseMsg(handle,options,buf,buf_len,cfs,(CF_ParseStatus*)NULL)
#endif

#ifdef __cplusplus
class IncomingCanonical
{
public:
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    IncomingCanonical(
        unsigned int options = (unsigned int)0,
        unsigned max_msg_length = CF_DFLT_MAX_MSG_LENGTH );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    ~IncomingCanonical();
#endif
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_GetErrorDetail(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
	unsigned int options,
		struct ErrorDetail* ErrorDetail);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_CheckIfFieldPresent(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options,
        int tag_num);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_SetInputVersion(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
		unsigned int options,
		unsigned version );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_ResetInputVersion(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
		unsigned int options);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_GetList(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned int options,
		ExtractList *list );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aParseMsg(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options,
        const char *buf,
        unsigned buf_len,
		CF_Structure* cfs, 
        CF_ParseStatus* ret_status);

#ifdef __cplusplus
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_ParseStream(
    unsigned int options,
	std::istream &is,
	char *buf,
	unsigned max_buflen,
	CF_Structure* cfs,
	CF_ParseStatus* ret_status);
#endif

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_ParseRecord(
#ifndef __cplusplus
    struct cf_handle *handle,
#endif
    unsigned int options,
	char * const buf,
	unsigned max_buflen,
	CF_Structure* cfs,
	CF_ParseStatus* ret_status);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetGroupFieldList(
#ifndef __cplusplus
	struct cf_handle* handle,
#endif
	unsigned int options,
	int	*group_id_list,
	int	*group_instance_list,
	ExtractList *list);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetGroupField(
#ifndef __cplusplus
	struct cf_handle* handle,
#endif
	unsigned int options,
	int	*group_id_list,
	int	*group_instance_list,
	int     tag_num,
	void	*buf,
	unsigned buf_len,
	unsigned *rtn_len,
	unsigned short *tag_type );

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetGroupInstanceCount(
#ifndef __cplusplus
	struct cf_handle* handle,
#endif
	unsigned int options,
	int     *group_id_list,
	int     *group_instance_list,
	unsigned *count);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_SetGroupInstance(
#ifndef __cplusplus
	struct cf_handle* handle,
#endif
	unsigned int options,
	int     *group_id_list,
	int     *group_instance_list);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetNextGroupField(
#ifndef __cplusplus
	struct cf_handle* handle,
#endif
	unsigned int options,
	int     *tag_num,
	void    *buf,
	unsigned   buf_len,
	unsigned *rtn_len,
	unsigned short  *tag_type);

#ifdef __cplusplus
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetField(
        unsigned int options,
        int tag_num,
		int index,
        CF_TagData &buf,
        unsigned *repeat_count,
		unsigned short *tag_type);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetField(
        unsigned int options,
        int tag_num,
		int index,
        CF_TagData &buf,
        unsigned *repeat_count){
		return(CF_aGetField(options,tag_num,index, buf, repeat_count,(unsigned short *)NULL));
		};
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetField(
        unsigned int options,
        int tag_num,
		int index,
        CF_Price &buf,
        unsigned *repeat_count);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetField(
        unsigned int options,
        int tag_num,
		int index,
        CF_Price_Ptr &p,
        unsigned *repeat_count);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetField(
        unsigned int options,
        int tag_num,
		int index,
        CF_Timestamp &buf,
        unsigned *repeat_count);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetField(
        unsigned int options,
        int tag_num,
		int index,
        CF_Timestamp_Ptr &p,
        unsigned *repeat_count);
#endif

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetField(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options,
        int tag_num,
        void *buf,
        unsigned max_buf_len,
        unsigned *rtn_len,
        unsigned *repeat_count,	/* 0 if no dups; otherwise repeat count (>=2) */
		unsigned short *tag_type);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_GetField_SMID(
#ifndef __cplusplus
		struct cf_handle* handle,
#endif
		unsigned int options,
		int tag_num,
		unsigned item,
		void *buf,
		unsigned max_buf_len,
		unsigned *buf_len);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_GetField_Float(
#ifndef __cplusplus
		struct cf_handle* handle,
#endif
		unsigned int options,
		int tag_num,
		void *bufWhole,
		unsigned max_bufWhole_len,
		void *bufFraction,
		unsigned max_bufFraction_len,
		unsigned *Decpt,
		unsigned *repeat_count, /* 0 if no dups; otherwise repeat count (>=2) */
		unsigned short *tag_type );


#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetRepeatField(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options,
        int tag_num,
		unsigned repeat,
        void **buf,                             /* array */
        unsigned *max_buf_len,  /* array */
        unsigned *rtn_buf_len,  /* array */
        unsigned max_array_size,
        unsigned *rtn_array_size,
		unsigned short *tag_type );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetRepeatField_Float(
#ifndef __cplusplus
	struct cf_handle* handle,
#endif
	unsigned int options,
	int tag_num,
	unsigned repeat,
	void **bufWhole,
	unsigned max_bufWhole_len,
	void **bufFraction,
	unsigned max_bufFraction_len,
	unsigned *Decpt,
	unsigned max_array_size,
	unsigned *rtn_array_size,
	unsigned short *tag_type );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aGetNextField(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options,
        int *tag_num,
        void *buf,
        unsigned max_buf_len,
        unsigned *rtn_len,
        unsigned *repeat_count,
		unsigned short *tag_type );
#ifdef __cplusplus
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_aGetNextField(
		unsigned int options,
		int *tag_num,
		CF_TagData &buf,
		unsigned *repeat_count,
		unsigned short *tag_type );
#endif
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
#ifdef __cplusplus
    int
    CF_SetNextField(
        unsigned int options,
        int next_field_index );
#else
    int
    CF_SetNextField(
        struct cf_handle* handle,
        unsigned int options,
        int next_field_index );
#endif
#ifdef __cplusplus
	inline
    int
    CF_GetNextFieldIndex( unsigned int options )
	{
		return ic_data.next_field;
	}
#else
    int
    CF_GetNextFieldIndex(
		struct cf_handle* handle,
		unsigned int options );
#endif
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
#ifndef __cplusplus
	int CF_MoreFields( struct cf_handle* handle );
#else
		bool CF_MoreFields( void );
#endif
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_GetTagType(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options,
        int tag_num,
        unsigned repeat_count,
        int *taginfo);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    IncomingCanonical__Print(
        struct _IncomingCanonical *ic,
        unsigned int options );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	unsigned int
	IncomingCanonical__get_options(
		IncomingCanonical *ic );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_BlockMsgInUpdate(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_FormatMsg(
#ifndef __cplusplus
	struct cf_handle*	handle,
#endif
	unsigned int	option,
	char*	in_buf,
	int	in_buf_len,
	char*	out_buf,
	int	out_buf_len,
	int*	rtn_buf_len,
	char*	tag_separator,
	int	column_size,
	int	indent_size,
	int*	rtn_row_count);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_GetMsgEnum(
#ifndef __cplusplus
	struct cf_handle*	handle,
#endif
	int*  msgEnum);

#ifdef __cplusplus

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_GetMsgEnum(char*	msgEnum,
        		  int 	msgEnumLen);
/*
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_GetMsgEnum(
        unsigned int 	options,
		char*			msgType,
		char*			subType);
*/
private:
#endif
    void
    IncomingCanonical__constructor(
    	struct _IncomingCanonical *ic,
        unsigned int options,
        unsigned max_msg_length );
    void
    IncomingCanonical__destructor(
        struct _IncomingCanonical *ic );
    int
    IncomingCanonical__cleanup(
        struct _IncomingCanonical *ic );
    int
    IncomingCanonical__Init(
        struct _IncomingCanonical *ic,
		unsigned options,
        const char *buf2,
        unsigned buf_len );
    int
    IncomingCanonical__Init2(
        struct _IncomingCanonical *ic,
		unsigned options,
        const char *buf2,
        unsigned buf_len );
	int
	Message_buf_assign(
		unsigned int options,
		struct _IncomingCanonical *ic,
		const char **buf2,
		char **buf,
		char **buf_end,
		unsigned *buf_len,
		CF_ParseStatus* ret_status,
		char **current_ptr);
  	int
	Parse_ordered_tags(
		unsigned int options,
		struct _IncomingCanonical *ic,
		const char **buf2,
		unsigned *buf_len,
		char **buf,
		char **buf_end,
		unsigned *rtn_version,
		int *rtn_tag_num,
		int *tag_count,
		CF_ParseStatus* ret_status,
		char **current_ptr);
	int
	CF_ParseMsg_Defer_Conversion(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned int options,
		unsigned version,
		const char *buf2,
		char *p,
		char *buf_end,
		unsigned buf_len,
		CF_Structure* cfs);
	int
	ChecksumTagValidation(
		int cfmo_options,
		unsigned version,
		int buf_len,
		const char* buf2,
		char* tag);
	int
	Get_TagNum(
		Field32bits noLeading0,
		char** p,
		int* tag_num);
	int
    IncomingCanonical__get_new_tag_ptr_and_type(
        struct _IncomingCanonical *ic,
        unsigned int options,
        int tag_num,
        Tag **tp,
        struct TagData *tag_data,
        Tag **tp2,
        TagList **tlp,
        unsigned *rtn_repeat );
    int
    IncomingCanonical__get_existing_tag_ptr_and_type(
        struct _IncomingCanonical *ic,
        unsigned int options,
        int tag_num,
		struct tag_array_item *tag_array,
		unsigned max_tp,
		unsigned *n_tp,
        unsigned short *tag_type,
        unsigned repeat,
        unsigned count,
        unsigned *repeat_count );
    void
    IncomingCanonical__Print2(
        struct _IncomingCanonical *ic,
        int first_tag_num,
        Tag *tag_array,
        int count,
		const char* tagnames[]);
	int
	IncomingCanonical__struct_sub(
		struct _IncomingCanonical *ic,
		StructDef *sd,
		int struct_repeat,
		char *tag,
		unsigned options,
		unsigned version,
		CF_Structure* cfs,
		char **rtn_p,
		int *tag_count,
		Tag **tp_prev,
		unsigned short *tag_type_prev,
		unsigned *group,
		char *buf_end);
	int
	set_incoming_error_detail(
		struct _IncomingCanonical *ic,
		struct ErrorDetail *ed,
		char *bufp,
   		int buf_len,
		int tag_num,
		int return_code);
	int	
	Set_incoming_msg_type_tag_list(
		struct _IncomingCanonical *ic);

	int	
	Chk_reset_incoming_msg_type_tag_list(
		struct _IncomingCanonical *ic,
		CS_BOOL ck_flag,
		int *tag_num);

	int
	repeating_group_FIX_Header(
		unsigned options,
		struct _IncomingCanonical *ic,
		struct ErrorDetail *ed,
		int tag_num_group,
		char *tag,
		char **rtn_p,
		int *tag_count,
		char *buf_end);

	int
	repeating_group_Canonical(
		unsigned options,
		struct _IncomingCanonical *ic,
		struct ErrorDetail *ed,
		int tag_num_group,
		char *tag,
		char **rtn_p,
		int *tag_count,
		NestGroup *nested_group,
		char *buf_end);

	short
	FindSize(struct _IncomingCanonical *ic, int startIndex);

	int
	repeating_group_FIX(
		unsigned options,
		struct _IncomingCanonical *ic,
		struct ErrorDetail *ed,
		int tag_num_group,
		char *tag,
		char **rtn_p,
		int *tag_count,
		NestGroup *nested_group,
		char *buf_end);

	int
	getFIXGroupField(
		struct _IncomingCanonical *ic,
		unsigned int options,
		unsigned int itemFlag,
		int	*group_id_list,
		int	*group_instance_list,
		int     tag_num,
		void	*buf,
		unsigned buf_len,
		unsigned *rtn_len,
		unsigned short *tag_type );

#ifdef __cplusplus
	int 
	(IncomingCanonical::*repeating_group[N_VERSION_ARRAY])
		(unsigned int,struct _IncomingCanonical *,struct ErrorDetail *, 
		int, char*, char**, int*, NestGroup*, char*);
#else
	int 
	(*repeating_group[N_VERSION_ARRAY])
		(unsigned int,struct _IncomingCanonical *,struct ErrorDetail *, 
		int, char*, char**, int*, NestGroup*, char*);
#endif

#ifdef __cplusplus
    struct _IncomingCanonical ic_data;
};
#endif




struct DepthInfo
{
	unsigned struct_tag_index;
	unsigned repeat;
	StructDef *sd;
};

struct _OutgoingCanonical
{
    short init_called;
    short first_field;
    char *buf;
    unsigned int buf_len;
    unsigned int max_buf_length;
    unsigned int options;
	unsigned version;
	struct ErrorDetail error_detail;
    char *blk_buf;
    unsigned int blk_msg_cnt;
    unsigned int blk_len;
    unsigned int blk_flag;
	unsigned struct_mode;
	unsigned struct_num;
	BitFieldTagData FieldTagList[CFD_MAX_BIT_FIELD_TAGS_PER_MSG];
	StructDef *sd;
	unsigned depth;
	struct DepthInfo *depth_info_p;
	struct DepthInfo depth_info[MAX_DEPTH];
	unsigned int createmsg_options;
	unsigned checksum_exists;
	unsigned int cfmo_options;
	unsigned group;
	unsigned n_required_tags;
	unsigned char dup_check_tbl[(CF_N_STD_TAG+7)/8];
	const MessageTypeInfo *msg_info;
    MsgTagInfo *tag_array_standard;
	MsgTagInfo *tag_array_user;
	MsgTagInfo *tag_array_siac;
	MsgTagInfo *tag_array_siac2;
	MsgTagInfo *tag_array_group;
	short sys_endian_flag;
	CS_BOOL nbo_conversion;
	CS_BOOL waitSubType;
	/**  RPG **/
	const GroupDefinition*		group_def[CFD_MAX_NEST_GROUP_DEPTH];
	OutgoingGroup*	group_built;
	int				group_nest_level;
	MsgGroup		*allowedGroupList;
	int				group_nbr;
	int 			max_group_nbr;
	/**  RPG **/
	int data_len;
	int groupNbr;
	int *groupIdList;
	CS_BOOL latencyON;
	CS_BOOL latencySwitch;
	short latencyArrayPreFill;
	DecimalRange decimalRange;
#if (!defined( _NT_BUILD) && !defined( __TANDEM )) || defined( _OSS_TARGET )
	CF_Latency latencyBlob;
#else
	char *latencyBlob;
#endif
};


#ifndef __cplusplus
struct cf_handle
{
    int ic_valid;
    int oc_valid;
	struct ErrorDetail error_detail;	/* used in 'C' implimentation only */
    struct _IncomingCanonical *ic;
    struct _OutgoingCanonical *oc;
};

typedef struct _OutgoingCanonical OutgoingCanonical;
#endif


#ifdef __cplusplus
#define	_OutgoingCanonical__get_options( oc )\
		(oc)->OutgoingCanonical__get_options( oc )
#define	_OutgoingCanonical__get_msg_buf( oc )\
		(oc)->OutgoingCanonical__get_msg_buf( oc )
#else
#define	_OutgoingCanonical__get_options( oc )\
		OutgoingCanonical__get_options( oc )
#define	_OutgoingCanonical__get_msg_buf( oc )\
		OutgoingCanonical__get_msg_buf( oc )
#endif

#ifdef __cplusplus
class OutgoingCanonical
{
public:
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    OutgoingCanonical( unsigned int options = (unsigned int)0 );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    ~OutgoingCanonical();
#endif
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_GetErrorDetail(
#ifndef __cplusplus
		struct cf_handle* handle,
#endif
		unsigned int options,
		struct ErrorDetail* ErrorDetail);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_CreateMsg(
#ifndef __cplusplus
		struct cf_handle* handle,
#endif
        unsigned int options,
        void *buf,
        unsigned int max_buf_length );

#if ! defined( __TANDEM ) || defined( _OSS_TARGET )
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_CreateMsg(
#ifndef __cplusplus
		struct cf_handle* handle,
#endif
        unsigned int options,
        void *buf,
        unsigned int max_buf_length,
		const char *emitter);
#endif

#ifdef __cplusplus
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_CreateMsg(
        unsigned int options,
        void *buf,
		const char *msgType,
        unsigned int max_buf_length );

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_CreateMsg(
		unsigned int options,
		int msgEnum,
		void *buf,
		unsigned int max_buf_length);
#endif

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_BeginGroup(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned int    options,
		int		group_id);
							
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
#ifndef __cplusplus
CF_BeginFIXGroup(
	struct cf_handle *handle,
#else
CF_BeginGroup(
#endif
    unsigned int	options,
	int		instance_count,
    int		group_id);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_EndGroup(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned int    options,
		int				group_id,
		unsigned*       rtn_buf_length);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PutNextGroupInstance(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned int    options);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
#ifndef __cplusplus
	CF_PutNextField_Float(
	struct cf_handle *handle,
#else
	CF_PutNextField(
#endif
		unsigned int options,
		int 	 tag_num,
		void 	 *field,
		unsigned length,
		unsigned *rtn_buf_length,
		unsigned short min_decimal,
		unsigned short max_decimal);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PutNextField(
#ifndef __cplusplus
		struct cf_handle* handle,
#endif
		unsigned int options,
		int tag_num,
		void *field,
		unsigned length,                         /* used only for FDT_data type */
		unsigned *rtn_buf_length );
#ifdef __cplusplus
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PutNextField(
		unsigned int options,
		int tag_num,
		CF_Price &price,
		unsigned length,                         /* used only for FDT_data type */
		unsigned *rtn_buf_length );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PutNextField(
		unsigned int options,
		int tag_num,
		CF_Timestamp &price,
		unsigned length,                         /* used only for FDT_data type */
		unsigned *rtn_buf_length );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PutNextField(
		unsigned int options,
		int tag_num,
		CF_TagData &tagData,
		unsigned length,                         /* used only for FDT_data type */
		unsigned *rtn_buf_length );
#endif
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PutNextField_SMID(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned int options,
		int tag_num,
		char    *emitter,
		unsigned int emitter_len,
		short   instance,
		char    *subject,
		unsigned subject_len,
		unsigned int sequence,                       /* used only for FDT_data type */
		unsigned *rtn_buf_length );

	int
	set_outgoing_error_detail(
		struct _OutgoingCanonical *oc,
		struct ErrorDetail *ed,
       	int tag_num,
		int tag_type,
		void *field,
       	int length,
		int return_code);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PutList(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned int options,
		ExtractList *list );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_PutStructList(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned int options,
		ExtractList *elist,
		unsigned struct_num,
		CF_Structure* cfs);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_SetOutputVersion(
#ifndef __cplusplus
		struct cf_handle* handle,
#endif
		unsigned int options,
		unsigned version );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_aPutNextStructField(
#ifndef __cplusplus
		struct cf_handle *handle,
#endif
		unsigned options,
		int tag_num,
		void *field,
		unsigned length,
		unsigned struct_num,
		unsigned nested_struct_num,
		CF_Structure* cfs,
		unsigned *rtn_buf_length);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	unsigned int
	OutgoingCanonical__get_options(
		OutgoingCanonical *oc );

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	char *
	OutgoingCanonical__get_msg_buf(
       	OutgoingCanonical *oc );

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    unsigned int
    OutgoingCanonical__get_buf_len(
        struct _OutgoingCanonical *oc );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    OutgoingCanonical__Print(
        struct _OutgoingCanonical *oc );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_aBlockMsgOutUpdate(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options,
		unsigned *rtn_buf_length);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
    CF_aBlockAddMsg(
#ifndef __cplusplus
       	struct cf_handle* handle,
#endif
       	unsigned int options,
       	char *outbuf,
       	unsigned buf_len,
       	char *msg,
       	unsigned msg_len,
		unsigned *rtn_buf_length);

	int
	Group_Check_Update_Header(
		unsigned int options,
		struct _OutgoingCanonical *oc,
		int tag_num);
	int
	Group_Check_Update_FIX(
		unsigned int options,
		struct _OutgoingCanonical *oc,
		int tag_num, 
		void *tag_value);
	int
	Group_Check_Update_Canonical(
		unsigned int options,
		struct _OutgoingCanonical *oc,
		int tag_num,
		void *tag_value);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
    int
    CF_SetLastField(
#ifndef __cplusplus
        struct cf_handle* handle,
#endif
        unsigned int options,
		unsigned *rtn_buf_length);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	int
	CF_SetDecimalRange(
#ifndef __cplusplus
       	struct cf_handle* handle,
#endif
		unsigned short low,
		unsigned short high);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
	unsigned short	
	CF_GetDecimalRange(
#ifndef __cplusplus
       	struct cf_handle* handle,
#endif
		enum CF_DRANGEINDICATOR side);

#ifdef __cplusplus
private:
#endif
    void
    OutgoingCanonical__constructor(
    	struct _OutgoingCanonical *oc,
        unsigned int options );
	void
	OutgoingCanonical__destructor(
		struct _OutgoingCanonical *oc );
	int
	OutgoingCanonical__last_field(
		unsigned int options,
		struct _OutgoingCanonical *oc,
		int *tag_num);
	int	
	Set_outgoing_msg_type_tag_list(
		struct _OutgoingCanonical *oc);
	int
	Chk_reset_outgoing_msg_type_tag_list(
		struct _OutgoingCanonical *oc,
		CS_BOOL ck_flag,
		int *tag_num);
	int
	Chk_updt_msg_type_info(
		struct _OutgoingCanonical *oc,
		int tag_num);
	int msgTypeAndGroupCheck(
		struct _OutgoingCanonical *oc,
		int options,
		int tag_num,
		void* field);
	int putLatecyBlob(
		struct _OutgoingCanonical *oc,
		unsigned int options,
		unsigned *rtn_buf_length);

#ifdef __cplusplus
	int 
	(OutgoingCanonical::*Group_Check_Update[N_VERSION_ARRAY])
		(unsigned int,struct _OutgoingCanonical *,int, void*);
#else
	int 
	(*Group_Check_Update[N_VERSION_ARRAY])
		(unsigned int,struct _OutgoingCanonical *,int, void*);
#endif

#ifdef __cplusplus

    struct _OutgoingCanonical oc_data;
};
#endif

#ifndef __cplusplus

void
ExtractItem__destructor(
	ExtractItem *ei );

void
TagItem__destructor(
	TagItem *ti );

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetErrorDetail(
	struct cf_handle* handle,
	unsigned int options,
	struct ErrorDetail* ErrorDetail);

#endif

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetVersionID(
#ifndef __cplusplus
	struct cf_handle *handle,
#endif
    unsigned int options,
	char *version,
	unsigned *rtn_versionID);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetVersionString(
#ifndef __cplusplus
	struct cf_handle *handle,
#endif
    unsigned int options,
	unsigned version,
	char *rtn_versionString);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
const char *
CF_GetTagName(
#ifndef __cplusplus
    struct cf_handle *handle,
#endif
    unsigned int options,
    int tag_num );

#ifdef __cplusplus

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetTagTypeByVersion(
    unsigned int options,
    int tag_num,
	unsigned short *tag_group,
	unsigned version);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
inline int
CF_GetTagTypeByVersion(
    unsigned int options,
    int tag_num,
	unsigned version)
{
	return CF_GetTagTypeByVersion( options, tag_num, (unsigned short *)NULL, version );
}

#else
/*__cplusplus*/

#define	CF_GetTagTypeByVersion( handle, options, tag_num, version ) \
		CF_GetTagTypeAndGroupByVersion( handle, options, tag_num, (unsigned short *)NULL, version ) 

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetTagTypeAndGroupByVersion(
    struct cf_handle *handle,
    unsigned int options,
    int tag_num,
	unsigned short *tag_group,
	unsigned version);

#endif
/*__cplusplus*/

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
#ifndef __cplusplus
CF_EditMsg_Float(
	struct cf_handle *handle,
#else
CF_EditMsg(
#endif
	unsigned int choice,
	unsigned int options,
	char *inbuf,
	unsigned inbuf_len,
	unsigned max_inbuf_len,
	unsigned *rtn_inbuf_len,
	char *outbuf,
	unsigned max_outbuf_len,
	unsigned *rtn_outbuf_len,
	int position_tag_num,
	unsigned position_repeat,
	int tgno,
	void *field,
	unsigned length,
	unsigned short  min_decimal,
	unsigned short  max_decimal
	);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_EditMsg(
#ifndef __cplusplus
	struct cf_handle *handle,
#endif
	unsigned int choice,
	unsigned int options,
	char *inbuf,
	unsigned inbuf_len,
	unsigned max_inbuf_len,
	unsigned *rtn_inbuf_len,
	char *outbuf,
	unsigned max_outbuf_len,
	unsigned *rtn_outbuf_len,
	int position_tag_num,
	unsigned position_repeat,
	int tag_num,
	void *field,
	unsigned length		/* used only for FDT_data type */
	);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_EditGroup(
	unsigned int choice,
	unsigned int options,
	int     *group_id_list,
	int     *group_instance_list,
	char 	*inbuf,
	int 	inbuf_len,
	char	 *outbuf,
	int 	max_buf_len,
	int 	*rtn_buf_len,
	int 	in_tag_num,
	void 	*field,
	int 	length
	);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_RemoveChecksum(
	unsigned int options,
	char *msg,
	unsigned msgLen,
	unsigned *rtnMsgLen
	);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
unsigned
get_tag_repeat(
	int tag_num,
	unsigned *n_tag_num_array,
	int tag_num_array[TEST_ARRAY_SIZE]);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
vl_dmp(
	char *s,
	short n_bytes,
	int lines );
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
vl_dmp1(
	char *s,
	short n_bytes,
	int lines);
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
get_tag_len(
	unsigned options,
	int el_tag_num,
	unsigned version,
	unsigned *rtn_len,
	int pass,
	unsigned repeat,
	unsigned short tag_type);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
GetTagDataByVersion(
    unsigned int options,
    int tag_num,
	unsigned version,
	struct TagData *tagdata,
	int undeftag_group);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
BuildSMID(
	char *SMID_buf,
	int buf_len,
    const char    *emitter,
	unsigned short   instance,
	const char    *subject,
	unsigned int sequence,                     
	unsigned *rtn_buf_length );

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
GetSMIDFields(
	char		*SMID_buf,
	int		SMID_buf_len,
	int		SMID_separator,
	char		*emitter,	
	int		max_emitte_len,
	unsigned short	*instance,
	char    	*subject,
	int		max_subject_len,
	unsigned int	*sequence,
	int		*rtn_SMID_len );

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
aGetSMIDItem(
	unsigned int options,
	char *SMID_buf,
	unsigned SMID_buf_len,
	unsigned item,
	void *buf,
	int max_buf_len,
	unsigned *rtn_buf_length );
						
#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
GetNextBitField(
	unsigned int    primary_tag_options,
	unsigned int    bit_tag_options,
	int             primary_tag_num,
	unsigned short	bit_tag_position,
	void*           primary_tag_value,
	unsigned        primary_tag_value_len,
	int*            bit_tag_num,
	void*           bit_tag_value,
	unsigned        bit_tag_value_max_len,
	unsigned*       bit_tag_value_len,
    unsigned short*	rtn_bit_tag_position);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_SearchTag(
	unsigned int    options,
	const char*     buf,
	int             buf_len,
	int 			tag_num,
    int*            begin_offset,
    int*            end_offset,
	void*           tag_buf,
	int             tag_buf_len,
	int*            rtn_buf_len);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_SearchMsg(
    unsigned int    options,
    char*			buf,
    int             buf_len,
    int*            msg_offset,
    int*            msg_len,
	int*			version);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetMinMsgSize(
	int             Options,
	int             VersionId,
	int*            Size);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetTagTypeNativeByteSize(
	int             Options,
	int				VersionId,
	int				Id,
	int*            Size);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_GetMaxSizeForLenField(
	int             Options,
	int             VersionId,
	int*            Size);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_SearchMsgLength(
	unsigned int    Options,
	char*           Buf,
	int             Buflen,
	int*            MsgLen);

#ifdef DECLSPEC
__declspec( DECLSPEC_TOKEN )
#endif
int
CF_IsEndOfMsg(
	int     Options,
	char    *MsgBuf,
	int     MsgSize);

#define GetSMIDItem(SMID_buf, item, buf, buf_len, rtn_buf_length)\
	aGetSMIDItem(0, SMID_buf, 60, item, buf, buf_len, rtn_buf_length)
	
#ifdef __cplusplus

#define CF_BlockMsgOutUpdate(options, buf, rtn_buf_length)\
		CF_aBlockMsgOutUpdate(options, rtn_buf_length)

#define CF_BlockAddMsg(options, outbuf, buf_len, msg, msg_len, rtn_buf_length)\
	CF_aBlockAddMsg(options, (char*)outbuf, buf_len, (char*)msg, msg_len, rtn_buf_length)

#define CF_PutNextStructField( options, tag_num, field, length, struct_num, cfs, rtn_buf_length)\
	CF_aPutNextStructField( ((options)&~CFO_BULK_LOAD), tag_num, field, length, struct_num, (int)0, cfs, rtn_buf_length)

#define CF_GetField( options, tag_num, buf, max_buf_len, rtn_len, repeat_count )\
	CF_aGetField( options, tag_num, buf, max_buf_len, rtn_len, repeat_count, (unsigned short*)NULL )

#define CF_GetNextField( options, tag_num, buf, max_buf_len, rtn_len, repeat_count )\
	CF_aGetNextField( options, tag_num, buf, max_buf_len, rtn_len, repeat_count, (unsigned short*)NULL )

#define CF_xGetRepeatField( options, tag_num, repeat, buf, max_buf_len, rtn_buf_len, max_array_size, rtn_array_size )\
	CF_aGetRepeatField( options, tag_num, repeat, buf, max_buf_len, rtn_buf_len, max_array_size, rtn_array_size, (unsigned short*)NULL )

#define CF_GetRepeatField( options, tag_num, buf, max_buf_len, rtn_buf_len, max_array_size, rtn_array_size )\
	CF_aGetRepeatField( options, tag_num, 1, buf, max_buf_len, rtn_buf_len, max_array_size, rtn_array_size, (unsigned short*)NULL)

#else

#define CF_BlockMsgOutUpdate(handle, options, buf, rtn_buf_length)\
		CF_aBlockMsgOutUpdate(handle, options, rtn_buf_length)

#define CF_BlockAddMsg(handle, options, outbuf, buf_len, msg, msg_len, rtn_buf_length)\
	CF_aBlockAddMsg(handle, options, (char*)outbuf, buf_len, (char*)msg, msg_len, rtn_buf_length)

#define CF_PutNextStructField( handle, options, tag_num, field, length, struct_num, cfs, rtn_buf_length)\
	CF_aPutNextStructField( handle, ((options)&~CFO_BULK_LOAD), tag_num, field, length, struct_num, (int)0, cfs, rtn_buf_length)

#define CF_GetField( handle, options, tag_num, buf, max_buf_len, rtn_len, repeat_count )\
	CF_aGetField( handle, options, tag_num, buf, max_buf_len, rtn_len, repeat_count, (unsigned short*)NULL )

#define CF_GetNextField( handle, options, tag_num, buf, max_buf_len, rtn_len, repeat_count )\
	CF_aGetNextField( handle, options, tag_num, buf, max_buf_len, rtn_len, repeat_count, (unsigned short*)NULL )

#define CF_xGetRepeatField( handle, options, tag_num, repeat, buf, max_buf_len, rtn_buf_len, max_array_size, rtn_array_size )\
	CF_aGetRepeatField( handle, options, tag_num, repeat, buf, max_buf_len, rtn_buf_len, max_array_size, rtn_array_size, (unsigned short*)NULL )

#define CF_GetRepeatField( handle, options, tag_num, buf, max_buf_len, rtn_buf_len, max_array_size, rtn_array_size )\
	CF_aGetRepeatField( handle, options, tag_num, 1, buf, max_buf_len, rtn_buf_len, max_array_size, rtn_array_size, (unsigned short*)NULL )

#endif


#endif
