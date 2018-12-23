// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <sstream>

/*
Recursion no final
Cuando numValores = 0 significa que no hay ningun operacion que satisfaga la igualdad
Cuando suma = 0 significa que hay una operacion que si lo satisface
por lo tanto a partir de ella con la ayuda de una matriz se va acumulando los valores hasta hallar el numero

Ejemplo:

5 10
4 2 6 3 5

		0		1		2		3		4		5		6		7		8		9		10

0		1		0		0		0		0		0		0		0		0		0		0

1		1		01		02		03		00+04	01+05			03+07	04+08			06+010

2		1		11		10+12			12+14	13+15			15+17					18+110

3		1				22						25				21+27					24+210

4		1										32+35									37+310

5		1																				45+410

T(numValores, 0) = 1; T(0, suma) = 0; T(numValores, suma) = 2T(n - 1) --> O(2 ^ n)
*/

int resolver(const std::vector<int> &v, std::vector<std::vector<int>> &m, int numValores, int suma) {
	int a = 0, b = 0;

	if (numValores == 0 || suma == 0 || m[numValores][suma] != 0)
		return m[numValores][suma];
	else {
		if (v[numValores - 1] <= suma) 
			a = resolver(v, m, numValores - 1, suma - v[numValores - 1]);
		b = resolver(v, m, numValores - 1, suma);
		m[numValores][suma] = a + b;
		
		return a + b;
	}
}

bool resuelveCaso() {
	int numValores, numSuma, cont = 0;

	std::cin >> numValores;
	if (!std::cin.fail()) {
		std::cin >> numSuma;
		std::vector<int> v(numValores);
		std::vector<std::vector<int>> m(numValores + 1, std::vector<int>(numSuma + 1));

		for (int &valor : v)
			std::cin >> valor;

		for (int i = 0; i < m.size(); ++i)
			m[i][0] = 1;

		std::cout << resolver(v, m, v.size(), numSuma) << '\n';

		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()){}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}