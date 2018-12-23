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

void mochila_pd(std::vector<int> const& P, std::vector<int> const& V, int M, int & valor, std::vector<bool> & cuales) {
	size_t n = P.size() - 1;
	std::vector<std::vector<int>> mochila(n + 1, std::vector<int>(M + 1, 0));
	// rellenar la matriz
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (P[i] > j)
				mochila[i][j] = mochila[i - 1][j];
			else
				mochila[i][j] = std::max(mochila[i - 1][j], mochila[i - 1][j - P[i]] + V[i]);
		}
	}
	valor = mochila[n][M];
	// cálculo de los objetos
	int resto = M;
	for (size_t i = n; i >= 1; --i) {
		if (mochila[i][resto] == mochila[i - 1][resto]) {
			// no cogemos objeto i
			cuales[i] = false;
		}
		else { // sí cogemos objeto i
			cuales[i] = true;
			resto = resto - P[i];
		}
	}
}

bool resuelveCaso() {
	int segundos;
	std::cin >> segundos;
	if (std::cin.fail()) return false;
	else {
		int numOros;
		std::cin >> numOros;
		std::vector<std::pair<int, int>> v(numOros);
		for (int i = 0; i < numOros; ++i)
			std::cin >> v[i].first >> v[i].second;
		std::vector<std::vector<int>> m(numOros + 1, std::vector<int>(segundos + 1, 0));
		int s;
		for (int i = 1; i < m.size(); ++i) {
			for (int j = 1; j < m[i].size(); ++j) {
				s = v[i - 1].first * 3;
				if (s > j) m[i][j] = m[i - 1][j];
				else m[i][j] = std::max(m[i - 1][j], m[i - 1][j - s] + v[i - 1].second);
			}
		}
		int valor = m[numOros][segundos], cont = 0, resto = segundos;
		std::vector<bool> b(numOros, false);
		for (int i = numOros; i > 0; --i) {
			if (m[i][resto] != m[i - 1][resto]) {
				++cont;
				b[i - 1] = true;
				resto -= v[i - 1].first * 3;
			}
		}
		std::cout << valor << "\n" << cont << "\n";
		for (int i = 0; i < b.size(); ++i)
			if (b[i]) std::cout << v[i].first << " " << v[i].second << "\n";
		std::cout << "----\n";
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