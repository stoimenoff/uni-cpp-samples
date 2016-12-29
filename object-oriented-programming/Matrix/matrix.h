#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>

class Matrix
{
	private:
		int rows;
		int columns;
		int **matrix;

		void initArray(int rows, int columns);
		void copyArray(int** array);
		void deleteArray();
		
		class Row
		{
			private:
				int* array;
				int size;
			public:
				Row(int* array, int size);
				int& operator [] (int j);
				int operator [] (int j) const;
		};

	public:
		Matrix(int rows, int columns);
		Matrix(int** array, int rows, int columns);
		Matrix(const Matrix &other);
		Matrix& operator = (const Matrix &other);
		~Matrix();

		Matrix operator * (const Matrix &other) const;
		Matrix operator * (const int &lambda) const;
		Matrix operator + (const Matrix &other) const;

		Row operator [] (int i);
		const Row operator [] (int i) const;
		
		void print() const;

		int getRows() const {return rows;}
		int getColumns() const {return columns;}

		friend std::ostream& operator << (std::ostream& stream, const Matrix& matrix);
		friend std::istream& operator >> (std::istream& stream, Matrix& matrix);

};

#endif
