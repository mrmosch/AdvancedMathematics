#include "pch.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "CMyVektor.h"
#include "CMyMatrix.h"

using namespace std;
CMyMatrix::CMyMatrix(int zeilenzahl, int spaltenzahl)
{
	zeilen = zeilenzahl;
	spalten = spaltenzahl;
	for (int i = 0; i < zeilen; i++)
	{
		matrix.push_back(CMyVektor(spalten));
	}
}

void CMyMatrix::SetKomponente(int zeile, int spalte, double wert)
{
	matrix[zeile].setWerte(spalte, wert);
}

double CMyMatrix::GetKomponente(int zeile, int spalte)
{
	return matrix[zeile].getWert(spalte);
}

int CMyMatrix::GetZeilen()
{
	return zeilen;
}

int CMyMatrix::GetSpalten()
{
	return spalten;
}
CMyMatrix CMyMatrix::invers()
{
	try
	{
		double det = (matrix[0].getWert(0) * matrix[1].getWert(1) - matrix[0].getWert(1) * matrix[1].getWert(0));
		if (det != 0)
		{
			CMyMatrix inverse(2,2); 
			double new1 = (1/det) * matrix[1].getWert(1);
			inverse.SetKomponente(0, 0, new1);
			double new2 = (1/det) * (-matrix[0].getWert(1));
			inverse.SetKomponente(0, 1, new2); 
			double new3 = (1/det) * (-matrix[1].getWert(0));
			inverse.SetKomponente(1, 0, new3);
			double new4 = (1/det) * matrix[0].getWert(0);
			inverse.SetKomponente(1, 1, new4);
			return inverse;
		}
		else
		{
			std::cout << "Determinante ist null" << endl;
		}
		
	}
	catch(int e)
	{
		cout << "Fehler: " << e; 
	}
}

std::ostream& operator<<(std::ostream& os, CMyMatrix a)
{
	os << "Matrix: " << std::endl;
	
	for (int i = 0; i < a.GetSpalten(); i++)
	{
		for (int j = 0; j < a.GetZeilen(); j++)
		{
			os << a.GetKomponente(j, i) << ", ";
		}
		os << std::endl << ""; 
	}
	
	return os;
}

CMyVektor CMyMatrix::operator[](int zeile)
{
	return matrix[zeile];
}
double CMyMatrix::operator()(int zeile, int spalte)
{
	return matrix[zeile].getWert(spalte);
}

//Matrix Vektor Multiplikation
CMyVektor operator*(CMyMatrix a, CMyVektor v)
{
	CMyVektor ergebnis(v.getDimension()); 
	double temp; 
	for (int i = 0; i < a.GetZeilen(); i++)
	{
		temp = a[i] * v;
		ergebnis.setWerte(i,temp);
	}
	return ergebnis;
}

CMyVektor CMyMatrix::gradient(CMyVektor x, double(*funktion)(CMyVektor x))
{
	const double h = pow(10, -4);
	const double fx = funktion(x);
	CMyVektor grad(x.getDimension());
	CMyVektor temp(x.getDimension());
	for (int j = 0; j < x.getDimension(); j++)
	{
		temp.setWerte(j, x.getWert(j));
	}
	for (int i = 0; i < x.getDimension(); i++)
	{
		//double wert zwischenspeichern
		x.setWerte(i, (x.getWert(i) + h));
		grad.setWerte(i, ((funktion(x) - fx) / h));
		x = temp;
	}
	return grad;
}


CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	int m = funktion(x).getDimension(); 
	CMyMatrix ergMatrix(x.getDimension(), m);
	const double h = 10e-4;
	CMyVektor xWackel(x.getDimension());
	xWackel = x;
	CMyVektor fVonX = funktion(x); 
	for (int i = 0; i < x.getDimension(); i++)
	{
		for (int j = 0; j < m; j++)
		{
			double temp = x.getWert(i);
			xWackel.setWerte(i, (x.getWert(i) + h));
			ergMatrix.SetKomponente(i, j, ((funktion(xWackel).getWert(j) - fVonX.getWert(j)) / h));
			xWackel.setWerte(i, temp);
		}
	}
	return ergMatrix;
}

CMyVektor wackelVektor(CMyMatrix jacobi, CMyVektor(*funktion)(CMyVektor x), CMyVektor start)
{
	CMyMatrix inverse = jacobi.invers(); 
	CMyVektor dx = inverse * ((-1)*(funktion(start)));
	return dx;
}

void newtonVerfahren(CMyVektor start, CMyVektor(*funktion)(CMyVektor x))
{
	cout << "Newton Verfahren wird ausgeführt: " << endl; 
	for (int i = 0; i < 50; i++)
	{
		CMyMatrix jf = jacobi(start, funktion);
		CMyMatrix invers = jf.invers();
		CMyVektor dx = invers * (-1 * funktion(start));
		CMyVektor fVonX = funktion(start);
		
		cout << "Schritt " << i << ": " << endl; 
		cout << "\t x = " << start << endl; 
		cout << "\t f(x) = " << funktion(start) << endl; 
		cout << "\t f'(x) = " << jf << endl; 
		cout << "\t f'(x)^(-1) = " << invers << endl;
		cout << "\t dx = " << dx << endl; 
		cout << "\t ||f(x)|| = " << fVonX.vektorLength() << endl;

		start = start + dx;
	}
}
