/*
** Copyright (c) 2007 Tervela Inc,   All rights reserved.
*/

/***********************************************************************
*
* FILE NAME
*      tvaClientAPIInterface.h
*
* DESCRIPTION
*      Tervela API Interface and Definitions
*
***********************************************************************/

#ifndef _TVACLIENTAPIINTERFACE_H_
#define _TVACLIENTAPIINTERFACE_H_

/* Common includes */
#include "tvaErrors.h"
#include "tvaSecurityContext.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Defines */
#define TVA_SUBSCRIPTIONTYPE_CALLBACK 1
#define TVA_SUBSCRIPTIONTYPE_QUEUE 2
#define TVA_SUBSCRIPTIONTYPE_SERVICE 3

#define TVA_LKV_SNAPSHOT 0
#define TVA_LKV_RESYNC 1
#define TVA_LKV_SNAPSHOT_NEXT 2

#define TVA_QOS_BEST_EFFORT               (0)
#define TVA_QOS_LAST_KNOWN_MESSAGE        (1)
#define TVA_QOS_GUARANTEED_CONNECTED      (2)
#define TVA_QOS_GUARANTEED_DISCONNECTED   (3)

/* API Interface Types */
typedef void* TVA_PUBLISHER_HANDLE;
typedef void* TVA_MESSAGE_QUEUE_HANDLE;
typedef void* TVA_MESSAGE_DATA_HANDLE;
typedef void* TVA_SESSION_INFORMATION_HANDLE;

typedef struct _loptions
{
    TVA_UINT32  subscriptionTimeout;    /* Depricated field Remove      */
    TVA_UINT32  schemaTimeout;          /* Depricated field Remove      */

    TVA_UINT16  clientPort;             /* Client Data Plane port       */
    char*       clientIPAddress;        /* IP address of the client     */
    TVA_UINT16  clientPortRangeLo;      /* Low value for DP port range  */
    TVA_UINT16  clientPortRangeHi;      /* High value for DP port range */
    TVA_UINT32  commBufferPoolSize;     /* Fixed buffer pool size       */
                                        /* Tuning Parameters            */
    TVA_UINT32  pub_rate;               /* Publisher rate               */
    TVA_UINT32  pub_msg_exp;            /* Pub Msg expiration           */
    TVA_UINT32  pub_bw_limit;           /* Pub B/W limitation	        */
    TVA_UINT32  pub_intr_delay;         /* Tx Interrupt Delay           */
    TVA_UINT32  pub_intr_qbytes;        /* Tx Interrupt Q-Bytes         */
    TVA_UINT32  pub_frag_burst;         /* Pub Frag burst               */
    TVA_UINT32  pub_frag_delay;         /* Pub Frag delay               */
    TVA_UINT32  sub_rate;               /* Subscriber rate              */
    TVA_UINT32  sub_msg_exp;            /* Sub Msg expiration           */
    TVA_UINT32  sub_frag_timeout;       /* Sub Frag timeout             */
    TVA_UINT32  sub_queue_tbuf;         /* Sub Queues buffers           */
} TVA_LOGIN_OPTIONS;

typedef void* TVA_PUBLISH_MESSAGE_DATA_HANDLE;

typedef void* TVA_MESSAGE_SCHEMA_HANDLE;

typedef void* TVA_FIELD_ITERATOR_HANDLE;

typedef struct tvaMessage
{
    TVA_MESSAGE_DATA_HANDLE messageData;
    TVA_UINT32              qosNotification;
    char*                   topicName;
    TVA_UINT64              totalMessageLatency;
    TVA_UINT32              topicSeqNum;
    TVA_UINT16              topicSeqGap;
    TVA_UINT64              msgReceiveTime;
    TVA_UINT64              msgGenerationTime;
} TVA_MESSAGE;

#define TVA_ERR_QOS_DATALOSS   (0x00000001)
#define TVA_ERR_QOS_OUTOFORDER (0x00000002)
#define TVA_ERR_QOS_RESYNC     (0x00000004)

#define TVA_MSG_DATALOSS(_m)   ((_m)->qosNotification & TVA_ERR_QOS_DATALOSS)
#define TVA_MSG_OUTOFORDER(_m) ((_m)->qosNotification & TVA_ERR_QOS_OUTOFORDER)
#define TVA_MSG_RESYNC(_m)     ((_m)->qosNotification & TVA_ERR_QOS_RESYNC)

