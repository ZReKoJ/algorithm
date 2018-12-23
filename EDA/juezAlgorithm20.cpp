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
Primero creo un vector auxiliar donde cada valor significa el numero de ceros que hay en la columna correspondiente

Despues compruebo mediante un contador el numero de columnas que cumple el requisito
mediante un limite superior y un limite inferior controlo la franja

Coste Implementacion f((filas * columnas) + columnas + franja); // Lineal
*/

void resolver(const std::vector<std::vector<int>>& m, int franja, int numCol, int numCeros) {
	std::vector<int> v(m[0].size());
	int cont = 0, contCol = 0;

	for (int i = 0; i < m[0].size(); ++i) {
		for (int j = 0; j < m.size(); ++j) {
			if (m[j][i] == 0)
				++v[i];
		}
	}

	for (int k = 0; k < franja; ++k) {
		if (v[k] >= numCeros) {
			++contCol;
		}
	}

	if (contCol >= numCol)
		++cont;

	for (int l = franja; l < v.size(); ++l) {
		if (v[l - franja] >= numCeros)
			--contCol;
		if (v[l] >= numCeros)
			++contCol;

		if (contCol >= numCol)
			++cont;
	}

	std::cout << cont << '\n';
}

bool resuelveCaso() {
	int filas, columnas, valor1, valor2, valor3, valor;
	std::cin >> filas;
	if (!std::cin.fail()) {
		std::cin >> columnas >> valor1 >> valor2 >> valor3;
		std::vector<std::vector<int>> m(filas, std::vector<int>(columnas));
		for (int i = 0; i < filas; ++i) {
			for (int j = 0; j < columnas; ++j) {
				std::cin >> valor;
				m[i][j] = valor;
			}
		}
		resolver(m, valor1, valor2, valor3);
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