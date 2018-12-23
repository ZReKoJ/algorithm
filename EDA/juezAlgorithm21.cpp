// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <sstream>

/*
Se recorre la matriz de forma diagonal mediante 2 parametros
y guardarlos en un vector auxiliar
y en el vector auxiliar se busca la franja maxima

Coste Implementacion O(dimension * dimension + dimension) // Lineal respecto a la matriz (dimension * dimension) y lineal respecto al vector (dimension)
*/

int resolver(const std::vector<std::vector<int>> & m, int valor) {
	std::vector<int> v(m.size());
	int suma;

	for (int i = 1; i <= m.size(); ++i) {
		suma = 0;
		for (int j = 0; j < i; ++j) {
			suma += m[j][m.size() + j - i];
		}
		v[i - 1] = suma / i;
	}

	int cont = 0, max = 0;

	for (int i = 0; i < v.size(); ++i) {
		if (v[i] >= valor)
			++cont;
		else
			cont = 0;
		if (cont > max)
			max = cont;
	}

	return max;
}

bool resuelveCaso() {
	int dimension, valor;
	std::cin >> dimension;
	if (!std::cin.fail()) {
		std::cin >> valor;
		std::vector<std::vector<int>> m(dimension, std::vector<int>(dimension));
		for (int i = 0; i < dimension; ++i)
			for (int j = 0; j < dimension; ++j)
				std::cin >> m[i][j];

		int solucion = resolver(m, valor);
		std::cout << solucion << '\n';

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

	while(resuelveCaso()){}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}