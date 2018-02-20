#ifndef __UTILFUNCTIONS_H__
#define __UTILFUNCTIONS_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT UtilFunctions {
public:
	static void info(const vstring& str);
	static void error(const vstring& str);
	static void debug(const vstring& str);
	static DataObject* makeCopy(const DataObject* obj) {
		DataObject* cloned = dynamic_cast<DataObject*>(obj->clone());
		cloned->setParentSection(NULL);
		return cloned;
	}
	static vstring getContextProperty(TransformContext& cxt, const vstring& propertyName);
	static vstring getContextProperty(TransformContext& cxt, const vstring& propertyName, const vstring& defaultValue);
	static void setContextProperty(TransformContext& cxt, const vstring& propertyname, const vstring& propertyValue);

};

VOLANTE_NAMESPACE_END

#endif //__UTILFUNCTIONS_H__

