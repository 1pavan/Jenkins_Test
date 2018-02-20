#ifndef __VSTRING_H__
#define __VSTRING_H__

#include "md.h"
#include <new>
#ifdef VOLANTE_USE_OLD_STREAMS
#include <iostream.h>
#else
#include <iostream>
#endif
#include <assert.h>
#include <algorithm>
#include <string.h>

VOLANTE_NAMESPACE_BEGIN

template<class T> inline
const T& maxOf(const T& t1, const T& t2)
{
	return (t1 < t2 ? t2 : t1);
}
template<class T> inline
const T& minOf(const T& t1, const T& t2)
{
	return (t1 > t2 ? t2 : t1);
}
/*
template <class E>
inline void trait_assign(E& _Left, const E& _Right){	
	_Left = _Right;
}
template <class E>
char* trait_copy(E *_First1, const E *_First2, size_t _Count)
{	// copy [_First1, _First1 + _Count) to [_First2, ...)
	char *_Next = _First1;
	for (; 0 < _Count; --_Count, ++_Next, ++_First2)
		trait_assign(*_Next, *_First2);
	return (_First1);
}
*/
template <class E>
void trait_copy(E * dest, const E * src, size_t count) {
	// copy [_First1, _First1 + _Count) to [_First2, ...)
	const E* end = src + count;
	while(src != end) {
		*dest++ = *src++; 
	}
}

class VOLANTE_EXPORT chararray {
private:
	chararray(size_t len, char* buffer) : len(len), buffer(buffer), refCount(1){
	}
protected:
	~chararray();
public:
	inline char operator[] (size_t index) const {
		//assert(index < len);
		return buffer[index];
	}
	inline char charAt (size_t index) const {
		assert(index < len);
		return buffer[index];
	}
	inline size_t length() const {
		return len; 
	}
	int getRefCount() {
		return refCount;
	}
	inline void addRef() {
		checkThreadOwner();
		SAFE_INC(refCount);
	}
	inline void releaseRef() {
		checkThreadOwner();
		if(SAFE_DEC(refCount) == 0) {
			delete this;
		}
	}
	char* getCharPtr() const {
		return buffer;
	}
	char* getPtr() const {
		return buffer;
	}
	static chararray* create(size_t length) {
		char* buffer = new char[length + sizeof(chararray)];
		return new (buffer) chararray(length, buffer + 	sizeof(chararray));
	}
	static chararray* resize(chararray* copyFrom, size_t length);
private:
#ifdef CHECK_THREAD_OWNER
	SingleThreadAccess singleThreadAccess;
	void checkThreadOwner() {
		singleThreadAccess.checkThreadOwner();
	}
#else 
	void checkThreadOwner() {
	}
#endif 

	char* buffer;
	size_t len;
	REF_COUNT_TYPE refCount;
};
////////////////////////////////////////////////////////////
/**
 *  A drop-in replacement of std::string. Only some of the more commonly 
 *  used methods are implemented in this class. 
 *  Objects of this class are not thread safe.
 */
class VOLANTE_EXPORT vlstring {
public:
	vlstring() {
		count = 0;
		start = "";
		carray = 0;
	}
	vlstring(const vlstring& from) {
		copyToThis(from);
	}
	vlstring(const char* str) {
		init(str, str == NULL ? 0 : strlen(str));
	}
	vlstring(const char* str, size_t length) {
		init(str, length);
	}
	vlstring(size_t length, char copyChar) {
		count = length;
		carray = chararray::create(count + 1);
		start = carray->getCharPtr();
		memset(carray->getCharPtr(), copyChar, count);
	}
	~vlstring() {
		clean();
	}
	const vlstring& operator = (const vlstring& from) {
		return assign(from);
	}
	const vlstring& operator = (const char* from) {
		return assign(from, strlen(from));
	}
	vlstring& assign(const vlstring& from) {
		chararray * oldArray = carray;
		copyToThis(from);
		clean(oldArray);
		return *this;
	}

	vlstring& assign(const char* from, size_t length) {
		chararray * oldArray = carray;
		init(from, length);
		clean(oldArray);
		return *this;
	}
	/*
	char charAt(size_t index) const  {
		return start[index];
	}*/
	char at(size_t index) const {
		if(index >= count) {
			//throw std::out_of_range("index out of range");
		}
		return start[index];
	}
	char operator[](size_t index) const {
		return start[index];
	}
	const char* c_str() const;
	char* getBuffer(int length);
	void setBufferLength(int length);
	void assign(int value);
	void assign(char value);
	void assign(double value);
	void assign(float value);
	void assign(dlong value);
	const char* data() const {
		return start;

	}
	//size_t find_last_of(const char* charSet) const;
	size_t find(int ch) const {
		return find(ch, 0);
	}
	size_t find(int ch, size_t fromIndex)const ;

