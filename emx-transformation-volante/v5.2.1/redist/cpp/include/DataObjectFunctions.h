#ifndef __DATAOBJECTFUNCTIONS_H__
#define __DATAOBJECTFUNCTIONS_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT DataObjectFunctions : public SectionHelper {
public:
public:

	static bool objIsNull(DataObject* obj, const vstring&  fieldName);
	static bool objIsNull(DataObject* obj, int fieldIndex);
	static bool objIsNotNull(DataObject* obj, const vstring&  fieldName);
	static bool objIsNotNull(DataObject* obj, int fieldIndex);
	static void objsetNull(DataObject* obj, const vstring&  fieldName) {
		obj->setNull(fieldName);
	}
	static void objsetNull(DataObject* obj, int fieldIndex) {
		obj->setNull(fieldIndex);
	}

	static int objGetInt(DataObject*  obj, const vstring& fieldName);
	static int objGetInt(DataObject*  obj, int fieldIndex);
	static float objGetFloat(DataObject*  obj, const vstring& fieldName);
	static float objGetFloat(DataObject*  obj, int fieldIndex);
	static double objGetDouble(DataObject*  obj, const vstring& fieldName);
	static double objGetDouble(DataObject*  obj, int fieldIndex);
	static vstring objGetString(DataObject*  obj, const vstring& fieldName);
	static vstring objGetString(DataObject*  obj, int fieldIndex);
	static DataObjectSection* objGetSection(DataObject*  obj, const vstring& fieldName);
	static DataObjectSection* objGetSection(DataObject*  obj, int fieldIndex);
	static DataObject* objGetObject(DataObject*  obj, const vstring& fieldName);
	static DataObject* objGetObject(DataObject*  obj, int fieldIndex);
	static DateTime objGetDate(DataObject*  obj, const vstring& fieldName);
	static DateTime objGetDate(DataObject*  obj, int fieldIndex);
	static dlong objGetLong(DataObject*  obj, const vstring& fieldName);
	static dlong objGetLong(DataObject*  obj, int fieldIndex);
	static Binary objGetBinary(DataObject*  obj, const vstring& fieldName);
	static Binary objGetBinary(DataObject*  obj, int fieldIndex);
	static BigInteger objGetBigInteger(DataObject*  obj, const vstring& fieldName);
	static BigInteger objGetBigInteger(DataObject*  obj, int fieldIndex);
	static BigDecimal objGetBigDecimal(DataObject*  obj, const vstring& fieldName);
	static BigDecimal objGetBigDecimal(DataObject*  obj, int fieldIndex);
	static bool objGetBoolean(DataObject*  obj, const vstring& fieldName);
	static bool objGetBoolean(DataObject*  obj, int fieldIndex);
	static char objGetCharacter(DataObject*  obj, const vstring& fieldName);
	static char objGetCharacter(DataObject*  obj, int fieldIndex);

	static void objSetInt(DataObject* obj, const vstring& fieldName, int value) ;
	static void objSetFloat(DataObject* obj, const vstring& fieldName, float value);
	static void objSetDouble(DataObject* obj, const vstring& fieldName, double value) ;
	static void objSetLong(DataObject* obj, const vstring& fieldName, dlong value);
	static void objSetBoolean(DataObject* obj, const vstring& fieldName, bool value);
	static void objSetDate(DataObject* obj, const vstring& fieldName, const DateTime& value);
	static void objSetString(DataObject* obj, const vstring& fieldName, const vstring& value);
	static void objSetBinary(DataObject* obj, const vstring& fieldName, const Binary& value) ;
	static void objSetBigInteger(DataObject* obj, const vstring& fieldName, const BigInteger& value);
	static void objSetBigDecimal(DataObject* obj, const vstring& fieldName, const BigDecimal& value) ;
	static void objSetCharacter(DataObject* obj, const vstring& fieldName, char value) ;

	static void objSetInt(DataObject* obj, int fieldIndex, int value) ;
	static void objSetFloat(DataObject* obj, int fieldIndex, float value);
	static void objSetDouble(DataObject* obj, int fieldIndex, double value) ;
	static void objSetLong(DataObject* obj, int fieldIndex, dlong value);
	static void objSetBoolean(DataObject* obj, int fieldIndex, bool value);
	static void objSetDate(DataObject* obj, int fieldIndex, const DateTime& value);
	static void objSetString(DataObject* obj, int fieldIndex, const vstring& value);
	static void objSetBinary(DataObject* obj, int fieldIndex, const Binary& value) ;
	static void objSetBigInteger(DataObject* obj, int fieldIndex, const BigInteger& value);
	static void objSetBigDecimal(DataObject* obj, int fieldIndex, const BigDecimal& value) ;
	static void objSetCharacter(DataObject* obj, int fieldIndex, char value) ;

	static bool equal(DataObject* obj1,  DataObject* obj2) {
		return obj1 == obj2;
	}
	static bool notEqual(DataObject* obj1,  DataObject* obj2) {
		return obj1 != obj2;
	}
	static vstring toText(DataObject* sec);
	static vstring toText(DataObjectSection* sec);

	static int objGetFieldCount(DataObject* obj);
	static int objGetFieldIndex(DataObject* obj, const vstring& fieldName);
	static vstring objGetFieldName(DataObject* obj, int fieldIndex);
	static vstring objGetFieldType(DataObject* obj, int fieldIndex);

	static vstring getFieldAt(DataObject* obj, int line, int column);

	static vstring fieldIdToFieldName(const vstring& fieldId);

	static void setExceptionProperty(DataObject* obj, const vstring& name, const vstring& value);
	static vstring getExceptionProperty(DataObject* obj, const vstring& name);
};

VOLANTE_NAMESPACE_END 

#endif //__DATAOBJECTFUNCTIONS_H__
