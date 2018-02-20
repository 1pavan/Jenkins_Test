#ifndef __REUTERSHEADER_H__
#define __REUTERSHEADER_H__
#include "AbstractDataObject.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "TransformContext.h"
#include "ExternalObject.h"
#include "InputParser.h"
#include <time.h>
#include <math.h>

#include "RDM/RDM.h"
#include "Data/Data_API.h"
#include "Data/Map.h"
#include "Data/MapWriteIterator.h"
#include "Data/MapReadIterator.h"
#include "Data/MapEntry.h"

#include "Data/Date.h"
#include "Common/Common.h"
#include "Message/RespMsg.h"
#include "reutersrt/ReutersUtil.h"

VOLANTE_NAMESPACE_BEGIN
class ReutersHeader {
	int MSG_TYPE_INDEX;
	int MSG_MODEL_TYPE_INDEX;
	int HINT_MASK_INDEX;
	int INDICATION_MASK_INDEX;
	int RESP_TYPE_INDEX;
	int RESP_TYPE_NUM_INDEX;
	int RESP_STATUS_INDEX;
	int QOS_INDEX;
	int ATTRIB_INFO_INDEX;
	int MANIFEST_INDEX;

	int ATTRIB_SERVICE_NAME_INDEX;
	int ATTRIB_DATA_MASK_INDEX;
	int ATTRIB_NAME_INDEX;
	int ATTRIB_NAME_TYPE_INDEX;
	int ATTRIB_ID_INDEX;
	int ATTRIB_ATTRIB_INDEX;

	int MANIFEST_SEQ_INDEX;
	int MANIFEST_FILTERED_COUNT_INDEX;
	int MANIFEST_FILTERED_TIME_INDEX;
	int MANIFEST_ITEM_GROUP;
	int MANIFEST_PERM_DATA_INDEX;

	int RESP_DATA_STATE_INDEX;
	int RESP_STATUS_CODE_INDEX;
	int RESP_STREAM_STATE_INDEX;
	int RESP_STATUS_TEXT_INDEX;

	enum {
		UNINITIALIZED = -2
	};
	rfa::message::AttribInfo cachedAttribInfo;
  rfa::message::Manifest cachedManifest;
  rfa::common::RespStatus cachedRespStatus;

public:
	ReutersHeader() : cachedAttribInfo(true) {
		MSG_TYPE_INDEX = UNINITIALIZED;
		ATTRIB_SERVICE_NAME_INDEX = UNINITIALIZED;
		MANIFEST_SEQ_INDEX = UNINITIALIZED;
		RESP_DATA_STATE_INDEX = UNINITIALIZED ;
	}
	void cacheHeaderIndex(DataObject* header) {
		if(MSG_TYPE_INDEX == UNINITIALIZED) {
			DataObjectMetaInfo* metaInfo = header->getMetaInfo();
			MSG_TYPE_INDEX = metaInfo->getFieldIndexIfExists("MsgType");
			MSG_MODEL_TYPE_INDEX = metaInfo->getFieldIndexIfExists("MsgModelType");
			HINT_MASK_INDEX = metaInfo->getFieldIndexIfExists("HintMask");
			INDICATION_MASK_INDEX = metaInfo->getFieldIndexIfExists("IndicationMask");
			RESP_TYPE_INDEX = metaInfo->getFieldIndexIfExists("RespType");
			RESP_TYPE_NUM_INDEX = metaInfo->getFieldIndexIfExists("RespTypeNum");
			RESP_STATUS_INDEX  = metaInfo->getFieldIndexIfExists("RespStatus");
			QOS_INDEX = -1;
			ATTRIB_INFO_INDEX = metaInfo->getFieldIndexIfExists("AttribInfo");
			MANIFEST_INDEX = metaInfo->getFieldIndexIfExists("Manifest");
		}
	}

