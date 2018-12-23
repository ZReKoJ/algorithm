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

#include<queue>

void bfs(
	std::vector<std::vector<char>> const& m, 
	std::vector<std::vector<std::pair<bool, int>>> & boolDist, 
	std::vector<std::pair<int, int>> const& dir,
	std::queue<std::pair<int, int>> & q
	) {
	int x, y;
	while (!q.empty()) {
		auto v = q.front(); q.pop();
		for (auto d : dir) {
			y = v.first + d.first;
			x = v.second + d.second;
			if (y >= 0 && y < m.size() && x >= 0 && x < m[0].size()) {
				if (!boolDist[y][x].first && m[y][x] == '.') {
					boolDist[y][x] = { true, boolDist[v.first][v.second].second + 1 };
					q.push({ y, x });
				}
			}
		}
	}
}

void resuelveCaso() {
	int ancho, alto;
	std::cin >> ancho >> alto;
	std::vector<std::vector<char>> m(alto, std::vector<char>(ancho));
	char c;
	std::pair<int, int> entrada, salida;
	std::vector<std::pair<std::pair<int, int>, int>> bloqueos;
	for (int i = 0; i < alto; ++i) {
		for (int j = 0; j < ancho; ++j) {
			std::cin >> c;
			m[i][j] = c;
			if (c == 'E') {
				entrada = { i, j };
				m[i][j] = '.';
			}
			else if (c == 'P') {
				salida = { i, j };
				m[i][j] = '.';
			}
			else if (int(c) >= 48 && int(c) <= 57) {
				bloqueos.emplace_back(std::pair<std::pair<int, int>, int>{ { i, j }, int(c) % 48 });
			}
			else {}
		}
	}
	int iter, x, y;
	std::vector<std::pair<int, int>> dir = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
	for (auto datos : bloqueos) {
		std::vector<bool> b = { false, false, false, false };
		iter = datos.second;
		for (int i = 1; i <= iter; ++i) {
			for (int j = 0; j < dir.size(); ++j) {
				y = datos.first.first + (i * dir[j].first);
				x = datos.first.second + (i * dir[j].second);
				if (y >= 0 && y < m.size() && x >= 0 && x < m[0].size()) {
					switch (m[y][x]) {
					case '#': b[j] = true; break;
					case '.': if (!b[j]) m[y][x] = char(iter + 48); break;
					}
				}
			}
		}
	}
	std::vector<std::vector<std::pair<bool, int>>> boolDist(alto, std::vector<std::pair<bool, int>>(ancho, { false, 0 }));
	std::queue<std::pair<int, int>> q;
	q.push(entrada);
	boolDist[entrada.first][entrada.second] = { true, 0 };
	bfs(m, boolDist, dir, q);
#ifndef DOMJUDGE
	for (int i = 0; i < alto; ++i) {
		for (int j = 0; j < ancho; ++j) {
			std::cout << std::setw(3);
			if (i == entrada.first && j == entrada.second) std::cout << "E";
			else if (i == salida.first && j == salida.second) std::cout << "P";
			else std::cout << m[i][j];
		}
		std::cout << "\n";
	}
	for (int j = 0; j < ancho; ++j) std::cout << "---";
	std::cout << "\n";
	for (int i = 0; i < alto; ++i) {
		for (int j = 0; j < ancho; ++j) {
			std::cout << std::setw(3);
			if (i == entrada.first && j == entrada.second) std::cout << "E";
			else if (i == salida.first && j == salida.second) std::cout << "P";
			else if (boolDist[i][j].second != 0) std::cout << boolDist[i][j].second;
			else std::cout << '.';
		}
		std::cout << "\n";
	}
#endif
	if (!boolDist[salida.first][salida.second].first || m[entrada.first][entrada.second] != '.' || m[salida.first][salida.second] != '.') std::cout << "NO\n";
	else std::cout << boolDist[salida.first][salida.second].second << "\n";
}

/* El coste de este algoritmo es de
O(n * m)
	n es el ancho
	m es el alto
*/
int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	//
	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i)
		resuelveCaso();
	//while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}