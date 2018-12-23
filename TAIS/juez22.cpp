// TAIS19, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <list>
#include <climits>
#include <limits.h>
#include <limits>
#include <queue>

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (num == 0) return false;
	else {
		std::vector<int> rivales(num), broncos(num);
		for (int i = 0; i < num; ++i)
			std::cin >> rivales[i];
		for (int i = 0; i < num; ++i)
			std::cin >> broncos[i];
		std::less<int> l;
		std::greater<int> g;
		std::sort(rivales.begin(), rivales.end(), l);
		std::sort(broncos.begin(), broncos.end(), g);
		int acumula = 0;
		for (int i = 0; i < num; ++i) {
			if (broncos[i] > rivales[i])
				acumula += (broncos[i] - rivales[i]);
		}
		std::cout << acumula << "\n";
		return true;
	}
}

/* El coste de este algoritmo es de
O(n * log n)
n es el numero resultados de los partidos
*/
int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	/*
	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i)
	resuelveCaso();*/
	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}