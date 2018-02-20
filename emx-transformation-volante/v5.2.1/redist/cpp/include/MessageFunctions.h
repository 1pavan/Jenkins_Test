#ifndef __MESSAGEFUNCTIONS_H__
#define __MESSAGEFUNCTIONS_H__
VOLANTE_NAMESPACE_BEGIN
typedef VList<std::vector<RawMessage>, RawMessage>	  RawMessageList;
/*
inline operator PropertyMap (const RawMessage& raw) {
	return PropertyMap(raw.get());
}*/
class VOLANTE_EXPORT MessageFunctions {
public:

    ////////////////////////////////////////////////////////////////////////////
    // getProperty

    static int getProperty(const RawMessage& message, const vstring& propertyName, int value) {
        value = message->getIntProperty(propertyName, value);
        return value;
    }

    static dlong getProperty(const RawMessage& message, const vstring& propertyName, dlong value) {
        value = message->getLongProperty(propertyName, value);
        return value;
    }

    static double getProperty(const RawMessage& message, const vstring& propertyName, double value) {
        value = message->getDoubleProperty(propertyName, value);
        return value;
    }

    static float getProperty(const RawMessage& message, const vstring& propertyName, float value) {
        value = (float) message->getDoubleProperty(propertyName, value);
        return value;
    }

    static bool getProperty(const RawMessage& message, const vstring& propertyName, bool value) {
        value = message->getBooleanProperty(propertyName, value);
        return value;
    }

    static DateTime getProperty(const RawMessage& message, const vstring& propertyName, const DateTime& value) {
        DateTime toRet = message->getDateProperty(propertyName, value);
        return toRet;
    }

    static vstring getProperty(const RawMessage& message, const vstring& propertyName, const vstring& value) {
        vstring toRet = message->getStringProperty(propertyName, value);
        return toRet;
    }


    static vstring getProperty(const RawMessage& message, const vstring& propertyName) {
        return message->getStringProperty(propertyName, "");
    }

    static PropertyMap getProperties(const RawMessage& message, const vstring& propertyname) {
        return message->getProperties(propertyname);
    }

    ////////////////////////////////////////////////////////////////////////////
    // setProperty
    static void setProperty(const RawMessage& message, const vstring& propertyname, const vstring& propertyValue) {
        message->setStringProperty(propertyname, propertyValue);
    }

    static void setProperty(const RawMessage& message, const vstring& propertyname, int propertyValue) {
        message->setIntProperty(propertyname, propertyValue);
    }

    static void setProperty(const RawMessage& message, const vstring& propertyname, dlong propertyValue) {
        message->setLongProperty(propertyname, propertyValue);
    }

    static void setProperty(const RawMessage& message, const vstring& propertyname, double propertyValue) {
        message->setDoubleProperty(propertyname, propertyValue);
    }

    static void setProperty(const RawMessage& message, const vstring& propertyname, float propertyValue) {
        message->setFloatProperty(propertyname, propertyValue);
    }

    static void setProperty(const RawMessage& message, const vstring& propertyname, bool propertyValue) {
        message->setBooleanProperty(propertyname, propertyValue);
    }

    static void setProperty(const RawMessage& message, const vstring& propertyname, DateTime propertyValue) {
        message->setDateProperty(propertyname, propertyValue);
    }


    // Other functions
    static void removeProperty(const RawMessage& message, const vstring& propertyname) {
        message->removeProperty(propertyname);
    }

    static void clearProperties(const RawMessage& message) {
        message->clearProperties();
    }

    static void putProperties(const RawMessage& dest, const RawMessage& sec) {
        dest->putProperties(sec.get());
    }
    static void putProperties(const RawMessage& dest, const PropertyMap& sec) {
        dest->putProperties(sec.get());
    }

    static int getPropertyCount(const RawMessage& message) {
        return message->getPropertyCount();
    }

    static bool hasProperty(const RawMessage& message, const vstring& propertyname) {
        return message->hasProperty(propertyname);
    }

    static StringList getPropertyNames(const RawMessage& message) {
        return message->getPropertyNames();
    }
		
    static StringList getPropertyNames(const RawMessage& message, const vstring& wildCard);

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    // getProperty - using propertyMap

    static int getProperty(const PropertyMap& message, const vstring& propertyName, int value) {
        value = message->getIntProperty(propertyName, value);
        return value;
    }

    static dlong getProperty(const PropertyMap& message, const vstring& propertyName, dlong value) {
        value = message->getLongProperty(propertyName, value);
        return value;
    }

