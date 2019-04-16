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
	return funktionswert = (sin(x*y) + sin(x) + cos(y)); //startstelle (0,2;-2,1)
}

double g(CMyVektor eingabeVektor)
{
	if (eingabeVektor.getDimension() != 3)
		return false;
	double funktionswert;
	double x1 = eingabeVektor.getWert(0);
	double x2 = eingabeVektor.getWert(1);
	double x3 = eingabeVektor.getWert(2); 
	//x1 = x, x2 = y, x3 = z
	return funktionswert = -(2 * x1*x1 - 2 * x1*x2 + x2 * x2 + x3 * x3 - 2 * x1 - 4 * x3);;
}

//CMyVektor gradientenverfahren(CMyVektor start, double(*funktion)(CMyVektor start), double lambda)
//{
//	CMyVektor grad(start.getDimension());
//	grad = gradient(start, funktion);
//	CMyVektor x_neu(start.getDimension());
//	CMyVektor x_test(start.getDimension());
//
//	for (int i = 0; i < 50 && grad.vektorLength() >= pow(10, -5); i++)
//	{
//#pragma region Konsolenausgaben
//		using namespace std;
//		cout << "Schritt: " << i << endl;
//		cout << "\t x = " << start << endl;
//		cout << "\t lambda = " << lambda << endl;
//		cout << "\t f(x) = " << funktion(start) << endl;
//		cout << "\t grad f(x) = " << grad << endl;
//		cout << "\t ||grad f(x)|| = " << grad.vektorLength() << endl << endl;
//#pragma endregion
//
//		x_neu = start + (lambda*grad);
//		cout << "\t x_neu = " << x_neu << endl;
//		cout << "\t f(x_neu) = " << funktion(x_neu) << endl << endl;
//		if (funktion(x_neu) > funktion(start))
//		{
//			lambda *= 2;
//			cout << "\t Teste mit doppelter Schrittweite (Lambda = " << lambda << "): " << endl;
//			x_test = start + (lambda * grad);
//			cout << "\t x_test = " << x_test << endl;
//			cout << "\t f(x_test) = " << funktion(x_test) << endl << endl;
//			if (funktion(x_test) > funktion(start))
//				start = x_test;
//			else
//			{
//				start = x_neu;
//				cout << "\t Behalte alte Schrittweite. " << endl;
//			}
//
//		}
//		else
//		{
//			while (funktion(x_neu) <= funktion(start))
//			{
//				lambda /= 2;
//				cout << "\t Neue und bereits halbierte Schrittweite (Lambda = " << lambda << ")" << endl;
//				x_neu = start + (lambda*grad);
//				cout << "\t x_neu = " << x_neu << endl;
//				cout << "\t f(x_neu) = " << funktion(x_neu) << endl;
//			}
//			start = x_neu;
//		}
//	}
//	return start;
//}

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
	
	CMyVektor testCaseOne(2); 
	testCaseOne.setWerte(0, 0.2);
	testCaseOne.setWerte(1, -2.1);


	CMyVektor testCaseTwo(3);
	testCaseTwo.setWerte(0, 0);
	testCaseTwo.setWerte(1, 0);
	testCaseTwo.setWerte(2, 0);

	cout << a;
	cout << b;
	
	cout << "Addition " << (a+b);
	cout << "Skalare Multiplikation mit Lambda: " << lambda << " * Vektor a " << (5*a);
	cout << "Skalare Multiplikation mit Lambda: " << lambda << " * Vektor b " << (5 * b);
	cout << "Gradient: " << gradient(b, g);

	//Testing
	gradientenVerfahren(testCaseOne, f);
	gradientenVerfahren(testCaseTwo, g, 0.1);

	return 0;
}