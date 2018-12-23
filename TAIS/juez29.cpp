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

const int INF = 1000000000;

bool resuelveCaso() {
	int cantidad;
	std::cin >> cantidad;
	if (std::cin.fail()) return false;
	else {
		int sectores;
		std::cin >> sectores;
		std::vector<int> v(sectores);
		for (int i = 0; i < v.size(); ++i)
			std::cin >> v[i];
		std::vector<std::vector<int>> m(sectores + 1, std::vector<int>(cantidad + 1, 0));
		for (int i = 1; i < m[0].size(); ++i) m[0][i] = INF;
		std::sort(v.begin(), v.end());
		for (int i = 1; i < m.size(); ++i) {
			for (int j = 1; j < m[i].size(); ++j) {
				if (j >= v[i - 1])
					m[i][j] = std::min(m[i][j - v[i - 1]] + 1, m[i - 1][j]);
				else m[i][j] = m[i - 1][j];
			}
		}

#ifndef DOMJUDGE
		std::cout << std::setw(3) << std::left << " ";
		for (int i = 0; i < m[0].size(); ++i) std::cout << std::setw(3) << std::left << i;
		std::cout << "\n";
		for (int i = 0; i < m.size(); ++i) {
			if (i == 0) std::cout << std::setw(3) << std::left << " ";
			else std::cout << std::setw(3) << std::left << v[i - 1];
			for (int j = 0; j < m[i].size(); ++j) {
				if (m[i][j] >= INF) std::cout << std::setw(3) << std::left << "#";
				else std::cout << std::setw(3) << std::left << m[i][j];
			}
			std::cout << "\n";
		}
#endif
		int pos = v.size();
		if (m[pos][cantidad] >= INF) std::cout << "Imposible\n";
		else {
			std::cout << m[pos][cantidad] << ":";
			while (m[pos][cantidad] != 0) {
				if (cantidad >= v[pos - 1] && m[pos][cantidad - v[pos - 1]] < m[pos][cantidad]) {
					cantidad -= v[pos - 1];
					std::cout << " " << v[pos - 1];
				}
				else --pos;
			}
			std::cout << "\n";
		}
		
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