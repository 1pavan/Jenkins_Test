#ifndef __PROPERTYMAP_H__
#define __PROPERTYMAP_H__

#include "Object.h"

VOLANTE_NAMESPACE_BEGIN
class VOLANTE_EXPORT IPropertyMap : public ObjectRef {
public:
		typedef SmartPtr<IPropertyMap> PropertyMap;
    class VOLANTE_EXPORT PropertyNameFilter {
		public:
        virtual bool match(const vstring& name) =0;
    };

    class VOLANTE_EXPORT Entry  {
		public:
        virtual vstring getName() =0;
        virtual Object* getValue() =0;
    };
		class VOLANTE_EXPORT EntryImpl : public Entry {
		public:
			EntryImpl(const vstring& name, Object* value) {
            this->name = name;
						//ObjectRef::addRef(value);
						this->value = value;
						hashCodeValue =0;
        }
				~EntryImpl() {
					//ObjectRef::releaseRef(value);
				}
        vstring getName() {
            return name;
        }

        vstring getKey() {
            return name;
        }

        Object* getValue() {
            return value;
        }
			

        /*public Object setValue(Object value) {
            Object old = this.value;
            this.value = value;
            return old;
        }*/


        vstring toString() {
            return name + "=" + value->toString();
        }

        int getKeyHashCode() {
            if (hashCodeValue == 0) {
                hashCodeValue = hashCode(name);
            }
            return hashCodeValue;
        }
				int hashCode(const vstring& name) {
						return 0;
				}
        int hashCodeValue;
        vstring name;
        Object* value;
    };

    /**
     * Gets a property of the message implementation
     *
     * @param name the key on which to lookup the property value
     * @return the property value or null if the property does not exist
     */
    virtual Object* getProperty(const vstring& name) = 0 ;

    /**
     * Set a property on the message
     *
     * @param name  the key on which to associate the value
     * @param value the property value
     */
    virtual void setProperty(const vstring& name, Object* value) = 0;

    /**
     * Removes a property on this message
     *
     * @param name the property key to remove
     * @return the removed property value or null if the property did not exist
     */
    virtual void removeProperty(const vstring& name) = 0;

    /**
     * Returns true if property by specified name exists
     *
     * @param name name of the property
     * @return true if property by specified name exists
     */
    virtual bool hasProperty(const vstring& name) = 0;

    /**
     * Gets a property from the message
     *
     * @param name         the name or key of the property
     * @param defaultValue a default value if the property doesn't exist in the
     *                     message
     * @return the property value or the defaultValue if the property does not
     *         exist
     */
    virtual Object* getProperty(const vstring& name, Object* defaultValue) = 0;

    /**
     * Gets a long property from the message
     *
     * @param name         the name or key of the property
     * @param defaultValue a default value if the property doesn't exist in the
     *                     message
     * @return the property value or the defaultValue if the property does not
     *         exist
     */
    virtual dlong getLongProperty(const vstring& name, dlong defaultValue) = 0 ;

    /**
     * Sets a long property on the message
     *
     * @param name  the property name or key
     * @param value the property value
     */
    virtual void setLongProperty(const vstring& name, dlong value) =0;


    /**
     * Gets a bool property from the message
     *
     * @param name         the name or key of the property
     * @param defaultValue a default value if the property doesn't exist in the
     *                     message
     * @return the property value or the defaultValue if the property does not
     *         exist
     */
    virtual bool getBooleanProperty(const vstring& name, bool defaultValue) = 0;

    /**
     * Sets a bool property on the message
     *
     * @param name  the property name or key
     * @param value the property value
     */
    virtual void setBooleanProperty(const vstring& name, bool value) = 0;

    /**
     * Gets an integer property from the message
     *
     * @param name         the name or key of the property
     * @param defaultValue a default value if the property doesn't exist in the
     *                     message
     * @return the property value or the defaultValue if the property does not
     *         exist
     */
    virtual int getIntProperty(const vstring& name, int defaultValue) = 0;

    /**
     * Sets a integerproperty on the message
     *
     * @param name  the property name or key
     * @param value the property value
     */
    virtual void setIntProperty(const vstring& name, int value) =0;


