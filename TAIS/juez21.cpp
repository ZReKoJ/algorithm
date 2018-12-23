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
	int peso;
	std::cin >> peso;
	if (std::cin.fail()) return false;
	else {
		int numSillas;
		std::cin >> numSillas;
		std::vector<int> v(numSillas);
		for (int i = 0; i < numSillas; ++i)
			std::cin >> v[i];
		std::greater<int> g;
		std::sort(v.begin(), v.end(), g);
		int i = 0, j = v.size() - 1, acumula = 0;
		while (j > i) {
			if (v[i] + v[j] <= peso) j--;
			i++;
			acumula++;
		}
		if (i == j) acumula++;
		std::cout << acumula << "\n";
		return true;
	}
}

/* El coste de este algoritmo es de
O(n * log n)
n es el numero de personas que se sientan en la silla
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