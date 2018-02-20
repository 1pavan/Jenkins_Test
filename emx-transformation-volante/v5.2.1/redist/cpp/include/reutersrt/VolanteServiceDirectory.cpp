#include "VolanteServiceDirectory.h"
//#include "Decoder.h"
//#include "StandardOut.h"


VolanteServiceDirectory::~VolanteServiceDirectory(void)
{
}

bool VolanteServiceDirectory::satisfies( const AttribInfo& attr, const UInt8 msgModel) const{

    // satisfy all directory requests 
    return (msgModel == rfa::rdm::MMT_DIRECTORY) ;
}

RespMsg* VolanteServiceDirectory::prepareImage() {
    _msg.clear();
	_attr.setServiceName(getServiceName());
	_attr.setName(getName());
    _msg.setMsgModelType(rfa::rdm::MMT_DIRECTORY);		
    _msg.setAttribInfo(_attr);
    RespStatus respStatus;
    respStatus.setStreamState(RespStatus::OpenEnum);
    respStatus.setDataState(RespStatus::OkEnum);	
    respStatus.setStatusCode(RespStatus::NoneEnum);
    RFA_String  tmpStr("RequestCompleted", 15, true);
    respStatus.setStatusText(tmpStr);
    _msg.setRespStatus(respStatus);

    _msg.setRespType(RespMsg::RefreshEnum);
    _msg.setIndicationMask( RespMsg::RefreshCompleteFlag );    
    _msg.setRespTypeNum(rfa::rdm::REFRESH_SOLICITED);   //for solicited refresh, value is 0     	

    _map.clear();

    createData(static_cast<Data*>(&_map),RespMsg::RefreshEnum);

    _msg.setPayload(static_cast<Data&>(_map));
		return &_msg;
}

void VolanteServiceDirectory::sendImage(RequestToken& token) {
    _msg.clear();
	_attr.setServiceName(getServiceName());
	_attr.setName(getName());
    _msg.setMsgModelType(rfa::rdm::MMT_DIRECTORY);		
    _msg.setAttribInfo(_attr);
    RespStatus respStatus;
    respStatus.setStreamState(RespStatus::OpenEnum);
    respStatus.setDataState(RespStatus::OkEnum);	
    respStatus.setStatusCode(RespStatus::NoneEnum);
    RFA_String  tmpStr("RequestCompleted", 15, true);
    respStatus.setStatusText(tmpStr);
    _msg.setRespStatus(respStatus);

    _msg.setRespType(RespMsg::RefreshEnum);
    _msg.setIndicationMask( RespMsg::RefreshCompleteFlag );    
    _msg.setRespTypeNum(rfa::rdm::REFRESH_SOLICITED);   //for solicited refresh, value is 0     	

    _map.clear();

    createData(static_cast<Data*>(&_map),RespMsg::RefreshEnum);

    _msg.setPayload(static_cast<Data&>(_map));
    OMMSolicitedItemCmd itemCmd;
    itemCmd.setMsg(_msg);
    itemCmd.setRequestToken(token);
    pOmmProvider->submit(&itemCmd);
	}

void VolanteServiceDirectory::sendUpdatesToAllRequestors() {

  return;

    /* We could send Group stale and un-stale messages as updates */

}

void VolanteServiceDirectory::createData(Data*  data, const RespMsg::RespType respType )
{
    encodeDirectoryMap(static_cast<Map*>(data), respType);
}


void VolanteServiceDirectory::encodeDirectoryMap( Map* pMap, const  RespMsg::RespType respType )
{
    assert(pMap);

    pMap->clear();

    pMap->setKeyDataType( DataBuffer::StringAsciiEnum);   

    // only publish our service
    pMap->setTotalCountHint(1); 
    pMap->setIndicationMask(  rfa::data::Map::EntriesFlag);
    MapWriteIterator mapWIt;

    try {
        mapWIt.start(*pMap);
    }
    catch (rfa::common::InvalidUsageException& e) {
        cout << e.getStatus().getStatusText() << endl;
        throw;
    }   
    encodeDirectoryMapEntry( mapWIt, respType);

    mapWIt.complete();
}

