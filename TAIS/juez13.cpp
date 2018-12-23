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

bool ovejas(std::pair<int, int> inicio, char c, std::vector<std::vector<char>> const& m, std::vector <std::vector<bool>> & b, std::vector<std::pair<int, int>> const& dir) {
	std::queue<std::pair<int, int>> q;
	q.push(inicio);
	bool valid = true;
	int x, y;
	while (!q.empty()) {
		auto v = q.front(); q.pop();
		for (auto d : dir) {
			y = v.first + d.first;
			x = v.second + d.second;
			if (y >= 0 && y < m.size() && x >= 0 && x < m[0].size()) {
				if (!b[y][x]) {
					if (m[y][x] == c) {
						b[y][x] = true;
						q.push({ y, x });
					}
					else {
						valid = false;
					}
				}
			}
		}
	}
	return valid;
}

bool resuelveCaso() {
	int ancho;
	std::cin >> ancho;
	if (std::cin.fail()) return false;
	else {
		int alto;
		char c;
		std::cin >> alto;
		std::vector<std::vector<char>> m(alto, std::vector<char>(ancho));
		for (int i = 0; i < alto; ++i) {
			for (int j = 0; j < ancho; ++j) {
				std::cin >> c;
				m[i][j] = c;
			}
		}

		std::vector<std::pair<int, int>> dir = { { -1, -1 },{ -1, 0 },{ -1, 1 },{ 0, -1 },{ 0, 1 },{ 1, -1 },{ 1, 0 },{ 1, 1 } };
		std::vector<std::pair<int, int>> dir2 = { { 0, -1 },{ 1, 0 },{ 0, 1 },{ -1, 0 } };
		std::vector<std::vector<bool>> b(alto, std::vector<bool>(ancho, false));
		int ovejasBlancas = 0;
		if (alto > 0 && ancho > 0) ovejas({ 0, 0 }, '.', m, b, dir2);

		for (int i = 0; i < m.size(); ++i)
			for (int j = 0; j < m[i].size(); ++j)
				if (!b[i][j] && m[i][j] == 'X')
					if (!ovejas({ i, j }, 'X', m, b, dir))
						++ovejasBlancas;

#ifndef DOMJUDGE
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m[i].size(); ++j) {
				std::cout << m[i][j] << " ";
			}
			std::cout << "\n";
		}
		for (int j = 0; j < ancho; ++j) std::cout << "---";
		std::cout << "\n";
		for (int i = 0; i < b.size(); ++i) {
			for (int j = 0; j < b[i].size(); ++j) {
				std::cout << (b[i][j] ? '#' : '.') << " ";
			}
			std::cout << "\n";
		}
#endif 
		std::cout << ovejasBlancas << "\n";
		return true;
	}
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