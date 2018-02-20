#ifndef __DATAOBJECTMETAINFO_H__
#define __DATAOBJECTMETAINFO_H__
#include "DesignerTypes.h"
#include "FieldMetaInfo.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT DataObjectMetaInfo : public Object {
public:
	typedef std::vector<int> IntSynthList;
public:
	DataObjectMetaInfo(const vstring& name, const char* fieldNames[], const char* types[], int length);
	DataObjectMetaInfo(const vstring& name, const char* fieldNames[], const char* types[], int length, IntSynthList& synthesized);
	DataObjectMetaInfo(const vstring& name, DataObjectMetaInfo* baseMetaInfo, const char* fieldNames[], const char* types[], int length, const IntSynthList& synthesized);
	DataObjectMetaInfo(const vstring& name, FieldMetaInfo* fieldInfos[], int length);
	~DataObjectMetaInfo();
	const vstring& getName() const {
		return name;
	}
	int getFieldCount() {
		return (int)fields.size();
	}
	bool isSynthesized(int index) const;

	const vstring& getFieldName(int index)  const;
	const vstring& getFieldType(int index) const;
	const vstring& getMangledName(int index) const;
	const vstring& getMangledName(const vstring& fieldName) const;
	int getFieldIndex(const vstring& fieldName) const;
	int getFieldIndexIfExists(const vstring&  fieldName) const;

	bool isSection(int index) const ;
    void setParentSection(SectionMetaInfo* parentSection) {
        this->parentSection = parentSection;
    }
	FieldMetaInfo* getFieldMetaInfo(int index) const;
	FieldMetaInfo* getFieldMetaInfo(const vstring&  fieldName) const;

private:
	void addFields(const char* fieldNames[],const char* types[], int length, const IntSynthList& synthesized);
	void addFields(FieldMetaInfo* fieldInfos[], int length);

	void addParentFields(DataObjectMetaInfo* baseMetaInfo);
	void createFieldMap();

	typedef std::map<vstring, FieldMetaInfo*> FieldMapType;
	typedef std::vector<FieldMetaInfo*> FieldListType;
    vstring name;
    FieldListType fields;
    FieldMapType fldMap;
    FieldMapType mangledFldMap;
    SectionMetaInfo* parentSection;

};

VOLANTE_NAMESPACE_END

#endif //__DATAOBJECTMETAINFO_H__

