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
	std::string palabra;
	getline(std::cin, palabra);
	if (std::cin.fail()) return false;
	else {
		bool llevo = true;
		for (int i = palabra.size() - 1; i >= 0 && llevo; --i) {
			switch (palabra.at(i)) {
			case '.': break;
			case '9': palabra.at(i) = '0'; break;
			default: palabra.at(i) = char(int(palabra.at(i) + 1)); llevo = false; break;
			}
		}
		if (llevo) {
			std::cout << "1";
			if (palabra.size() % 4 == 3) std::cout << '.';
		}
		for (int i = 0; i < palabra.length(); ++i)
			std::cout << palabra.at(i);
		std::cout << "\n";
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