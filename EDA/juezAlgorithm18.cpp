// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

/*
Forma especial para recorrer el matriz
primero el diagonal despues el triangulo superior y el triangulo inferior

Coste Implementacion f(filas * columnas); // Lineal
*/

void resolver(const std::vector<std::vector<int>>& m) {
	int suma = 0, sumaD = 0;

	for (int i = 0; i < m.size(); ++i) {
		sumaD += m[i][i];
	}
	std::cout << sumaD << " ";
	for (int i = 1; i < m.size(); ++i) {
		for (int j = 0; j < m.size() - i; ++j) {
			suma += m[j][j + i];
		}
		std::cout << suma << " ";
		suma = 0;
	}
	std::cout << '\n';
	std::cout << sumaD << " ";
	for (int i = 1; i < m.size(); ++i) {
		for (int j = 0; j < m.size() - i; ++j) {
			suma += m[j + i][j];
		}
		std::cout << suma << " ";
		suma = 0;
	}
	std::cout << '\n';
}

bool resuelveCaso() {
	int dim, valor;
	std::cin >> dim;
	if (!std::cin.fail()) {
		std::vector<std::vector<int>> m(dim, std::vector<int>(dim));
		for (int i = 0; i < dim; ++i) {
			for (int j = 0; j < dim; ++j) {
				std::cin >> valor;
				m[i][j] = valor;
			}
		}
		resolver(m);
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}