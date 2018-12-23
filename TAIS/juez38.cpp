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
#include <unordered_set>

const int MODULO = 1000000007, NUM_LETRAS = 3;

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (num == 0) return false;
	else {
		std::unordered_set<std::string> s;
		std::string clave;
		for (int i = 0; i < num; ++i) {
			std::cin >> clave;
			s.insert(clave);
		}
		s.insert("0");
		std::cin >> clave;

		std::vector<int> v(clave.length() + NUM_LETRAS, 1);
		v[v.size() - 1] = 0; v[v.size() - 2] = 0;

		long long int cont;
		for (int i = clave.length() - 1; i >= 0; --i) {
			cont = 0;
			for (int j = 1; j <= NUM_LETRAS; ++j) {
				cont += (s.count(clave.substr(i, j)) > 0 ? v[i + j] : 0);
				cont %= MODULO;
			}
			v[i] = cont;
		}
		std::cout << v[0] << "\n";
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