#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <cassert>

template <class T>
class Vector
{
	public:
		Vector(unsigned int capacity = 4);
		Vector(const Vector<T>& other);
		Vector<T>& operator = (const Vector<T>& other);
		~Vector();

		T& operator [] (unsigned int index);
		T operator [] (unsigned int index) const;

		void pushBack(T element);
		bool popBack();
		bool insertAt(unsigned int index, T element);
		bool removeAt(unsigned int index);
		bool empty() const;
		bool full() const;
		int Size() const;

	private:
		T* buffer;
		unsigned int size;
		unsigned int capacity;
		void resize(unsigned int new_capacity);
		void allocateBuffer(unsigned int new_capacity);
		void deallocateBuffer();
		void copyBuffer(const T* otherBuffer);
};

/*Private helper functions*/
template <class T>
void Vector<T>::allocateBuffer(unsigned int new_capacity)
{
	capacity = new_capacity;
	buffer = new T[capacity];
}

template <class T>
void Vector<T>::deallocateBuffer()
{
	delete[] buffer;
	size = 0;
	capacity = 0;
}

template <class T>
void Vector<T>::copyBuffer(const T* otherBuffer)
{
	for (int i = 0; i < size; ++i)
	{
		buffer[i] = otherBuffer[i];
	}
}

template <class T>
void Vector<T>::resize(unsigned int new_capacity)
{
	T* oldBuffer = buffer;
	allocateBuffer(new_capacity);
	copyBuffer(oldBuffer);
	delete[] oldBuffer;
}

/*Constructors*/
template <class T>
Vector<T>::Vector(unsigned int capacity)
{
	allocateBuffer(capacity);
	size = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
	allocateBuffer(other.capacity);
	size = other.size;
	copyBuffer(other.buffer);
}

/*Assignment operator*/
template <class T>
Vector<T>& Vector<T>::operator = (const Vector<T>& other)
{
	if (this != &other)
	{
		deallocateBuffer();
		allocateBuffer(other.capacity);
		size = other.size;
		copyBuffer(other.buffer);
	}
	return *this;
}
/*Destructor*/
template <class T>
Vector<T>::~Vector()
{
	deallocateBuffer();
}
/*[] operator*/
template <class T>
T& Vector<T>::operator [] (unsigned int index)
{
	assert(index >= 0 && index < size);
	return buffer[index];
}

template <class T>
T Vector<T>::operator [] (unsigned int index) const
{
	assert(index >= 0 && index < size);
	return buffer[index];	
}

/*Public methods*/
template <class T>
bool Vector<T>::full() const
{
	return size == capacity;
}

template <class T>
bool Vector<T>::empty() const
{
	return size == 0;
}

template <class T>
int Vector<T>::Size() const
{
	return size;
}

template <class T>
void Vector<T>::pushBack(T element)
{
	if (full())
	{
		resize(2 * capacity);
	}
	buffer[size] = element;
	size += 1;
}

template <class T>
bool Vector<T>::popBack()
{
	if(empty())
	{
		return false;
	}
	size -= 1;
	return true;
}

template <class T>
bool Vector<T>::insertAt(unsigned int index, T element)
{
	if (index >= size)	
	{
		return false;
	}
	if (full())
	{
		resize(2 * capacity);
	}
	for (int i = size; i > index; --i)
	{
		buffer[i] = buffer[i - 1];
	}
	buffer[index] = element;
	size += 1;
	return true;
}

template <class T>
bool Vector<T>::removeAt(unsigned int index)
{
	if (index >= size)	
	{
		return false;
	}
	for (int i = index; i < size - 1; ++i)
	{
		buffer[i] = buffer[i + 1];
	}
	size -= 1;
	return true;
}

/*Output stream operator*/

template <class T>
std::ostream& operator << (std::ostream& out, const Vector<T>& vector)
{
	for (int i = 0; i < vector.Size(); ++i)
	{
		out << vector[i] << " ";
	}
	return out;
}

#endif