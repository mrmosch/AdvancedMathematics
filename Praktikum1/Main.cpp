#include "pch.h"
#include <iostream>
#include "CMyVektor.h"

using namespace std;

int main()
{
	CMyVektor a(3);
	a.setWerte(0, 1);
	a.setWerte(1, 2);
	a.setWerte(2, 3);

	CMyVektor b(3);
	b.setWerte(0, 4);
	b.setWerte(1, 5);
	b.setWerte(2, 6);

	cout << a;
	cout << b;
	
	cout << "Addition" << (a+b);

	return 0;
}