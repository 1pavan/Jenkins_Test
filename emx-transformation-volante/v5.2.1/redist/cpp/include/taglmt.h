/*****************************************************************************
 *
 *                    DATE:        ~M~/~D~/~Y~
 *                    CATALOG:     ~C~
 *                    SOURCE FILE: ~F~
 *                    RELEASE:     ~R~.~L~
 *                    SYS REL:     ~V~
 *
 *****************************************************************************/

#ifndef ID__tag_limits
#define ID__tag_limits

/* TANDEM DEFINES BEGIN */

#define CF_FIRST_SPEC_STD_TAG	1
#define	CF_LAST_SPEC_STD_TAG	4999

#define	CF_FIRST_SPEC_USER_TAG	5000
#define	CF_LAST_SPEC_USER_TAG	9999

#define	CF_FIRST_SPEC_SIAC_TAG	10000
#define	CF_LAST_SPEC_SIAC_TAG	39999

#define CF_FIRST_STD_TAG	1
#define	CF_LAST_STD_TAG		999
#define CF_N_STD_TAG    	((CF_LAST_STD_TAG-CF_FIRST_STD_TAG)+2)

#define	CF_FIRST_USER_TAG	9000
#define	CF_LAST_USER_TAG	9999
#define CF_N_USER_TAG   	((CF_LAST_USER_TAG-CF_FIRST_USER_TAG)+1)

#define	CF_FIRST_SIAC_TAG	10000
#define	CF_LAST_SIAC_TAG	11999
#define CF_N_SIAC_TAG   	((CF_LAST_SIAC_TAG-CF_FIRST_SIAC_TAG)+1)

#define	CF_FIRST_SIAC_HEADER_TAG	10000
#define	CF_LAST_SIAC_HEADER_TAG		10199
#define CF_N_SIAC_HEADER_TAG   	((CF_LAST_SIAC_HEADER_TAG-CF_FIRST_SIAC_HEADER_TAG)+1)

#define CF_FIRST_SIAC_CS_TAG	19000
#define CF_LAST_SIAC_CS_TAG	19999
#define CF_N_SIAC_CS_TAG   ((CF_LAST_SIAC_CS_TAG-CF_FIRST_SIAC_CS_TAG)+1)

#define CF_FIRST_SIAC_LOGICAL_TAG 90000
#define CF_LAST_SIAC_LOGICAL_TAG  99999		/* reserved range 90000 - 99999 */
#define CF_LAST_DEFINED_SIAC_LOGICAL_TAG  90063
#define CF_N_SIAC_LOGICAL_TAG   ((CF_LAST_DEFINED_SIAC_LOGICAL_TAG-CF_FIRST_SIAC_LOGICAL_TAG)+1)

#define CFD_MAX_BIT_FIELD_TAGS_PER_MSG CF_N_SIAC_LOGICAL_TAG/16

/*
	Number of tag_seq structures per allocation
*/
#define CF_MAX_TAG_SEQUENCE		1024

/*
	Number of tag_value_t3 structures per allocation
*/
#define CF_MAX_TAG_VALUE_T3		512


#define CF_FIRST_STRUCT_TAGNUM	20000
#define CF_LAST_STRUCT_TAGNUM	24999

#define CF_FIRST_GROUP_TAG     26001
#define CF_LAST_GROUP_TAG      26998
#define CF_LAST_DEFINED_GROUP_TAG  26200
#define CF_N_GROUP_TAG   ((CF_LAST_DEFINED_GROUP_TAG-CF_FIRST_GROUP_TAG)+1)

#define CF_MAX_MSG_ENUM			5000

#define	N_STRUCT_TAGNUM			5000

#define CF_MAX_DEFINED_MSGTYPE                         50

#define CF_GET_REPEAT_FIELD_TAG_ARRAY_SIZE	200

#define	MAX_REPEAT	INT_MAX

#define MAX_DEPTH	100

#define CF_DFLT_MAX_MSG_LENGTH	1000

#define N_VERSION_ARRAY 4

#define	N_STRUCTDEF_ARRAY	100

/* TANDEM DEFINES END */

#endif
