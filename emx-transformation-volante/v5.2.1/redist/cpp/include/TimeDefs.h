#ifndef __TIMEDEFS_H__
#define __TIMEDEFS_H__

#include "md.h"
#include "stddef.h"
#include <string>

#ifdef VOLANTE_USE_STD_STRING
VOLANTE_NAMESPACE_BEGIN
typedef std::string		vstring;
typedef std::string		vstringbuffer;
typedef std::string		vstringliteral;
VOLANTE_NAMESPACE_END
#else 
#include "vstring.h"
VOLANTE_NAMESPACE_BEGIN
typedef vlstring		vstring;
typedef vlstringbuffer	vstringbuffer;
typedef vlstringliteral vstringliteral;
VOLANTE_NAMESPACE_END
#endif


VOLANTE_NAMESPACE_BEGIN


class VOLANTE_EXPORT TimeDefs {
public:

    /**
     * Constant for the number of seconds in a minute.
     */
    static const int SECONDS_IN_MINUTE;

    /**
     * Constant for the number of seconds in an hour.
     */
    static const int SECONDS_IN_HOUR;

    /**
     * Constant for the number of seconds in a day.
     */
    static const int SECONDS_IN_DAY;

    /**
     * Constant for the number of seconds in a week.
     */
    static const int SECONDS_IN_WEEK;

    /**
     * Constant for the number of seconds in a year.
     */
    static const int SECONDS_IN_YEAR;

    /**
     * Constant for the number of seconds in a leap year.
     */
    static const int SECONDS_IN_LEAP_YEAR;

    // Constant for the number of seconds in the timespan between
    // January 1, 4712 BC at 00:00:00 ( midnight ) and December 31,
    // 32767 at 23:59:59.
    static const dlong SECONDS_IN_XCHRON_RANGE;

    /**
     * Constant for the number of minutes in an hour.
     */
    static const int MINUTES_IN_HOUR;

    /**
     * Constant for the number of hours in a day.
     */
    static const int HOURS_IN_DAY;

    /**
     * Constant for the number of days in a week.
     */
    static const int DAYS_IN_WEEK;

    /**
     * Constant for the number of days in a regular year.
     */
    static const int DAYS_IN_YEAR;

    /**
     * Constant for the number of days in a leap year.
     */
    static const int DAYS_IN_LEAP_YEAR;

    /**
     * Constant for the number of months in a year.
     */
    static const int MONTHS_IN_YEAR;

    /**
     * Constant for the julian day number of the last day to occur in
     * the Julian calendar, which was October 4, 1582.
     */
    static const int LAST_JULIAN_CALENDAR_DAY;

    /**
     * Constant for the julian day number of the last day handled by the
     * XChron library, which is December 31, 32767.
     */
    static const int LAST_JULIAN_DAY;

    /**
     * Constant for the julian day number of the first day handled by
     * the XChron library, which is January 1, 4712 BC.
     */
    static const int FIRST_JULIAN_DAY;

    /**
     * Constant for the minimum year handled by the XChron library,
     * -which is 4712.
     */
    static const int MINIMUM_YEAR;

    /**
     * Constant for the maximum year handled by the XChron library,
     * which is 32767 A.D. ( Gregorian )
     */
    static const int MAXIMUM_YEAR;

    /**
     * A maximum string length.
     */
    static const size_t MAX_FORMAT_STR_SIZE;

    /**
     * The default format used as an argument to the xstrftime function
     * to produce formatted time output when no other format string is
     * explicitly provided.
     */
    static const char* DEFAULT_TIME_FORMAT;

    /**
     * The default format used as an argument to the xstrftime function
     * to produce formatted date output when no other format string is
     * explicitly provided.
     */
    static const char* DEFAULT_DATE_FORMAT;

    /**
     * The default format used as an argument to the xstrftime function
     * to produce formatted datetime output when no other format string
     * is explicitly provided.
     */
    static const char* DEFAULT_DATE_TIME_FORMAT;

    // The default format used to signify years occurring before Christ.
    static const char* DEFAULT_BC_STRING;


    /**
     * Enumeration for days of the week.
     */
    enum { SUNDAY = 1, MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY };

    /**
     * Enumeration for months of the year.
     */
    enum { JANUARY = 1, FEBRUARY,MARCH,APRIL,MAY,JUNE,JULY,AUGUST,SEPTEMBER,OCTOBER,NOVEMBER,DECEMBER };
};


VOLANTE_NAMESPACE_END






#endif //__TIMEDEFS_H__
