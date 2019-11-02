#pragma once
#include <iostream>
using namespace std;

template <class T>
class SharedPointer
{
public:
	explicit SharedPointer(T* p = 0);
	~SharedPointer();

	SharedPointer(const SharedPointer<T>& sp);
	SharedPointer& operator=(const SharedPointer<T>& sp);

	template <class O>
	SharedPointer(const SharedPointer<O>& sp);

	template <class O> 
	SharedPointer& operator=(const SharedPointer<O>& sp);

	T* operator->() const;
	T& operator*() const;

	T* getPtr() const;
	unsigned int getRefCnt() const;
private:
	template <class O>
	friend class SharedPointer;

	T* mPtr;
	size_t* mpRefCounter;


	// Helper functions
	void releaseCurrentPtr();
	void copyData(const SharedPointer<T>& sp);
	
	template <class O>
	void copyData(const SharedPointer<O>& sp);

	void addRef();
	void removeRef();
	bool lastReference();
	void clearAllocations();
};



// Implementation

template <class T>
SharedPointer<T>::SharedPointer(T* p = 0)
	: mPtr(p), mpRefCounter(NULL)
{
	mpRefCounter = new size_t(p == NULL ? 0 : 1);
}

template <class T>
SharedPointer<T>::~SharedPointer()
{
	releaseCurrentPtr();
}

// Initialize mPtr and mpRefCounter with NULL to allow
// generic code for data copying
template <class T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& sp)
	: mPtr(NULL), mpRefCounter(NULL)
{
	copyData(sp);
}

template <class T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& sp)
{
	copyData(sp);

	return *this;
}

// Initialize mPtr and mpRefCounter with NULL to allow
// generic code for data copying
template <class T>
template <class O>
SharedPointer<T>::SharedPointer(const SharedPointer<O>& sp)
	: mPtr(NULL), mpRefCounter(NULL)
{
	copyData(sp);
}

template <class T>
template <class O>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<O>& sp)
{
	copyData(sp);

	return *this;
}

template <class T>
T* SharedPointer<T>::operator->() const
{
	return mPtr;
}

template <class T>
T& SharedPointer<T>::operator*() const
{
	return *mPtr;
}

template <class T>
T* SharedPointer<T>::getPtr() const
{
	return mPtr;
}

template <class T>
unsigned int SharedPointer<T>::getRefCnt() const
{
	return *mpRefCounter;
}

template <class T>
void SharedPointer<T>::releaseCurrentPtr()
{
	if (mPtr == NULL)
		return;

	removeRef();

	if (lastReference())
		clearAllocations();
}

template <class T>
void SharedPointer<T>::copyData(const SharedPointer<T>& sp)
{
	releaseCurrentPtr();

	mPtr = sp.mPtr;
	mpRefCounter = sp.mpRefCounter;

	if (mPtr != NULL)
		addRef();
}

template <class T>
template <class O>
void SharedPointer<T>::copyData(const SharedPointer<O>& sp)
{
	releaseCurrentPtr();

	mPtr = sp.mPtr;
	mpRefCounter = sp.mpRefCounter;

	if( mPtr != NULL)
		addRef();
}

template <class T>
void SharedPointer<T>::addRef()
{
	(*mpRefCounter)++;
}

template <class T>
void SharedPointer<T>::removeRef()
{
	// No need for NULL check since this is called 
	// only of mPtr is not NULL, their c-allocation
	// is parallel
	if (*mpRefCounter != 0)
		(*mpRefCounter)--;
}

template <class T>
bool SharedPointer<T>::lastReference()
{
	return (*mpRefCounter == 0);
}

template <class T>
void SharedPointer<T>::clearAllocations()
{
	if (mPtr != NULL)
		delete mPtr;

	if (mpRefCounter != NULL)
		delete mpRefCounter;
}
