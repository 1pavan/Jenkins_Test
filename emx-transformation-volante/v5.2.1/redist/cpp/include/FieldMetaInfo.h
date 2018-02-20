#ifndef __FIELDMETAINFO_H__
#define __FIELDMETAINFO_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FieldMetaInfo  : public Object {
public:
	FieldMetaInfo(const vstring& fieldName, const vstring& designerType, bool optional) : fieldName(fieldName), designerType(designerType) {
		this->index = -1;
		this->optional = optional;
		this->synthesized = false;
	}
	FieldMetaInfo(const vstring& fieldName, const vstring& designerType, bool optional, bool synthesized) : fieldName(fieldName), designerType(designerType){
		this->index = -1;
		this->optional = optional;
		this->synthesized = synthesized;
	}
	FieldMetaInfo(const FieldMetaInfo& copyFrom) : fieldName(copyFrom.fieldName), designerType(copyFrom.designerType){
		this->index = copyFrom.index;
		this->optional = copyFrom.optional;
		this->synthesized = copyFrom.synthesized;
	}
	virtual ~FieldMetaInfo() {
	}
	virtual Object* clone() const {
		return new FieldMetaInfo(*this);
	}

	const vstring& getName() {
		return fieldName;
	}

	int getIndex() {
		return index;
	}
	void setIndex(int index);

	const vstring& getType() {
		return designerType;
	}

	bool isOptional() {
		return optional;
	}

	bool isSynthesized() {
		return synthesized;
	}

	const vstring& getMangledName() {
		if(mangledName.length() == 0) {
			mangledName = computeMangledName(fieldName);
		}
		return mangledName;
	}

	static vstring computeMangledName(const vstring& fldName);
private:
	vstring fieldName;
	vstring designerType;
	bool optional;
	bool synthesized;
	int index;
	vstring mangledName;
};
class DataObjectMetaInfo;
class VOLANTE_EXPORT SectionMetaInfo : public FieldMetaInfo {
public:
	SectionMetaInfo(DataObjectMetaInfo* dataObjectMetaInfo, const vstring& fieldName) 		: FieldMetaInfo(fieldName, DESIGNER_SECTION_TYPE, minOccurs > 0, false) {
		init(dataObjectMetaInfo, 0, -1);
	}
	SectionMetaInfo(const SectionMetaInfo& copyFrom) : FieldMetaInfo(copyFrom) {
		init(copyFrom.dataObjectMetaInfo, copyFrom.minOccurs, copyFrom.maxOccurs); 
	}

	SectionMetaInfo(DataObjectMetaInfo* dataObjectMetaInfo, const vstring& fieldName, int minOccurs, int maxOccurs) 
		: FieldMetaInfo(fieldName, DESIGNER_SECTION_TYPE, minOccurs > 0, false) {
			init(dataObjectMetaInfo, minOccurs, maxOccurs);
		}
	SectionMetaInfo(DataObjectMetaInfo* dataObjectMetaInfo, const vstring& fieldName,  const vstring& designerType, int minOccurs, int maxOccurs, bool synthesized) 
		: FieldMetaInfo(fieldName, designerType, minOccurs > 0, synthesized) {
			init(dataObjectMetaInfo, minOccurs, maxOccurs);
		}
		SectionMetaInfo(DataObjectMetaInfo* dataObjectMetaInfo, const vstring& fieldName, int minOccurs, int maxOccurs, bool synthesized) 
			: FieldMetaInfo(fieldName, DESIGNER_SECTION_TYPE, minOccurs > 0, synthesized) {
				init(dataObjectMetaInfo, minOccurs, maxOccurs);
			}
			void init(DataObjectMetaInfo* dataObjectMetaInfo, int minOccurs, int maxOccurs);
			virtual Object* clone() const {
				return new SectionMetaInfo(*this);
			}
			int getMinOccurs() {
				return minOccurs;
			}
			int getMaxOccurs() {
				return maxOccurs;
			}
			DataObjectMetaInfo* getDataObjectMetaInfo() {
				return dataObjectMetaInfo;
			}
private:
	int minOccurs;
	int maxOccurs;
	DataObjectMetaInfo* dataObjectMetaInfo;
};

VOLANTE_NAMESPACE_END

#endif //__FIELDMETAINFO_H__