typedef struct tvaMsgFieldInfo
{
    TVA_UINT16      fieldId;
    TVA_FIELD_TYPE  fieldType;
}TVA_MSG_FIELD_INFO;

typedef void* TVA_SUBSCRIPTION_HANDLE;


/* Function Declarations */

/* Session Control */
TVA_EXPORTED TVA_STATUS tvaLogin(
    char* userName,
    TVA_SECURITY_CONTEXT securityInformation,
    char* messagingAppliances[],
    TVA_UINT16 noOfMAInList,
    TVA_UINT64 timeout,
    TVA_LOGIN_OPTIONS *loginOptions,
    void (*errorNotificationCallback)(TVA_UINT32, char*),
    TVA_SESSION_INFORMATION_HANDLE *sessionInfo);

TVA_EXPORTED TVA_STATUS tvaTerminateSession(TVA_SESSION_INFORMATION_HANDLE sessionInfo);


/* Message Queue */
TVA_EXPORTED TVA_STATUS tvaCreateMessageQueue(
    TVA_UINT32 size,
    TVA_BOOLEAN isThreadSafe,
    TVA_MESSAGE_QUEUE_HANDLE *queueRef);

TVA_EXPORTED TVA_STATUS tvaDisposeMessageQueue(
    TVA_MESSAGE_QUEUE_HANDLE messageQueue);

TVA_EXPORTED TVA_STATUS tvaGetNextMessageFromQueue(
    TVA_MESSAGE_QUEUE_HANDLE messageQueue,
    TVA_MESSAGE **message);

TVA_EXPORTED TVA_UINT32 tvaGetNumberOfQueuedMessages(
    TVA_MESSAGE_QUEUE_HANDLE queue);

TVA_EXPORTED TVA_BOOLEAN tvaWaitForDataInMessageQueue(
    TVA_MESSAGE_QUEUE_HANDLE messageQueue,
    TVA_UINT64 timeOut);

TVA_EXPORTED TVA_BOOLEAN tvaIsMessageQueueEmpty(
    TVA_MESSAGE_QUEUE_HANDLE messageQueue);

TVA_EXPORTED TVA_BOOLEAN tvaIsMessageQueueFull(
    TVA_MESSAGE_QUEUE_HANDLE messageQueue);


/* Pub Sub */
TVA_EXPORTED TVA_STATUS tvaCreatePublication(
    TVA_SESSION_INFORMATION_HANDLE sessionInfo,
    char* topicName,
    TVA_UINT64 maximumCachePeriod,
    TVA_BOOLEAN enableQOSNotifications,
    TVA_BOOLEAN allowPartialPublish,
    TVA_PUBLISHER_HANDLE *publisher);

TVA_EXPORTED TVA_STATUS tvaCancelPublication(
    TVA_PUBLISHER_HANDLE publicationToCancel,
    TVA_SESSION_INFORMATION_HANDLE sessionInfo);

TVA_EXPORTED TVA_STATUS tvaCreateMessage(
    TVA_PUBLISHER_HANDLE publisher,
    TVA_PUBLISH_MESSAGE_DATA_HANDLE *publishMessageData);

TVA_EXPORTED TVA_STATUS tvaCreateMessageForTopic(
    TVA_PUBLISHER_HANDLE publisher,
    char* topicName,
    TVA_PUBLISH_MESSAGE_DATA_HANDLE *publishMessageData);

TVA_EXPORTED TVA_STATUS tvaCreateSubMessage(
    TVA_UINT16 fieldId,
    TVA_PUBLISH_MESSAGE_DATA_HANDLE parentData,
    TVA_PUBLISH_MESSAGE_DATA_HANDLE *childData);

TVA_EXPORTED TVA_STATUS tvaSendMessage(TVA_PUBLISH_MESSAGE_DATA_HANDLE message);

TVA_EXPORTED TVA_STATUS tvaSubscribeWithQueue(
    TVA_STRING topicName,
    TVA_MESSAGE_QUEUE_HANDLE receiveQueue,
    TVA_SESSION_INFORMATION_HANDLE sessInfoHandle,
    TVA_UINT32 qualityOfService,
    TVA_BOOLEAN guaranteeOrder, 
    TVA_UINT64 maximumCachePeriod, 
    TVA_SUBSCRIPTION_HANDLE *subscriptionHandle);

TVA_EXPORTED TVA_STATUS tvaSubscribeWithCallback(
    TVA_STRING topicName,
    void (*subscriptionCallback)(TVA_MESSAGE *),
    TVA_SESSION_INFORMATION_HANDLE sessionInfoHandle,
    TVA_UINT32 qualityOfService,
    TVA_BOOLEAN guaranteeOrder,
    TVA_UINT64 maximumCachePeriod,
    TVA_SUBSCRIPTION_HANDLE *subscriptionHandle);

