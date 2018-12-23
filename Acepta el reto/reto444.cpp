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
#include <map>

bool resuelveCaso() {
	int num, k;
	std::cin >> num >> k;
	if (num == 0 && k == 0) return false;
	else {
		std::vector<int> v(num);
		for (int i = 0; i < num; ++i) std::cin >> v[i];
		bool periodo = false;
		int ceroCount = 0, cont = 0, max = 0, uno = -1, ultimoUno = -1;
		for (int i = 0; i < v.size(); ++i) {
			if (v[i] == 0) {
				ceroCount++;
			}
			else {
				if (!periodo) {
					periodo = true;
					uno = i;
				}
				ultimoUno = i;
				ceroCount = 0;
			}
			if (ceroCount > k) {
				periodo = false;
				if (uno != -1 && ultimoUno != -1)
					max = std::max(max, ultimoUno - uno + 1);
				ceroCount = 0;
				uno = -1;
			}
		}
		if (uno != -1 && ultimoUno != -1)
			max = std::max(max, ultimoUno - uno + 1);
		std::cout << max << "\n";
		return true;
	}
}

#define RKJ
int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifdef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}