    static double getProperty(const PropertyMap& message, const vstring& propertyName, double value) {
        value = message->getDoubleProperty(propertyName, value);
        return value;
    }

    static float getProperty(const PropertyMap& message, const vstring& propertyName, float value) {
        value = (float) message->getDoubleProperty(propertyName, value);
        return value;
    }

    static bool getProperty(const PropertyMap& message, const vstring& propertyName, bool value) {
        value = message->getBooleanProperty(propertyName, value);
        return value;
    }

    static DateTime getProperty(const PropertyMap& message, const vstring& propertyName, const DateTime& value) {
        DateTime toRet = message->getDateProperty(propertyName, value);
        return toRet;
    }

    static vstring getProperty(const PropertyMap& message, const vstring& propertyName, const vstring& value) {
        vstring toRet = message->getStringProperty(propertyName, value);
        return toRet;
    }


    static vstring getProperty(const PropertyMap& message, const vstring& propertyName) {
        return message->getStringProperty(propertyName, "");
    }

    static PropertyMap getProperties(const PropertyMap& message, const vstring& propertyname) {
        return message->getProperties(propertyname);
    }

    ////////////////////////////////////////////////////////////////////////////
    // setProperty
    static void setProperty(const PropertyMap& message, const vstring& propertyname, const vstring& propertyValue) {
        message->setStringProperty(propertyname, propertyValue);
    }

    static void setProperty(const PropertyMap& message, const vstring& propertyname, int propertyValue) {
        message->setIntProperty(propertyname, propertyValue);
    }

    static void setProperty(const PropertyMap& message, const vstring& propertyname, dlong propertyValue) {
        message->setLongProperty(propertyname, propertyValue);
    }

    static void setProperty(const PropertyMap& message, const vstring& propertyname, double propertyValue) {
        message->setDoubleProperty(propertyname, propertyValue);
    }

    static void setProperty(const PropertyMap& message, const vstring& propertyname, float propertyValue) {
        message->setFloatProperty(propertyname, propertyValue);
    }

    static void setProperty(const PropertyMap& message, const vstring& propertyname, bool propertyValue) {
        message->setBooleanProperty(propertyname, propertyValue);
    }

    static void setProperty(const PropertyMap& message, const vstring& propertyname, DateTime propertyValue) {
        message->setDateProperty(propertyname, propertyValue);
    }


    // Other functions
    static void removeProperty(const PropertyMap& message, const vstring& propertyname) {
        message->removeProperty(propertyname);
    }

    static void clearProperties(const PropertyMap& message) {
        message->clearProperties();
    }

    static void putProperties(const PropertyMap& dest, const PropertyMap& sec) {
        dest->putProperties(sec.get());
    }

    int getPropertyCount(const PropertyMap& message) {
        return message->getPropertyCount();
    }

    static bool hasProperty(const PropertyMap& message, const vstring& propertyname) {
        return message->hasProperty(propertyname);
    }

    static StringList getPropertyNames(const PropertyMap& message) {
        return message->getPropertyNames();
    }
		
    static StringList getPropertyNames(const PropertyMap& message, const vstring& wildCard);

    //////////////////////////////////////////////////////////////////////////////////////////////////


    static vstring getName(const RawMessage& message) {
        return message->getName();
    }
    static void setName(const RawMessage& message, const vstring& name) {
        message->setName(name);
    }
    static StringList getAttachmentNames(const RawMessage& message) {
        return message->getAttachmentNames();
    }

    static RawMessageList getAttachments(const RawMessage& message) {
        //return message->getAttachments();
				return RawMessageList();
    }

    static RawMessage getAttachment(const RawMessage& message, const vstring& name) {
        RawMessage value = message->getAttachment(name);
        return value;
    }

    static bool hasAttachment(const RawMessage& message, const vstring& name) {
        return message->hasAttachment(name);
    }

    static void setAttachment(const RawMessage& message, const vstring& name, const RawMessage& attachment) {
        message->addAttachment(name, attachment);
    }

    static RawMessage toRawMessage(const Binary& bytes);

    static RawMessage toRawMessage(const vstring& value);

    static vstring toText(const RawMessage& message)  {
        return message->getAsString();
    }

    static Binary toBinary(const RawMessage& message)  {
        return message->getAsBinary();
    }
};

VOLANTE_NAMESPACE_END
#endif //__MESSAGEFUNCTIONS_H__



