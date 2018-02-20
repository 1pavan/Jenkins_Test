#ifndef __OBJECTUTILS_H__
#define __OBJECTUTILS_H__

#include "ObjectList.h"
#include "ObjectFactory.h"

VOLANTE_NAMESPACE_BEGIN

template<class T>
class ObjectPtrMap {
public:
	typedef std::map<vstring, T*> ObjectMapImpl;
	typedef typename ObjectMapImpl::iterator iterator;
	typedef typename ObjectMapImpl::value_type value_type;

	ObjectPtrMap() {
	}
	~ObjectPtrMap() {
		clear();
	}
	void clear() {
		for(typename ObjectMapImpl::iterator it = mapImpl.begin(); it != mapImpl.end(); ++it) {
			deleteObject(it->second);
		}
		mapImpl.clear();
	}
	void put(const vstring& name, T* value) {
		typename ObjectMapImpl::iterator it = mapImpl.find(name);
		if(it != mapImpl.end()) {
			T* obj = it->second;
			mapImpl.erase(it);
			deleteObject(obj);
		}
		addObject(value);
		mapImpl.insert(value_type(name, value));
	}
	T* get(const vstring& name) {
		typename ObjectMapImpl::iterator it = mapImpl.find(name);
		if(it != mapImpl.end()) {
			return it->second;
		}
		return NULL;
	}
	bool remove(const vstring& name) {
		typename ObjectMapImpl::iterator it = mapImpl.find(name);
		if(it != mapImpl.end()) {
			T* obj = it->second;
			mapImpl.erase(it);
			deleteObject(obj);
			return true;
		}
		return false;
	}
	std::vector< std::pair<vstring, T*> > entries() {
		std::vector<std::pair<vstring, T*> > entries;
		for(typename ObjectMapImpl::iterator it = mapImpl.begin(); it != mapImpl.end(); ++it) {
			entries.push_back(std::pair<vstring, T*>(it->first, it->second));
		}
		return entries;
	}
	std::vector<T*> values() {
		std::vector<T*> values;
		for(typename ObjectMapImpl::iterator it = mapImpl.begin(); it != mapImpl.end(); ++it) {
			values.push_back(it->second);
		}
		return values;
	}
	std::vector<vstring> keys() {
		std::vector<vstring> keys;
		for(typename ObjectMapImpl::iterator it = mapImpl.begin(); it != mapImpl.end(); ++it) {
			keys.push_back(it->first);
		}
		return keys;
	}
	iterator begin() {
		return mapImpl.begin();
	}
	iterator end() {
		return mapImpl.end();
	}
	void erase(iterator it) {
		mapImpl.erase(it);
	}
	size_t size() {
		return mapImpl.size();
	}
public:
	static void deleteObject(T* obj) {
		ObjectRef::releaseRef(obj);
	}
	static void addObject(T* obj) {
		ObjectRef::addRef(obj);
	}
private:
	ObjectMapImpl mapImpl;
};

template<class T>
class ObjectMap {
public:
	typedef std::map<vstring, T> ObjectMapImpl;
	typedef typename ObjectMapImpl::iterator iterator;
	typedef typename ObjectMapImpl::const_iterator const_iterator;
	typedef typename ObjectMapImpl::value_type value_type;

	ObjectMap() {
	}
	~ObjectMap() {
	}
	void put(const vstring& name, T value) {
		typename ObjectMapImpl::iterator it = mapImpl.find(name);
		if(it != mapImpl.end()) {
			mapImpl.erase(it);
		}
		mapImpl.insert(value_type(name, value));
	}
	T get(const vstring& name) const {
		typename ObjectMapImpl::const_iterator it = mapImpl.find(name);
		if(it != mapImpl.end()) {
			return it->second;
		}
		return T();
	}
	bool remove(const vstring& name) {
		typename ObjectMapImpl::iterator it = mapImpl.find(name);
		if(it != mapImpl.end()) {
			mapImpl.erase(it);
			return true;
		}
		return false;
	}
	iterator begin() {
		return mapImpl.begin();
	}
	iterator end() {
		return mapImpl.end();
	}
	const_iterator begin() const {
		return mapImpl.begin();
	}
	const_iterator  end() const {
		return mapImpl.end();
	}
	void erase(iterator it) {
		mapImpl.erase(it);
	}
	int size() const {
		return mapImpl.size();
	}
private:
	ObjectMapImpl mapImpl;
};

class Properties : public ObjectMap<vstring> {
};

template<class T>
class ObjectRefPool {
public:
	ObjectRefPool() {
		objectPool.reserve(10);
	}
	~ObjectRefPool() {
		clear();
	}
	T* create() {
		for(typename ObjectPool::iterator it = objectPool.begin(); it != objectPool.end(); ++it) {
			T* obj = *it;
			if(obj->getRefCount() == 1) {
				obj->reset();
				return obj;
			}
		}
		T* obj = createNew();
		obj->addRef();
		objectPool.push_back(obj);
		return obj;
	}
	void clear() {
		for(typename ObjectPool::iterator it = objectPool.begin(); it != objectPool.end(); ++it) {
			T* obj = *it;
			obj->releaseRef();
		}
		objectPool.clear();
	}
	T* createNew() {
		return new T();
	}
private:
	typedef std::vector<T*> ObjectPool;
	ObjectPool objectPool;
};


class VOLANTE_EXPORT SmallStringMap {
public:
	~SmallStringMap() {
		for(size_t i =0; i<objectRefMap.size(); ++i) {
			ObjectRef::releaseRef(objectRefMap.at(i).second);
		}
	}
	void put(const vstring& name, ObjectRef* ref) {
		ObjectRef::addRef(ref);
		for(size_t i =0; i<objectRefMap.size(); ++i) {
			if(objectRefMap.at(i).first == name) {
				ObjectRef::releaseRef(objectRefMap.at(i).second);
				objectRefMap.at(i).second = ref;
				return;
			}
		}
		objectRefMap.push_back(std::pair<vstring, ObjectRef*>(name, ref));
	}
	ObjectRef* get(const vstring& name) {
		for(size_t i =0; i<objectRefMap.size(); ++i) {
			if(objectRefMap.at(i).first == name) {
				return objectRefMap.at(i).second;
			}
		}
		return NULL;
	}
	typedef ArrayList< std::pair<vstring, ObjectRef*> > ObjectRefMap;
	ObjectRefMap objectRefMap;
};



//typedef std::vector<vstring> StringList;
std::ostream& operator << (std::ostream& os, const Object& obj);

template<class T>
class StaticInit {
public:
	StaticInit() {
		T::staticBlock();
	}
};
#define STATIC_INIT(className) \
	StaticInit<className> className ## Static;

extern vstring lineSeparator;
extern vstring fullindent;

vstring indentStr(int val);



VOLANTE_NAMESPACE_END

#include "Collections.h"


#endif //__OBJECTUTILS_H__
