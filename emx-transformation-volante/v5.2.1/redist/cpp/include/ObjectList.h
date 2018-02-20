#ifndef __OBJECTLIST_H__
#define __OBJECTLIST_H__


VOLANTE_NAMESPACE_BEGIN

template<class T>
class VOLANTE_EXPORT ArrayList {
public:
	ArrayList() {
		_values = NULL;
		_size = 0;
		_capacity = 0;
	}
	~ArrayList() {
		delete [] _values;
	}
	void reserve(size_t count) {
		ensureFree(count);
	}
	T& at(size_t index) const {
		return _values[index];
	}
	T& operator[](size_t index) const{
		return at(index);
	}
	void add(const T& toAdd) {
		push_back(toAdd);
	}
	void push_back(const T& toAdd) {
		ensureFree(1);
		_values[_size++] = toAdd;
	}
	const T& top() {
		return _values[_size-1];
	}

	void pop_back() {
		if(_size > 0) {
			--_size;
		}
	}
	size_t size() const {
		return _size;
	}
	void clear() {
		_size = 0;
	}
private:
	void ensureFree(size_t count) {
		size_t reqSize = _size + count;
		if(reqSize >= _capacity) {
			size_t newSize = _capacity + (count < 10 ? 10 : count); 
			T* newValues = new T[newSize];
			for(size_t i =0; i<_size; ++i) {
				newValues[i] = _values[i];
			}
			delete [] _values;
			_values = newValues;
			_capacity = newSize;
		}
	}
	T* _values;
	size_t _size;
	size_t _capacity;
};

class VOLANTE_EXPORT ObjectListRef : public ObjectRef {
	typedef ArrayList<Object*> ListImpl;
	ListImpl listObj;
	ObjectListRef() {
		listObj.reserve(10);
	}
	~ObjectListRef();
	ObjectListRef(const ObjectListRef& copyForm);
	void clear();
	size_t size() const{
		return listObj.size();
	}
	void add(Object* obj);
	void add(const Object& o) {
		add(o.clone());
	}

	Object* at(int index) const {
		return listObj.at(index);
	}
	Object* operator[](int index) const{
		return listObj.at(index);
	}
	friend class ObjectList;
};
typedef SmartPtr<ObjectListRef> ObjectListPtr;

class VOLANTE_EXPORT ObjectList : public Object {
public:
	ObjectList();
	ObjectList(const ObjectList& copyFrom);
	ObjectList& operator = (const ObjectList& copyFrom);
	~ObjectList();
	ObjectList(int val);
	ObjectList(const vstring& val);
	ObjectList(const Binary& val);
	ObjectList(const char* val);
	ObjectList(Object* val);

	ObjectList(const char* val1, const char* val2);
	ObjectList(int val1, const vstring& val2);
	ObjectList(const vstring& val1, int val2);
	ObjectList(const vstring& val1, const vstring& val2);
	ObjectList& add(int val);
	ObjectList& add(dlong val);
	ObjectList& add(float val);
	ObjectList& add(double val);
	ObjectList& add(char val);
	ObjectList& add(bool val);
	ObjectList& add(const vstring& val);
	ObjectList& add(const Binary& val);
	ObjectList& add(const BigInteger& val);
	ObjectList& add(const BigDecimal& val);
	ObjectList& add(const char* val);
	ObjectList& add(const DateTime& val);
	ObjectList& add(Object* val);
	ObjectList& add(const Object& val);
	Object* at (int index) const;
	Object* operator[] (int index) const;
	int size() const;
	Object* get(int index) const {
		return at(index);
	}
	Object*  getValue(int index) const {
		return at(index);
	}
	void clear();
	vstring toString() const;

	Object* clone() const {
		return new ObjectList(*this);
	}

private:
	void addObject0(Object* val);
	ObjectListPtr getListPtr() const;
	ObjectListPtr getListPtrForChange();
	mutable ObjectListPtr listRef;
};
VOLANTE_NAMESPACE_END

#endif //__OBJECTLIST_H__
