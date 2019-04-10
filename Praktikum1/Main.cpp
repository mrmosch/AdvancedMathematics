#include "pch.h"
#include <iostream>
#include "CMyVektor.h"

using namespace std;

double f(CMyVektor eingabeVektor)
{
	if (eingabeVektor.getDimension() != 2)
		return false;
	double funktionswert;
	double x = eingabeVektor.getWert(0);
	double y = eingabeVektor.getWert(1);
	funktionswert = sin(x*y) + sin(x) + cos(y); //startstelle (0,2) -2,1^t
}

double g(CMyVektor eingabeVektor)
{
	if (eingabeVektor.getDimension() != 3)
		return false;
	double funktionswert;
	double x = eingabeVektor.getWert(0);
	double y = eingabeVektor.getWert(1);
	double z = eingabeVektor.getWert(2); 
	//x1 = x, x2 = y, x3 = z
	funktionswert = (-(2 * pow(x, 2) - 2 * x*y + pow(y, 2) + pow(z, 2) - 2 * x - 4 * y));
}

int main()
{
	double lambda = 5;

	CMyVektor a(3);
	a.setWerte(0, 1);
	a.setWerte(1, 2);
	a.setWerte(2, 3);

	CMyVektor b(3);
	b.setWerte(0, 4);
	b.setWerte(1, 5); 
	b.setWerte(2, 5);
	

	cout << a;
	cout << b;
	
	cout << "Addition " << (a+b);
	cout << "Skalare Multiplikation mit Lambda: " << lambda << " * Vektor a " << (5*a);
	cout << "Skalare Multiplikation mit Lambda: " << lambda << " * Vektor b " << (5 * b);
	cout << "Gradient: " << gradient(b, g);

	return 0;
}