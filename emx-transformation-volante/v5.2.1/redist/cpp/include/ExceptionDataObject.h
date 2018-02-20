#ifndef __EXCEPTIONDATAOBJECT_H__
#define __EXCEPTIONDATAOBJECT_H__


#include "AbstractDataObject.h"
#include "DataObjectSectionImpl.h"
#include "ExceptionObject.h"

VOLANTE_NAMESPACE_BEGIN
class VOLANTE_EXPORT ExceptionDataObject : public AbstractDataObject, public ExceptionObject {
public:
	enum FieldIndices {
		Type_INDEX=0, 
		Message_INDEX=1, 
		ErrorCode_INDEX=2, 
		Severity_INDEX=3, 
		Cascadable_INDEX=4, 
		FFieldName_INDEX=5, 
		FieldID_INDEX=6
	};
public:
	ExceptionDataObject();
	ExceptionDataObject(const ExceptionDataObject& exceptionDataObject);
	ExceptionDataObject& operator = (const ExceptionDataObject& exceptionDataObject);

	virtual Object* clone() const {
		return new ExceptionDataObject(*this);
	}

	const vstring& getType() const {
		AbstractDataObject::ensureNotNull(0);
		return _Type;
	}
	void setType(const vstring& value){
		AbstractDataObject::setNotNull(0);
		this->_Type=value;
	}
	const vstring& getMessage() const {
		AbstractDataObject::ensureNotNull(1);
		return _Message;
	}
	void setMessage(const vstring& value){
		AbstractDataObject::setNotNull(1);
		this->_Message=value;
	}
	const vstring& getErrorCode() const {
		AbstractDataObject::ensureNotNull(2);
		return _ErrorCode;
	}
	void setErrorCode(const vstring& value){
		AbstractDataObject::setNotNull(2);
		this->_ErrorCode=value;
	}
	const vstring& getSeverity() const {
		AbstractDataObject::ensureNotNull(3);
		return _Severity;
	}
	void setSeverity(const vstring& value){
		AbstractDataObject::setNotNull(3);
		this->_Severity=value;
	}
	bool getCascadable() const {
		AbstractDataObject::ensureNotNull(4);
		return _Cascadable;
	}
	void setCascadable(bool value){
		AbstractDataObject::setNotNull(4);
		this->_Cascadable=value;
	}
	const vstring& getFFieldName() const {
		AbstractDataObject::ensureNotNull(5);
		return _FFieldName;
	}
	void setFFieldName(const vstring& value){
		AbstractDataObject::setNotNull(5);
		this->_FFieldName=value;
	}
	const vstring& getFieldID() const {
		AbstractDataObject::ensureNotNull(6);
		return _FieldID;
	}
	void setFieldID(const vstring& value){
		AbstractDataObject::setNotNull(6);
		this->_FieldID=value;
	}



protected:
	Object* getField0(int index) const ;

protected:
	void setField0(int index, const Object* value);

protected: static DataObjectMetaInfo metaInfo;

public:
	vstring toXMLString(int indent)  const {
		return AbstractDataObject::toXMLString(indent);
	}
	vstring toXMLString()  const;
	void setErrorPhase(const vstring& phase) {
		setContextProperty(getERROR_PHASE(), phase);
	}
	void setPhase(const vstring& phase) {
		setErrorPhase(phase);
	}

	vstring getErrorPhase() {
		return  getContextProperty(getERROR_PHASE());
	}
	vstring getPhase() {
		return  getErrorPhase();
	}

	void setErrorType(const vstring& errorType) {
		setContextProperty(getERROR_TYPE(), errorType);
	}

	vstring getErrorType() {
		return  getContextProperty(getERROR_TYPE());
	}
	void fillErrorType(const vstring& value) {
		if(getErrorType().length() == 0) {
			setErrorType(value);
		}
	}
	void fillPhase(const vstring& value) {
		if(getErrorPhase().length() == 0) {
			setErrorPhase(value);
		}
	}
	void setLine(int line) {
		setContextProperty(ExceptionObject::getLINE(), intToString(line));
	}
	void setColumn(int column) {
		setContextProperty(ExceptionObject::getCOLUMN(), intToString(column));
	}

	int getLine() const {
		vstring lineStr = getContextProperty(ExceptionObject::getLINE());
		if(lineStr.size()> 0) {
			return Parsing::parseInt(lineStr);
		}
		return -1;
	}
	int getColumn() const {
		vstring lineStr = getContextProperty(ExceptionObject::getCOLUMN());
		if(lineStr.size()> 0) {
			return Parsing::parseInt(lineStr);
		}
		return -1;
	}

	void setContextProperty(const vstring& name, const vstring& value) {
		if(value.length() == 0) {
			props.remove(name);
		}
		else {
			props.put(name, value);
		}
	}
	vstring  getContextProperty(const vstring& name) const {
		return props.get(name);
	}
	const Properties& getContextProperties() {
		return props;
	}



private:
	vstring _Type;
	vstring _Message;
	vstring _ErrorCode;
	vstring _Severity;
	bool _Cascadable;
	vstring _FFieldName;
	vstring _FieldID;
	Properties props;

	V_DECLARE_NULL_FLAG_FIELD (nullFields, 7);

	vstring getRootXMLTag() const;
	bool instanceOf(const vstring& type) const;
	static vstring THIS_TYPE;
};

VOLANTE_NAMESPACE_END


#endif //__EXCEPTIONDATAOBJECT_H__
