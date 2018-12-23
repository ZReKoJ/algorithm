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

void resolver(std::vector<std::vector<char>> const& m, std::vector<std::vector<bool>> & b, int y, int x, int & counter, std::vector<std::pair<int, int>> const& dir) {
	b[y][x] = true;
	++counter;
	int y2, x2;
	for (auto d : dir) {
		y2 = y + d.first; x2 = x + d.second;
		if (m.size() > 0 && y2 >= 0 && y2 < m.size() && x2 >= 0 && x2 < m[0].size() && m[y2][x2] == '#') {
			if (!b[y2][x2])
				resolver(m, b, y2, x2, counter, dir);
		}
	}
}

bool resuelveCaso() {
	int ancho, alto;
	std::cin >> alto;
	if (std::cin.fail())
		return false;
	else {
		std::cin >> ancho;
		std::vector<std::vector<char>> m(alto, std::vector<char>(ancho));
		std::string line;
		getline(std::cin, line);
		for (int i = 0; i < alto; ++i) {
			getline(std::cin, line);
			for (int j = 0; j < ancho; ++j)
				m[i][j] = line.at(j);
		}

		std::vector<std::vector<bool>> b(alto, std::vector<bool>(ancho, false));
		std::vector<std::pair<int, int>> dir = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

		int max = 0, counter = 0;

		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m[i].size(); ++j) {
				if (m[i][j] == '#' && !b[i][j]) {
					resolver(m, b, i, j, counter, dir);
					if (counter > max) max = counter;
					counter = 0;
				}
			}
		}
		printf("%d\n", max);
		return true;
	}
}

#define RKJ

int main() {
#ifndef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifndef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}