	size_t  find(const vlstring& str) const {
		return find(str, 0);
	}
	size_t find(const vlstring& str, size_t fromIndex) const ;

	size_t rfind(char ch) const {
		return rfind(ch, count - 1);
	}
	size_t rfind(char ch, size_t fromIndex) const;

	size_t rfind(const vlstring& str) const {
		return rfind(str, count);
	}
	size_t rfind(const vlstring& str, size_t fromIndex)const ;

	//bool regionMatches(bool ignoreCase,int toffset, const vlstring& other, int ooffset, int len);

	vlstring substr(size_t beginIndex) const {
		return vlstring(start + beginIndex , count - beginIndex, carray);
	}
	vlstring substr(size_t beginIndex, size_t subCount) const {
		return vlstring(start + beginIndex, minOf(count-beginIndex, subCount), carray);
	}
	void substr(size_t beginIndex, vlstring& assignTo) const {
		substr(beginIndex, count - beginIndex, assignTo);
	}
	void substr(size_t beginIndex, size_t subCount, vlstring& assignTo) const {
		chararray* oldArray = assignTo.carray;
		assignTo.assign0(start+ beginIndex, subCount, carray);
		clean(oldArray);
	}
	vlstring operator + (const vlstring& toAdd) const {
		size_t totalLength = count + toAdd.count;
		chararray* newValue = chararray::create(totalLength + 1);
		char* newStart = newValue->getCharPtr();
		trait_copy(newStart, start, count);
		trait_copy(newStart + count, toAdd.start, toAdd.count);
		return vlstring(newStart, totalLength, newValue, false);
	}
	bool operator > (const vlstring& str) const {
		return compare(str) > 0;
	}
	bool operator > (const char* str) const {
		return compare(str) > 0;
	}
	bool operator < (const vlstring& str) const {
		return compare(str) < 0;
	}
	bool operator < (const char* str) const {
		return compare(str) < 0;
	}
	bool operator == (const vlstring& str) const {
		return equals(str);
	}
	bool operator == (const char* str) const {
		return equals(str, strlen(str));
	}
	bool operator != (const vlstring& str) const {
		return !equals(str);
	}
	bool operator != (const char* str) const {
		return !equals(str, strlen(str));
	}
	bool empty() const {
		return count == 0;
	}
	size_t size() const {
		return count;
	}
	size_t length() const {
		return count;
	}
	/*	
	int toInt() const {
		return v_atoi(data(), data() + length());
	}
	int toInt(size_t start, size_t length) const {
		return v_atoi(data() + start, data() + start + length);
	}*/
	void toString(vlstring& str) const {
		str.assign(*this);
	}
	inline const vlstring& toString() const {
		return *this;
	}
	vlstring span(const vlstring & endPoint) const;
	size_t distance(const vlstring& subsequence) const;
	vlstring static_string(const char* str) {
		return vlstring(str, str);
	}
	int compare(const vlstring& anotherString) const {
		return compare(anotherString.data(), anotherString.count);
	}
	int compare(const char* anotherString) const {
		return compare(anotherString, strlen(anotherString));
	}
	int compare(const char* anotherString, size_t length) const;

private:
	bool equals(const vlstring& anotherString) const {
		return (count == anotherString.count) && 
					((data() == anotherString.data()) || 
						equals(data(), anotherString.data(), count));
	}
	bool equals(const char* anotherString, size_t length) const{
		return (count == length) && 
					equals(data(), anotherString, length);
	}
	bool equalsIgnoreCase(const vlstring& anotherString) const;
	static bool equalsIgnoreCase(const char* v1, const char* v2, size_t length);

	friend class Binary;
public:
	static bool equals(const char* v1, const char* v2, size_t length)  {
		while (length-- != 0) {
			if (*v1++ != *v2++) {
				return false;
			}
		}
		return true;
	}


protected:
	size_t capacity() const {
		return carray ==NULL ? 0 : carray->length();
	}
	vlstring(const char* start, size_t count, chararray* carray, bool addRef = true) {
		assign0(start, count, carray, addRef);
	}
	void assign0(const char* start, size_t count, chararray* carray, bool addRef = true) {
		this->start = start;
		this->count = count;
		this->carray = carray;
		if(carray != NULL && addRef) {
			carray->addRef();
		}
		/*
		// special case - we do not own the 'start' string make a copy
		if(count != 0 && carray == NULL) {
			init(start, count);			
		}*/
	}


