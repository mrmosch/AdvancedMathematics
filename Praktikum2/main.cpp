#include <iostream>
#include "CMyMatrix.h"

using namespace std;

int main()
{
	// Matrix Inverse test
	// Matrix Inverse test
	// Matrix Inverse test
	/*
	CMyMatrix testMatrix = CMyMatrix(2, 2);
	testMatrix.setKomponente(0, 0, 2);
	testMatrix.setKomponente(1, 0, -3);
	testMatrix.setKomponente(0, 1, 1);
	testMatrix.setKomponente(1, 1, 5);

	testMatrix = testMatrix.invers();

	cout << testMatrix.getKomponente(0, 0) << " , " << testMatrix.getKomponente(1, 0) << endl;
	cout << testMatrix.getKomponente(0, 1) << " , " << testMatrix.getKomponente(1, 1) << endl;*/

	// Matrix-Vektor-Multiplikation
	// Matrix-Vektor-Multiplikation
	// Matrix-Vektor-Multiplikation
	/*
	CMyMatrix testMatrix = CMyMatrix(3, 3);
	testMatrix.setKomponente(0, 0, 2);
	testMatrix.setKomponente(1, 0, 2);
	testMatrix.setKomponente(2, 0, 2);
	testMatrix.setKomponente(0, 1, 1);
	testMatrix.setKomponente(1, 1, 3);
	testMatrix.setKomponente(2, 1, 4);
	testMatrix.setKomponente(0, 2, 4);
	testMatrix.setKomponente(1, 2, 1);
	testMatrix.setKomponente(2, 2, 2);

	CMyVektor testVektor = CMyVektor(3);
	testVektor.setKomponente(0, 1);
	testVektor.setKomponente(1, 1);
	testVektor.setKomponente(2, 1);

	testVektor = testMatrix * testVektor;

	cout << testVektor.getKomponente(0) << " , " << testVektor.getKomponente(1) << " , " << testVektor.getKomponente(2) << endl;*/


	//Jacobi-Matrix Test
	//Jacobi-Matrix Test
	//Jacobi-Matrix Test

	//CMyVektor stelle = CMyVektor(4);
	//stelle.setKomponente(0, 1);
	//stelle.setKomponente(1, 2);
	//stelle.setKomponente(2, 0);
	//stelle.setKomponente(3, 3);

	//CMyMatrix jacobim = CMyMatrix(4, 3);
	//jacobim = jacobi(stelle, h);

	//cout << jacobim.getKomponente(0, 0) << " , " << jacobim.getKomponente(1, 0) << " , " << jacobim.getKomponente(2, 0) << " , " << jacobim.getKomponente(3, 0) << endl;
	//cout << jacobim.getKomponente(0, 1) << " , " << jacobim.getKomponente(1, 1) << " , " << jacobim.getKomponente(2, 1) << " , " << jacobim.getKomponente(3, 1) << endl;
	//cout << jacobim.getKomponente(0, 2) << " , " << jacobim.getKomponente(1, 2) << " , " << jacobim.getKomponente(2, 2) << " , " << jacobim.getKomponente(3, 2) << endl;

	CMyVektor startwert = (2);
	startwert.setKomponente(0, 1);
	startwert.setKomponente(1, 1);
	newtonverfahren(startwert, i);

	system("PAUSE");
	return 0;
}