void VolanteServiceDirectory::encodeDirectoryMapEntry( MapWriteIterator& mapWIt, const RespMsg::RespType respType)
{

    //********* Begin Encode MapEntry **********
    _mapEntry.clear();
    _mapEntry.setAction(respType==RespMsg::RefreshEnum? MapEntry::Add : MapEntry::Update);

    // Set ServiceName as key for MapEntry
    DataBuffer keyDataBuffer(true);
    keyDataBuffer.setFromString(_attr.getServiceName(), DataBuffer::StringAsciiEnum);
    _mapEntry.setKeyData(keyDataBuffer);

    _filterList.clear();
    encodeDirectoryFilterList(&_filterList, respType);
    _mapEntry.setData(static_cast<Data&>(_filterList));

    mapWIt.bind(_mapEntry);

}


void VolanteServiceDirectory::encodeDirectoryFilterList( FilterList* pFilterList, const  RespMsg::RespType respType)

{
    assert(pFilterList);
    FilterListWriteIterator filterListWIt;
    filterListWIt.start(*pFilterList);  

    if (respType == RespMsg::RefreshEnum) {

        pFilterList->setTotalCountHint(2);

        //Encode ElementList for Service Info  
        _filterEntry.clear();
        _filterEntry.setFilterId(rfa::rdm::SERVICE_INFO_ID);
        _filterEntry.setAction(FilterEntry::Set);		// Set this to Set since this is the full filterEntry
        _elementList.clear();
        encodeDirectoryInfoElementList(&_elementList);
        _filterEntry.setData(static_cast<const Data&>(_elementList));
        filterListWIt.bind(_filterEntry);

        //Encode ElementList for Service State
        _filterEntry.clear();
        _filterEntry.setFilterId(rfa::rdm::SERVICE_STATE_ID);
        _filterEntry.setAction(FilterEntry::Set);   // Set this to Set since this is the full filterEntry
        _elementList.clear();
        encodeDirectoryStateElementList(&_elementList, respType);
        _filterEntry.setData(static_cast<const Data&>(_elementList));
        filterListWIt.bind(_filterEntry);
    }
    else
        assert(0);
    // only send directory status when a responding to login with closed/closedrecoverable

    filterListWIt.complete();
}


void VolanteServiceDirectory::encodeDirectoryInfoElementList(ElementList* pElementList)
{
    assert(pElementList);
    ElementListWriteIterator elemListWIt;
    elemListWIt.start(*pElementList);


    DataBuffer dataBuffer(true); 	
    RFA_String str;
    RFA_String nameValue;

    // Encode Name
    str = "Name";
    _element.clear();
    _element.setName(str);
    nameValue =_attr.getServiceName();
    dataBuffer.setFromString(nameValue,DataBuffer::StringAsciiEnum);
    _element.setData( dataBuffer );
    elemListWIt.bind(_element);

    // Encode Vendor
    _element.clear();
    dataBuffer.clear();
    str = "Vendor";
    _element.setName(str);
    nameValue = "Reuters";
    dataBuffer.setFromString(nameValue,DataBuffer::StringAsciiEnum);
    _element.setData( dataBuffer );
    elemListWIt.bind(_element);

    // Encode  isSource 
    _element.clear();
    dataBuffer.clear();
    str = "IsSource";
    _element.setName(str);
    dataBuffer.setUInt32(1);		// Original Publisher  
    _element.setData( dataBuffer );
    elemListWIt.bind(_element);

    // Encode Capabilities
    _element.clear();
    str = "Capabilities";
    _element.setName(str);
    _array.clear();
    encodeDirectoryArray(&_array);
    _element.setData(static_cast<const Data&>(_array));
    elemListWIt.bind(_element);

    // Encode DictionariesUsed
    _element.clear();
    str = "DictionariesUsed";
    _element.setName(str);
    _array2.clear();
    encodeDirectoryArrayDictUsed(&_array2);
    _element.setData(static_cast<const Data&>(_array2));
    elemListWIt.bind(_element);


    // Encode Quality of Service
    _element.clear();
    str = "QoS";
    _element.setName(str);
    _arrayqos.clear();
    encodeDirectoryArrayQoS(&_arrayqos);
    _element.setData(static_cast<const Data&>(_arrayqos));
    elemListWIt.bind(_element);

    elemListWIt.complete();
}

