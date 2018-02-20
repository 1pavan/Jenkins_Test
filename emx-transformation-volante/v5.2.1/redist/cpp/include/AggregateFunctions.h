#ifndef __AGGREGATEFUNCTIONS_H__
#define __AGGREGATEFUNCTIONS_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT SectionHelper {
public:
	static int  getFieldIndex(DataObjectCollection* sec,  const vstring& fieldName);
	static int  getFieldIndex(DataObject* obj,  const vstring& fieldName);
	static void handleFieldAccessException(const vstring& fieldName,Exception* e);
	static void handleFieldAccessException(int fieldIndex, Exception* e);

};
class VOLANTE_EXPORT AggregateFunctions : public SectionHelper {

public:

	static int fieldCount(DataObjectSection*  sec, const vstring& fieldName);
	static int fieldCount(DataObjectCollection*  sec, const vstring& fieldName);

	static int fieldValueCount(DataObjectSection* sec, const vstring& fieldName,const vstring& fieldValue); 
	static int fieldValueCount(DataObjectCollection* sec, const vstring& fieldName,const vstring& fieldValue); 

	static bool fieldValueExistsInAll(DataObjectSection* sec, const vstring& fieldName,const vstring& fieldValue); 
	static bool fieldValueExistsInAll(DataObjectCollection* sec, const vstring& fieldName,const vstring& fieldValue); 

	static bool fieldValueExistsInAtLeastOne(DataObjectSection* sec, const vstring& fieldName,const vstring& fieldValue); 
	static bool fieldValueExistsInAtLeastOne(DataObjectCollection* sec, const vstring& fieldName,const vstring& fieldValue); 

	static bool fieldExistsInOne(DataObjectSection* sec,const vstring& fieldName); 
	static bool fieldExistsInOne(DataObjectCollection* sec,const vstring& fieldName); 

	static bool fieldExistsInAtMostOne(DataObjectSection* sec,const vstring& fieldName); 
	static bool fieldExistsInAtMostOne(DataObjectCollection* sec,const vstring& fieldName); 

	static bool fieldExistsInAtLeastOne(DataObjectSection* sec,const vstring& fieldName); 
	static bool fieldExistsInAtLeastOne(DataObjectCollection* sec,const vstring& fieldName); 


	static bool fieldExistsInAll(DataObjectSection* sec, const vstring& fieldName);
	static bool fieldExistsInAll(DataObjectCollection* sec, const vstring& fieldName);

	static bool fieldExistsInAll(DataObjectSection* sec, const vstring& fieldName,const vstring& inSecName);
	static bool fieldExistsInAll(DataObjectCollection* sec, const vstring& fieldName,const vstring& inSecName);

	static bool secExistsInOne(DataObjectSection* sec,const vstring& sectionName); 
	static bool secExistsInOne(DataObjectCollection* sec,const vstring& sectionName); 

	static bool secExistsInAtMostOne(DataObjectSection* sec,const vstring& sectionName); 
	static bool secExistsInAtMostOne(DataObjectCollection* sec,const vstring& sectionName); 

	static bool secExistsInAtLeastOne(DataObjectSection* sec,const vstring& sectionName); 
	static bool secExistsInAtLeastOne(DataObjectCollection* sec,const vstring& sectionName); 

	static bool secExistsInAll(DataObjectCollection* sec, const vstring& secName);
	static bool secExistsInAll(DataObjectSection* sec, const vstring& secName);

	static bool secExistsInAll(DataObjectSection* sec, const vstring& secName,const vstring& inSecName);
	static bool secExistsInAll(DataObjectCollection* sec, const vstring& secName,const vstring& inSecName);

	static double secAvg(DataObjectSection* sec, const vstring& fieldName);
	static double secAvg(DataObjectCollection* sec, const vstring& fieldName);

	static int secSum(DataObjectSection* sec, const vstring& fieldName);
	static int secSum(DataObjectCollection* sec, const vstring& fieldName);

	static double secSumDouble(DataObjectSection* sec, const vstring& fieldName);
	static double secSumDouble(DataObjectCollection* sec, const vstring& fieldName);

	static int secCount(DataObjectSection* sec);
	static int secCount(DataObjectCollection* sec);

	static int secCount(DataObjectSection* sec, const vstring& secName);
	static int secCount(DataObjectCollection* sec,const vstring& secName); 

	static DataObject* secElm(DataObjectSection* sec, int index);
	static DataObject* secElm(DataObjectCollection* sec, int index);

	static int secMax(DataObjectSection* sec, const vstring& fieldName);
	static int secMax(DataObjectCollection* sec, const vstring& fieldName);

	static int secMin(DataObjectSection* sec, const vstring& fieldName);
	static int secMin(DataObjectCollection* sec, const vstring& fieldName);

	static double secMaxDouble(DataObjectSection* sec, const vstring& fieldName);
	static double secMaxDouble(DataObjectCollection* sec, const vstring& fieldName);

	static double secMinDouble(DataObjectSection* sec, const vstring& fieldName);
	static double secMinDouble(DataObjectCollection* sec, const vstring& fieldName);




private:
	static int simpleFieldCount(DataObjectCollection* sec, const vstring& fieldName); 

	static int simpleFieldValueCount(DataObjectCollection* sec, const vstring& fieldName,const vstring& fieldValue); 

	static bool simpleCheckFieldValueExistenceInAll(DataObjectCollection* sec, const vstring& fieldName,const vstring& fieldValue); 
	static bool simpleCheckFieldValueExistence(DataObjectCollection* sec, const vstring& fieldName,const vstring& fieldValue); 

	static bool checkFieldValueExistenceInAll(DataObjectCollection* sec, const vstring& fieldName,const vstring& fieldValue); 
	static bool checkFieldValueExistence(DataObjectCollection* sec, const vstring& fieldName,const vstring& fieldValue); 

	static bool checkFieldExistence(DataObjectCollection* sec, const vstring& fieldName);
	static bool simpleCheckFieldExistence(DataObjectCollection* sec, const vstring& fieldName);

	static bool checkFieldExistenceInAll(DataObjectCollection* sec, const vstring& fieldName);
	static bool simpleCheckFieldExistenceInAll(DataObjectCollection* sec, const vstring& fieldName);

	static bool checkSecExistenceInAll(DataObjectCollection* sec, const vstring& secName);
	static bool simpleCheckSecExistenceInAll(DataObjectCollection* sec, const vstring& secName);

	static bool checkSecExistence(DataObjectCollection* sec, const vstring& secName);
	static bool simpleCheckSecExistence(DataObjectCollection* sec, const vstring& secName);

	static double simpleSecSumDouble(DataObjectCollection* sec, const vstring& fieldName);

	static int simpleSecCount(DataObjectCollection* sec, const vstring& fieldName); 

	static int simpleSecMax0(DataObjectCollection* sec, const vstring& fieldName);
	static int secMax0(DataObjectCollection* sec, const vstring& fieldName);

	static int simpleSecMin0(DataObjectCollection* sec, const vstring& fieldName);
	static int secMin0(DataObjectCollection* sec, const vstring& fieldName);

	static double simpleSecMaxDouble0(DataObjectCollection* sec, const vstring& fieldName);
	static double secMaxDouble0(DataObjectCollection* sec, const vstring& fieldName);

	static double simpleSecMinDouble0(DataObjectCollection* sec, const vstring& fieldName);
	static double secMinDouble0(DataObjectCollection* sec, const vstring& fieldName);


};

VOLANTE_NAMESPACE_END

#endif //__AGGREGATEFUNCTIONS_H__

