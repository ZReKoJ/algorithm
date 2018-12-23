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
	int h, m, s;
	char residuo;
	std::cin >> h >> residuo >> m >> residuo >> s;
	int segundos = (h * 60) + m;
	segundos = (segundos * 60) + s;
	segundos = 86400 - segundos;
	int hh, mm, ss;
	ss = segundos % 60;
	segundos /= 60;
	mm = segundos % 60;
	hh = segundos / 60;
	std::cout << std::setfill('0') << std::setw(2) << hh << ":" << std::setw(2) << mm << ":" << std::setw(2) << ss << "\n";
	return true;
}

#define RKJ
int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i) {
		resuelveCaso();
	}
	//while (resuelveCaso()) {}

#ifdef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}