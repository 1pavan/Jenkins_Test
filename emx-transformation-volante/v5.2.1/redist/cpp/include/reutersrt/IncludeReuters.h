#ifndef __INCLUDEREUTERS_H__
#define __INCLUDEREUTERS_H__
#include <iostream>
#include <assert.h>
#include "Common/Client.h"
#include "Common/Common.h"
#include "Common/Data.h"
#include "Common/EventQueue.h"
#include "Common/CommonEnums.h"
#include "Common/RFA_String.h"
#include "Common/Context.h"
#include "Common/RespStatus.h"

#include "Logger/AppLogger.h"
#include "Logger/AppLoggerMonitor.h"


#include "RDM/RDM.h"

#include "Config/ConfigDatabase.h"
#include "Config/StagingConfigDatabase.h"
#include "Config/ConfigTree.h"
#include "Config/ConfigNode.h"
#include "Config/ConfigNodeIterator.h"

#include "Data/Array.h"
#include "Data/ArrayEntry.h"
#include "Data/ElementList.h"
#include "Data/ArrayWriteIterator.h"
#include "Data/ElementListWriteIterator.h"
#include "Data/ElementEntry.h"
#include "Data/FieldList.h"
#include "Data/FieldEntry.h"
#include "Data/FieldListWriteIterator.h"
#include "Data/FilterList.h"
#include "Data/FilterEntry.h"
#include "Data/FilterListWriteIterator.h"
#include "Data/Map.h"
#include "Data/MapEntry.h"
#include "Data/MapWriteIterator.h"


#include "Message/AttribInfo.h"
#include "Message/ReqMsg.h"
#include "Message/RespMsg.h"

#include "SessionLayer/OMMProvider.h"
#include "SessionLayer/OMMListenerConnectionIntSpec.h"
#include "SessionLayer/OMMClientSessionListenerIntSpec.h"
#include "SessionLayer/OMMErrorIntSpec.h"
#include "SessionLayer/OMMActiveClientSessionEvent.h"
#include "SessionLayer/OMMInactiveClientSessionEvent.h"
#include "SessionLayer/OMMSolicitedItemEvent.h"
#include "SessionLayer/OMMSolicitedItemCmd.h"
#include "SessionLayer/OMMCmdErrorEvent.h"
#include "SessionLayer/ClientSessionStatus.h"
#include "SessionLayer/OMMClientSessionCmd.h"
#include "SessionLayer/OMMClientSessionIntSpec.h"
#include "SessionLayer/RequestToken.h"
#include "SessionLayer/ConnectionEvent.h"
#include "SessionLayer/Session.h"

#include <vector>
#include <map>
#include <set>

using namespace std;
using namespace rfa::logger;
using namespace rfa::message;
using namespace rfa::config;
using namespace rfa::rdm;
using namespace rfa::common;
using namespace rfa::data;
using namespace rfa::sessionLayer;
#pragma warning(disable: 4251)  // using non-exported as public in exported

#endif //__INCLUDEREUTERS_H__
