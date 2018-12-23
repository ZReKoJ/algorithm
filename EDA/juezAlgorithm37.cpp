// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <climits>

//#define RKJ

/*
Primero se recorre cada una de las ramas haciendo sus calculos correspondientes
Despues ver si es correcto la operacion realizada
Despues ver si se ha conseguido la solucion y se busca el mejor para guardarlo en min
La estimacion se basa en hacer un array de minimos acumulados
se comprueba sumando estos minimos con los resultados actuales para ver si ha superado el minimo y si supera no entra a la siguente recursion
*/

void resolver(const std::vector<std::vector<int>> &m, std::vector<int> &contador, int stage, int &min, int menor, const std::vector<int> &cMin) {
	for (int i = 0; i < m.size(); ++i) {
		if (contador[i] < 3) {
			menor += m[i][stage];
			++contador[i];
#ifdef RKJ
			for (int a = 0; a < m.size(); ++a) {
				for (int c = 0; c < m[a].size(); ++c) {
					if (b[a][c])
						std::cout << "T ";
					else
						std::cout << "F ";
				}
				std::cout << '\n';
			}
			std::cout << "-------------------------------------------\n";
#endif
			if (stage < m[0].size() - 1) {
				if ((menor + cMin[stage + 1]) < min) {
					resolver(m, contador, stage + 1, min, menor, cMin);
				}
			}
			else {
				if (menor < min)
					min = menor;
			}
			--contador[i];
			menor -= m[i][stage];
		}
	}
}

void resuelveCaso() {
	int numMercados, numProductos;
	std::cin >> numMercados >> numProductos;
	std::vector<std::vector<int>> m(numMercados, std::vector<int>(numProductos));
	std::vector<int> contador(numMercados);
	std::vector<int> cMin(numProductos);
	for (int i = 0; i < m.size(); ++i)
		for (int j = 0; j < m[i].size(); ++j)
			std::cin >> m[i][j];
	for (int i = 0; i < numProductos; ++i) {
		cMin[i] = m[0][i];
		for (int j = 1; j < numMercados; ++j) {
			if (m[j][i] < cMin[i])
				cMin[i] = m[j][i];
		}
	}
	for (int i = cMin.size() - 2; i >= 0; --i)
		cMin[i] += cMin[i + 1];
	int min = INT_MAX;
	resolver(m, contador, 0, min, 0, cMin);
	std::cout << min << '\n';
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}