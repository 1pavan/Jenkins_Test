#ifndef __RDM_GenericManager_H__
#define __RDM_GenericManager_H__

/**
	\class GenericManager GenericManager.h 
	\brief
	Generic domain handler. It domain neutral and does not cache data. It should be 
    used either for diagnostic purposes for for handling domain models that do not
    currently have a specific implementation written for them (like MarketPrice
    and MarketByOrder have in this application).


*/

#include "Transform.h"
#include "ConsumerDomainManager.h"
#include "ConsumerCache.h"

class ReutersMessageHandler;
//  Generic info will not be cached so in this case GenericManager will inherit from ConsumerCache
class VolanteManager : public ConsumerDomainManager , public ConsumerCache
{
public:
	VolanteManager(RDMConsumer &consumer,
			const RFA_String & serviceName, int messgeModelType);

	~VolanteManager();

		// inherited from ConsumerDomainManager
	virtual void init();
	virtual void cleanup();

		// inherited from ConsumerCache
	virtual ConsumerItem & getCreateItem(const std::string & name);
	virtual ConsumerItem & getItem(const std::string & name);
	virtual void deleteItem(ConsumerItem & item);
	virtual void deleteItem(const std::string & name);
};

#endif

