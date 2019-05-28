#include "C_Complex.h"
#include <iostream>
using namespace std; 

int main()
{
	CKomplex a(2, -4); 
	CKomplex b(-3, 5); 
	//Komplexe Multiplikation
	CKomplex erg = a * b; 
	cout << erg.re << " + " << erg.im << "i" << endl; 
	//Reele Zahl multipliziert mit Komplexer Zahl
	erg = 3 * erg; 
	cout << erg.re << " + " << erg.im << "i" << endl;
	//Komplexe Addition 
	erg = a + b;
	cout << erg.re << " + " << erg.im << "i" << endl;


	vector<CKomplex> test = werte_einlesen("Daten_original.txt");
	test = ft(test, true);
	werte_ausgeben("Daten_Test.txt", test);
	werte_ausgeben("Daten_Test_01.txt", test, 0.1);
	werte_ausgeben("Daten_Test_10.txt", test, 1.0);
	//zurück transformieren 
	test = ft(test, false); 
	werte_ausgeben("Daten_Test_Vergleich.txt", test);



	//Vergleich Trafo 0 
	double max; 
	CKomplex differenz(0,0); 
	test = werte_einlesen("Daten_Test.txt"); 
	vector<CKomplex> f = werte_einlesen("Daten_original.txt"); 
	vector<CKomplex> ff = ft(test, false);
	max = 0.0; 
	for (int i = 0; i < test.size(); i++)
	{
		differenz = f[i] + (-1* ff[i]); 
		if (differenz.abs() > max)
			max = differenz.abs(); 
	}
	cout << "Max Differenz epsilon -1.0: " << max << endl;

	//Vergleich Trafo Episolon 0.1
	test = werte_einlesen("Daten_Test_01.txt");
	ff = ft(test, false);
	for (int i = 0; i < test.size(); i++)
	{
		differenz = f[i] + (-1 * ff[i]);
		if (differenz.abs() > max)
			max = differenz.abs();
	}
	cout << "Max Differenz epsilon 0.1: " << max << endl;

	//Vergleich Trafo Epsilon 1.0
	test = werte_einlesen("Daten_Test_10.txt");
	ff = ft(test, false);
	for (int i = 0; i < test.size(); i++)
	{
		differenz = f[i] + (-1 * ff[i]);
		if (differenz.abs() > max)
			max = differenz.abs();
	}
	cout << "Max Differenz epsilon 1.0: " << max << endl;
	system("PAUSE"); 
}