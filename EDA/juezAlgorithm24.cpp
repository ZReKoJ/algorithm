// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Guardo las medias en un vector auxiliar y a partir de ella sacar los resultados

Coste lineal respecto al vector auxiliar
*/

void resolver(const std::vector<std::vector<int>> &m, int valor) {
	int suma, contDiag = 0, max = 0, inicio, contFranjas = 0;
	std::vector<int> v(m.size());

	for (int i = 0; i < m.size(); ++i) {
		suma = 0;
		for (int j = 0; j < m.size() - i; ++j) {
			suma += m[j + i][j];
		}
		v[i] = suma / (m.size() - i);
	}

	for (int i = 0; i < v.size(); ++i) {
		if (v[i] >= valor)
			++contDiag;
		else
			contDiag = 0;

		if (contDiag > max) {
			max = contDiag;
			inicio = i - max + 1;
		}
	}

	contDiag = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] >= valor)
			++contDiag;
		else
			contDiag = 0;

		if (contDiag == max)
			++contFranjas;
	}

	if (max == 0)
		std::cout << "NO\n";
	else
		std::cout << max << " " << inicio << " " << contFranjas << '\n';
}

bool resuelveCaso() {
	int dimension, valor;

	std::cin >> dimension;
	if (!std::cin.fail()) {
		std::cin >> valor;
		std::vector<std::vector<int>> m(dimension, std::vector<int>(dimension));

		for (int i = 0; i < m.size(); ++i)
			for (int j = 0; j < m[i].size(); ++j)
				std::cin >> m[i][j];

		resolver(m, valor);

		return true;
	}
	else return false;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}