TVA_EXPORTED TVA_STATUS tvaSubscribeWithCallbackEx(
    TVA_STRING topicName,
    void (*subscriptionCallback)(TVA_MESSAGE *, void *),
    void *callbackContext,
    TVA_SESSION_INFORMATION_HANDLE sessionInfoHandle,
    TVA_UINT32 qualityOfService,
    TVA_BOOLEAN guaranteeOrder,
    TVA_UINT64 maximumCachePeriod,
    TVA_SUBSCRIPTION_HANDLE *subscriptionHandle);

TVA_EXPORTED TVA_STATUS tvaTerminateSubscription(
    TVA_SUBSCRIPTION_HANDLE subscriptionsToCancel,
    TVA_SESSION_INFORMATION_HANDLE sessionInfo);

TVA_EXPORTED TVA_STATUS tvaGetSchemaIdByName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE publishMessageData,
    char* schemaName,
    TVA_UINT32 *schemaId);

TVA_EXPORTED TVA_STATUS tvaCreateSchemaFieldIterator(
    TVA_MESSAGE_DATA_HANDLE msgDataHandle,
    TVA_FIELD_ITERATOR_HANDLE *fieldHandle) ;

TVA_EXPORTED TVA_STATUS tvaGetNextSchemaField(
    TVA_FIELD_ITERATOR_HANDLE fieldHandle,
    TVA_MSG_FIELD_INFO **pFieldInformation);

TVA_EXPORTED void tvaReleaseSchemaFieldIterator(
    TVA_FIELD_ITERATOR_HANDLE fieldHandle);

TVA_EXPORTED TVA_STATUS tvaCreateMessageFieldIterator(
    TVA_MESSAGE_DATA_HANDLE msgDataHandle,
    TVA_FIELD_ITERATOR_HANDLE* messageItrHandle);

TVA_EXPORTED TVA_STATUS tvaGetNextMessageField(
    TVA_FIELD_ITERATOR_HANDLE fieldHandle, 
    TVA_MSG_FIELD_INFO **pFieldInformation);

TVA_EXPORTED void tvaReleaseMessageFieldIterator(
    TVA_FIELD_ITERATOR_HANDLE fieldHandle);

TVA_EXPORTED TVA_STATUS tvaGetSchemaForFieldId(
    TVA_UINT16 fieldId,
    TVA_MESSAGE_SCHEMA_HANDLE *schema);

TVA_EXPORTED TVA_STATUS tvaGetSchemaForTopic(char* topicName,
    TVA_MESSAGE_SCHEMA_HANDLE *schema);

TVA_EXPORTED TVA_STATUS tvaSelectSchemaForMessage(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE publishMessageData,
    TVA_UINT32 schemaId);

TVA_EXPORTED TVA_STATUS tvaGetLatency(
        TVA_MESSAGE_DATA_HANDLE msgDataHandle,
        TVA_UINT64 *latency);

TVA_EXPORTED void tvaReleaseSchema(TVA_MESSAGE_SCHEMA_HANDLE schema);

TVA_EXPORTED void tvaReleaseMessageData(TVA_MESSAGE *element);

TVA_EXPORTED void tvaReleasePublishData(TVA_PUBLISH_MESSAGE_DATA_HANDLE msgData);

TVA_EXPORTED TVA_STATUS tvaGetFieldNameFromFieldId(
    TVA_MESSAGE_DATA_HANDLE msgDataHandle,
    TVA_UINT16 fieldId,
    char** pFieldName);

TVA_EXPORTED void tvaReleaseFieldName(char* fieldName);

/* Message Processing */
TVA_EXPORTED TVA_STATUS tvaGetBooleanFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE msgDataHandle,
    TVA_UINT16 fieldId,
    TVA_BOOLEAN *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetByteFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_UINT8 *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetShortFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_INT16 *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetIntFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_INT32 *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetLongFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_INT64 *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetFloatFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_FLOAT *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetDoubleFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,TVA_DOUBLE *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetDateTimeFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId, 
    TVA_DATE *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetStringFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    char** fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetBytesFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_UINT8 **fieldValue,
    TVA_UINT32 *fieldLength);

