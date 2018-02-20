#ifndef __BINARY_H__
#define __BINARY_H__

#include <assert.h>
#include <algorithm>

VOLANTE_NAMESPACE_BEGIN
/*
class bytearray {
private:
	bytearray(size_t len, char* buffer) : len(len), buffer((vbyte*)buffer), refCount(1){
	}
protected:
	~bytearray();
public:
	inline vbyte operator[] (size_t index) const {
		assert(index < len);
		return buffer[index];
	}
	inline vbyte byteAt (size_t index) const {
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
		++refCount;
	}
	inline void releaseRef() {
		checkThreadOwner();
		if(--refCount == 0) {
			delete this;
		}
	}
	vbyte* getBytePtr() const {
		return buffer;
	}
	static bytearray* create(size_t length) {
		char* buffer = new char[length + sizeof(bytearray)];
		return new (buffer) bytearray(length, buffer + 	sizeof(bytearray));
	}
	static bytearray* resize(bytearray* copyFrom, size_t length);
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

	vbyte* buffer;
	size_t len;
	int refCount;
};*/
typedef chararray bytearray;
class VOLANTE_EXPORT Binary {
public:
	Binary() {
		count = 0;
		start = (vbyte*)"";
		carray = 0;
	}
	Binary(const vstring& str);
	Binary(size_t size) {
		count = size;
		carray = bytearray::create(count + 1);
		start = carray->getPtr();
	}
	Binary(const Binary& from) {
		copyToThis(from);
	}
	Binary(const char* str, size_t length) {
		init((vbyte*)str, length);
	}
	Binary(const char* str, size_t length, bool noCopy) {
		if(noCopy) {
			count = length;
			start = str;
			carray = 0;
		}
		else {
			init((vbyte*)str, length);
		}
	}
	/*
	Binary(const vbyte* str, size_t length) {
		init(str, length);
	}*/
	Binary(size_t length, char copyChar) {
		count = length;
		carray = bytearray::create(count + 1);
		start = carray->getPtr();
		memset(carray->getPtr(), copyChar, count);
	}
	~Binary() {
		clean();
	}
	const Binary& operator = (const Binary& from) {
		return assign(from);
	}
	Binary& assign(const Binary& from) {
		bytearray * oldArray = carray;
		copyToThis(from);
		clean(oldArray);
		return *this;
	}

	Binary& assign(const vbyte* from, size_t length) {
		bytearray * oldArray = carray;
		init(from, length);
		clean(oldArray);
		return *this;
	}
	void init(const vbyte* str, size_t length) {
		count = length;
		carray = bytearray::create(count + 1);
		start = carray->getPtr();
		memcpy(carray->getPtr(), str, count);
		//trait_copy(carray->getPtr(), str, count);
	}
	void copyToThis(const Binary& from) {
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
	static void clean(bytearray* arr) {
		if(arr!= NULL) {
			arr->releaseRef();
		}
	}
	bool empty() const {
		return count == 0;
	}
	const vbyte* data() const {
		return start;
	}
	size_t size() const {
		return count;
	}
	int at(size_t index) const {
		return (signed char)(*(start + index) & 0xff);
	}
	size_t length() const {
		return count;
	}
	vbyte operator[](size_t index) const {
		return start[index];
	}
	void set(size_t index, vbyte value) const{
		(const_cast <vbyte*>(start))[index] = value;
	}
	Binary operator + (const Binary& toAdd) const {
		Binary toRet(length() + toAdd.length());
		memcpy((void*)toRet.start, start, length());
		memcpy((void*)(toRet.start  + length()), toAdd.start, toAdd.length());
		return toRet;
	}
	Binary sub(int offset, int subsize) const {
		Binary toRet(subsize);
		memcpy((void*)toRet.start, start + offset, subsize);
		return toRet;
	}
	bool operator == (const Binary& str) const;
	bool operator != (const Binary& str) const;
	bool operator < (const Binary& str) const;
	bool operator > (const Binary& str) const;

	vstring toString() const {
		return toASCIIString();
	}
	vstring toASCIIString() const;
	vstring toHexString() const;
	vstring toBase64String() const;

	static Binary fromHexString(const vstring& hexStr);
	static Binary fromBase64String(const vstring& base64Str);
protected:
	const vbyte* start;
	size_t count;
	bytearray* carray;
	friend class HexBinary;
	static vbyte* EMPTY_BIN_LITERAL;
};

VOLANTE_NAMESPACE_END

#endif //__BINARY_H__
