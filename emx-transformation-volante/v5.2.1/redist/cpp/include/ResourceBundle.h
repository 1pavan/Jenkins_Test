#ifndef __RESOURCEBUNDLE_H__
#define __RESOURCEBUNDLE_H__
#include "Object.h"

VOLANTE_NAMESPACE_BEGIN


class VOLANTE_EXPORT ResourceBundle {
public:
	virtual ~ResourceBundle();
	vstring getProperty(const char* name) const;
	virtual vstring getProperty(const vstring& name) const = 0;
};

class VOLANTE_EXPORT PropertyResourceBundle : public ResourceBundle {
public:
	void addProperty(const char* name, const char* value);
	virtual vstring getProperty(const vstring& name) const;
private:
	typedef std::map<vstring, vstring> PropertyMap;
	PropertyMap  propertyMap;
};



class VOLANTE_EXPORT Resources {
public:
	void addResourceBundle(const vstring& name, const ResourceBundle& bundle);
	const ResourceBundle* getBundle(const vstring& name) const ;

	static Resources& getDefaultResources();
	static vstring getProperty(const char* bundleName, const char* name);
	static vstring getProperty(const char* name);
	static vstring getProperty(const vstring& name);
private:
	typedef std::map<vstring, const ResourceBundle*> BundleMap;
	BundleMap  bundleMap;
};



class ResourceRegistrar  {
public:
	ResourceRegistrar(const vstring& name, const ResourceBundle& bundle) {
		Resources::getDefaultResources().addResourceBundle(name, bundle);	
	}
};

#define RESOURCE_BUNDLE_BEGIN(name)  static PropertyResourceBundle& createBundle ## name () { static PropertyResourceBundle bundle;
	
#define RESOURCE_PROPERTY(name, value) bundle.addProperty(name, value);

#define RESOURCE_BUNDLE_END(name)	return bundle; } \
	static ResourceRegistrar registrar(#name, createBundle ## name ()); \
	void resourceLoader ## name () {}
	
#define USING_RESOURCE_BUNDLE(name)	 \
	extern void resourceLoader ## name(); \
	static VOLANTE_NAMESPACE::Registrar reg ## name (resourceLoader ## name);



VOLANTE_NAMESPACE_END

#endif //__RESOURCEBUNDLE_H__
