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
	int num;
	std::cin >> num;
	if (num == 0) return false;
	else {
		std::vector<int> v(num);
		for (int i = 0; i < num; ++i)
			std::cin >> v[i];
		int min = INT_MAX, min2 = INT_MAX, cont = 0;
		std::vector<int> w(num);
		for (int i = v.size() - 1; i >= 0; --i) {
			if (v[i] <= min)
				min = v[i];
			else {
				if (v[i] < min2) min2 = v[i];
				++cont;
			}
			w[i] = min;
		}
		for (int i = v.size() - 1; i >= 0; --i) {
			if (v[i] == w[i]) {
				if (min2 < w[i]) ++cont;
			}
		}
		std::cout << cont << "\n";
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