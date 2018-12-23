// TAIS19, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <list>
#include <climits>
#include <limits.h>
#include <limits>
#include <queue>

bool resuelveCaso() {
	int numAgujeros;
	std::cin >> numAgujeros;
	if (std::cin.fail()) return false;
	else {
		int longitud;
		std::cin >> longitud;
		std::vector<int> v(numAgujeros);
		for (int i = 0; i < numAgujeros; ++i)
			std::cin >> v[i];
		if (v.size() > 0) {
			int inicio = v[0], acumula = 1, i = 1;
			while (i < v.size()) {
				if (v[i] - inicio > longitud) {
					inicio = v[i];
					++acumula;
				}
				++i;
			}
			std::cout << acumula << "\n";
		}
		else std::cout << "0\n";
		return true;
	}
}

/* El coste de este algoritmo es de
O(n)
n es el numero de agujeros en la manguera
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