#ifndef __USERCLASSMANAGER_H__
#define __USERCLASSMANAGER_H__
#include "Object.h"
VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT UserClassManager {
public:
	static void registerClass(const vstring& className, ObjectFactory* factory);
	static Object* createInstance(const vstring& className);
	//typedef std::map<vstring, ObjectFactory*> ClassMap;
private:
	typedef ObjectPtrMap<ObjectFactory> ClassMap; 
	static ClassMap& getClassMap();
};

class VOLANTE_EXPORT UserClass {
public:
	UserClass(const vstring& className, ObjectFactory* factory) {
		UserClassManager::registerClass(className, factory);
	}
};

typedef void (*RegisterFunction )() ;
class VOLANTE_EXPORT Registrar  {
public:
	Registrar(RegisterFunction fn) {
		fn();
	}
};

#define DECLARE_CARTRIDGE(cartName) \
	void PLATFORM_EXPORT registerCartridge ## cartName() { \
	static cartName ## Cartridge cart; \
	} 

#define CARTRDIGE_BEGIN
#define CARTRDIGE_END

#define USING_CARTRIDGE(cartName) \
	extern void registerCartridge ## cartName(); \
static VOLANTE_NAMESPACE::Registrar reg ## cartName (registerCartridge ## cartName);



#define REGISTER_CLASS(className) \
	void PLATFORM_EXPORT registerClass ## className() { \
		static VOLANTE_NAMESPACE::UserClass userClass(#className, new VOLANTE_NAMESPACE::GenericObjectFactory<className>); \
	}

#define REGISTER_CLASS_NS(className, nspace) \
	void PLATFORM_EXPORT registerClass ## className() { \
	static VOLANTE_NAMESPACE::UserClass userClass(#className, new VOLANTE_NAMESPACE::GenericObjectFactory<nspace::className>); \
	}


#define USING_CLASS(className) \
	extern void registerClass ## className(); \
static VOLANTE_NAMESPACE::Registrar reg ## className (registerClass ## className); 


#define USING_CLASS2(className, varName) \
	extern void registerClass ## className(); \
	static VOLANTE_NAMESPACE::Registrar reg ## className ## varName (registerClass ## className); 


#define INVOKE_REGISTER_CLASS(className) \
	registerClass ## className();	

#define DECL_REGISTER_CLASS(className) \
	extern void registerClass ## className();



VOLANTE_NAMESPACE_END
  
#endif //__USERCLASSMANAGER_H__

