// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Recursion no final
Divido cada array en dos mitades y de esta a su vez en dos hasta que salga arrays de 1 valor 
de alli se comprueba los requisitos descritos

T(0) = c0; T(n) = 2T(n / 2) + C0 --> O(2 ^ n)
*/

bool resolver(std::vector<int> &v, int ini, int fin, int &max, int&min) {
	if (fin <= ini) { max = v[ini]; min = v[ini]; return true; }
	else {
		int maxIzq, maxDch, minIzq, minDch, mitad = (fin + ini) / 2;
		bool izq = resolver(v, ini, mitad, maxIzq, minIzq);
		bool dch = resolver(v, mitad + 1, fin, maxDch, minDch);
		if (maxDch >= maxIzq && minIzq <= minDch && izq && dch) {
			max = maxDch; min = minIzq; return true;
		}
		else return false;
	}
}

bool resuelveCaso() {
	int numValores, cambios = 0;

	std::cin >> numValores;
	if (numValores != 0) {
		std::vector<int> v;
		v.emplace_back(numValores);

		std::cin >> numValores;
		while (numValores != 0) {
			v.emplace_back(numValores);
			std::cin >> numValores;
		}

		int max, min;
		if (resolver(v, 0, v.size() - 1, max, min))
			std::cout << "SI\n";
		else
			std::cout << "NO\n";

		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}