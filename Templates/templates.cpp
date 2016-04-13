#include <iostream>

template <typename T>
using mapFn = T (*) (T);


typedef int Board[3][3];

template <typename T>
using Board2 = T[3][3];

typedef bool (*comparatorPointer) (int, int);

template <typename T>
using Comparator = bool (*) (T, T);


template <typename T>
bool azsampesho(T a, T b)
{
	return a < b;
}

template <typename T>
int findExtremum (T arr [] , int arrSize , Comparator<T> compare)
{
	int indexMax = 0;
	for (int i = 1; i < arrSize ; i ++)
		if ( compare ( arr [indexMax], arr [i]))
			indexMax = i;
	return indexMax;
}

int main()
{

	int ia [] = {1 ,3 ,5};
	double da [] = {1.7 ,6.5 ,3.4 ,5.8};

	std::cout << findExtremum<int>(ia ,3 , azsampesho<int>) << std::endl;
	std::cout << findExtremum<double>(da ,4 , azsampesho<double>) << std::endl;

	return 0;
}