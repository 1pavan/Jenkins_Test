#ifndef __CHARSEQUENCE_H__
#define __CHARSEQUENCE_H__

VOLANTE_NAMESPACE_BEGIN

#ifdef VOLANTE_USE_STD_STRING
class VOLANTE_EXPORT CharSequence {
public:
	CharSequence() {
		this->characters = NULL;
		this->count = 0;
	}
	CharSequence(const char* characters,  int count) {
		this->characters = characters;
		this->count = count;
	}
	int getLength() const {
		return count;
	}
	const char* data() const {
		return characters;
	}
	char at(int i) const{
		return characters[i];
	}
	inline char operator[] (int index) const {
		return characters[index];
	}
	CharSequence span(const CharSequence& endPoint) const;
	bool operator == (const vstring& with) const;

	inline operator vstring() const {
		return vstring(characters, count);
	}
	inline vstring toString() const {
		return vstring(characters, count);
	}
	void toString(vstring& str) const {
		str.assign(characters, count);
	}
	int distance(const CharSequence& subsequence) const;
	int atoi(const char *nptr, const char *eptr) const;
	bool empty() const {
		return count == 0;
	}
	int toInt() const {
		return atoi(characters, characters + count);
	}
	int toInt(int start, int length) const {
		return atoi(characters + start, characters + start + length);
	}
	int find(const char* toFind) const;

	int find(int start, char c) const;
	int find(char c) const {
		return find(0, c);
	}

	void substr(int start, int length, CharSequence& assignTo) const {
		assignTo.characters = characters + start;
		assignTo.count= length;
	}
	void substr(int start, CharSequence& assignTo) const {
		assignTo.characters = characters + start;
		assignTo.count= count - start;
	}

	CharSequence substr(int start, int length) const {
		return CharSequence(characters + start, length);
	}
	CharSequence substr(int start) const {
		return CharSequence(characters + start, count - start);
	}
	inline size_t size()const {
		return count;
	}
	inline size_t length()const {
		return size();
	}
private:
	const char* characters;
	int count;
public:
	static CharSequence EMPTY;
};

#else
typedef vlstring CharSequence;
#endif

VOLANTE_NAMESPACE_END

#endif //__CHARSEQUENCE_H__