	void cacheRespIndex(DataObject* resp) {
		if(RESP_DATA_STATE_INDEX == UNINITIALIZED) {
			DataObjectMetaInfo* metaInfo = resp->getMetaInfo();
			RESP_DATA_STATE_INDEX = metaInfo->getFieldIndexIfExists("DataState");
			RESP_STATUS_CODE_INDEX = metaInfo->getFieldIndexIfExists("StatusCode");
			RESP_STREAM_STATE_INDEX = metaInfo->getFieldIndexIfExists("StreamState");
			RESP_STATUS_TEXT_INDEX = metaInfo->getFieldIndexIfExists("StatusText");
		}
	}
	void cacheAttribIndex(DataObject* attrib) {
		if(ATTRIB_SERVICE_NAME_INDEX == UNINITIALIZED) {
			DataObjectMetaInfo* metaInfo = attrib->getMetaInfo();
			ATTRIB_SERVICE_NAME_INDEX = metaInfo->getFieldIndexIfExists("ServiceName");
			ATTRIB_DATA_MASK_INDEX = metaInfo->getFieldIndexIfExists("DataMask");
			ATTRIB_NAME_INDEX = metaInfo->getFieldIndexIfExists("Name");
			ATTRIB_NAME_TYPE_INDEX = metaInfo->getFieldIndexIfExists("NameType");
			ATTRIB_ID_INDEX = metaInfo->getFieldIndexIfExists("ID");
			ATTRIB_ATTRIB_INDEX = metaInfo->getFieldIndexIfExists("Attrib");
		}
	}
	void cacheManifestIndex(DataObject* manifest) {
		if(MANIFEST_SEQ_INDEX == UNINITIALIZED) {
			DataObjectMetaInfo* metaInfo = manifest->getMetaInfo();
			MANIFEST_SEQ_INDEX = metaInfo->getFieldIndexIfExists("SeqNum");
			MANIFEST_FILTERED_COUNT_INDEX = metaInfo->getFieldIndexIfExists("FilteredCount");
			MANIFEST_FILTERED_TIME_INDEX = metaInfo->getFieldIndexIfExists("FilteredTime");
			MANIFEST_ITEM_GROUP = metaInfo->getFieldIndexIfExists("ItemGroup");
			MANIFEST_PERM_DATA_INDEX = metaInfo->getFieldIndexIfExists("PermissionData");
		}
	}

