#include "matrix.h"
#include <fstream>

using namespace std;
int main()
{

	int size = 3;

	Matrix m1(size, size);
	Matrix m2(size, size);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			m1[i][j] = i * size + j + 1;
			m2[i][j] = size*size - i * size - j;
		}
	}
	
	m1.print();
	m2.print();

	Matrix m3 = m1 * m2;

	Matrix m4 = m1 * 2;

	Matrix m5 = m1 + m2;

	m3.print();

	m4.print();
	
	m5.print();

	m5[1][1] = 100;
	m5.print();
	
	Matrix m6(3, 4);
	
	ifstream infile;
	infile.open("input");
	infile >> m6;
	infile.close();
	
	//cin >> m6;
	cout << endl << m6 << endl;

	cout << m1 * m6 << endl;

	return 0;
}