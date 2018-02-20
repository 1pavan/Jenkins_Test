#ifndef __SIACCANONICALTYPE_H__
#define __SIACCANONICALTYPE_H__
#include "Object.h"
#include "Parsing.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT SIACCanonicalType {


public:
	static DateTime parseUTCTimestamp(const vstring& str);

	static DateTime parseUTCTimeOnly(const vstring& str);

	static DateTime parseLocalMktDate(const vstring& str);

	static DateTime parseUTCDate(const vstring& str);

	static DateTime parsemonth_year(const vstring& str);

	static DateTime parseLocalMktTimestamp(const vstring& str);

	static DateTime parseLocalMktTimeOnly(const vstring& str);
	static DateTime parseUTCTimestamp_int64(const vstring& str);
	static DateTime parseUTCTimestamp_int64(dlong value);
	static bool parseBoolean(const vstring& str);
	static bool parseBoolean_4_1(const vstring& str);


	static vstring& formatUTCTimestamp(const DateTime& date, vstring& out);

	static vstring& formatUTCTimeOnly(const DateTime& date, vstring& out);

	static vstring& formatLocalMktDate(const DateTime& date, vstring& out);

	static vstring& formatUTCDate(const DateTime& date, vstring& out);

	static vstring& formatmonth_year(const DateTime& date, vstring& out);

	static vstring& formatLocalMktTimestamp(const DateTime& date, vstring& out);

	static vstring& formatLocalMktTimeOnly(const DateTime& date, vstring& out);

	static vstring& formatUTCTimestamp_int64(const DateTime& date, vstring& out);

	static vstring& formatBoolean(bool bl, vstring& out);
	static vstring& formatBoolean_4_1(bool bl, vstring& out);

};


VOLANTE_NAMESPACE_END

#endif //__SIACCANONICALTYPE_H__

