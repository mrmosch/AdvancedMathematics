#include <iostream>
#include "DGL_Solver.h"
#include "CMyVektor.h"

using namespace std;

CMyVektor dglF(CMyVektor y, double x)
{
	CMyVektor erg(2);
	erg.setKomponente(0, (2 * y.getKomponente(1) - x * y.getKomponente(0))); 
	erg.setKomponente(1, (y.getKomponente(0)*y.getKomponente(1) - 2 * (x*x*x)));
	return erg; 
}


double dglDritterOrdnungF(CMyVektor y, double x)
{
	double y_0 = y.getKomponente(0);
	double y_1 = y.getKomponente(1);
	double y_2 = y.getKomponente(2);
	return ((2*x*y_1*y_2) + (2*y_0 * y_0 *y_1));
}

int main()
{
	C_DGLSolver mySolver(dglF);
	CMyVektor lul(2); 
	lul.setKomponente(0, 0);
	lul.setKomponente(1, 1);
	//mySolver.eulerVerfahren(0, 2, 100, lul);
	//mySolver.heunVerfahren(0, 2, 100, lul); 

	C_DGLSolver mySolverZwei(dglDritterOrdnungF); 
	CMyVektor startVektorZwei(3); 
	startVektorZwei.setKomponente(0, 1); 
	startVektorZwei.setKomponente(1, -1);
	startVektorZwei.setKomponente(2, 2);
	//mySolverZwei.heunVerfahren(0, 2, 100, startVektorZwei);
	//mySolverZwei.eulerVerfahren(1, 2, 100, startVektorZwei); 

	for (int i = 10; i <= 10000; i = i * 10)
	{
		CMyVektor y = mySolverZwei.eulerVerfahrenNoPrint(1, 2, i, startVektorZwei); 
		cout << "Abweichung bei Euler bei " << i << " Schritten: " << y.getKomponente(0) - 0.5 << endl;
		CMyVektor y_heun = mySolverZwei.heunVerfahrenNoPrint(1, 2, i, startVektorZwei);
		cout << "Abweichung bei Heun bei " << i << " Schritten: " << y_heun.getKomponente(0) - 0.5 << endl;
	}
	std::system("PAUSE");
	return 0;
}
