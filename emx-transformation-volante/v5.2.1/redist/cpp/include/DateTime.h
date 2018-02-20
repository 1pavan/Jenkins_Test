#ifndef __DATETIME_H__
#define __DATETIME_H__


#include "TimeSpan.h"
#include "Date.h"
#include "VolanteTime.h"

VOLANTE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////////////
class VOLANTE_EXPORT DateTime {
public:
	DateTime();
	DateTime(const TimeSpan& _offset);
	DateTime( int year, int month, int date, int hours, int mins, int secs = 0,  int millis = 0);
	DateTime(const Date& date, const Time& time);

	const Date& getDatePortion() const {
		return date;
	}
	const Time& getTimePortion()const  {
		return time;
	}
	int getYear() const {
		return date.getYear();
	}
	int getMonth() const {
		return date.getMonth();
	}
	int getDate() const {
		return date.getDate();
	}
	int getHours()const  {
		return time.getHours();
	}
	int getMinutes()const  {
		return time.getMinutes();
	}
	int getSeconds()const  {
		return time.getSeconds();
	}
	int getMilliSeconds() const {
		return time.getMilliSeconds();
	}
	bool operator==( const DateTime& rhs ) const {
		return this->date == rhs.date && this->time == rhs.time;
	}
	bool operator!=( const DateTime& dt ) const {
    return ! (operator==(dt));
 }

	int compare( const DateTime& rhs)const	{
		int cmp = date.compare(rhs.date);
		if(cmp == 0) {
			cmp = time.compare(rhs.time);
		}
		return cmp;
	}
	bool operator < ( const DateTime& rhs )const {
		return compare(rhs) < 0;
	}
	bool operator <= ( const DateTime& rhs )const {
		return compare(rhs) <= 0;
	}
	bool operator > ( const DateTime& rhs )const {
		return compare(rhs) > 0;
	}
	bool operator >= ( const DateTime& rhs )const {
		return compare(rhs) > 0;
	}
	TimeSpan getTimeSpan() const;
	DateTime operator+( const TimeSpan& t ) const;
	DateTime operator-( const TimeSpan& t ) const;
	TimeSpan  operator-( const DateTime& dt )const;
	/*
	DateTime& operator+=( const TimeSpan& t );
	DateTime& operator-=( const TimeSpan& t );
	DateTime& operator++();
	DateTime  operator++( int );
	DateTime& operator--();
	DateTime  operator--( int );*/

	size_t asString( char* out, size_t size, const char* format) const;
	vstring toString(const vstring& pattern)const;
	static DateTime fromString(const char* dateStr, const char* format);
	dlong toTimestamp() const;
	bool isValid() const;
	void validate() const;
	static DateTime fromTimestamp(dlong time);

	static DateTime now();
	static DateTime today();
private:
	Date date;
	Time time;
};

class VOLANTE_EXPORT ISODateTime : public DateTime {
public:
	ISODateTime() {
	}
	ISODateTime(const DateTime& dt) :DateTime(dt) {
		timeZoneOffsetMins = 0;
	}
	ISODateTime(const DateTime& dt, int timeZoneOffsetMins) :DateTime(dt), timeZoneOffsetMins(timeZoneOffsetMins) {
	}
	int getTimeZoneOffset() {
		return timeZoneOffsetMins;
	}
private:
	int timeZoneOffsetMins;
};

struct tm2 {
    int tm_msec;     /* mills seconds after the second - [0,1000] */
    int tm_sec;     /* seconds after the minute - [0,59] */
    int tm_min;     /* minutes after the hour - [0,59] */
    int tm_hour;    /* hours since midnight - [0,23] */
    int tm_mday;    /* day of the month - [1,31] */
    int tm_mon;     /* months since January - [0,11] */
    int tm_year;    /* years since 1900 */
};


size_t datetostring( char *s, size_t maxs, const char *format, const struct tm2 *t);
void stringtodate( const char* dateStr, const char* format, struct tm2* t );

VOLANTE_NAMESPACE_END





#endif //__DATETIME_H__
