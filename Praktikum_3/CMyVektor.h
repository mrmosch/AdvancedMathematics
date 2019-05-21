#pragma once
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class CMyVektor {
private:
	int dimension;
	vector<double> werte;

public:

	CMyVektor(int dim)
	{
		dimension = dim;

		for (int i = 0; i < dim; i++)
			werte.push_back(0);
	}

	int getDimension()
	{
		return dimension;
	}

	double getKomponente(int stelle)
	{
		return werte[stelle];
	}

	void setKomponente(int stelle, double wert)
	{
		werte[stelle] = wert;
	}

	double getlaenge()
	{
		double ergebnis = 0;

		for (int i = 0; i < dimension; i++)
		{
			ergebnis = ergebnis + pow(werte[i], 2);
		}

		return sqrt(ergebnis);
	}



};


CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	if (a.getDimension() != b.getDimension())
	{
		cout << "Dimensionen sind ungleich";
	}
	else
	{
		int dim = a.getDimension();
		CMyVektor c = CMyVektor(dim);

		for (int i = 0; i < dim; i++)
		{
			c.setKomponente(i, a.getKomponente(i) + b.getKomponente(i));
		}

		return c;
	}
}

CMyVektor operator*(double lambda, CMyVektor a)
{
	int dim = a.getDimension();
	CMyVektor c = CMyVektor(dim);

	for (int i = 0; i < dim; i++)
	{
		c.setKomponente(i, lambda * a.getKomponente(i));
	}

	return c;
}

double f(CMyVektor v)
{
	double x = v.getKomponente(0);
	double y = v.getKomponente(1);
	return sin(x*y) + sin(x) + cos(y);
}

double g(CMyVektor v)
{
	double x1 = v.getKomponente(0);
	double x2 = v.getKomponente(1);
	double x3 = v.getKomponente(2);
	return -((2 * pow(x1, 2)) - (2 * x1 * x2) + pow(x2, 2) + pow(x3, 2) - (2 * x1) - (4 * x3));
}

CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x))
{
	double h = 1e-8;
	double fx = funktion(x); //speichere f(x) als fx, damit es nicht immer neu errechnet werden muss
	CMyVektor grad = CMyVektor(x.getDimension()); //erstelle vektor grad, der so groß ist wie x(der Startpunkt)

	for (int i = 0; i < x.getDimension(); i++) //gehe schleife durch so lang wie x(der Startpunkt) dimensionen hat.
	{
		double aktuelleKomponente = x.getKomponente(i); //aktuelleKomponente ist die Stelle von x nach der in diesem durchlauf abgeleitet werden soll

		x.setKomponente(i, aktuelleKomponente + h); //die aktuelleKomponente wird mit h addiert, alle anderen Stellen nicht. x ist hier sozusagen x+h

		grad.setKomponente(i, (funktion(x) - fx) / h); //der gradient an der jeweiligen Stelle ist (f(x+h) - f(x)) / h

		x.setKomponente(i, aktuelleKomponente); //aktuelleKomponente ist noch ohne h zwischengespeichert. Dies wird also so wieder eingesetzt.
	}
	return grad;
}



std::ostream& operator<<(std::ostream& s, CMyVektor a)
{
	s << "(";
	for (int i = 0; i < a.getDimension(); i++)
	{
		s << a.getKomponente(i);
		if (i + 1 != a.getDimension())
			s << "; ";
		else
			s << ")";
	}
	return s;
}



