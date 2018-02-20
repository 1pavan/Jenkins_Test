#ifndef __BYTEBUFFER_H__
#define __BYTEBUFFER_H__

#include "MathUtil.h"

VOLANTE_NAMESPACE_BEGIN

#define DOT_DECIMAL_POINT		'.'
#define COMMA_DECIMAL_POINT		','
#define NO_DECIMAL_POINT 		(char)0

class VOLANTE_EXPORT ByteBuffer {
	signed char* buf;
	int capacity;
	int count;
	int readCursor;
	bool ownBuffer;
	ByteBuffer(const ByteBuffer&);
public:
	ByteBuffer() {
		init(16);
	}

	ByteBuffer(int capacity) {
		init(capacity);
	}
	ByteBuffer(const char* data, int count) {
		buf = (signed char*)data;
		this->count = count;
		this->capacity = capacity;
		readCursor = 0;
		ownBuffer = false;
	}

	~ByteBuffer() {
		if(ownBuffer) {
			delete[] buf;
		}
	}

	int read() {
		if(readCursor >= count) {
			throw TransformException("Out of bounds");
		}
		int toRet = buf[readCursor];
		readCursor++;
		return toRet;
	}
   bool hasMore() {
        return readCursor < count;
   }
	signed char* getCursor(int toRead) {
		if(readCursor + toRead >= count) {
			throw TransformException("Out of bounds");
		}
		signed char* toRet = buf + readCursor;
		readCursor += toRead;
		return toRet;
	}
	
	void init(int capacity) {
		buf = new signed char[capacity];
		this->capacity = capacity;
		count = 0;
		readCursor = 0;
		ownBuffer = true;
	}

	void ensureFree(int length) {
		expandCapacity(count + length);
	}

	void expandCapacity(int newcount) {
		if(newcount > capacity) {
			int newCapacity = MathUtil::maxVal(capacity << 1, newcount);
			signed char* newbuf = new signed char[newCapacity];
			memcpy(newbuf, buf, count);
			delete[] buf;
			buf = newbuf;
			capacity = newCapacity;
		}
	}

	int length() const {
		return count;
	}

	void write(int byteVal) {
		ensureFree(1);
		buf[count++] = (signed char)byteVal;
	}

public: 
	void append(char c) {
		ensureFree(1);
		buf[count++] = c;
	}
	vstring tempStr;
	void append(int i) {
		intToString(i, tempStr);
		append(tempStr);
		//append(Parsing::intToString(i));
	}

	void append(dlong l) {
		append(Parsing::longToString(l));
	}

	void append(float f) {
		floatToString(f, tempStr);
		append(tempStr);
	}
	void append(float f,  char decimalPoint) {
		vstring valueStr = Parsing::floatToString(f);
		if(f != DOT_DECIMAL_POINT) {
			valueStr = TextFunctions::replace(valueStr, DOT_DECIMAL_POINT, decimalPoint);
		}
		append(valueStr);
	}

	void append(double d) {
		doubleToString(d, tempStr);
		append(tempStr);
	}
	void append(double d, char decimalPoint ) {
		doubleToString(d, tempStr);
		if(d != DOT_DECIMAL_POINT) {
			tempStr = TextFunctions::replace(tempStr, DOT_DECIMAL_POINT, decimalPoint);
		}
		append(tempStr);
	}

	void append(const vstring& str) {
		append0(str);
	}
	void append(const char* data, int len) {
		append0(data, len);
	}
	void append(const ByteBuffer& toAdd) {
		int len = toAdd.length();
		ensureFree(len);
		memcpy(buf + count, toAdd.buf, len); 
		count += len;
	}
	void append(const Binary& str) {
		append0(str.data(), str.length());
	}
	void write(const Binary& str) {
		append0(str.data(), str.length());
	}
	void appendDelimiter(const vstring& str) {
		append0(str);
	}
	void appendDelimiter(const char* str) {
		append0(str, strlen(str));
	}
private:
	void append0(const vstring& str) {
		if(str.length() == 0) {
			return;
		}
		append0(str.data(), str.length());
	}
	void append0(const char* data, int len) {
		ensureFree(len);
		memcpy(buf + count, data, len);
		count += len;
	}

public: 
	void chop(int marker){ 
		count = marker;
	}        
	const char* toByteArray(int& length) const {
		char* newbuf = new char[count];
		memcpy(newbuf, buf, count);
		length = count;
		return newbuf;
	}
	const char* str() const {
		return (const char*)buf;
	}
	int pcount() const {
		return count;
	}
	const char* getByteArray(int& length) const {
		length = count;
		return (const char*)buf;
	}
	vstring toString() const {
		return vstring((const char*)buf, count);
	}
	static float intBitsToFloat(int value) {
		return *((float*)(&value));
	}
	static int floatToIntBits(float value) {
		return *((int*)(&value));
	}
	static double longBitsToDouble(dlong value) {
		return *((double*)(&value));
	}
	static dlong doubleToLongBits(double value) {
		return *((dlong*)(&value));
	}
};
VOLANTE_NAMESPACE_END

#endif //__BYTEBUFFER_H__
