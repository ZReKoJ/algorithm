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
#include <unordered_map>

/*
grado(i, j, k) = el minimo grado de separacion entre dos personas i e j por medio de 1 hasta k
grado(i, j) = {
el minimo de (grado(i, j, k - 1) y grado(i, k, k - 1) + grado(k, j, k - 1))
}
El tiempo es O(n^3) // Donde la n es el numero de personas
El espacio es O(n^2) // Donde la n es el numero de personas
*/

const int INF = 1000000000;

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (std::cin.fail()) return false;
	else {
		int n, from, to;
		std::cin >> n;
		std::unordered_map<std::string, int> m;
		std::vector<std::vector<int>> v(num + 1, std::vector<int>(num + 1, INF));
		for (int i = 1; i < v.size(); ++i) v[i][i] = 0;

		std::string palabra;
		for (int i = 0; i < n; ++i) {
			std::cin >> palabra;
			if (m.count(palabra) == 0) {
				from = m.size() + 1;
				m[palabra] = from;
			}
			else from = m[palabra];
			std::cin >> palabra;
			if (m.count(palabra) == 0) {
				to = m.size() + 1;
				m[palabra] = to;
			}
			else to = m[palabra];
			v[from][to] = 1;
			v[to][from] = 1;
		}

		for (int k = 1; k <= num; ++k)
			for (int i = 1; i <= num; ++i)
				for (int j = 1; j <= num; ++j)
					v[i][j] = std::min(v[i][k] + v[k][j], v[i][j]);

		int max = 0;
		bool desconectada = false;
		for (int i = 1; i < v.size() && !desconectada; ++i) {
			for (int j = i; j < v.size() && !desconectada; ++j) {
				max = std::max(max, v[i][j]);
				if (max == INF) desconectada = true;
			}
		}

#ifndef DOMJUDGE
		for (int i = 1; i < v.size(); ++i) {
			for (int j = 1; j < v[i].size(); ++j)
				std::cout << std::setw(11) << v[i][j];
			std::cout << "\n";
		}
#endif

		if (desconectada) std::cout << "DESCONECTADA\n";
		else std::cout << max << "\n";

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