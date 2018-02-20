#ifndef __SESSION_LAYER_COMMON__OMMDICT__H__
#define __SESSION_LAYER_COMMON__OMMDICT__H__

// STL Includes
#include <map>
#include <list>
#include <vector>
#include <new>

// RFA Includes
#include "Common/Common.h"
#include "Common/Data.h"


#include "reutersrt/Out.h"
#include "Data/SeriesWriteIterator.h"

// Forward declarations
class OMMFieldDict;
class OMMFieldDef;
class OMMEnumDict;
class OMMEnumDef;
class OMMEnumVal;


using namespace std;
using namespace rfa::common;
using namespace rfa::data;

// Auxilary class to prevent copying
class __NO_COPY
{
protected:
	__NO_COPY() {}
	virtual ~__NO_COPY() {}
private:
	__NO_COPY( const __NO_COPY & );
	__NO_COPY operator=( const __NO_COPY & );
};

// Base dict class
class OMMDict : private __NO_COPY
{
	public:
		enum DictLoadType
		{
			Network = 0,
			File
		};

		OMMDict(DictLoadType type);

		void		setDictId( Int32 dictId ) { _dictId = dictId; };
		Int32		getDictId() const { return _dictId; }

		void		setDictType( UInt16 dictType ) { _dictType = dictType; };
		UInt16		getDictType() const { return _dictType; }

		void		setVersion(std::string version) {_version = version;};
		std::string getVersion() const {return _version;};

		void		setDictLoadType( DictLoadType dictType ) { _dictLoadType = dictType; };
		DictLoadType		getDictLoadType() const { return _dictLoadType; }
		static UInt32 Trace;
private:
		Int32		_dictId;
		UInt16		_dictType;
		std::string _version;
		DictLoadType _dictLoadType;
};

// Field Data Dictionary Declaration
class OMMFieldDict : public OMMDict
{
public:


		OMMFieldDict(DictLoadType type);
		virtual ~OMMFieldDict();
		void	insertFieldDef( Int16 fieldId, const OMMFieldDef *pFieldDef );

		const	OMMFieldDef	* findFieldDef( Int16 fieldId ) const
		{
			return _fieldDefMap[fieldId];
		}

		UInt16 maxFieldLength() const { return _maxFieldLength; }

		void	associateEnumDict( OMMEnumDict		*pEnumDict );
		void	fixRipple();
		//virtual void	setDictType( DictType dictType ) { _dictType= dictType; };
		//DictType	getDictType() const { return _dictType; }
	
		OMMFieldDef** fields() { return _fieldDefMap; }


protected:
		OMMFieldDef *			_fieldDefMap[10000];
		OMMEnumDict		*_pEnumDict;
		UInt16					_maxFieldLength;
private:
		
};


// Field Definitition Declaration
class OMMFieldDef
{
public:
		OMMFieldDef();
		OMMFieldDef( const std::string & name, 
					  DataBuffer::DataBufferEnumeration dataType,
					  const std::string & displayName);

		// virtual ~OMMFieldDef(); not intended to be derived from
		
		void	setName( const std::string & name ) { _name = name; }
		const	std::string & getName() const { return _name; }

        void    setDisplayName( const std::string & displayName ) { _displayName = displayName; }
        const   std::string & getDisplayName() const { return _displayName; }

        void    setRipplesToFieldName( const std::string & rippleFieldName ) { _rippleFieldName = rippleFieldName; }
        void    setRipplesToFid( Int32 rippleFieldFid ) { _rippleFieldFid = rippleFieldFid; }
        const   std::string & getRipplesToFieldName() const { return _rippleFieldName; }
        const   unsigned int getRipplesToFid() const { return _rippleFieldFid; }

        void    setMFFieldTypeName( const std::string & mfFieldTypeName); 
        void    setMFFieldType( Int32 fieldType) { _mfFieldType = fieldType; }
        const   Int32	getMFFieldType() const { return _mfFieldType; }

        void    setMFFieldLength( Int32 mfFieldLength) { _mfFieldLength = mfFieldLength; }
        const   Int32  getMFFieldLength() const { return _mfFieldLength; }

        void    setMFEnumLength( Int32 mfEnumLength) { _mfEnumLength = mfEnumLength; }
        const   Int32  getMFEnumLength() const { return _mfEnumLength; }

		void	setDataType( DataBuffer::DataBufferEnumeration dataType )
		{
			_dataType = dataType;
		}

		void	resetDataType() { return; };

        UInt8	getDataType() const { return _dataType; }

		// does string to Common::DataBufferEnum translation
		void	setDataType( const std::string & dataTypeStr, int length );
		void	setDataType( UInt8 dataType ) {_dataType = dataType;};

        void    setMaxFieldLength( unsigned int  maxFieldLength) { _maxFieldLength = maxFieldLength; }
        const   int  getMaxFieldLength() const { return _maxFieldLength; }

		// EnumDef is just referenced so it's not included into "constness"
		void	 setEnumDef( OMMEnumDef* pEnumDef ) { _pEnumDef = pEnumDef; }
		const	 OMMEnumDef* getEnumDef() const { return _pEnumDef; }		

		const std::string & getEnumString ( Int16 enumVal ) const;

		void dumpFieldDef(Int32 fid) const;

private:
		std::string									   _name;
		UInt8											_dataType;
		std::string									   _displayName;
		std::string                                    _rippleFieldName;
		Int32										   _rippleFieldFid;
        Int32										   _mfFieldType;
        Int32                                          _mfFieldLength;
        Int32						                   _mfEnumLength;
        Int32								            _maxFieldLength;
        
