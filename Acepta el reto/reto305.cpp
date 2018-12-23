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
	if (std::cin.fail()) return false;
	else {
		std::vector<int> enemigos(num), aliados(num);
		for (int i = 0; i < num; ++i)
			std::cin >> enemigos[i];
		for (int i = 0; i < num; ++i)
			std::cin >> aliados[i];
		std::sort(enemigos.begin(), enemigos.end());
		std::sort(aliados.begin(), aliados.end());
		int i = 0, j = 0, cont = 0;
		while (j < aliados.size()) {
			if (aliados[j] >= enemigos[i]) {
				++cont;
				++i;
			}
			++j;
		}
		std::cout << cont << "\n";
		return true;
	}
}

#define DOMJUDGE
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