#ifndef __OBJECTFACTORY_H__
#define __OBJECTFACTORY_H__
VOLANTE_NAMESPACE_BEGIN
/**
* Internal class used for dynamic instantiation of classes.
*/
class VOLANTE_EXPORT ObjectFactory : public Object {
public:
	//virtual bool isFactoryFor(const std::type_info& id) const  = 0;
	virtual Object* create() = 0;

};

/**
* Internal implementation class used for dynamic instantiation of classes.
*/
template<class T>
class GenericObjectFactory : public ObjectFactory {
public:
	/*
	bool isFactoryFor(const std::type_info& id) const {
	const std::type_info& tid = typeid(T);
	int cmp = (tid == id);
	return cmp != 0;
	}    */
	Object* create() {
		return new T();
	}
	CLONE_IMPL(GenericObjectFactory)
};
VOLANTE_NAMESPACE_END

#endif //__OBJECTFACTORY_H__
