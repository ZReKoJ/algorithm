// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Primero se recorre cada una de las ramas haciendo sus calculos correspondientes
Despues ver si es correcto la operacion realizada
Despues ver si se ha conseguido la solucion y se busca el mejor para guardarlo en min
*/

bool esValido(std::vector<bool> &b, int stage) {
	int contador = 0;
	for (int i = 0; i < b.size(); ++i)
		if (b[i])
			++contador;
	return contador == stage;
}

void resolver(std::vector<std::vector<int>> &m, std::vector<bool> &b, int &min, int stage, int menor) {
	for (int i = 0; i < m.size(); ++i) { // Recorriendo todas las ramas
		menor += m[stage - 1][i];
		b[i] = true;

		if (esValido(b, stage)) { // Validez
			if (stage < m.size()) // Recursion
				resolver(m, b, min, stage + 1, menor);
			else {
				if (menor < min) // Guardando solucion
					min = menor;
			}
			b[i] = false;
		}

		menor -= m[stage - 1][i]; // Poniendo los datos a normal
	}
}

bool resuelveCaso() {
	int numValores, min;

	std::cin >> numValores;
	if (numValores != 0) {
		std::vector<std::vector<int>> m(numValores, std::vector<int> (numValores));

		for (int i = 0; i < numValores; ++i) {
			for (int j = 0; j < numValores; ++j) {
				std::cin >> m[i][j];
			}
		}
		int min = 0;
		for (int i = 0; i < m.size(); ++i)
			min += m[i][i];

		std::vector<bool> b(numValores);

		resolver(m, b, min, 1, 0);
		std::cout << min << '\n';

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