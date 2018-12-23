// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <climits>

/*
RecursionFinal y no final
se basa en hacer modulos
*/

void resolverFinal(int num, int &sol) {
	sol = (sol * 10) + num % 10;
	if (num >= 10) {
		resolverFinal(num / 10, sol);
	}
}

int resolverNoFinal(int num, int &potencia) {
	if (num >= 10) {
		int x = resolverNoFinal(num / 10, potencia);
		int resto = num % 10;
		potencia *= 10;
		return (resto * potencia) + x;
	}
	else {
		return num;
	}
}

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (!std::cin.fail()) {
		int sol = 0;
		//resolverFinal(num, sol);
		//std::cout << sol << '\n';
		int potencia = 1;
		std::cout << resolverNoFinal(num, potencia) << '\n';
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock(), tParcial = t;
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