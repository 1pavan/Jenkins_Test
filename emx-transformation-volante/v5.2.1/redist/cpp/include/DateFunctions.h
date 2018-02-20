#ifndef __DATEFUNCTIONS_H__
#define __DATEFUNCTIONS_H__
#include "Object.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT DateFunctions {
public:

	static int day(const DateTime& date);
	static int month(const DateTime& date);
	static int year(const DateTime& date);

	static int hour(const DateTime& date);
	static int minute(const DateTime& date);
	static int second(const DateTime& date);
	static int millis(const DateTime& date);
	static dlong toTimestamp(const DateTime& date);
	static DateTime fromTimestamp(dlong time);

	static DateTime toUTCTime(const DateTime& date);
	static DateTime toLocalTime(const DateTime& date);

	static int weekDay(const DateTime& date);
	static vstring weekDayName(const DateTime& date);

	static DateTime today();
	static DateTime now();

	static DateTime datePart(const DateTime& dt);
	static DateTime timePart(const DateTime& dt);

	static DateTime newDate(int year, int month, int date);
	static DateTime newTime(int hour, int min, int sec, int millis = 0);
	static DateTime newDateTime(int year, int month, int date, int hour, int min, int sec, int millis = 0);

	static DateTime nextDay(const DateTime& date);
	static DateTime previousDay(const DateTime& date);

	static DateTime addDays(const DateTime& date, int days);
	static DateTime addHours(const DateTime& date, int hours);
	static DateTime addMinutes(const DateTime& date, int minutes);
	static DateTime addSeconds(const DateTime& date, int seconds);
	////////////////////////////////////////  incorrect
	static DateTime addMonths(const DateTime& date, int months);
	static DateTime addYears(const DateTime& date, int years);
	////////////////////////////////////////////////////////
	static int daysBetween(const DateTime& date1, const DateTime& date2);
	static bool after(const DateTime& date1, const DateTime& date2);

	static bool before(const DateTime& date1, const DateTime& date2);
	static bool equal(const DateTime& date1, const DateTime& date2);
	static bool notEqual(const DateTime& date1, const DateTime& date2);

	static bool less(const DateTime& date1, const DateTime& date2) {
		return compare(date1, date2) < 0;
	}	
	static bool greater(const DateTime& date1, const DateTime& date2) {
		return compare(date1, date2) > 0;
	}	
	static bool lessEqual(const DateTime& date1, const DateTime& date2) {
		return compare(date1, date2) <= 0;
	}	
	static bool greaterEqual(const DateTime& date1, const DateTime& date2) {
		return compare(date1, date2) >= 0;
	}	


	/**
	*	Compares <i>date1</i> with <i>date2</i>. Returns 0 if both are equal. Returns a value 
	*	less than 0 if date1 lesser than date2. Returns a value greater than 0 if date1 greater than date2.
	*	If both are empty, returns 0. If only date2 is empty, returns -1. If only date2 is empty, returns 1. 
	*
	*	@param	str1	any string.
	*	@param	str2	string to be compared with str1.
	*/
	static int compare(const DateTime& date1, const DateTime& date2);

	static DateTime toDate(const ISODateTime& cal) {
		return DateTime(cal);;
	}

	static ISODateTime toISODate(const DateTime& dt) {
		ISODateTime isoDateTime(dt);
		return isoDateTime;
	}
	static ISODateTime toISODate(const DateTime& dt, int zoneoffset) {
		ISODateTime isoDateTime(dt, zoneoffset);
		return isoDateTime;
	}

	static int monthsBetween(const DateTime& date1, const DateTime& date2);
	static int yearsBetween(const DateTime& date1, const DateTime& date2);
  static int getTimeZoneOffset();

};

VOLANTE_NAMESPACE_END

#endif //__DATEFUNCTIONS_H__

