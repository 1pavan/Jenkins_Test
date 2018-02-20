#ifndef __COLLECTIONS_H__
#define __COLLECTIONS_H__
#include "Object.h"
#include <deque>
VOLANTE_NAMESPACE_BEGIN


template <class Container, class T>
class VList :  public Object {
	typedef VList<Container, T> ListClass;
	typedef Container ListBase;
	class ListImpl : public Container, public ObjectRef {
	};
	typedef SmartPtr<ListImpl> ListImplPtr;
	ListImplPtr listObj;
public:
	VList() {
  	 listObj = new ListImpl();
		 listObj->reserve(10);
	}
	VList(const VList<Container, T>& copyFrom)  {
		listObj = copyFrom.listObj;
	}

	~VList() {
	}

	ListClass& operator = (const ListClass& copyFrom) {
		listObj = copyFrom.listObj;
		return *this;
	}

	ListClass& add(const T& element) {
		listObj->push_back(element);
		return *this;
	}

	void add(int index, const T& element) {
		listObj->insert(getiteratorAt(index), element);
	}

	Object* clone() const {
		return new ListClass(*this);
	}

	ListClass& addAll(const ListClass& list) {
		for(int i =0; i < list.size(); ++i) {
			add(list.get(i));
		}
		return *this;
	}

	ListClass& addAll(T* values, int start, int count) {
		for(int i =start; i < start + count; ++i) {
			add(values[i]);
		}
		return *this;
	}

	const T& get(int index) const {
		return listObj->at(index);
	}

	const T& getValue(int index) const {
		return listObj->at(index);
	}

	int size() const {
		return (int)listObj->size();
	}

	void clear() {
		listObj->clear();
	}

	T removeElementAt(int index) {
		const T& old = get(index);
		listObj->erase(getiteratorAt(index));
		return old;
	}

	T set(int index, const T& element) {
		const T& old = get(index);
		operator[](index) = element;
		return old;
	}

	bool contains(const T& element) const {
		return indexOf(element) != -1;
	}
	bool intersects(const ListClass& thatList) const {
		int size1 = size();
		for(int j = 0; j < thatList.size(); ++j) {
			const T& element = thatList.get(j);
			for(int i = 0; i < size1; ++i) {
				if(get(i) == element) { 
					return true;
				}
			}
		}
		return false;
	}

	int indexOf(const T& element) const {
		for(int i = 0; i < size(); ++i) {
			if(get(i) == element) { 
				return i;
			} 
		}
		return -1;
	}

	int lastIndexOf(const T& element) const {
		for(int i = size()-1; i >=0; --i) {
			if(get(i) == element) { 
				return i;
			} 
		}
		return -1;
	}

	bool equals(const ListClass& thatList) const {
		if(this == &thatList) { 
			return true; 
		} 
		if(size() != thatList.size()) {
			return false;
		}
		int nsize = size();
		for(int i =0; i < nsize ; ++i) {
			if(get(i) != thatList.get(i)) { 
				return false; 
			}
		}
		return true;
	}

	T& operator[](int index) {
		return listObj->at(index);
	}
	
	const T& operator[](int index) const {
		return listObj->at(index);
	}


	int compareTo(const ListClass& thatList) const {
		if(this == &thatList) { 
			return 0; 
		} 
		int size1 = size();
		int size2 = thatList.size();
		int nsize = size1 < size2 ? size1 : size2;
		for(int i =0; i < nsize; ++i) {
			const T&  v1 = get(i); 
			const T&  v2 = thatList.get(i); 
			if( v1 < v2) { 
				return -1; 
			}
			if( v1 > v2) { 
				return 1; 
			}
		}
		return size1-size2;
	}
	/*
	int hashCode() const {
		int hash = 1;
		int size = size();
		for(int i = 0; i < size; ++i) {
			hash = 31*hash + (int)get(i);
		}
		return hash;
	}*/

	vstring toString() const {
		vstringbuffer buf;
		int nsize = size();
		buf.append("[");
		for(int i = 0; i < nsize; ++i) {
			const T&  c = get(i);
			//ObjectList obj;
			//obj.add(c);
			buf.append(valueToString(c));
			if(i < nsize -1) {
				buf.append(", ");
			}
		}
		buf.append("]");
		return buf;
	}

public:    

	typedef typename Container::const_iterator const_iterator;
	typedef typename ListBase::iterator iterator;
	const_iterator getiteratorAt(int index) const {
		return begin() + index;
	}
	iterator getiteratorAt(int index)  {
		return listObj->begin() + index;
	}
	iterator begin() {
		return listObj->begin();
	}
	iterator end() {
		return listObj->end();
	}
	const_iterator begin() const {
		return listObj->begin();
	}
	const_iterator end() const {
		return listObj->end();
	}
	iterator erase(iterator it) {
		return listObj->erase(it);
	}
};

template <class T>
class SimpleDeque : public  std::deque<T> {
public:
	void reserve(size_t count) {}
};

typedef VList<std::vector<ISODateTime>, ISODateTime>		CalendarList;
typedef VList<std::vector<DateTime>, DateTime>		DateList;
typedef VList<std::vector<vstring>, vstring>		StringList;
typedef VList<std::vector<int>, int>			IntList;
typedef VList<std::vector<dlong>, dlong>		LongList;
typedef VList<std::vector<float>, float>		FloatList;
typedef VList<std::vector<double>, double>		DoubleList;
typedef VList<SimpleDeque<bool>, bool>			BooleanList;
typedef VList<std::vector<char>, char>			CharList;
typedef VList<std::vector<BigInteger>, BigInteger>	BigIntegerList;
typedef VList<std::vector<BigDecimal>, BigDecimal>	BigDecimalList;
typedef VList<std::vector<Binary>, Binary>	  BinaryList;
//typedef VList<std::vector<RawMessage>, RawMessage>	  RawMessageList;

template class VOLANTE_EXPORT VList<std::vector<DateTime>, DateTime>;
template class VOLANTE_EXPORT VList<std::vector<vstring>, vstring>;
template class VOLANTE_EXPORT VList<std::vector<int>, int>;
template class VOLANTE_EXPORT VList<std::vector<dlong>, dlong>;
template class VOLANTE_EXPORT VList<std::vector<float>, float>;
template class VOLANTE_EXPORT VList<std::vector<double>, double>;
template class VOLANTE_EXPORT VList<SimpleDeque<bool>, bool>;
template class VOLANTE_EXPORT VList<std::vector<char>, char>;
template class VOLANTE_EXPORT VList<std::vector<BigInteger>, BigInteger>;
template class VOLANTE_EXPORT VList<std::vector<BigDecimal>, BigDecimal>;
template class VOLANTE_EXPORT VList<std::vector<Binary>, Binary>;

VOLANTE_NAMESPACE_END



#endif //__COLLECTIONS_H__
