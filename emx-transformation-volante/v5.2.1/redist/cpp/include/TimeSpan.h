#ifndef __TIMESPAN_H__
#define __TIMESPAN_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT TimeSpan {
public:
	TimeSpan() {
		_seconds = 0;
		_millis = 0;
	}
	TimeSpan(dlong _second) {
		this->_seconds = _second;
		this->_millis = 0;
	}
	TimeSpan(dlong _second, int millis) {
		this->_seconds = _second;
		this->_millis = millis;
	}
	TimeSpan( const TimeSpan& rhs ){
		_seconds = rhs._seconds;
		_millis = rhs._millis;
	}
	TimeSpan( int d, int h = 0L, int m =0L, int s = 0L, int millis =0L );

	TimeSpan& operator=( const TimeSpan& rhs ) {
		if ( this != &rhs )
		{
			_seconds = rhs._seconds;
		}
		return *this;
	}
	TimeSpan& operator=( int days );

	TimeSpan& operator+=( const TimeSpan& t );
	TimeSpan& operator-=( const TimeSpan& t );
	//TimeSpan& operator*=( int value );
	//TimeSpan& operator/=( int value );
	//TimeSpan& operator%=( int value );

	TimeSpan operator+( const TimeSpan& t ) const;
	TimeSpan operator-( const TimeSpan& t ) const;
	//TimeSpan operator*( int value ) const;
	//TimeSpan operator/( int value ) const;
	//TimeSpan operator%( int value ) const;

	bool operator< ( const TimeSpan& t ) const;
	bool operator<=( const TimeSpan& t )const;
	bool operator> ( const TimeSpan& t )const;
	bool operator>=( const TimeSpan& t )const;
	bool operator==( const TimeSpan& t )const;
	bool operator!=( const TimeSpan& t )const;

	int days() const;
	int hours()const;
	int minutes() const;
	int seconds() const;
	int millis() const {
		return _millis;
	}
	dlong elapsedseconds() const;
	void asString( char* out, size_t size )const;

private:

	dlong _seconds;
	int _millis;
	void assertRange();

	friend class Date;
	friend class Time;
	friend class DateTime;
};

VOLANTE_NAMESPACE_END







#endif //__TIMESPAN_H__
