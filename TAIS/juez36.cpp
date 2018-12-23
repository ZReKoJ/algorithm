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

const int INF = 1000000000;

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (std::cin.fail()) return false;
	else {
		std::vector<std::pair<int, int>> v(num);
		for (int i = 0; i < v.size(); ++i) std::cin >> v[i].first;
		for (int i = 0; i < v.size(); ++i) std::cin >> v[i].second;
		int c; std::cin >> c;
		std::sort(v.begin(), v.end());

		std::vector<std::vector<int>> m(num + 1, std::vector<int>(c + 1));
		for (int j = 1; j < m[0].size(); ++j) m[0][j] = INF;
		int cont;
		for (int i = 1; i < m.size(); ++i) {
			for (int j = 1; j < m[i].size(); ++j) {
				m[i][j] = m[i - 1][j];
				if (j >= v[i - 1].first) {
					cont = std::min(j / v[i - 1].first, v[i - 1].second);
					while (cont > 0) {
						m[i][j] = std::min(m[i][j], m[i - 1][j - (cont * v[i - 1].first)] + cont);
						--cont;
					}
				}
			}
		}

#ifndef DOMJUDGE
		int espacio = 3;
		std::cout << std::setw(espacio + 1) << " ";
		for (int j = 1; j < m[0].size(); ++j)
			std::cout << std::setw(espacio) << j;
		std::cout << "\n";
		for (int i = 1; i < m.size(); ++i) {
			std::cout << std::setw(espacio) << v[i - 1].first << ":";
			for (int j = 1; j < m[i].size(); ++j) {
				std::cout << std::setw(espacio);
				if (m[i][j] >= INF) std::cout << "#";
				else std::cout << m[i][j];
			} 
			std::cout << "\n";
		}
#endif

		int ans = m[num][c];
		if (ans >= INF) std::cout << "NO\n";
		else std::cout << "SI " << ans << "\n";
		return true;
	}
	
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