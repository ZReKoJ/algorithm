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
#include "PriorityQueue.h"

struct Nodo {
	std::vector<bool> b;
	int k;
	int tiempo;
	int tiempoEst;
};

bool operator<(Nodo const& a, Nodo const&b) {
	if (a.tiempoEst == b.tiempoEst) return a.tiempo < b.tiempo;
	else return a.tiempoEst < b.tiempoEst;
}

int ramificacionYPoda(std::vector<std::vector<int>> const& m, std::vector<int> const& v) {
	int t = 0, mejor = INT_MAX;
	PriorityQueue<Nodo> pq;
	pq.push({ std::vector<bool>(v.size() - 1, false), 0, 0, v[0] });
	Nodo n, nn;
	while (!pq.empty() && pq.top().tiempoEst < mejor) {
		n = pq.top(); pq.pop();
		for (int j = 0; j < m[0].size(); ++j) {
			if (n.k < m.size()) {
				if (!n.b[j] && n.tiempoEst < mejor) {
					nn = n;
					nn.b[j] = true;
					nn.k++;
					nn.tiempo += m[n.k][j];
					nn.tiempoEst = nn.tiempo + v[n.k + 1];
					pq.push(nn);
				}
			}
			else {
				mejor = std::min(n.tiempo, mejor);
			}
		}
	}
	return mejor;
}

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (num == 0) return false;
	else {
		std::vector<std::vector<int>> m(num, std::vector<int>(num));
		std::vector<int> v(num);
		for (int i = 0; i < num; ++i) {
			std::cin >> m[i][0];
			v[i] = m[i][0];
			for (int j = 1; j < num; ++j) {
				std::cin >> m[i][j];
				v[i] = std::min(v[i], m[i][j]); // Minimos
			}
		}
		for (int i = v.size() - 2; i >= 0; --i) // Minimos acumulados
			v[i] += v[i + 1];
		v.emplace_back(0);
		std::cout << ramificacionYPoda(m, v) << "\n";
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