CMyVektor gradientenverfahren(CMyVektor x, double(*funktion)(CMyVektor x), double lambda = 1.0)
{
	CMyVektor grad = CMyVektor(x.getDimension());
	CMyVektor x_neu = CMyVektor(x.getDimension());
	CMyVektor x_test = CMyVektor(x.getDimension());
	grad = gradient(x, funktion);


	int schritt = 0;
	while (grad.getlaenge() >= pow(10, -5) && schritt < 25)
	{
		x_neu = x + (lambda * grad);


		cout << "Schritt " << schritt << ":" << endl;
		cout << "\t x = (";
		for (int i = 0; i < x.getDimension(); i++) //gehe jede Komponente durch und gebe sie einzeln aus
		{
			cout << " " << x.getKomponente(i);
			if (i != x.getDimension() - 1) //wenn es nicht die letzte Komponente ist wird ein semikolon ausgegeben wegen schreibform (x1; x2; x3)
				cout << ";";
		}
		cout << ")" << endl;
		cout << "\t lambda = " << lambda << endl;
		cout << "\t f(x) = " << funktion(x) << endl;
		cout << "\t grad f(x) = (";
		for (int i = 0; i < grad.getDimension(); i++)
		{
			cout << " " << grad.getKomponente(i);
			if (i != grad.getDimension() - 1)
				cout << ";";
		}
		cout << ")" << endl;
		cout << "\t ||grad f(x)|| = " << grad.getlaenge() << endl << endl;

		cout << "\t x_neu = (";
		for (int i = 0; i < x_neu.getDimension(); i++)
		{
			cout << " " << x_neu.getKomponente(i);
			if (i != x_neu.getDimension() - 1)
				cout << ";";
		}
		cout << ")" << endl;
		cout << "\t f(x_neu) = " << funktion(x_neu) << endl << endl;


		if (funktion(x_neu) > funktion(x)) //wenn f(x_neu) > f(x) wird doppelte Schrittweite getestet
		{
			x_test = x + (2 * lambda * grad);
			cout << "\t Test mit doppelter Schrittweite (lambda = " << lambda * 2 << "):\n";
			cout << "\t x_test = (";
			for (int i = 0; i < x_test.getDimension(); i++)
			{
				cout << " " << x_test.getKomponente(i);
				if (i != x_test.getDimension() - 1)
					cout << ";";
			}
			cout << ")" << endl;
			cout << "\t f(x_test) = " << funktion(x_test) << endl;

			if (funktion(x_test) > funktion(x_neu)) //falls f(x_test) > f(x_neu) wird x_test als neues x genommen und lambda * 2 beibehalten
			{
				x = x_test;
				lambda *= 2;
				cout << "\t verdoppele Schrittweite!\n\n";
			}
			else //ansonsten wird x_neu zu x
			{
				x = x_neu;
				cout << "\t behalte alte Schrittweite!\n\n";
			}
		}
		else if (funktion(x_neu) <= funktion(x))
		{
			while (funktion(x_neu) <= funktion(x)) //ansonsten wird so lange lambda halbiert bis f(x_neu) > f(x). Dieses wird als x genommen und die Schrittweise beibehalten
			{
				lambda = lambda / 2;
				x_neu = x + (lambda * grad);

				cout << "\t halbiere Schrittweite (lambda = " << lambda << "):\n";
				cout << "\t x_neu = (";
				for (int i = 0; i < x_neu.getDimension(); i++)
				{
					cout << " " << x_neu.getKomponente(i);
					if (i != x_neu.getDimension() - 1)
						cout << ";";
				}
				cout << ")" << endl;
				cout << "\t f(x_neu) = " << funktion(x_neu) << endl << endl;
			}
			x = x_neu;
		}

		schritt++;
		grad = gradient(x, funktion);
	}


	if (grad.getlaenge() < pow(10, -5))
		cout << "Ende wegen ||grad f(x)|| < 1e-5 bei\n";
	else
		cout << "Ende wegen Schrittzahl = 25 bei\n";

	cout << "\t x = (";
	for (int i = 0; i < x.getDimension(); i++)
	{
		cout << " " << x.getKomponente(i);
		if (i != x.getDimension() - 1)
			cout << ";";
	}
	cout << ")" << endl;
	cout << "\t lambda = " << lambda << endl;
	cout << "\t f(x) = " << funktion(x) << endl;
	cout << "\t grad f(x) = (";
	for (int i = 0; i < grad.getDimension(); i++)
	{
		cout << " " << grad.getKomponente(i);
		if (i != grad.getDimension() - 1)
			cout << ";";
	}
	cout << ")" << endl;
	cout << "\t ||grad f(x)|| = " << grad.getlaenge() << endl << endl;


	return grad;
}