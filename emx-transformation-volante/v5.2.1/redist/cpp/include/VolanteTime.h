#ifndef __TIME_H__
#define __TIME_H__


#include "TimeSpan.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT Time {
public:
	Time() : hours(0), mins(0), secs(0), millis(0) {
	}
	Time(	int hours,	int mins, int secs, int millis) : hours(hours), mins(mins), secs(secs), millis(millis) {

	}
	Time(const TimeSpan& timespan)  {
		hours = timespan.hours();
		mins = timespan.minutes();
		secs = timespan.seconds();
		millis = timespan.millis();
	}
	int getHours()const  {
		return hours;
	}
	int getMinutes() const {
		return mins;
	}
	int getSeconds() const {
		return secs;
	}
	int getMilliSeconds() const {
		return millis;
	}
	bool operator==( const Time& rhs )const {
		return this->hours == hours && this->mins == rhs.mins &&
			this->secs == rhs.secs && this->millis == rhs.millis;
	}
	bool operator < ( const Time& rhs )const {
		return compare(rhs) < 0;
	}
	bool operator <= ( const Time& rhs )const {
		return compare(rhs) <= 0;
	}
	bool operator > ( const Time& rhs )const {
		return compare(rhs) > 0;
	}
	bool operator >= ( const Time& rhs )const {
		return compare(rhs) > 0;
	}
	int compare(const Time& rhs)const;
	TimeSpan getTimeSpan() const;
	bool isValid() const;
	vstring toString() const;
private:
	static bool isValidTime( int h, int m, int s );
	static bool isValidHour( int h );
	static bool isValidMinute( int m );
	static bool isValidSecond( int s );
	static bool isValidMilliSecond( int m );

private:
	int hours;
	int mins;
	int secs;
	int millis;
};


VOLANTE_NAMESPACE_END






#endif //__TIME_H__
