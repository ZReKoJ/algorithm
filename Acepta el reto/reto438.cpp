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
	getline(std::cin, p);
	if (std::cin.fail()) return false;
	else {
		int exc = 0, alf = 0;
		char c;
		for (int i = 0; i < p.size(); ++i) {
			c = p.at(i);
			if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) ++alf;
			if (c == '!') ++exc;
		}
		std::cout << ((exc > alf) ? "ESGRITO" : "escrito") << "\n";
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