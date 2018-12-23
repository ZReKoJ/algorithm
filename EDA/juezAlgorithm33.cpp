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
La estimacion se basa en hacer un array de minimos acumulados
se comprueba sumando estos minimos con los resultados actuales para ver si ha superado el minimo y si supera no entra a la siguente recursion
*/

void resolver(const std::vector<std::vector<int>> &m, std::vector<bool> &b, int bCounter, int &min, int stage, int menor, const std::vector<int> &cMin) {
	for (int i = 0; i < m.size(); ++i) { // Recorriendo todas las ramas
		menor += m[stage - 1][i];

		if (!b[i]) { // Validez
			b[i] = true;
			++bCounter;
			if (stage < m.size()) { // Recursion
				if ((menor + cMin[stage]) < min) { // Estimacion
					resolver(m, b, bCounter, min, stage + 1, menor, cMin);
				}
			}
			else {
				if (menor < min) // Guardando solucion
					min = menor;
			}
			--bCounter;
			b[i] = false;
		}

		menor -= m[stage - 1][i]; // Poniendo los datos a normal
	}
}

bool resuelveCaso() {
	int numValores, min;

	std::cin >> numValores;
	if (numValores != 0) {
		std::vector<std::vector<int>> m(numValores, std::vector<int>(numValores));
		std::vector<int> cMin(m.size());

		for (int i = 0; i < numValores; ++i) {
			std::cin >> m[i][0];
			cMin[i] = m[i][0];
			for (int j = 1; j < numValores; ++j) {
				std::cin >> m[i][j]; // Matriz
				if (m[i][j] < cMin[i]) // Array de minimos
					cMin[i] = m[i][j];
			}
		}
		int min = 0;
		for (int i = 0; i < m.size(); ++i)
			min += m[i][i];

		std::vector<bool> b(numValores); // Matriz booleanos
		for (int i = cMin.size() - 2; i >= 0; --i) // Minimos acumulados
			cMin[i] += cMin[i + 1];

		resolver(m, b, 0, min, 1, 0, cMin);
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