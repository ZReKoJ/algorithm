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

typedef std::vector<std::vector<std::vector<std::vector<std::pair<int, char>>>>> mmmm;
const int INF = 1000000000;

#define DOMJUDGE

std::pair<int, int> calculo(int iniF, int finF, int iniC, int finC, std::vector<std::string> const& ch, mmmm & m) {
	if (m[iniF][finF][iniC][finC].first >= INF) {
		if (iniF == finF && iniC == finC)
			m[iniF][finF][iniC][finC] = { 0, ch[iniF].at(iniC) };
		else {
			std::pair<int, char> a, b;
			int min = INF;
			for (int i = iniF + 1; i <= finF; ++i) {
				a = calculo(iniF, i - 1, iniC, finC, ch, m);
				b = calculo(i, finF, iniC, finC, ch, m);
				if (a.second != '*' && a.second == b.second) {
					m[iniF][finF][iniC][finC] = { 0, a.second };
					return m[iniF][finF][iniC][finC];
				}
				else min = std::min(min, a.first + b.first + 1);
			}
			for (int j = iniC + 1; j <= finC; ++j) {
				a = calculo(iniF, finF, iniC, j - 1, ch, m);
				b = calculo(iniF, finF, j, finC, ch, m);
				if (a.second != '*' && a.second == b.second) {
					m[iniF][finF][iniC][finC] = { 0, a.second };
					return m[iniF][finF][iniC][finC];
				}
				else min = std::min(min, a.first + b.first + 1);
			}
			m[iniF][finF][iniC][finC] = { min, '*' };
		}
	}
	return m[iniF][finF][iniC][finC];
}

bool resuelveCaso() {
	int f, c;
	std::cin >> f >> c;
	if (std::cin.fail()) return false;
	else {
		std::vector<std::string> ch(f);
		mmmm m(f, std::vector<std::vector<std::vector<std::pair<int, char>>>>(
				f, std::vector<std::vector<std::pair<int, char>>>(
					c, std::vector<std::pair<int, char>>(c, { INF, '*' }))));
		// El maximo numero de espacio que ocupo es 160000, y el maximo numero de cortes es 361
		for (int i = 0; i < ch.size(); ++i) std::cin >> ch[i];
		std::cout << calculo(0, f - 1, 0, c - 1, ch, m).first << "\n";
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