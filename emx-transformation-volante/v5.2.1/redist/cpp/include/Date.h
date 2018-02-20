#ifndef __DATE_H__
#define __DATE_H__

#include "TimeDefs.h"
#include "TimeSpan.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT Date {
public:
	Date();
	Date(	int year, int month, int date) : year(year), month(month), date(date) {
	}
	Date(	const TimeSpan& timespan) {
		unpack(timespan, year, month, date);
	}
	int getYear() const {
		return year;
	}
	int getMonth() const {
		return month;
	}
	int getDate()const  {
		return date;
	}
	bool operator==( const Date& rhs ) const{
		return this->year == rhs.year && this->month == rhs.month &&
			this->date == rhs.date;
	}
	bool operator < ( const Date& rhs ) const{
		return compare(rhs) < 0;
	}
	bool operator <= ( const Date& rhs ) const{
		return compare(rhs) <= 0;
	}
	bool operator > ( const Date& rhs ) const{
		return compare(rhs) > 0;
	}
	bool operator >= ( const Date& rhs ) const{
		return compare(rhs) > 0;
	}
	int compare(const Date& rhs)const;
	TimeSpan getTimeSpan() const ;
	int dayOfWeek() const;
	bool isValid() const ;
	vstring toString() const;
	static Date now();
	static TimeSpan pack( int y, int m, int d );
	static void unpack(const TimeSpan& timespan, int& y, int& m, int& d);
private:
	static bool isValidYear( int y );
	static bool isValidMonth( int m );
	static bool isValidDate( int y, int m, int d );
	static bool isLeapYear( int y );
	static bool isDayInMonth( int y, int m, int d );
	static int daysInMonth( int y, int m );

private:
	int year;
	int month;
	int date;
};


VOLANTE_NAMESPACE_END


#endif //__DATE_H__

