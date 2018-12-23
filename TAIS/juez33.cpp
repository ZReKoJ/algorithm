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

/*
v[i] = el corte i v[j] = el corte j
esfuerzo(i, j) = es el esfuerzo minimo necesario para cortar la tabla de longitud v[j] - v[i] (desde i hasta j) dados unos cortes
esfuerzo(i, j) = {
	el minimo de todos los cortes de la tabla de longitud j - i cortando por k (esfuerzo(i, k) + esfuerzo(k, j)) // donde k son los cortes entre i e j
}
El tiempo es O(v^3) // Donde v es el numero de cortes que hay que hacer
El espacio es O(v^2) // Donde v es el numero de cortes que hay que hacer
*/

const int INF = 1000000000, ESPACIO = 5;

int calculo(int i, int j, const std::vector<int> &v, const std::vector<std::vector<int>> &m) {
	int min = INF;
	for (int k = i + 1; k < j; ++k) {
		min = std::min(m[i][k] + m[k][j] + (2 * (v[j] - v[i])), min);
	}
	return min >= INF ? 0 : min;
}

bool resuelveCaso() {
	int longitud, num;
	std::cin >> longitud >> num;
	if (longitud == 0 && num == 0) return false;
	else {
		std::vector<int> v;
		v.emplace_back(0);
		int n;
		for (int i = 0; i < num; ++i) {
			std::cin >> n;
			v.emplace_back(n);
		}
		v.emplace_back(longitud);
		std::vector<std::vector<int>> m(v.size(), std::vector<int>(v.size(), 0));
		for (int d = 1; d < m.size(); ++d) {
			for (int i = 0; i < m.size() - d; ++i) {
				int j = i + d;
				m[i][j] = calculo(i, j, v, m);
			}
		}
#ifndef DOMJUDGE
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m[i].size(); ++j) {
				if (m[i][j] >= INF) std::cout << std::setw(ESPACIO) << "#";
				else std::cout << std::setw(ESPACIO) << m[i][j];
			}
			std::cout << "\n";
		}
#endif
		std::cout << m[0][v.size() - 1] << "\n";
		return true;
	}
}

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