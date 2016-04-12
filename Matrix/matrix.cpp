#include "matrix.h"
#include <iostream>

void Matrix::initArray(int rows, int columns)
{
	rows = (rows <= 0) ? 1 : rows;
	columns = (columns <= 0) ? 1 : columns;

	this->rows = rows;
	this->columns = columns;
	matrix = new int*[rows];
	for (int i = 0; i < rows; ++i)
	{
		matrix[i] = new int[columns];
	}
}
void Matrix::copyArray(int** array)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			matrix[i][j] = array[i][j];
		}
	}
}
void Matrix::deleteArray()
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
Matrix::Matrix(int rows, int columns)
{
	initArray(rows, columns);
}
Matrix::Matrix(int** array, int rows, int columns)
{
	initArray(rows, columns);
	copyArray(array);
}
Matrix::Matrix(const Matrix &other)
{
	initArray(other.rows, other.columns);
	copyArray(other.matrix);
}
Matrix::~Matrix()
{
	deleteArray();
}
Matrix& Matrix::operator = (const Matrix &other)
{
	if (this != &other)
	{
		deleteArray();
		initArray(other.rows, other.columns);
		copyArray(other.matrix);
	}
	return *this;
}
Matrix Matrix::operator * (const Matrix &other) const
{
	if (columns != other.rows)
	{
		std::cout << "Multiplication error, sizes differ!" << std::endl;
		//exit(1);
	}

	Matrix result(rows, other.columns);
	int cell;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < other.columns; ++j)
		{
			cell = 0;
			for (int k = 0; k < other.rows; ++k)
			{
				cell += (matrix[i][k] * other.matrix[k][j]);
			}
			result.matrix[i][j] = cell;
		}
	}
	return result;
}

Matrix Matrix::operator * (const int &lambda) const
{
	Matrix result(rows, columns);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			result.matrix[i][j] = matrix[i][j] * lambda;
		}
	}
	return result;
}
Matrix Matrix::operator + (const Matrix &other) const
{
	if (rows != other.rows || columns != other.columns)
	{
		std::cout << "Addition error, sizes differ!" << std::endl;
		//exit(1);
	}

	Matrix result(rows, columns);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
		}
	}
	return result;
}
Matrix::Row::Row(int* array, int size)
{
	this->array = array;
	this->size = size;
}
int& Matrix::Row::operator [] (int j)
{
	if (j >= size || j < 0)
	{
		std::cout << "Index out of bounds !" << std::endl;
		//exit(1);
	}
	return array[j];
}
int Matrix::Row::operator [] (int j) const
{
	if (j >= size || j < 0)
	{
		std::cout << "Index out of bounds !" << std::endl;
		//exit(1);
	}
	return array[j];
}
Matrix::Row Matrix::operator [] (int i)
{
	if (i >= rows || i < 0)
	{
		std::cout << "Index out of bounds !" << std::endl;
		//exit(1);
	}
	return Row(matrix[i], columns);
}
const Matrix::Row Matrix::operator [] (int i) const
{
	if (i >= rows || i < 0)
	{
		std::cout << "Index out of bounds !" << std::endl;
		//exit(1);
	}
	return Row(matrix[i], columns);
}
void Matrix::print() const
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
//stream operators
std::ostream& operator << (std::ostream& stream, const Matrix& matrix)
{
	for (int i = 0; i < matrix.rows; ++i)
	{
		for (int j = 0; j < matrix.columns; ++j)
		{
			stream << matrix[i][j] << " ";
		}
		stream << std::endl;
	}
	stream << std::endl;
	return stream;
}

std::istream& operator >> (std::istream& stream, Matrix& matrix)
{
	for (int i = 0; i < matrix.rows; ++i)
	{
		for (int j = 0; j < matrix.columns; ++j)
		{
			stream >> matrix[i][j];
		}
	}
	return stream;
}
