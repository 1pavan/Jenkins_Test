/*
** Copyright (c) 2007 Tervela Inc,   All rights reserved.
*/

/***********************************************************************
*
* FILE NAME
*      tvaErrors.h
*
* DESCRIPTION
*      This file contains common error defines for API support
*
***********************************************************************/

#ifndef _TVAERRORS_H_
#define _TVAERRORS_H_

#include "tvaTypes.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef TVA_INT32 TVA_STATUS;

#define TVA_ERROR                                       (-1)
#define TVA_OK                                          (0)
#define TVA_WARN                                        (1)
#define TVA_NOCONNECT_CM                                (2)
#define TVA_BUSY                                        (3)
#define TVA_NOT_FOUND                                   (4)
#define TVA_TIMEOUT                                     (7)
#define TVA_ERR_OUT_OF_MEMORY                           (8)
#define TVA_ERR_NETWORK_WRITE                           (9)
#define TVA_ERR_NETWORK_READ                            (10)
#define TVA_ERR_THREAD_CREATE                           (11)
#define TVA_ERR_INVALID_OBJECT                          (12)
#define TVA_ERR_INVALID_REF_COUNT                       (13)
#define TVA_ERR_OBJECT_ALREADY_RELEASED                 (14)

#define TVA_ERR_API_INIT_FAILED                         (20)
#define TVA_ERR_INVALID_CONFIG_FILE                     (21)
#define TVA_ERR_BAD_NETWORK_CONFIG                      (22)

#define TVA_ERR_CONFIG_FILE_NOT_FOUND                   (23)
#define TVA_ERR_CONFIG_FILE_DP_PORT                     (24)
#define TVA_ERR_CONFIG_FILE_DP_PORTS                    (25)
#define TVA_ERR_CONFIG_FILE_IP_ADDR                     (26)
#define TVA_ERR_CONFIG_FILE_SUB_TIMEOUT                 (27)
#define TVA_ERR_CONFIG_FILE_SCH_TIMEOUT                 (28)
#define TVA_ERR_CONFIG_FILE_LOG_FILE                    (29)
#define TVA_ERR_CONFIG_FILE_PUB_RATE                    (30)
#define TVA_ERR_CONFIG_FILE_PUB_MSG_EXP                 (31)
#define TVA_ERR_CONFIG_FILE_PUB_FRAG_BURST              (32)
#define TVA_ERR_CONFIG_FILE_PUB_FRAG_DELAY              (33)
#define TVA_ERR_CONFIG_FILE_PUB_INTR_DELAY              (34)
#define TVA_ERR_CONFIG_FILE_PUB_INTR_QBYTES             (35)
#define TVA_ERR_CONFIG_FILE_PUB_BW_LIMIT                (36)
#define TVA_ERR_CONFIG_FILE_SUB_RATE                    (37)
#define TVA_ERR_CONFIG_FILE_SUB_MSG_EXP                 (38)
#define TVA_ERR_CONFIG_FILE_SUB_FRAG_TIMEOUT            (39)
#define TVA_ERR_CONFIG_FILE_SUB_QUEUE_TBUF              (40)
#define TVA_ERR_CONFIG_FILE_TVACLASS                    (41)
#define TVA_ERR_CONFIG_FILE_TVADEBUG                    (42)
#define TVA_ERR_CONFIG_FILE_TVAFSWITCH                  (43)
#define TVA_ERR_CONFIG_FILE_TVAFS_OFF                   (44)
#define TVA_ERR_CONFIG_FILE_SEND_RECEIVE_PORT           (45)
#define TVA_ERR_CONFIG_FILE_APP_CFG                     (46)

#define TVA_ERR_NULL_USERNAME                           (50)
#define TVA_ERR_USERNAME_NOT_VALID                      (51)
#define TVA_ERR_USERNAME_MAX_LENGTH_EXCEED              (52)
#define TVA_ERR_NULL_SECURITYCONTEXT                    (53)
#define TVA_ERR_NULL_MA_LIST                            (54)
#define TVA_ERR_NULL_ERRORCALLBACK                      (55)
#define TVA_ERR_MAX_NUM_SESSIONS_REACHED                (56)
#define TVA_ERR_MA_LIST_MISSING                         (57)
#define TVA_ERR_MA_NOT_FOUND                            (58)
#define TVA_ERR_LOGIN_TIMEOUT                           (59)
#define TVA_LOGIN_REJECT_INVALIDLOGINAME                (60)
#define TVA_LOGIN_REJECT_INVALIDPASSWORD                (61)
#define TVA_LOGIN_REJECT_NORIGHTS                       (62)
#define TVA_ERR_CHANEG_FAILED                           (63)

#define TVA_ERR_NULL_SESSION_INFORMATION                (65)
#define TVA_ERR_NULL_PASSWORD                           (66)

#define TVA_ERR_NULL_PUBLISH_MESSAGE_DATA               (70)
#define TVA_ERR_NULL_SCHEMA_NAME                        (71)
#define TVA_ERR_NULL_MESSAGE_DATA                       (72)
#define TVA_ERR_NULL_FIELD_ITERATOR                     (73)
#define TVA_ERR_NULL_PUBLICATION                        (74)
#define TVA_ERR_NULL_SUBSCRIPTION                       (75)
#define TVA_ERR_NULL_SUBSCRIPTION_QUEUE                 (76)
#define TVA_ERR_NO_RIGHT_PUBLICATION                    (77)
#define TVA_ERR_NO_RIGHT_SUBSCRIPTION                   (78)
#define TVA_ERR_INVALID_TOPIC_FOR_PUBLISHER             (79)
#define TVA_ERR_MESSAGE_TOPIC_WILDCARD                  (80)

