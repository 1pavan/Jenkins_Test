#ifndef __VOLANTESERVICEDIRECTORY_H__
#define __VOLANTESERVICEDIRECTORY_H__
/*

ServiceDirectorySimulator

Creates streaming data for service directories. Only one service is supported.

*/



#include "IncludeReuters.h"
#include "VolanteOMMProvider.h"

class VolanteServiceDirectory : public MessageProvider
{
public:
	VolanteServiceDirectory(OMMProvider* pOmmProvider, const MessageInfo& messageInfo, const std::string& serviceName, const std::string& name) : MessageProvider(pOmmProvider, messageInfo, serviceName, name), _attr(true) {
	}
    virtual ~VolanteServiceDirectory(void);

		RespMsg* prepareImage();
		void sendImage(RequestToken& token);
    virtual void sendUpdatesToAllRequestors();
    virtual bool satisfies( const AttribInfo& attr, const UInt8 msgModel) const;

protected:

    void createData(Data* data, const RespMsg::RespType respType);
    void encodeDirectoryMap(Map* pMap, const  RespMsg::RespType respType );
    void encodeDirectoryMapEntry(MapWriteIterator& mapWIt, const  RespMsg::RespType respType);
    void encodeDirectoryFilterList(FilterList* pFilterList, const  RespMsg::RespType respType);
    void encodeDirectoryInfoElementList(ElementList* pElementList);
    void encodeDirectoryStateElementList(ElementList* pElementList, const  RespMsg::RespType respType);
    void encodeDirectoryArray(Array* pArray);
    void encodeDirectoryArrayDictUsed(Array* pArray);
    void encodeDirectoryArrayQoS(Array* pArray);


private:
    RespMsg _msg;
    FilterList _filterList;
    FilterEntry _filterEntry;  
    ElementList _elementList;
    Map _map;
    MapEntry _mapEntry;
    ElementEntry _element;
    Array _array;
    Array _array2;
    ArrayEntry _arrayEntry;
    Array _arrayqos;
		AttribInfo _attr;

};

#endif //__VOLANTESERVICEDIRECTORY_H__