	void parseHeader(const rfa::message::RespMsg* msg, DataObject* header, TransformContext& cxt) {
		cacheHeaderIndex(header);
		rfa::common::UInt8 hintMask = msg->getHintMask();
		if(MSG_TYPE_INDEX != -1) {
			header->setField(MSG_TYPE_INDEX, IntObject(msg->getMsgType()));
		}
		if(MSG_MODEL_TYPE_INDEX != -1) {
			header->setField(MSG_MODEL_TYPE_INDEX, IntObject(msg->getMsgModelType()));
		}
		if(HINT_MASK_INDEX != -1) {
			header->setField(HINT_MASK_INDEX, IntObject(hintMask));
		}
		if(INDICATION_MASK_INDEX != -1) {
			rfa::common::UInt8 indicationMask = msg->getIndicationMask();
			header->setField(INDICATION_MASK_INDEX, IntObject(indicationMask));
		}

		if(RESP_TYPE_INDEX != -1) {
			//if(hintMask & rfa::message::RespMsg::RespTypeFlag)
			{
				const rfa::message::RespMsg::RespType respType = msg->getRespType();
				header->setField(RESP_TYPE_INDEX, IntObject(respType));

			}
		}
		if(RESP_TYPE_NUM_INDEX != -1) {
			if(hintMask & rfa::message::RespMsg::RespTypeNumFlag) {
				rfa::common::UInt8 respTypeNum = msg->getRespTypeNum();
				header->setField(RESP_TYPE_NUM_INDEX, IntObject(respTypeNum));
			}
		}
		if(RESP_STATUS_INDEX != -1) {
			if(hintMask & rfa::message::RespMsg::RespStatusFlag) {
				DataObjectSection* sec = header->getSection(RESP_STATUS_INDEX);
				DataObject* respStatusElm = sec->createElement();
				sec->addElement(respStatusElm);
				cacheRespIndex(respStatusElm);
				const rfa::common::RespStatus& respStatus = msg->getRespStatus();
				if(RESP_DATA_STATE_INDEX != -1) {
					respStatusElm->setField(RESP_DATA_STATE_INDEX, IntObject(respStatus.getDataState()));
				}
				if(RESP_STATUS_CODE_INDEX != -1) {
					respStatusElm->setField(RESP_STATUS_CODE_INDEX, IntObject(respStatus.getStatusCode()));
				}
				if(RESP_STREAM_STATE_INDEX != -1) {
					respStatusElm->setField(RESP_STREAM_STATE_INDEX, IntObject(respStatus.getStreamState()));
				}
				if(RESP_STATUS_TEXT_INDEX != -1) {
					respStatusElm->setField(RESP_STATUS_TEXT_INDEX, StringObject(StringObject(ReutersUtils::toVString(respStatus.getStatusText()))));
				}
			}
		}
		if(QOS_INDEX != -1) {
			if(hintMask & rfa::message::RespMsg::QualityOfServiceFlag) {
				const rfa::common::QualityOfService& qos = msg->getQualityOfService();
				//TODO
			}
		}
		if(ATTRIB_INFO_INDEX != -1) {
			if(hintMask & rfa::message::RespMsg::AttribInfoFlag) {
				const rfa::message::AttribInfo& attribInfo = msg->getAttribInfo();
				DataObjectSection* sec = header->getSection(ATTRIB_INFO_INDEX);
				DataObject* attribElm = sec->createElement();
				sec->addElement(attribElm);
				cacheAttribIndex(attribElm);
				UInt32 attribHint = attribInfo.getHintMask();
				if(ATTRIB_SERVICE_NAME_INDEX != -1) {
					if( attribHint &  rfa::message::AttribInfo::ServiceNameFlag) {
						attribElm->setField(ATTRIB_SERVICE_NAME_INDEX, StringObject(ReutersUtils::toVString(attribInfo.getServiceName())));
					}
				}
				if(ATTRIB_DATA_MASK_INDEX != -1) {
					if( attribHint &  rfa::message::AttribInfo::DataMaskFlag) {
						attribElm->setField(ATTRIB_DATA_MASK_INDEX, IntObject(attribInfo.getDataMask()));
					}
				}
				if(ATTRIB_NAME_INDEX != -1) {
					if( attribHint &  rfa::message::AttribInfo::NameFlag) {
						attribElm->setField(ATTRIB_NAME_INDEX, StringObject(ReutersUtils::toVString(attribInfo.getName())));
					}
				}
				if(ATTRIB_NAME_TYPE_INDEX != -1) {
					if( attribHint &  rfa::message::AttribInfo::NameTypeFlag) {
						attribElm->setField(ATTRIB_NAME_TYPE_INDEX, IntObject(attribInfo.getNameType()));
					}
				}
				if(ATTRIB_ID_INDEX != -1) {
					if( attribHint &  rfa::message::AttribInfo::IDFlag) {
						attribElm->setField(ATTRIB_ID_INDEX, IntObject(attribInfo.getID()));
					}
				}
				if(ATTRIB_ATTRIB_INDEX != -1) {
					if( attribHint &  rfa::message::AttribInfo::AttribFlag) {
						attribElm->setField(ATTRIB_ATTRIB_INDEX, StringObject(ReutersUtils::toVString(attribInfo.getName())));
					}
				}

			}
		}
		if(MANIFEST_INDEX != -1) {
			if(hintMask & rfa::message::RespMsg::ManifestFlag) {
				const rfa::message::Manifest& manifest= msg->getManifest();
				UInt32 manifestHint = manifest.getHintMask();
				if(manifestHint != 0) {
					DataObjectSection* sec = header->getSection(MANIFEST_INDEX);
					DataObject* manifestElm = sec->createElement();
					sec->addElement(manifestElm);
					cacheManifestIndex(manifestElm);
					if(MANIFEST_SEQ_INDEX != -1) {
						if( manifestHint &  rfa::message::Manifest::SeqFlag) {
							manifestElm->setField(MANIFEST_SEQ_INDEX, IntObject(manifest.getSeqNum()));
						}
					}
					if(MANIFEST_FILTERED_COUNT_INDEX != -1) {
						if( manifestHint &  rfa::message::Manifest::FilteredFlag) {
							manifestElm->setField(MANIFEST_FILTERED_COUNT_INDEX, IntObject(manifest.getFilteredCount()));
							manifestElm->setField(MANIFEST_FILTERED_TIME_INDEX, IntObject(manifest.getFilteredTime()));
						}
					}
					if(MANIFEST_ITEM_GROUP != -1) {
						if( manifestHint &  rfa::message::Manifest::ItemGroupFlag) {
							manifestElm->setField(MANIFEST_ITEM_GROUP, BinaryObject(ReutersUtils::toBuffer(manifest.getItemGroup())));
						}
					}
					if(MANIFEST_PERM_DATA_INDEX != -1) {
						if( manifestHint &  rfa::message::Manifest::PermissionDataFlag) {
							manifestElm->setField(MANIFEST_PERM_DATA_INDEX, BinaryObject(ReutersUtils::toBuffer(manifest.getPermissionData())));
						}
					}
				}

			}
		}
		if(hintMask & rfa::message::RespMsg::HeaderFlag) {
			const rfa::common::Buffer& header = msg->getHeader();
		}
		if(hintMask & rfa::message::RespMsg::PayloadFlag) {
			//rfa::common::RespStatus& respStatus = msg->getRespStatus();
		}
	}
	void serializeHeader(rfa::message::RespMsg* msg, DataObject* header, TransformContext& cxt) {
		cacheHeaderIndex(header);
		if(MSG_TYPE_INDEX != -1) {
			IntObject msgType;
			if(header->getField(MSG_TYPE_INDEX, msgType)) {
				msg->setMsgType(msgType.intValue());
			}
		}
		if(MSG_MODEL_TYPE_INDEX != -1) {
			IntObject msgModelType;
			if(header->getField(MSG_MODEL_TYPE_INDEX, msgModelType)) {
				msg->setMsgModelType(msgModelType.intValue());
			}
		}
		if(HINT_MASK_INDEX != -1) {
			IntObject intFldVal;
			if(header->getField(HINT_MASK_INDEX, intFldVal)) {
				//msg->setHintMask(intFldVal.intValue());
			}
		}
		if(INDICATION_MASK_INDEX != -1) {
			IntObject intFldVal;
			if(header->getField(INDICATION_MASK_INDEX, intFldVal)) {
				msg->setIndicationMask(intFldVal.intValue());
			}
		}

		if(RESP_TYPE_INDEX != -1) {
			//if(hintMask & rfa::message::RespMsg::RespTypeFlag)
			{
				IntObject intFldVal;
				if(header->getField(RESP_TYPE_INDEX, intFldVal)) {
					msg->setRespType((rfa::message::RespMsg::RespType)intFldVal.intValue());
				}
			}
		}
		if(RESP_TYPE_NUM_INDEX != -1) {
			IntObject intFldVal;
			if(header->getField(RESP_TYPE_NUM_INDEX, intFldVal)) {
				msg->setRespTypeNum(intFldVal.intValue());
			}
		}
		if(RESP_STATUS_INDEX != -1) {
			DataObjectSection* sec = header->getSection(RESP_STATUS_INDEX);
			if(sec->getElementCount() == 1) {
				DataObject* respElm = sec->getElement(0);
				cacheRespIndex(respElm);
				IntObject intFldVal;
				cachedRespStatus.clear();
				if(respElm->getField(RESP_DATA_STATE_INDEX, intFldVal)) {
					cachedRespStatus.setDataState((rfa::common::RespStatus::DataState)intFldVal.intValue());
				}
				if(respElm->getField(RESP_STATUS_CODE_INDEX, intFldVal)) {
					cachedRespStatus.setStatusCode(intFldVal.intValue());
				}
				if(respElm->getField(RESP_STREAM_STATE_INDEX, intFldVal)) {
					cachedRespStatus.setStreamState((rfa::common::RespStatus::StreamState)intFldVal.intValue());
				}
				StringObject stringFldVal;
				if(respElm->getField(RESP_STATUS_TEXT_INDEX, stringFldVal)) {
					RFA_String statusText = ReutersUtils::toRMTESString(stringFldVal.getValue());
					cachedRespStatus.setStatusText(statusText);
				}
				msg->setRespStatus(cachedRespStatus);
			}
		}
		if(QOS_INDEX != -1) {
			IntObject intFldVal;
			if(header->getField(QOS_INDEX, intFldVal)) {
				msg->setRespTypeNum(intFldVal.intValue());
			}
		}
		if(ATTRIB_INFO_INDEX != -1) {
			DataObjectSection* sec = header->getSection(ATTRIB_INFO_INDEX);
			if(sec->getElementCount() == 1) {
				DataObject* attribElm = sec->getElement(0);
				cacheAttribIndex(attribElm);
				rfa::message::AttribInfo* attribInfo = &cachedAttribInfo;
				attribInfo->clear();
				msg->setAttribInfo(*attribInfo);
				if(ATTRIB_SERVICE_NAME_INDEX != -1) {
					StringObject stringFldVal;
					if(attribElm->getField(ATTRIB_SERVICE_NAME_INDEX, stringFldVal)) {
						RFA_String serviceName = ReutersUtils::toRMTESString(stringFldVal.getValue());
						attribInfo->setServiceName(serviceName);
					}
				}
				if(ATTRIB_DATA_MASK_INDEX != -1) {
					IntObject intFldVal;
					if(attribElm->getField(ATTRIB_DATA_MASK_INDEX, intFldVal)) {
						attribInfo->setDataMask(intFldVal.getValue());
					}
				}
				if(ATTRIB_NAME_INDEX != -1) {
					StringObject stringFldVal;
					if(attribElm->getField(ATTRIB_NAME_INDEX, stringFldVal)) {
						attribInfo->setName(ReutersUtils::toRMTESString(stringFldVal.getValue()));
					}
				}
				if(ATTRIB_NAME_TYPE_INDEX != -1) {
					IntObject intFldVal;
					if(attribElm->getField(ATTRIB_NAME_TYPE_INDEX, intFldVal)) {
						attribInfo->setNameType(intFldVal.getValue());
					}
				}
				if(ATTRIB_ID_INDEX != -1) {
					IntObject intFldVal;
					if(attribElm->getField(ATTRIB_ID_INDEX, intFldVal)) {
						attribInfo->setID(intFldVal.getValue());
					}
				}
				if(ATTRIB_ATTRIB_INDEX != -1) {
					IntObject intFldVal;
					if(attribElm->getField(ATTRIB_ATTRIB_INDEX, intFldVal)) {
						attribInfo->setID(intFldVal.getValue());
					}
				}
			}
		}
		if(MANIFEST_INDEX != -1) {
			DataObjectSection* sec = header->getSection(MANIFEST_INDEX);
			if(sec->getElementCount() == 1) {
				DataObject* manifestElm = sec->getElement(0);
				cacheManifestIndex(manifestElm);
				rfa::message::Manifest* manifest = &cachedManifest;
				msg->setManifest(*manifest);
				if(MANIFEST_SEQ_INDEX != -1) {
					IntObject intFldVal;
					if(manifestElm->getField(MANIFEST_SEQ_INDEX, intFldVal)) {
						manifest->setSeqNum(intFldVal.getValue());
					}
				}
				if(MANIFEST_FILTERED_COUNT_INDEX != -1) {
					IntObject intFldVal1;
					IntObject intFldVal2;
					if(manifestElm->getField(MANIFEST_FILTERED_COUNT_INDEX, intFldVal1)) {
						if(manifestElm->getField(MANIFEST_FILTERED_TIME_INDEX, intFldVal2)) {
								manifest->setFiltered(intFldVal1.getValue(), intFldVal2.getValue());
						}
					}
				}
				if(MANIFEST_ITEM_GROUP != -1) {
					BinaryObject binaryFldVal;
					if(manifestElm->getField(MANIFEST_ITEM_GROUP, binaryFldVal)) {
						manifest->setItemGroup(ReutersUtils::toBinary(binaryFldVal.getValue()));
					}
				}
				if(MANIFEST_PERM_DATA_INDEX != -1) {
					BinaryObject binaryFldVal;
					if(manifestElm->getField(MANIFEST_PERM_DATA_INDEX, binaryFldVal)) {
						manifest->setPermissionData(ReutersUtils::toBinary(binaryFldVal.getValue()));
					}
				}
			}
		}
		/*if(hintMask & rfa::message::RespMsg::HeaderFlag) {
			const rfa::common::Buffer& header = msg->getHeader();
		}
		if(hintMask & rfa::message::RespMsg::PayloadFlag) {
			//rfa::common::RespStatus& respStatus = msg->getRespStatus();
		}*/
	}

};
VOLANTE_NAMESPACE_END

#endif //__REUTERSHEADER_H__
