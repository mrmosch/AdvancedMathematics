#ifndef CMyVektor
#pragma once

#include <cstdlib>
#include <vector>

class CMyVektor
{
	private: 
		int dimension; 
		double* werte;
	public: 
		CMyVektor(int d);
		void setDimension(int d);
		int getDimension();
		void setWerte(int d, double w);
		double getWert(int d) const;
		double vektorLength();
};

//Operatoren überladen
CMyVektor operator+(CMyVektor a, CMyVektor b); //Vektoraddition
//Skalare Multiplikation
/* 
		(1)	  (5*1)	  (5)
	5 * (2) = (5*2) = (10)
		(3)	  (5*3)	  (15)
*/
CMyVektor operator*(double lambda, CMyVektor a); 

//Ausgabe eines Vektors
std::ostream& operator<<(std::ostream& os, CMyVektor a);

//Gradient
CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x));
CMyVektor gradientenVerfahren(CMyVektor start, double(*funktion)(CMyVektor start), double lambda = 1);
#endif // !CMyVektor