#define TVA_ERR_INVALID_MESSAGE                         (85)
#define TVA_ERR_MESSAGE_ALREADY_SENT                    (86)
#define TVA_ERR_INVALID_MESSAGE_FIELD_SIZE              (87)

#define TVA_ERR_DATA_PLANE_INACTIVE                     (90)
#define TVA_ERR_FLOW_NOT_FOUND                          (91)
#define TVA_ERR_FLOW_INVALID                            (92)
#define TVA_ERR_FLOW_INACTIVE                           (93)
#define TVA_ERR_FLOW_STALLED                            (94)
#define TVA_ERR_FLOW_NOTSTALLED                         (95)
#define TVA_ERR_TSN_WRAPPING                            (96)

#define TVA_ERR_NULL_QUEUE                              (100)
#define TVA_ERR_INVALID_QUEUE                           (101)
#define TVA_ERR_QUEUE_EMPTY                             (102)
#define TVA_ERR_QUEUE_FULL                              (103)
#define TVA_ERR_QUEUE_IN_USE                            (104)
#define TVA_ERR_QUEUE_SIZE_ZERO                         (105)
#define TVA_ERR_SUB_CB_Q_TABLE_FULL                     (106)

#define TVA_ERR_NO_SCHEMA                               (110)
#define TVA_ERR_NO_SUB_SCHEMA                           (111)
#define TVA_ERR_MULTIPLE_SCHEMAS_FOUND                  (112)
#define TVA_ERR_SCHEMA_NOT_FOUND                        (113)
#define TVA_ERR_SCHEMA_RESP_FAILED                      (114)
#define TVA_ERR_NO_TOPICNAME                            (115)

#define TVA_ERR_INVALID_SUBSCRIPTION                    (116)

#define TVA_ERR_INVALID_FIELD_CONVERSION                (117)
#define TVA_ERR_POSSIBLE_DATA_TRUNCATION                (118)
#define TVA_ERR_RANGE_EXCEEDED                          (119)

#define TVA_ERR_INVALID_FIELD_ID                        (120)
#define TVA_ERR_INVALID_FIELD_NAME                      (121)
#define TVA_ERR_NO_FIELD_VALUE                          (122)
#define TVA_ERR_FIELD_ID_NOT_FOUND                      (123)

#define TVA_ERR_INPUT_PARAMETER_NULL                    (124)
#define TVA_ERR_OUTPUT_PARAMETER_NULL                   (125)
#define TVA_ERR_INVALID_PARAMETER_VALUE                 (126)

#define TVA_ERR_INVALID_TOPIC                           (127)
#define TVA_ERR_INVALID_QOSTYPE                         (128)

#define TVA_ERR_NULL_ITERATOR                           (130)
#define TVA_ERR_INVALID_ITERATOR                        (131)
#define TVA_ERR_NO_FIELD_VALUES_IN_PUBMSGDATA           (132)
#define TVA_ERR_NO_FIELDS_REMAINING                     (133)

#define TVA_ERR_FIELD_FRAGMENTED                        (137)

#define TVA_ERR_AM_INVALID_FLDID                        (140)
#define TVA_ERR_AM_INVALID_MESSAGE                      (141)

#define TVA_ERR_ENTERED_SLOW_CONSUMER_STATE             (147)
#define TVA_ERR_RECOVERED_SLOW_CONSUMER_STATE           (148)
#define TVA_ERR_SLOW_CONSUMER_DISCONNECT                (149)

#define TVA_ERR_MA_CONNECTION_FAILED                    (150)
#define TVA_ERR_MA_FAILED                               (151)
#define TVA_ERR_PORT_INUSE                              (152)
#define TVA_ERR_MA_RECONNECT                            (153)
#define TVA_ERR_MA_RECONNECT_FAIL                       (154)
#define TVA_ERR_MA_SESSION_TERMINATED                   (155)

#define TVA_ERR_PAM_CONNECTION_FAILED                   (160)
#define TVA_ERR_PAM_TOPIC_INACTIVE                      (161)
#define TVA_ERR_PAM_TOPIC_NOT_FOUND                     (162)
#define TVA_ERR_PAM_USER_INACTIVE                       (163)

#define TVA_ERR_SCHEMA_NOT_YET_IN_EFFECT                (170)
#define TVA_ERR_SCHEMA_EXPIRED                          (171)

#define TVA_ERR_NOT_IMPLEMENTED                         (200)

#define TVA_ERR_SHORT_PKT                               (201)
#define TVA_ERR_MISSING_US                              (202)     

/* Backwards Compatibility */
#define TVA_ERR_INITIALIZATION_STARTUP_EXPECTED         TVA_ERR_MA_RECONNECT_FAIL



/* Function definitions	*/

/* -------------------------------------------------------------------- */
/* tvaGetErrorMessage -- This function returns the error message        */
/* assiciated with the errorcode.                                       */
/* -------------------------------------------------------------------- */

TVA_EXPORTED TVA_STRING tvaGetErrorMessage(TVA_STATUS errorcode);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_TVAERRORS_H_*/

