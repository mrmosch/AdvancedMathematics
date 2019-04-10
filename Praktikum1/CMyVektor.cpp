#include "pch.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "CMyVektor.h"

CMyVektor::CMyVektor(int d)
{
	dimension = d;
	werte = new double[dimension];
}
void CMyVektor::setDimension(int d)
{
	dimension = d;
}
int CMyVektor::getDimension()
{
	return dimension;
}
void CMyVektor::setWerte(int d, double w)
{
	werte[d] = w;
}
double CMyVektor::getWert(int d)
{
	return werte[d];
}
double CMyVektor::vektorLength()
{
	double length = 0; 
	for (int i = 0; i < dimension; i++)
	{
		length += pow(werte[i], 2);
	}
	length = sqrt(length);
	return length; 
}
//Vektoraddition
CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	if (a.getDimension() != b.getDimension())
	{
		std::cout << "Ungleiche Dimensionen, daher keine Addition möglich"; 
	}
	else
	{
		CMyVektor *c = new CMyVektor(a.getDimension());
		for (int i = 0; i < a.getDimension(); i++)
		{
			c->setWerte(i, (a.getWert(i) + b.getWert(i)));
		}
		return *c;
	}
	
}
//Vektor Skalare Multiplikation
CMyVektor operator*(double lambda, CMyVektor a)
{
	for (int i = 0; i < a.getDimension(); i++)
	{
		a.setWerte(i, (lambda * a.getWert(i)));
	}
	return a; 
}

//Ausgabe eines Vektor in der Form (Wert1, Wert2, Wert3,..)
std::ostream& operator<<(std::ostream& os, CMyVektor a)
{
	os << "Vektor mit Dimension " << a.getDimension() << " (";
	for (int i = 0; i < a.getDimension(); i++)
	{
		os << a.getWert(i);
		//letztes element filter
		if (i + 1 < a.getDimension())
			os << ", ";
		else
			os << ") \n";
	}
	return os;
}

/// <summary>
/// Gradientenfunktion
/// </summary>
/// <param name="x">
/// Der Vektor auf dem das Gradientenverfahren angewandt werden soll
/// </param>
/// <returns>
/// Gradient vom Typ CMyVektor
/// </returns>
CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x))
{
	const double h = pow(10, -8);
	CMyVektor grad(x.getDimension());
	CMyVektor shift(x.getDimension());
	for (int i = 0; i < x.getDimension(); i++)
	{
		shift = x;
		shift.setWerte(i, (x.getWert(i) + h));
		grad.setWerte(i, (funktion(shift) - funktion(x) / h));
		shift = x; 
	}
	return grad; 
}