    /**
     * Gets a double property from the message
     *
     * @param name         the name or key of the property
     * @param defaultValue a default value if the property doesn't exist in the
     *                     message
     * @return the property value or the defaultValue if the property does not
     *         exist
     */
    virtual double getDoubleProperty(const vstring& name, double defaultValue) = 0;

    /**
     * Sets a double property on the message
     *
     * @param name  the property name or key
     * @param value the property value
     */
    virtual void setDoubleProperty(const vstring& name, double value)=0;

    /**
     * Gets a double property from the message
     *
     * @param name         the name or key of the property
     * @param defaultValue a default value if the property doesn't exist in the
     *                     message
     * @return the property value or the defaultValue if the property does not
     *         exist
     */
    virtual float getFloatProperty(const vstring& name, float defaultValue) = 0;

    /**
     * Sets a double property on the message
     *
     * @param name  the property name or key
     * @param value the property value
     */
    virtual void setFloatProperty(const vstring& name, float value)=0;

    /**
     * Gets a String property from the message
     *
     * @param name         the name or key of the property
     * @param defaultValue a default value if the property doesn't exist in the
     *                     message
     * @return the property value or the defaultValue if the property does not
     *         exist
     */
    virtual vstring getStringProperty(const vstring& name, const vstring& defaultValue) = 0;

    /**
     * Sets a String property on the message
     *
     * @param name  the property name or key
     * @param value the property value
     */
    virtual void setStringProperty(const vstring& name, const vstring& value) =0;

    virtual DateTime getDateProperty(const vstring& name,  const DateTime& defaultValue) =0;

    virtual void setDateProperty(const vstring& name, const DateTime& value) =0;

    /**
     * Returns a list of all proeprty names
     *
     * @return all property keys on this message
     */
    virtual StringList getPropertyNames() =0;

    virtual StringList getPropertyNames(PropertyNameFilter* filter) =0;

    virtual int getPropertyCount() =0;


    virtual void clearProperties() =0;

    virtual PropertyMap getProperties(const vstring& prefix) =0;
    virtual void putProperties(IPropertyMap* properties) =0;

};

/**
 * Package level enhanced interface
 */
 class VOLANTE_EXPORT IPropertyMap2 : public IPropertyMap {
 public:
		typedef std::vector<IPropertyMap::EntryImpl> PropertyEntryList;
    virtual PropertyEntryList getEntries(const vstring& prefix) =0;

    virtual void clear(const vstring& prefix) =0;

    virtual StringList getNames(const vstring& prefix) =0;
};
typedef SmartPtr<IPropertyMap> PropertyMap;
typedef SmartPtr<IPropertyMap2> PropertyMap2;



class VOLANTE_EXPORT PropertyMapImpl : public IPropertyMap2 {
public:
	PropertyMapImpl();
	~PropertyMapImpl();
	typedef std::vector<IPropertyMap::EntryImpl> PropertyEntryList;
	PropertyEntryList propertyList;
	Object* getProperty(const vstring& name);
	void setProperty(const vstring& name, Object* value);
	void removeProperty(const vstring& name);
	bool hasProperty(const vstring& name);
	Object* getProperty(const vstring& name, Object* defaultValue);
	dlong getLongProperty(const vstring& name, dlong defaultValue) ;
	void setLongProperty(const vstring& name, dlong value) ;
	bool getBooleanProperty(const vstring& name, bool defaultValue) ;
	void setBooleanProperty(const vstring& name, bool value) ;
	int getIntProperty(const vstring& name, int defaultValue) ;
	void setIntProperty(const vstring& name, int value) ;
	double getDoubleProperty(const vstring& name, double defaultValue) ;
	void setDoubleProperty(const vstring& name, double value) ;
	float getFloatProperty(const vstring& name, float defaultValue) ;
	void setFloatProperty(const vstring& name, float value) ;
	vstring getStringProperty(const vstring& name, const vstring& defaultValue) ;
	void setStringProperty(const vstring& name, const vstring& value) ;
	DateTime getDateProperty(const vstring& name, const DateTime& defaultValue) ;
	void setDateProperty(const vstring& name, const DateTime& value) ;
	PropertyMap getProperties(const vstring& prefix) ;
	void putProperties(IPropertyMap* props) ;
	void addEntry(EntryImpl entry) ;
	EntryImpl getEntry(int index) ;
	//EntryImpl getEntry(const vstring& name) ;
	int getEntryIndex(const vstring& name) ;
	int getPropertyCount() ;
	void clearProperties() ;
	void clear(const vstring& prefix) ;
	int size() ;
	PropertyEntryList getEntries(const vstring& prefix) ;
	StringList getPropertyNames() ;
	StringList getNames(const vstring& prefix) ;
	StringList getPropertyNames(PropertyNameFilter* filter) ;
	static int toValue(Object* obj, int def) ;
	static dlong toValue(Object* obj, dlong def) ;
	static double toValue(Object* obj, double def) ;
	static float toValue(Object* obj, float def) ;
	static DateTime toValue(Object* obj, const DateTime& def) ;
	static bool toValue(Object* obj, bool def) ;
	static int hashCode(const vstring& str) ;

};

