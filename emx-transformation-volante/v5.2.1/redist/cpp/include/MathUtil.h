#ifndef __MATHUTIL_H__
#define __MATHUTIL_H__
#include <math.h>

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT MathUtil {
public:
	template <class T>
	inline static T maxVal(const T& t1, const T& t2) {
		return (t1 > t2 ? t1 : t2);
	}
	template <class T>
	inline static T minVal(const T& t1, const T& t2) {
		return (t1 < t2 ? t1 : t2);
	}
    static double round(double a) {
			return ::floor(a + 0.5);
    }
    static double floor(double a) {
			return (double)::floor(a);
	}
	/*
    static float round(float a) {
		return (int)floor(a + 0.5f);
    }
    static float floor(float a) {
		return ::floor(a);
	}*/
	template <class T>
	inline static T abs(const T& t1) {
		return (t1 < 0 ? -t1 : t1);
	}
};

VOLANTE_NAMESPACE_END


#endif //__MATHUTIL_H__
