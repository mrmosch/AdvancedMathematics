#include "pch.h"
#include <iostream>
#include "CMyVektor.h"
#include <vector>
#include <cmath>


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
	CMyVektor *c = new CMyVektor(a.getDimension());
	for (int i = 0; i < a.getDimension(); i++)
	{
		c->setWerte(a.getDimension, (a.getWert(i) + b.getWert(i)));
	}
	return *c;
}
//Vektor Skalare Multiplikation
CMyVektor operator*(double lambda, CMyVektor a)
{
	for (int i = 0; i < a.getDimension(); i++)
	{
		a.setWerte(a.getDimension, (lambda * a.getWert(i)));
	}
}

//Ausgabe eines Vektor in der Form (Wert1, Wert2, Wert3,..)
std::ostream& operator<<(std::ostream& os, CMyVektor a)
{
	os << "Vektor mit Dimension " << a.getDimension() << " (";
	for (int i = 0; i < a.getDimension(); i++)
	{
		os << a.getWert(i);
		os << ", "; 
	}
	os << ") \n";
	return os;
}

//Gradientenfunktion
CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x))
{

}