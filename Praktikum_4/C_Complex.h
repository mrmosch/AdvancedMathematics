#pragma once
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

class CKomplex
{
public: 
	double re; 
	double im; 
	CKomplex()
	{
		re = 0; 
		im = 0; 
	}
	CKomplex(double a, double b)
	{
		re = a; 
		im = b; 
	}
	CKomplex(double phi)
	{
		re = cos(phi); 
		im = sin(phi); 
	}

	double getReal()
	{
		return re; 
	}
	double getIm()
	{
		return im; 
	}

	double abs()
	{
		return sqrt((this->re*this->re) + (this->im*this->im));
	}


};

CKomplex operator +(CKomplex a, CKomplex b)
{
	CKomplex erg(0,0); 
	erg.re = (a.re + b.re); 
	erg.im = (a.im + b.im); 
	return erg; 
}

CKomplex operator *(CKomplex a, CKomplex b)
{
	CKomplex erg(0, 0); 
	erg.re = (a.re * b.re) - (a.im * b.im); 
	erg.im = (a.re * b.im) + (a.im * b.re); 
	return erg;
}

CKomplex operator *(double b, CKomplex a)
{
	CKomplex erg(0, 0);
	erg.re = (a.re * b);
	erg.im = (a.im * b);
	return erg;
}

//Hoever Ein- / Ausgabe
vector<CKomplex>  werte_einlesen(const char *dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const char *dateiname, vector<CKomplex> werte, double epsilon = -1.0)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].getReal() << "\t" << werte[i].getIm() << endl;
	// File schliessen
	fp.close();
}

vector<CKomplex> ft(vector<CKomplex> werte, bool hin)
{
	int N = werte.size(); 
	vector<CKomplex> erg(N);
	const double pi = 3.14159265358979323846;
	for (int n = 0; n < N; n++)
	{
		CKomplex summe; 
		double a; 
		for (int k = 0; k < N; k++)
		{
			if (hin == true)
			{
				a = (-1 * ((2 * pi*k*n) / N));
			}
			else if(hin == false)
			{
				a = ((2 * pi*k*n) / N);
			}
			CKomplex e(a);
			summe = summe + (werte[k] * e);
		}
		erg[n] = (1 / sqrt(N)*summe); 
	}
	return erg; 
}

