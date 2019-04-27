#ifndef CMyMatrix
#pragma once
#include "CMyVektor.h"
#include <cstdlib>
#include <map>
#include <vector>

class CMyMatrix
{
private: 
	int zeilen;
	int spalten;
	std::vector<CMyVektor> matrix;
public: 
	CMyMatrix(int zeile, int spalte);
	void SetKomponente(int zeile, int spalte, double wert);
	double GetKomponente(int zeile, int spalte);
	int GetZeilen();
	int GetSpalten();
	CMyMatrix invers();
	CMyVektor operator[](int zeile); 
	double operator()(int zeile, int spalte);
	CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x));
	
};
std::ostream& operator<<(std::ostream& os, CMyMatrix a);
CMyVektor operator*(CMyMatrix a, CMyVektor v);
CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));

#endif