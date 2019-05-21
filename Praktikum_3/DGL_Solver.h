#pragma once
#include "CMyVektor.h"

class C_DGLSolver
{
private: 
	bool system = false;
	bool nterOrdnung = false;
	CMyVektor(*DGL_System)(CMyVektor y, double x);
	double(*DGL_nterOrdnung)(CMyVektor y, double x);
	CMyVektor ableitungen(CMyVektor y, double x)
	{
		if (this->system == true)
		{
			return DGL_System(y,x); 
		}
		else if (this->nterOrdnung == true)
		{
			CMyVektor ableitungen(y.getDimension()); 
			for (int i = 0; i < y.getDimension()-1; i++)
			{
				ableitungen.setKomponente(i, y.getKomponente(i + 1));
			}
			ableitungen.setKomponente(ableitungen.getDimension() - 1, DGL_nterOrdnung(y, x));

			return ableitungen;
		}
	}

public: 
	//DGL System Konstruktor 
	C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x))
	{
		this->system = true;
		DGL_System = f_DGL_System;
	}
	//DGL nter Ordnung Konstruktor 
	C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x))
	{
		this->nterOrdnung = true;
		DGL_nterOrdnung = f_DGL_nterOrdnung;
	}

	CMyVektor eulerVerfahren(double xStart, double xEnd, int schritte, CMyVektor y_Start)
	{
		double h = (xEnd - xStart) / schritte; 

		//Anfangswertproblem 
		double x = xStart; 
		CMyVektor y(y_Start); 
		CMyVektor y_ableitung(ableitungen(y_Start, xStart)); 

		for (int i = 0; i < schritte; i++)
		{
			cout << "Schritt " << i << ": \t" << endl
				<< "\t x  = " << x << endl
				<< "\t y  = " << y << endl
				<< "\t y' = " << y_ableitung << endl << endl << endl; 

			x = xStart + (i + 1) * h;
			y = y + h * y_ableitung;
			y_ableitung = ableitungen(y, x);
		}

		cout << "Ende bei" << endl
			<< "         x = " << xEnd << endl
			<< "         y = " << y << endl << endl;
		std::system("PAUSE"); 
		return y; 
	}

	CMyVektor eulerVerfahrenNoPrint(double xStart, double xEnd, int schritte, CMyVektor y_Start)
	{
		double h = (xEnd - xStart) / schritte;

		//Anfangswertproblem 
		double x = xStart;
		CMyVektor y(y_Start);
		CMyVektor y_ableitung(ableitungen(y_Start, xStart));

		for (int i = 0; i < schritte; i++)
		{
			x = xStart + (i + 1) * h;
			y = y + h * y_ableitung;
			y_ableitung = ableitungen(y, x);
		}
		return y;
	}

	CMyVektor heunVerfahren(double xStart, double xEnd, int schritte, CMyVektor y_Start)
	{
		double h = (xEnd - xStart) / schritte;

		//Anfangswertproblem 
		double x = xStart;
		CMyVektor y(y_Start);
		CMyVektor y_ableitung(ableitungen(y_Start, xStart));
		CMyVektor y_a_mittel(y_Start.getDimension());

		for (int i = 0; i < schritte; i++)
		{
			cout << "Schritt " << i << ": \t" << endl
				<< "\t x  = " << x << endl
				<< "\t y  = " << y << endl
				<< "\t y' = " << y_ableitung << endl << endl << endl;

			x = xStart + (i + 1) * h;
			

			/*y_a_mittel bestimmen*/
			y_a_mittel = 0.5 * (y_ableitung + (ableitungen((y + h * y_ableitung), x)));

			cout << "\t y_Test = " << y + h * y_ableitung << endl
				<< "\t y'_Test = " << ableitungen(y + h * y_ableitung, x) << endl
				<< "\t y'_Mittel = " << y_a_mittel << endl << endl << endl;

			y = y + h * y_a_mittel;
			y_ableitung = ableitungen(y, x);
		}

		cout << "Ende bei" << endl
			<< "         x = " << xEnd << endl
			<< "         y = " << y << endl << endl;
		std::system("PAUSE");
		return y;
	}

	CMyVektor heunVerfahrenNoPrint(double xStart, double xEnd, int schritte, CMyVektor y_Start)
	{
		double h = (xEnd - xStart) / schritte;

		//Anfangswertproblem 
		double x = xStart;
		CMyVektor y(y_Start);
		CMyVektor y_ableitung(ableitungen(y_Start, xStart));
		CMyVektor y_a_mittel(y_Start.getDimension());

		for (int i = 0; i < schritte; i++)
		{
			x = xStart + (i + 1) * h;

			y_a_mittel = 0.5 * (y_ableitung + (ableitungen((y + h * y_ableitung), x)));
			y = y + h * y_a_mittel;
			y_ableitung = ableitungen(y, x);
		}
		return y;
	}
};