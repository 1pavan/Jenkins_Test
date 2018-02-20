/*****************************************************************************
 *
 *                    DATE:        ~M~/~D~/~Y~
 *                    CATALOG:     ~C~
 *                    SOURCE FILE: ~F~
 *                    RELEASE:     ~R~.~L~
 *                    SYS REL:     ~V~
 *
 *****************************************************************************/

#ifndef ID__tags
#define ID__tags

#if defined( __TANDEM ) && !(defined _OSS_TARGET )
#include <cftdm.h>
#endif

#include <tagsgen.h>

/* TANDEM DEFINES BEGIN */

/* FIX 4.2 Data Types */

enum {
        FDT_not_defined			= 0,
        FDT_Qty_4_1				= 1,
        FDT_int					= 1,
        FDT_float				= 2,
        FDT_Qty					= 2,    /* FDT_float */
        FDT_Price				= 2,    /* FDT_float */
        FDT_PriceOffset			= 2,    /* FDT_float */
        FDT_Amt					= 2,    /* FDT_float */
        FDT_Percentage			= 2,    /* FDT_float */
        FDT_Quantity			= 2,    /* FDT_float */
        FDT_char				= 3,
        FDT_char_4_1			= 4,
        FDT_Boolean_4_1			= 4,
        FDT_String				= 4,
        FDT_MultipleValueString	= 4,    /* FDT_String */
        FDT_Currency			= 4,    /* FDT_String */
        FDT_Exchange			= 4,    /* FDT_String */
        FDT_Country				= 4,    /* FDT_String */
        FDT_UTCTimestamp		= 5,    /* 'GMT' time and date  YYYYMMDD-HH:MM:SS (or) YYYYMMDD-HH:MM:SS.sss */
        FDT_UTCTimeOnly			= 6,    /* 'GMT' time  HH:MM:SS (or) HH:MM:SS.sss */
        FDT_LocalMktDate		= 7,    /* date of local market  YYYYMMDD */
        FDT_UTCDate				= 8,    /* 'GMT' date  YYYYMMDD */
        FDT_data				= 9,    /* raw data with no format or content restrictions */
        FDT_month_year			= 10,   /* month of year  YYYYMM */
        FDT_Boolean				= 11,
        FDT_day_of_month		= 12,	/* int field  range: 1-31 */
		FDT_LocalMktTimestamp	= 13,	/* 'LOCAL' time and date  YYYYMMDD-HH:MM:SS (or) YYYYMMDD-HH:MM:SS.sss */
		FDT_LocalMktTimeOnly	= 14,	/* 'LOCAL' time  HH:MM:SS (or) HH:MM:SS.sss */
		FDT_SMID                = 15,   /* 'ABCDEF:99:AAAAAAA...(max 40 chars):999999999' */
		FDT_bit_field			= 16,   /* int, bit 0 - 15 are mask, bit 16 - 31 are bit value */
        FDT_data_len			= 20,   /* length of raw data with no format or content restrictions */
        FDT_Length				= 20,	/* length of data used in FIX 4.3 */
        FDT_NumInGroup			= 20,
        FDT_int_zero_positive	= 20,

		FDT_bit					= 21,	/* For 90000 and + tags only */
        FDT_UTCTimestamp_int64	= 22,    /* UTCTimestamp converted from 64 bits integer to YYYYMMDD-HH:MM:SS.sss */
        FDT_SeqNum				= 23,
        FDT_TagNum				= 23,
        FDT_int_positive		= 23,
        FDT_int8				= 24,
        FDT_int16				= 25,
        FDT_int32				= 26,
        FDT_int64				= 27,
        FDT_uint8				= 28,
        FDT_uint16				= 29,
        FDT_uint32				= 30,
        FDT_uint64				= 31,

		FDT_struct				= 30	/* structure tag type (for Canonical messages only) */
};

#define CF_N_TAG_TYPES	256
#define CF_N_TAG_GROUPS 8


/*
	Siac Structure Tags
*/

enum {
	SST_MinReqCanonHdr		= 20000	/* structure tag (10003,10005,10006,10007,10010) */
};


#endif