void VolanteServiceDirectory::encodeDirectoryStateElementList(ElementList* pElementList, const  RespMsg::RespType respType)
{
    assert(pElementList);
    ElementListWriteIterator elemListWIt;
    elemListWIt.start(*pElementList);

    //Encode Element ServiceState
    RFA_String str = "ServiceState";
    _element.clear();
    _element.setName(str);

    DataBuffer dataBuffer(true);

    if (!_serviceUp) cout <<"Service DOWN " <<endl;
    else
        cout <<"Service UP "<<  endl;

    dataBuffer.setUInt32(_serviceUp); 

    _element.setData( dataBuffer );
    elemListWIt.bind(_element);

    //Encode Element AcceptingRequests
    _element.clear();
    str = "AcceptingRequests";
    _element.setName(str);

    // accept requests 
    DataBuffer dataBuffer2(true); 
    dataBuffer2.setUInt32(_serviceUp);  
    _element.setData( dataBuffer2 );
    elemListWIt.bind(_element);
    elemListWIt.complete();
}


void VolanteServiceDirectory::encodeDirectoryArray(Array* pArray)
{
    assert(pArray);
    ArrayWriteIterator arrWIt; 
    arrWIt.start(*pArray);

    DataBuffer dataBuffer(true);

    int mType;

    // use default capabilities lise
    // Specify Dictionary as a capability
    /* 
    mType = rfa::rdm::MMT_DICTIONARY;
    dataBuffer.setUInt32((UInt32)mType);
    _arrayEntry.setData(dataBuffer);
    arrWIt.bind(_arrayEntry);

    _arrayEntry.clear();
    dataBuffer.clear();
    */
    // Specify Market Price as a capability
    mType = rfa::rdm::MMT_MARKET_PRICE;
    dataBuffer.setUInt32((UInt32)mType);
    _arrayEntry.clear();
    _arrayEntry.setData(dataBuffer);
    arrWIt.bind(_arrayEntry);

    // Specify Market By Order  as a capability
    mType = rfa::rdm::MMT_MARKET_BY_ORDER;
    dataBuffer.clear();
    dataBuffer.setUInt32((UInt32)mType);
    _arrayEntry.clear();
    _arrayEntry.setData(dataBuffer);
    arrWIt.bind(_arrayEntry);

    arrWIt.complete();
}


void VolanteServiceDirectory::encodeDirectoryArrayDictUsed( Array* pArray)
{
    assert(pArray);

    ArrayWriteIterator arrWIt; 
    arrWIt.start(*pArray);

    DataBuffer dataBuffer(true);
    dataBuffer.setFromString("RWFFld", DataBuffer::StringAsciiEnum);
    _arrayEntry.clear();   
    _arrayEntry.setData(dataBuffer);
    arrWIt.bind(_arrayEntry);

    dataBuffer.setFromString("RWFEnum", DataBuffer::StringAsciiEnum);
    _arrayEntry.setData(dataBuffer);
    arrWIt.bind(_arrayEntry);
    arrWIt.complete();
}

void VolanteServiceDirectory::encodeDirectoryArrayQoS( Array* pArray)														
{
    rfa::common::QualityOfService	QoS;
    QoS.setRate(QualityOfService::tickByTick);
    QoS.setTimeliness(QualityOfService::realTime);

    assert(pArray);
    ArrayWriteIterator arrWIt; 
    arrWIt.start(*pArray);

    DataBuffer dataBuffer(true);

    rfa::common::QualityOfServiceInfo QoSInfo;  
    QoSInfo.setQualityOfService(QoS);

    dataBuffer.setQualityOfServiceInfo(QoSInfo);
    _arrayEntry.clear();
    _arrayEntry.setData(dataBuffer);
    arrWIt.bind(_arrayEntry);

    arrWIt.complete();
}

