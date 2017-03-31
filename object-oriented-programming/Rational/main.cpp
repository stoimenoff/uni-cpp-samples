#include "rational.h"
using namespace std;


Rational evaluatePolynom(Rational coefficients[], int n, Rational x)
{
	Rational result;
	for (int i = 0; i <= n; ++i)
	{
		result += coefficients[i] * (x ^ (n - i));
	}
	return result;
}

int main()
{
	Rational r1(2, 3), r2(3, 4);

	cout << "r1 = " << r1 << endl << endl;
	cout << "r2 = " << r2 << endl << endl;

	Rational r3 = r1 + r2;

	cout << "r3 = r1 + r2 = " << r3 << endl << endl;

	Rational r4 = r1 + 10;

	cout << "r4 = r1 + 10 = " << r4 << endl << endl;
	cout << "-r4 = " << -r4 << endl;

	cout << "r1 * 2 = " << r1 * 2 << endl << endl;
	cout << "r1 + 2 = " << r1 + 2 << endl << endl;
	cout << "r1 - 2 = " << r1 - 2 << endl << endl;
	cout << "r1 / 2 = " << r1 / 2 << endl << endl;

	cout << "2 * r1 = " << 2 * r1 << endl << endl;
	cout << "2 + r1 = " << 2 + r1 << endl << endl;
	cout << "2 - r1 = " << 2 - r1 << endl << endl;
	cout << "2 / r1 = " << 2 / r1 << endl << endl;

	cout << "r1 * r2 = " << r1 * r2 << endl << endl;
	cout << "-r1 / r4 = " << -r1 / r4 << endl << endl;
	cout << "-r1 + r4 = " << -r1 + r4 << endl << endl;
	cout << "-r1 - r4 = " << -r1 - r4 << endl << endl;

	cout << "r1 ^ 3 = " << (r1 ^ 3) << endl << endl;
	cout << "r1 ^ 0 = " << (r1 ^ 0) << endl << endl;

	Rational r5 = 10;
	//cin >> r5;
	cout << "r5 = " << r5 << endl << endl;
	cout << "r5++ " << r5++ << endl << endl;
	cout << "++r5 " << ++r5 << endl << endl;
	cout << "r5-- " << r5-- << endl << endl;
	cout << "--r5 " << --r5 << endl << endl;
	cout << "r5 = " << r5 << endl << endl;

	Rational coefficients[] = {r1, r2, r1 * r2};
	cout << evaluatePolynom(coefficients, 2, Rational(1, 3)) << endl;

	return 0;
}
