#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

template <typename T>
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
		bool contains(const T& element) const;
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
template <typename T>
void Vector<T>::allocateBuffer(unsigned int new_capacity)
{
	capacity = new_capacity;
	buffer = new T[capacity];
}

template <typename T>
void Vector<T>::deallocateBuffer()
{
	delete[] buffer;
	size = 0;
	capacity = 0;
}

template <typename T>
void Vector<T>::copyBuffer(const T* otherBuffer)
{
	for (int i = 0; i < size; ++i)
	{
		buffer[i] = otherBuffer[i];
	}
}

template <typename T>
void Vector<T>::resize(unsigned int new_capacity)
{
	T* oldBuffer = buffer;
	allocateBuffer(new_capacity);
	copyBuffer(oldBuffer);
	delete[] oldBuffer;
}

/*Constructors*/
template <typename T>
Vector<T>::Vector(unsigned int capacity)
{
	allocateBuffer(capacity);
	size = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	allocateBuffer(other.capacity);
	size = other.size;
	copyBuffer(other.buffer);
}

/*Assignment operator*/
template <typename T>
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
template <typename T>
Vector<T>::~Vector()
{
	deallocateBuffer();
}
/*[] operator*/
template <typename T>
T& Vector<T>::operator [] (unsigned int index)
{
	if (index < 0 || index >= size)
	{
		//exception
		//return 0;
	}
	return buffer[index];
}

template <typename T>
T Vector<T>::operator [] (unsigned int index) const
{
	if (index < 0 || index >= size)
	{
		//exception
		//return 0;
	}
	return buffer[index];	
}

/*Public methods*/
template <typename T>
bool Vector<T>::full() const
{
	return size == capacity;
}

template <typename T>
bool Vector<T>::empty() const
{
	return size == 0;
}

template <typename T>
int Vector<T>::Size() const
{
	return size;
}

template <typename T>
void Vector<T>::pushBack(T element)
{
	if (full())
	{
		resize(2 * capacity);
	}
	buffer[size] = element;
	size += 1;
}

template <typename T>
bool Vector<T>::popBack()
{
	if(empty())
	{
		return false;
	}
	size -= 1;
	return true;
}

template <typename T>
bool Vector<T>::insertAt(unsigned int index, T element)
{
	if (index < 0 || index >= size)
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

template <typename T>
bool Vector<T>::removeAt(unsigned int index)
{
	if (index < 0 || index >= size)
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

template <typename T>
bool Vector<T>::contains(const T& element) const
{
	for (int i = 0; i < size; ++i)
	{
		if (buffer[i] == element)
		{
			return true;
		}
	}
	return false;
}
/*Output stream operator*/

template <typename T>
std::ostream& operator << (std::ostream& out, const Vector<T>& vector)
{
	for (int i = 0; i < vector.Size(); ++i)
	{
		out << vector[i] << std::endl;
	}
	return out;
}

template <typename T>
using Comparator = bool (*) (const T&, const T&);

template <typename T>
using Filter = bool (*) (const T&);

template <typename T, typename M>
using ParamFilter = bool (*) (const T&, const M&);

template <typename T>
using Map = T (*) (T);

template <typename T>
void sortVector(Vector<T> &vector, Comparator<T> isGreater, bool reverse = false)
{
	int minIndex = 0;
	for (int i = 0; i < vector.Size(); ++i)
	{
		minIndex = i;
		for (int j = i; j < vector.Size(); ++j)
		{
			if (reverse ^ isGreater(vector[minIndex], vector[j]))
			{
				minIndex = j;
			}
		}
		T tmp = vector[minIndex];
		vector[minIndex] = vector[i];
		vector[i] = tmp;
	}
}

template <typename T>
Vector<T> filterVector(const Vector<T> &vector, Filter<T> predicate)
{
	Vector<T> filtred;
	for (int i = 0; i < vector.Size(); ++i)
	{
		if (predicate(vector[i]))
		{
			filtred.pushBack(vector[i]);
		}
	}
	return filtred;
}

template <typename T>
void mapVector(Vector<T> &vector, Map<T> mapper)
{
	for (int i = 0; i < vector.Size(); ++i)
	{
		vector[i] = mapper(vector[i]);
	}
}

template <typename T, typename M>
Vector<T> paramFilterVector(const Vector<T> &vector, ParamFilter<T, M> predicate, const M &param)
{
	Vector<T> filtred;
	for (int i = 0; i < vector.Size(); ++i)
	{
		if (predicate(vector[i], param))
		{
			filtred.pushBack(vector[i]);
		}
	}
	return filtred;
}

#endif