	void init(const char* str, size_t length) {
		count = length;
		carray = chararray::create(count + 1);
		//memcpy(value->getBuffer(), str, count);
		start = carray->getCharPtr();
		trait_copy(carray->getCharPtr(), str, count);
	}
	void copyToThis(const vlstring& from) {
		count = from.count;
		carray = from.carray;
		start = from.start;
		if(carray != NULL) {
			carray->addRef();
		}
	}
	void clean() {
		clean(carray);
	}
	static void clean(chararray* arr) {
		if(arr!= NULL) {
			arr->releaseRef();
		}
	}

	friend vlstring VOLANTE_EXPORT addvlstrings(const char* first, size_t firstLen, const char* second, size_t secondLen);

	friend std::ostream& operator << (std::ostream& os, const vlstring& str);
	friend bool VOLANTE_EXPORT operator == (const char* first, const vlstring& anotherString);

	friend class vlstringbuffer;
	// special vlstring - for static string literal
	vlstring(const char* str, const char* dummy) {
		assert(str == dummy);
		count = strlen(str);
		start = str;
		carray = 0;
	}

protected:
	const char* start;
	size_t count;
	chararray* carray;
	char* ensureCleanFree(size_t size);
public:
	//static const size_type npos = -1;
	enum {
		npos = -1
	};
	//static const char* EMPTY_STR_LITERAL;
	static vlstring EMPTY;
};
////////////////////////////////////////////////////////////
class VOLANTE_EXPORT vlstringliteral : public vlstring {
public:
	vlstringliteral(const char* str) :vlstring(str, str) {
	}
};
////////////////////////////////////////////////////////////
class VOLANTE_EXPORT vlstringbuffer : public vlstring {
public:
	vlstringbuffer() {
	}
	vlstringbuffer(const char* str) :vlstring(str) {
	}
	vlstringbuffer(const char* str, size_t length) : vlstring(str, length){
	}
	vlstringbuffer(const vlstring& from) : vlstring(from.data(), from.length()){
	}
	vlstringbuffer& operator +=(const vlstring& toAdd) {
		return append(toAdd);
	}
	vlstringbuffer& operator +=(char c) {
		return append(c);
	}
	vlstringbuffer& append(const vlstring& toAdd) {
		return append(toAdd.start, toAdd.count);
	}
	vlstringbuffer& append(const char* buffer) {
		return append(buffer, strlen(buffer));
	}
	void reserve(size_t newCapacity);

	vlstringbuffer& append(const char* buffer, size_t bufferLength);
	vlstringbuffer& append(char c);
	vlstringbuffer& append(int count, char c);
	vlstringbuffer& insert(size_t at, const vlstring& toAdd) {
		return insert(at, toAdd.start, toAdd.count);
	}
	vlstringbuffer& insert(size_t at, const char* buffer) {
		return insert(at, buffer, strlen(buffer));
	}
	vlstringbuffer& insert(size_t at, const char* buffer, size_t bufferLength);
	vlstringbuffer& insert(size_t at, char c) {
		return insert(at, &c, 1);
	}
	vlstringbuffer& replace(size_t pos1, size_t num1, const char* buffer) {
		return replace(pos1, num1, buffer, strlen(buffer));
	}
	vlstringbuffer& replace(size_t pos1, size_t num1,  const vlstring& toAdd) {
		return replace(pos1, num1, toAdd.start, toAdd.count);
	}

	vlstringbuffer& replace(size_t pos1, size_t num1, const char* buffer, size_t bufferLength);
	vlstringbuffer& erase(size_t pos1, size_t num1);
	void clear() {
		count = 0;
	}
	char& operator[](size_t index)  {
		return *(getMutableBuffer() + index);
	}
private:
	char* getMutableBuffer()  {
		assert(carray != NULL);
		return (char*)start;
	}
	size_t bufferOffset() {
		return carray == NULL ? 0 : (carray->getCharPtr() - start);
	}
	void ensureFree(size_t bufferLength);
};
///////////////////////////////////////////////////////////////////////////////////////////

vlstring VOLANTE_EXPORT addvlstrings(const char* first, size_t firstLen, const char* second, size_t secondLen);

vlstring VOLANTE_EXPORT operator + (const vlstring& first, char c);
vlstring VOLANTE_EXPORT operator + (const vlstring& first, const char* second);
vlstring VOLANTE_EXPORT operator + (char c, const vlstring& second);
vlstring VOLANTE_EXPORT operator + (const char* first, const vlstring& second);

bool VOLANTE_EXPORT operator == (const char* first, const vlstring& anotherString);

inline std::ostream& operator << (std::ostream& os, const vlstring& str) {
	os.write(str.data(), (int)str.length());
	return os;
}


VOLANTE_NAMESPACE_END

#endif //__VSTRING_H__
