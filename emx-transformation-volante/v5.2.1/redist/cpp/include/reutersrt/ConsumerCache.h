#ifndef _RFA_ConsumerCache_h_
#define _RFA_ConsumerCache_h_

/**
	\class ConsumerCache ConsumerCache.h 
	\brief
	Base class for a Cache implementation. Provides an interface for basic
	cache management of ConsumerItems

*/

#include "Common/Handle.h"
#include "Message/AttribInfo.h"
#include "ConsumerItem.h"

#include <map>

typedef std::map<std::string, ConsumerItem *> StringConsumerItemMap;

class ConsumerCache
{
public:
	inline ConsumerCache(bool cacheEnabled);

	virtual ~ConsumerCache();

	inline bool cacheEnabled() { return _cacheEnabled; }

	virtual ConsumerItem & getCreateItem(const std::string & name) = 0;
	virtual ConsumerItem & getItem(const std::string & name) = 0;
	virtual void deleteItem(ConsumerItem & item) = 0;
	virtual void deleteItem(const std::string & name) = 0;

   const StringConsumerItemMap* getCachedItemList();

protected:
	bool _cacheEnabled;
	StringConsumerItemMap _cache;
};

inline ConsumerCache::ConsumerCache(bool cacheEnabled)
		: _cacheEnabled(cacheEnabled) 
{} 

inline ConsumerCache::~ConsumerCache()
{}

inline const StringConsumerItemMap* ConsumerCache::getCachedItemList()
{
	return &_cache;
}


#endif