		mutable const OMMEnumDef						*_pEnumDef;

};


// Enum Dictionary Declaration
class OMMEnumDict : public OMMDict
{
public:
		OMMEnumDict();
		virtual ~OMMEnumDict();
		void	insertEnumDef( const OMMEnumDef * enumDef );

		const	OMMEnumDef	* findEnumDef( Int16 fieldId ) const
		{
			OMMEnumDefMap::const_iterator cit = _enumDefMap.find( fieldId );
			return cit != _enumDefMap.end() ? cit->second : 0;
		}

		const std::map<Int16, const OMMEnumDef *> & enums() const
		{
			return _enumDefMap;
		}
		const std::list<const OMMEnumDef *> & enumList() const
		{
			return _enumDefList;
		}

protected:
		typedef std::map<Int16, const OMMEnumDef *>	OMMEnumDefMap;
		typedef std::list<const OMMEnumDef*>						OMMEnumDefList;

		
		OMMEnumDefMap									_enumDefMap;
		OMMEnumDefList									_enumDefList;
};

// Enum Definitiona Declaration
class OMMEnumDef
{
public:
		class EnumStrings 
		{
			public:
				std::string			_enumDisplayString;
				std::string			_enumMeaningString; 
		}; 

		void	setMeaningName( char* s) 
		{
			_enumStrings._enumMeaningString = std::string(s);
		}

		void	setDisplayName( char* s) 
		{
			_enumStrings._enumDisplayString = std::string(s);
		}

		void	setEnumVal(int val)
		{
			_enumVal = val;
		}

		void	insertEnumVal()
		{
			_enumValMap.insert( OMMEnumValMap::value_type(_enumVal, _enumStrings));
		}	

		void	insertEnumVal( UInt16 enumVal, const std::string& enumString )
		{
			_enumStrings._enumDisplayString = enumString;
			_enumValMap.insert( OMMEnumValMap::value_type( enumVal, _enumStrings ) );
		}

		const std::string & findEnumVal( UInt16 enumVal ) const
		{
			OMMEnumValMap::const_iterator cit = _enumValMap.find( enumVal );

			return cit != _enumValMap.end() ? ((cit->second)._enumDisplayString) : _emptyEnumString;
		}

		static const std::string & getEmptyEnumString() { return _emptyEnumString; }

		const std::map<UInt16, EnumStrings> values() const
		{
			return _enumValMap;
		}

		const std::list<Int16> fids() const
		{
			return _fids;
		}

		void addFid( Int16 fid )
		{
			_fids.push_back(fid);
		}

		void dumpEnumDef() const;

protected:
		typedef std::map< UInt16, EnumStrings> OMMEnumValMap;
		OMMEnumValMap				_enumValMap;
		std::list<Int16> _fids;


		static	std::string			_emptyEnumString;
		EnumStrings		_enumStrings;
		int				_enumVal;
};



class OMMNetworkFieldEnumDict : public OMMFieldDict
{
public:
	OMMNetworkFieldEnumDict();
	virtual ~OMMNetworkFieldEnumDict();
	void	loadEnumTypeDef(const Data& data);
	void	loadAppendix_A(const Data& data);
	void	associate();

protected:
	typedef void (OMMNetworkFieldEnumDict::*ConcreteDecFunction)(const DataBuffer& dataBuffer);
	typedef std::map<UInt16, const DataDef *>  OMMDefMap;
	typedef std::vector<Int16>  OMMFidIds;

	OMMDefMap		_defs;
	OMMFidIds fidIds;
	UInt16			_defId;
	DataDef*			_def;
	DataDef*			_defTemp;
	OMMEnumDict*	_enumDict;
	Out*			_out;
	bool			_first;

	OMMFieldDef* pFieldDef;
	OMMEnumDef *pEnumDef;
	int		mFieldId;

	virtual bool decodeFirstFieldDef(const ElementList& elementList, OMMFieldDef* def);
	virtual bool decodeOtherFieldDef(const ElementList& elementList, OMMFieldDef* def);
	virtual void decodeFieldDefDictionary(const Data& data, int recursionLevel=0, ConcreteDecFunction pFunc=0);
	void decodeFieldDefDictionarySummaryData(const ElementList& elementList);
	void decodeFieldDefDictionaryRow(const ElementList& elementList);


	void decodeEnumDefTables(const Data& data, int recursionLevel=0, ConcreteDecFunction pFunc=0);
	void decodeEnumDefTablesSummaryData(const ElementList& elementList);
	void decodeEnumDefTable(const ElementList& elementList);
};

class OMMFileFieldEnumDict : public OMMFieldDict
{
	bool    loadEnumTypeDef( const std::string & enumTypeDef,  OMMEnumDict *pEnumDict );
	bool    loadAppendix_A( const std::string & appendix_a );
	OMMEnumDict*	_enumDict;
public:
	OMMFileFieldEnumDict();
	void	associate();
	virtual ~OMMFileFieldEnumDict();
	OMMEnumDict & enumDict()
	{
		return *_enumDict;
	}
	bool 	load( const std::string & appendix_a, 
				  const std::string & enumTypeDef );
};

typedef const map<Int16, const OMMFieldDef*> FieldDefMap;
typedef const list<const OMMEnumDef*> EnumList;
typedef const map<UInt16, OMMEnumDef::EnumStrings> EnumValues;


#endif // __SESSION_LAYER_COMMON__OMMDICT__H__

