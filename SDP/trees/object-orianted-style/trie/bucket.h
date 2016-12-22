#ifndef _BUCKET_H_
#define _BUCKET_H_

#include <cassert>

template <class T>
class Bucket
{
	private:
		T* data;
	public:
		Bucket();
		Bucket(const Bucket<T>& other);
		Bucket<T>& operator=(const Bucket<T>& other);
		~Bucket();
		bool hasData() const;
		const T& getData() const;
		void setData(const T&);
		void deleteData();
};

template <class T>
void Bucket<T>::setData(const T& newData)
{
	if (data != nullptr)
		delete data;
	data = new T(newData);
}

template <class T>
Bucket<T>::Bucket() : data(nullptr) {}

template <class T>
Bucket<T>::Bucket(const Bucket<T>& other)
{
	if (other.hasData())
		setData(other.getData());
	else
		data = nullptr;
}

template <class T>
Bucket<T>& Bucket<T>::operator=(const Bucket<T>& other)
{
	if(this != &other)
	{
		deleteData();
		if (other.hasData())
			setData(other.getData());
		else
			data = nullptr;
	}
	return *this;
}

template <class T>
Bucket<T>::~Bucket()
{
	deleteData();
}

template <class T>
bool Bucket<T>::hasData() const
{
	return data != nullptr;
}

template <class T>
const T& Bucket<T>::getData() const
{
	assert(hasData());
	return *data;
}

template <class T>
void Bucket<T>::deleteData()
{
	delete data;
	data = nullptr;
}

#endif
