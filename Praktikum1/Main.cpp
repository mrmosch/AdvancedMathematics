#include "pch.h"
#include <iostream>
#include "CMyVektor.h"
#include "CMyMatrix.h"
#include <cmath>

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

CMyVektor f2(CMyVektor x)
{
	double x1 = x.getWert(0); 
	double x2 = x.getWert(1);
	double x3 = x.getWert(2);
	double x4 = x.getWert(3);

	CMyVektor erg(3); //R^4 nach R^3 
	erg.setWerte(0, x1*x2*exp(x3));
	erg.setWerte(1, x2*x3*x4); 
	erg.setWerte(2, x4); 

	return erg;
}

CMyVektor f3(CMyVektor eingabe)
{
	double x = eingabe.getWert(0);
	double y = eingabe.getWert(1); 

	CMyVektor erg(2); //r2 nach r2
	erg.setWerte(0, ((pow(x, 3)*pow(y, 3)) - 2 * y));
	erg.setWerte(1, (x - 2));
	return erg; 
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
	//double lambda = 5;

	//CMyVektor a(3);
	//a.setWerte(0, 1);
	//a.setWerte(1, 2);
	//a.setWerte(2, 3);

	//CMyVektor b(3);
	//b.setWerte(0, 4);
	//b.setWerte(1, 5); 
	//b.setWerte(2, 5);
	//
	//CMyVektor testCaseOne(2); 
	//testCaseOne.setWerte(0, 0.2);
	//testCaseOne.setWerte(1, -2.1);


	//CMyVektor testCaseTwo(3);
	//testCaseTwo.setWerte(0, 0);
	//testCaseTwo.setWerte(1, 0);
	//testCaseTwo.setWerte(2, 0);

	//cout << a;
	//cout << b;
	//
	//cout << "Addition " << (a+b);
	//cout << "Skalare Multiplikation mit Lambda: " << lambda << " * Vektor a " << (5*a);
	//cout << "Skalare Multiplikation mit Lambda: " << lambda << " * Vektor b " << (5 * b);
	//cout << "Gradient: " << gradient(b, g);

	//Testing
	//gradientenVerfahren(testCaseOne, f);
	//gradientenVerfahren(testCaseTwo, g, 0.1);

	CMyMatrix a(2, 2);
	a.SetKomponente(0, 0, 2);
	a.SetKomponente(0, 1, -3);
	a.SetKomponente(1, 0, 1);
	a.SetKomponente(1, 1, 5); 
	CMyVektor vek(2);
	vek.setWerte(0, 1);
	vek.setWerte(1, 1);

	CMyMatrix inverse = a.invers();
	std::cout << inverse; 
	CMyVektor MatVekMul = a * vek;
	std::cout << MatVekMul;

	CMyVektor testVektorVier(4);
	testVektorVier.setWerte(0, 1);
	testVektorVier.setWerte(1, 2);
	testVektorVier.setWerte(2, 0);
	testVektorVier.setWerte(3, 3);

	cout << testVektorVier << std::endl;
	cout << jacobi(testVektorVier, f2) << std::endl;

	CMyVektor startVektor(2);
	startVektor.setWerte(0, 1);
	startVektor.setWerte(1, 1);

	newtonVerfahren(startVektor, f3);

	return 0;
}