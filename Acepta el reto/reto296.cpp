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

typedef struct {
	int ini;
	int fin;
}tTramo;

bool operator<(tTramo const& a, tTramo const& b) {
	if (a.ini == b.ini) return a.fin > b.fin;
	else return a.ini < b.ini;
}

bool resuelveCaso() {
	int ini, fin, num;
	std::cin >> ini >> fin >> num;
	if (ini == 0 && fin == 0 && num == 0) return false;
	else {
		std::vector<tTramo> v(num);
		for (int i = 0; i < num; ++i)
			std::cin >> v[i].ini >> v[i].fin;
		std::less<tTramo> l;
		std::sort(v.begin(), v.end(), l);
		int limit = ini, max = ini, cont = 0;
		for (int i = 0; i < v.size() && limit < fin; ++i) {
			if (v[i].ini > limit) {
				limit = max;
				++cont;
			}
			if (v[i].ini <= limit && v[i].fin > max) max = v[i].fin;
		}
		if (limit >= fin) std::cout << cont << "\n";
		else {
			if (max >= fin) std::cout << cont + 1 << "\n";
			else std::cout << "Imposible\n";
		}
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