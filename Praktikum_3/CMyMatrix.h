#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "CMyVektor.h"

class CMyMatrix {
private:
	int dimension_spalten;
	int dimension_zeilen;
	vector<CMyVektor> werte;

public:

	CMyMatrix(int dimS, int dimZ)
	{
		dimension_spalten = dimS;
		dimension_zeilen = dimZ;
		
		for (int i = 0; i < dimS; i++)
		{
			CMyVektor neueSpalte = CMyVektor(dimZ);
			werte.push_back(neueSpalte);
		}
	}

	double getKomponente(int spalte, int zeile)
	{
		return werte[spalte].getKomponente(zeile);
	}

	void setKomponente(int spalte, int zeile, double wert)
	{
		werte[spalte].setKomponente(zeile, wert);
	}

	int getDimensionZ()
	{
		return dimension_zeilen;
	}

	int getDimensionS()
	{
		return dimension_spalten;
	}

	CMyMatrix invers()
	{
		CMyMatrix inversMatrix = CMyMatrix(2, 2);
		
		double a = this->getKomponente(0, 0);
		double b = this->getKomponente(1, 0);
		double c = this->getKomponente(0, 1);
		double d = this->getKomponente(1, 1);

		double multiplikator = 1 / (a * d - b * c);

		if (a * d - b * c == 0)
		{
			cout << "Determinante = 0, inversierung nicht möglich.\n";
			return inversMatrix;
		}

		inversMatrix.setKomponente(0, 0, multiplikator * d);
		inversMatrix.setKomponente(1, 0, multiplikator * -1 * b);
		inversMatrix.setKomponente(0, 1, multiplikator * -1 * c);
		inversMatrix.setKomponente(1, 1, multiplikator * a);

		return inversMatrix;
	}

};

CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	CMyMatrix ergebnis = CMyMatrix(x.getDimension(), funktion(x).getDimension());  //erstelle ergebnis-Matrix
	double h = 1e-4; //h bleibt gleich
	CMyVektor x_plus_h(x.getDimension()); //erstelle vektor um x+h zu speichern
	CMyVektor fx = funktion(x); //speichere f(x) vorher da es immer das selbe ist

	for (int aktuelle_zeile = 0; aktuelle_zeile < ergebnis.getDimensionZ(); aktuelle_zeile++) //gehe alle Zeilen der Ergebnis-Matrix durch
	{
		for (int aktuelle_spalte = 0; aktuelle_spalte < ergebnis.getDimensionS(); aktuelle_spalte++) //gehe alle Spalten der Ergebnis-Matrix durch
		{
			x_plus_h = x; //x+h ist erstmal das selbe wie x
			x_plus_h.setKomponente(aktuelle_spalte, (x.getKomponente(aktuelle_spalte) + h)); //x+h wird an der aktuellen Stelle um +h ergänzt. Die anderen Werte bleiben gleich
			ergebnis.setKomponente(aktuelle_spalte, aktuelle_zeile, (funktion(x_plus_h).getKomponente(aktuelle_zeile) - fx.getKomponente(aktuelle_zeile)) / h); //rechne (f(x+h)-f(x))/h für die aktuelle Zeile.  setze an aktueller Stelle das Ergebnis ein
		}
	}

	return ergebnis;

}


CMyVektor h(CMyVektor v)
{
	double x1 = v.getKomponente(0);
	double x2 = v.getKomponente(1);
	double x3 = v.getKomponente(2);
	double x4 = v.getKomponente(3);

	CMyVektor ergebnis = CMyVektor(3);
	ergebnis.setKomponente(0, x1*x2*exp(x3));
	ergebnis.setKomponente(1, x2*x3*x4);
	ergebnis.setKomponente(2, x4);

	return ergebnis;
}

CMyVektor i(CMyVektor v)
{
	double x = v.getKomponente(0);
	double y = v.getKomponente(1);

	CMyVektor ergebnis = CMyVektor(2);
	ergebnis.setKomponente(0, (x * x * x * y * y * y) - (2 * y));
	ergebnis.setKomponente(1, x - 2);

	return ergebnis;
}

CMyVektor operator*(CMyMatrix m, CMyVektor v)
{
	CMyVektor ergebnis = CMyVektor(m.getDimensionZ());

	for (int i = 0; i < m.getDimensionZ(); i++)
	{
		double temp = 0;
		for (int j = 0; j < m.getDimensionS(); j++)
		{
			temp += m.getKomponente(j, i) * v.getKomponente(j);
		}
		ergebnis.setKomponente(i, temp);
	}
	return ergebnis;
}


void newtonverfahren(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	// CMyVektor fx = funktion(x);

	for (int i = 0; i < 50 && funktion(x).getlaenge() >= 1e-5; i++)
	{
		CMyMatrix jacobi_matrix = jacobi(x, funktion);
		CMyMatrix inverse = jacobi_matrix.invers();
		CMyVektor dx = inverse * ((-1) * funktion(x));

		cout << "Schritt: " << i << ":\n";
		cout << "\t x = ( " << x.getKomponente(0) << "; " << x.getKomponente(1) << ")\n";
		cout << "\t f(x) = ( " << funktion(x).getKomponente(0) << "; " << funktion(x).getKomponente(1) << ")\n";
		cout << "\t f'(x) =\n";
		cout << "\t\t ( " << jacobi_matrix.getKomponente(0, 0) << "; " << jacobi_matrix.getKomponente(1, 0) << endl;
		cout << "\t\t " << jacobi_matrix.getKomponente(0, 1) << "; " << jacobi_matrix.getKomponente(1, 1) << ")\n";
		cout << "\t (f'(x))^(-1) =\n";
		cout << "\t\t ( " << inverse.getKomponente(0, 0) << "; " << inverse.getKomponente(1, 0) << endl;
		cout << "\t\t " << inverse.getKomponente(0, 1) << "; " << inverse.getKomponente(1, 1) << ")\n";
		cout << "\t dx = ( " << dx.getKomponente(0) << "; " << dx.getKomponente(1) << ")\n";
		cout << "\t ||f(x)|| = " << funktion(x).getlaenge() << endl << endl;

		x = x + dx;
	}

	if (funktion(x).getlaenge() < 1e-5)
	{
		cout << "Ende wegen ||f(x)<1e-5 bei\n";
		cout << "\t x = ( " << x.getKomponente(0) << "; " << x.getKomponente(1) << ")\n";
		cout << "\t f(x) = ( " << funktion(x).getKomponente(0) << "; " << funktion(x).getKomponente(1) << ")\n";
		cout << "\t ||f(x)|| = " << funktion(x).getlaenge() << endl << endl;
	}
	else
	{
		cout << "Ende wegen Schrittzahl = 49";
	}
}