TVA_EXPORTED TVA_STATUS tvaGetEmbeddedMessageFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_MESSAGE **fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetReferenceFromMessageByFieldId(
    TVA_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    void **fieldData,
    TVA_UINT32 *fieldLen);

TVA_EXPORTED TVA_STATUS tvaGetFieldIDFromFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_UINT16 *fieldId);

TVA_EXPORTED TVA_STATUS tvaGetBooleanFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_BOOLEAN *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetByteFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_UINT8 *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetShortFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_INT16 *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetIntFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_INT32 *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetLongFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_INT64 *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetFloatFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_FLOAT *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetDoubleFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_DOUBLE *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetDateTimeFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName, 
    TVA_DATE *fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetStringFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    char** fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetBytesFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_UINT8 **fieldValue,
    TVA_UINT32 *fieldLength);

TVA_EXPORTED TVA_STATUS tvaGetEmbeddedMessageFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_MESSAGE **fieldValue);

TVA_EXPORTED TVA_STATUS tvaGetReferenceFromMessageByFieldName(
    TVA_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    void **fieldData,
    TVA_UINT32 *fieldLen);

TVA_EXPORTED TVA_STATUS tvaSetBooleanIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_BOOLEAN fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetByteIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_UINT8 fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetShortIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_INT16 fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetIntIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_INT32 fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetLongIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_INT64 fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetFloatIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_FLOAT fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetDoubleIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_DOUBLE fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetDateTimeIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_DATE fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetStringIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    char* fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetBytesIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_UINT8* fieldValue,
    TVA_UINT32 fieldLength);

TVA_EXPORTED TVA_STATUS tvaSetEmbeddedMessageIntoMessageByFieldId(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    TVA_UINT16 fieldId,
    TVA_PUBLISH_MESSAGE_DATA_HANDLE fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetBooleanIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_BOOLEAN fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetByteIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_UINT8 fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetShortIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_INT16 fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetIntIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_INT32 fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetLongIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_INT64 fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetFloatIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_FLOAT fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetDoubleIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_DOUBLE fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetDateTimeIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_DATE fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetStringIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    char* fieldValue);

TVA_EXPORTED TVA_STATUS tvaSetBytesIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message,
    char* fieldName,
    TVA_UINT8* fieldValue,
    TVA_UINT32 fieldLength);

TVA_EXPORTED TVA_STATUS tvaSetEmbeddedMessageIntoMessageByFieldName(
    TVA_PUBLISH_MESSAGE_DATA_HANDLE message, 
    char* fieldName,
    TVA_PUBLISH_MESSAGE_DATA_HANDLE fieldValue);

TVA_EXPORTED void tvaReleaseFieldValue(void *fieldValue);

TVA_EXPORTED void tvaReleaseMsgFieldInfo(TVA_MSG_FIELD_INFO *fieldInfo);


/* Misc */
TVA_EXPORTED TVA_STATUS tvaGetMAList(char* **maList);

/* The LKV API calls require the LKV library */
TVA_EXPORTED TVA_STATUS tvaGetLKVforTopic(
    TVA_SESSION_INFORMATION_HANDLE sessionInfo,
    char* topicName,
    TVA_UINT32 requestType,
    TVA_UINT64 timeout,
    TVA_MESSAGE **message);

TVA_EXPORTED TVA_STATUS tvaSubscribeLKVWithQueue(
    TVA_STRING topicName,
    TVA_MESSAGE_QUEUE_HANDLE receiveQueue,
    TVA_SESSION_INFORMATION_HANDLE sessInfoHandle,
    TVA_UINT32 qualityOfService,
    TVA_BOOLEAN guaranteeOrder,
    TVA_UINT64 maximumCachePeriod,
    TVA_SUBSCRIPTION_HANDLE *subscriptionHandle);

TVA_EXPORTED TVA_STATUS tvaSubscribeLKVWithCallback(
    TVA_STRING topicName,
    void (*subscriptionCallback)(TVA_MESSAGE *),
    TVA_SESSION_INFORMATION_HANDLE sessionInfoHandle,
    TVA_UINT32 qualityOfService,
    TVA_BOOLEAN guaranteeOrder,
    TVA_UINT64 maximumCachePeriod,
    TVA_SUBSCRIPTION_HANDLE *subscriptionHandle);

TVA_EXPORTED TVA_STATUS tvaGetLKVTopicList(
   TVA_SESSION_INFORMATION_HANDLE sessionInfo,
   TVA_STRING wildcardTopic,
   TVA_MESSAGE **message);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_TVACLIENTAPIINTERFACE_H_*/
