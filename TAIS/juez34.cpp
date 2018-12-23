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
	int num;
	std::cin >> num;
	if (num == 0) return false;
	else {
		std::vector<int> v(num);
		for (int i = 0; i < num; ++i)
			std::cin >> v[i];
		std::vector<std::vector<int>> m(num, std::vector<int>(num, 0));
		for (int i = 0; i < v.size(); ++i)
			m[i][i] = v[i];
		int ii, jj, res1, res2;
		for (int d = 1; d < m.size(); ++d) {
			for (int i = 0; i < m.size() - d; ++i) {
				int j = i + d;
				ii = i + 1; jj = j; res1 = v[i];
				if (ii < jj) {
					(v[ii] < v[jj]) ? jj-- : ii++;
					res1 += m[ii][jj];
				}
				ii = i; jj = j - 1; res2 = v[j];
				if (ii < jj) {
					(v[ii] < v[jj]) ? jj-- : ii++;
					res2 += m[ii][jj];
				}
				m[i][j] = std::max(res1, res2);
			}
		}
#ifndef DOMJUDGE
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m[i].size(); ++j) {
				std::cout << std::setw(3) << m[i][j];
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

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}