#ifndef __BITFUNCTIONS_H__
#define __BITFUNCTIONS_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT BitFunctions {
public:
    static int leftShift(int value, int shiftBy) {
		return value << shiftBy;
	}
	static int rightShift(int value, int shiftBy) {
		return value >> shiftBy;
	}
	static int unsignedRightShift(int value, int shiftBy) {
		return ((unsigned int)value) >> shiftBy;
	}
	static bool isBitSet(int value, int at) {
		return (value & (1 << at)) != 0;
	}

	static int setBit(int value, int at) {
		return (value | (1 << at));
	}

	static int clearBit(int value, int at)  {
		return (value & ~(1 << at));
	}
	static int flipBit(int value, int at) {
		return isBitSet(value, at) ? clearBit(value, at) : setBit(value, at);
	}

	static int bitAnd(int value1, int value2) {
		return (value1 & value2);
	}
	static int bitOr(int value1, int value2) {
		return (value1 | value2);
	}
	static int bitXOR(int value1, int value2) {
		return (value1 ^ value2);
	}
	static int bitNot(int value) {
		return ~(value);
	}

	

	// Long

    static dlong leftShift(dlong value, int shiftBy) {
		return value << shiftBy;
	}
	static dlong rightShift(dlong value, int shiftBy) {
		return value >> shiftBy;
	}
	static dlong unsignedRightShift(dlong value, int shiftBy) {
		return ((udlong)value) >> shiftBy;
	}
	static bool isBitSet(dlong value, int at) {
		return (value & (((dlong)1) << at)) != 0;
	}

	static dlong setBit(dlong value, int at) {
		return (value |= (((dlong)1) << at));
	}

	static dlong clearBit(dlong value, int at)  {
		return (value &= ~(((dlong)1) << at));
	}
	static dlong flipBit(dlong value, int at) {
		return isBitSet(value, at) ? clearBit(value, at) : setBit(value, at);
	}

	static dlong bitAnd(dlong value1, dlong value2) {
		return (value1 & value2);
	}
	static dlong bitOr(dlong value1, dlong value2) {
		return (value1 | value2);
	}
	static dlong bitXOR(dlong value1, dlong value2) {
		return (value1 ^ value2);
	}
	static dlong bitNot(dlong value) {
		return ~(value);
	}



};
VOLANTE_NAMESPACE_END

#endif //__BITFUNCTIONS_H__
