#ifndef __OBJECTREF_H__
#define __OBJECTREF_H__

VOLANTE_NAMESPACE_BEGIN

/**
 *  Provides object reference counting service. Instances of the class (derived)
 *  can be wrapped by SmartPtr object to create a self deleting smart pointer object.
 *  Objects of this class and derived classes are not thread safe. 
 *
 *  @see SmartPtr
 */
class VOLANTE_EXPORT ObjectRef : public virtual Object {
protected:
	~ObjectRef();
	ObjectRef() {
		refCount = 0;
	}
public :
	void addRef() {
		checkThreadOwner();
		SAFE_INC(refCount);
	}
	void releaseRef() {
		checkThreadOwner();
		if(SAFE_DEC(refCount) == 0) {
			delete this;
		}
	}
	void decRef() {
		if(refCount > 0) {
			SAFE_DEC(refCount);
		}
	}
	
private:
#ifdef CHECK_THREAD_OWNER
	SingleThreadAccess singleThreadAccess;
	void checkThreadOwner() {
		singleThreadAccess.checkThreadOwner(this);
	}
#else 
	void checkThreadOwner() {
	}
#endif 

	REF_COUNT_TYPE refCount;
public:
	int getRefCount() {
		return refCount;
	}
	bool unique() {
		return refCount == 1;
	}
	static void releaseRef(Object* obj) {
		if(obj != NULL) {
			obj->releaseRef();
		}
	}
	static void addRef(Object* obj) {
		if(obj != NULL) {
			obj->addRef();
		}
	}
	//template <class T> friend class ObjectRefPool;

};
/**
 *  Smart pointer class. Instances of ObjectRef wrapped by an object of this class acts 
 *  like smart pointer. The main idea is to make the client code simpler. In particular
 *  the ownership of the object is managed by the SmartPtr class, hence the client need not
 *  delete it. The method of the wrapped object can be called using obj->f() syntax.
 *
 *  @see ObjectRef
 */
template <class T>
class SmartPtr {
public:
	SmartPtr() {
		this->obj = NULL;
	}
	SmartPtr(T* obj) {
		set(obj);
	}
	SmartPtr(const SmartPtr<T>& right)  {	
		set(right.obj);
	}
	SmartPtr<T>& operator=(const SmartPtr<T>& right) {	
		reset(right.obj);
		return (*this);
	}
	SmartPtr<T>& operator=(T* obj) {	
		reset(obj);
		return (*this);
	}

	inline T *operator->() const {	
		if(obj == NULL) {
			//throw TransformNullValueException("Attempt to dereference a null pointer");
		}
		return obj;
	}
	inline T* get() const {
		return obj;
	}
	inline T& operator*() const 	{	
		return (*obj);
	}
	/**
	 * Return true if the referred pointer is NULL.
	 */
	inline bool isNull() const {
		return obj == NULL;
	}
	/*
	operator T*() const {	
		return obj;
	}*/
	/* 	
	template <class P>
	inline operator SmartPtr<P>() const {	
		return SmartPtr<P>(get());
	}*/
	

	inline void reset(T* obj) {
		release();
		set(obj);
	}
	inline void release() {
		if(obj != NULL) {
			obj->releaseRef();
			obj = NULL;
		}
	}
	inline ~SmartPtr() {
		release();
	}
private:
	inline void set(T* obj) {
		this->obj = obj;
		if(obj != NULL) {
			obj->addRef();
		}
	}
protected:
	T* obj;
};
template <class T>
class ObjectPin {
public:
	ObjectPin(T* obj) {
		this->obj = obj;
		obj->addRef();
	}
	~ObjectPin() {
		obj->decRef();;
	}
protected:
	T* obj;
};

typedef SmartPtr <Object> ObjectVal;

VOLANTE_NAMESPACE_END

#endif //__OBJECTREF_H__
