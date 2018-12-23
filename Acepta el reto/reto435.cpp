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

bool resuelveCaso() {
	std::string p;
	std::cin >> p;
	if (std::cin.fail()) return false;
	else {
		std::vector<int> v(10, 0);
		int a;
		for (int i = 0; i < p.length(); ++i) {
			a = int(p.at(i));
			a -= int('0');
			++v[a];
		}
		bool b = true;
		for (int i = 0; i < v.size() - 1; ++i) {
			b = b && (v[i] == v[i + 1]);
		}
		if (b) std::cout << "subnormal\n";
		else std::cout << "no subnormal\n";
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