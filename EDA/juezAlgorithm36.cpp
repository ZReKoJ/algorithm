// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Vuelta Atras
Como va por orden solo hay que podar las de la izq para que salga todos los resultados
*/

void resolver(std::vector<char> &v, int numLetras, int num, int stage, int letra) {
	for (int i = letra; i < numLetras; ++i) {
		v[stage] = char(97 + i);
		if (stage == num - 1) {
			for (int j = 0; j < v.size(); ++j)
				std::cout << v[j] << " ";
			std::cout << '\n';
		}
		else resolver(v, numLetras, num, stage + 1, i + 1);
	}
}

bool resuelveCaso() {
	int numLetras, num;
	std::cin >> numLetras;
	if (!std::cin.fail()) {
		std::cin >> num;
		std::vector<char> v(num);
		resolver(v, numLetras, num, 0, 0);
		return true;
	}
	else return false;
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