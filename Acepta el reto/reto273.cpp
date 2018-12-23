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

#define DOMJUDGE

bool resuelveCaso() {
	std::string f, c;
	std::cin >> c >> f;
	if (std::cin.fail()) return false;
	else {
		std::vector<std::vector<int>> v(f.length() + 1, std::vector<int>(c.length() + 1, 0));

		for (int i = 1; i <= f.length(); ++i) {
			for (int j = 1; j <= c.length(); ++j) {
				if (f.at(i - 1) == c.at(j - 1))
					v[i][j] = v[i - 1][j - 1] + 1;
				else v[i][j] = std::max(v[i][j - 1], v[i - 1][j]);
			}
		}

#ifndef DOMJUDGE
		std::cout << " ";
		for (int i = 0; i < c.length(); ++i)
			std::cout << " " << c[i];
		for (int i = 1; i <= f.length(); ++i) {
			std::cout << "\n" << f[i - 1];
			for (int j = 1; j <= c.length(); ++j)
				std::cout << " " << v[i][j];
		}
		std::cout << "\n";
#endif
		std::cout << v[f.length()][c.length()] << "\n";
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