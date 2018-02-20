#ifndef __BYTEARRAYINPUTSOURCE_H__
#define __BYTEARRAYINPUTSOURCE_H__

#include "AbstractRawMessage.h"

VOLANTE_NAMESPACE_BEGIN
/*
class VOLANTE_EXPORT  ByteArrayInputSource : public AbstractRawMessage {
public:
	ByteArrayInputSource(const Binary& binary) {
		this->source = (const char*)binary.data();
		this->length = binary.length();
		this->own = false;
	}
	ByteArrayInputSource(const char* source, int length, bool own) {
		this->source = source;
		this->length = length;
		this->own = own;
	}
	ByteArrayInputSource(char* source, int length, bool own) {
		this->source = source;
		this->length = length;
		this->own = own;
	}
	ByteArrayInputSource(char* source, int length) {
		this->source = source;
		this->length = length;
		this->own = true;
	}
	~ByteArrayInputSource() {
		if(own) {
			delete[] (const_cast<char*>(source));
		}
	}
	const char* getAsBytes(int& length)  {
		length = this->length;
		return source;
	}
	int length;
	const char* source;
	bool own;
};*/

class VOLANTE_EXPORT  ByteArrayInputSource : public AbstractRawMessage {
public:
	ByteArrayInputSource(const Binary& binary) : value(binary) {
		this->own = false;
	}
	ByteArrayInputSource(const char* source, int length, bool own) : value(source, length, own){
		this->own = own;
	}
	ByteArrayInputSource(char* source, int length, bool own) : value(source, length, own) {
		this->own = own;
	}
	ByteArrayInputSource(char* source, int length) : value(source, length, true) {
		this->own = true;
	}
	~ByteArrayInputSource() {
		if(own) {
			delete ((char*)value.data());
		}
	}
	const char* getAsBytes(int& length)  {
		length = (int)value.size();
		return value.data();
	}
	Binary value;
	bool own;
};
class VOLANTE_EXPORT StringInputSource : public AbstractRawMessage {
public:
	StringInputSource(const vstring& str) {
		this->source = str;
	}
	const char* getAsBytes(int& length)  {
		length = (int)source.length();
		return source.data();
	}
	vstring source;
};

VOLANTE_NAMESPACE_END

#endif //__BYTEARRAYINPUTSOURCE_H__
