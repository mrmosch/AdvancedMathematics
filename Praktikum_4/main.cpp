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

	system("PAUSE"); 
}