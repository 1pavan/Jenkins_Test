#ifndef __CLASS_H__
#define __CLASS_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT Class {
public:
	Class(const std::type_info& type) : type(type){
	}
	vstring getName() const;
	bool operator == (const Class& cls) const;
	operator vstring() const {
		return vstring(type.name());
	}


	template <class T>
	static Class getClass(const T& t) {
		return Class(typeid(t));
	}
	template <class T>
	static Class getClass() {
		return Class(typeid(T));
	}
private:
	const std::type_info& type;
};

/*
template <class T>
class polymorphic_cast {
	T value;
	public:
	polymorphic_cast(Object* obj) {
		if(!(value = dynamic_cast<T>(obj))) {
			throw ClassCastException("Cannot cast " + obj->toString()  + " to " + Class::getClass<T>().getName());
		}
	}
	operator T() const {
		return value;
	}
};*/

VOLANTE_NAMESPACE_END

#endif //__CLASS_H__