#define PROPERTY_MAP_DELETE \
private:  \
    PropertyMap _properties; \
public: \
	  void setProperty(const vstring& key, Object* value) { \
        getProperties()->setProperty(key, value); \
    } \
    PropertyMap getProperties(const vstring& name) { \
        return getProperties()->getProperties(name); \
    } \
 \
    void putProperties(IPropertyMap* properties) { \
        getProperties()->putProperties(properties); \
    } \
 \
    Object* getProperty(const vstring& name, Object* defaultValue) { \
        return getProperties()->getProperty(name, defaultValue); \
    } \
 \
    int getIntProperty(const vstring& name, int defaultValue) { \
        return getProperties()->getIntProperty(name, defaultValue); \
    } \
 \
    dlong getLongProperty(const vstring& name, dlong defaultValue) { \
        return getProperties()->getLongProperty(name, defaultValue); \
    } \
 \
    double getDoubleProperty(const vstring& name, double defaultValue) { \
        return getProperties()->getDoubleProperty(name, defaultValue); \
    } \
    float getFloatProperty(const vstring& name, float defaultValue) { \
        return getProperties()->getFloatProperty(name, defaultValue); \
    } \
 \
    bool getBooleanProperty(const vstring& name, bool defaultValue) { \
        return getProperties()->getBooleanProperty(name, defaultValue); \
    } \
 \
    vstring getStringProperty(const vstring& name, const vstring& defaultValue) { \
        return getProperties()->getStringProperty(name, defaultValue); \
    } \
 \
    DateTime getDateProperty(const vstring& name, const DateTime& defaultValue) { \
        return getProperties()->getDateProperty(name, defaultValue); \
    } \
 \
    void setBooleanProperty(const vstring& name, bool value) { \
        getProperties()->setBooleanProperty(name, value); \
    } \
 \
    void setIntProperty(const vstring& name, int value) { \
        getProperties()->setIntProperty(name, value); \
    } \
 \
    void setLongProperty(const vstring& name, dlong value) { \
        getProperties()->setLongProperty(name, value); \
    } \
 \
    void setDoubleProperty(const vstring& name, double value) { \
        getProperties()->setDoubleProperty(name, value); \
    } \
    void setFloatProperty(const vstring& name, float value) { \
        getProperties()->setFloatProperty(name, value); \
    } \
 \
   void setStringProperty(const vstring& name, const vstring& value) { \
        getProperties()->setStringProperty(name, value); \
    } \
 \
    void setDateProperty(const vstring& name, const DateTime& value) { \
        getProperties()->setDateProperty(name, value); \
    } \
    void clearProperties() { \
        getProperties()->clearProperties(); \
     } \
 \
    void removeProperty(const vstring& key) { \
        getProperties()->removeProperty(key); \
    } \
 \
    bool hasProperty(const vstring& key) { \
        return getProperties()->hasProperty(key); \
    } \
 \
    Object* getProperty(const vstring& key) { \
        return getProperties()->getProperty(key); \
    } \
 \
    StringList getPropertyNames() { \
        return getProperties()->getPropertyNames(); \
    } \
 \
		StringList getPropertyNames(PropertyNameFilter* filter) {\
        return getProperties()->getPropertyNames(filter); \
		} \
    int getPropertyCount() { \
        return getProperties()->getPropertyCount(); \
    } \
 \
    PropertyMap getProperties() { \
        if (_properties.isNull()) { \
            _properties = new PropertyMapImpl(); \
        } \
        return _properties; \
    } 


VOLANTE_NAMESPACE_END

#endif //__PROPERTYMAP_H__
