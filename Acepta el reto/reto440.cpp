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
		for (int i = 1; i < v.size(); ++i)
			if (v[i - 1] < v[i]) v[i] = v[i - 1];
		int cont = 1, min = INT_MAX, max = 0, grupos = 0;
		for (int i = 1; i < v.size(); ++i) {
			if (v[i - 1] == v[i]) {
				cont++;
			}
			else {
				++grupos;
				max = std::max(max, cont);
				min = std::min(min, cont);
				cont = 1;
			}
		}
		grupos++;
		max = std::max(max, cont);
		min = std::min(min, cont);
		std::cout << grupos << " " << min << " " << max << "\n";
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