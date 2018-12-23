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
Se calcula la primera suma y se le va restando y sumando las filas y columnas (recorriendo) y se busca la maxima suma
Lo he dividido en tres partes uno inicializacion otro las filas del medio y la fila primera y el ultimo la fila ultima

Coste Implementacion lineal

P = {0 < p <= n < 100}
func xxxx (int m[][], int n, int area) return int maximo;
Q = { maximo = max x, y : 0 <= x, y <= n - area : summation a, b : 0 <= a, b < area : m[x + a][y + b] }
*/

void resolver(const std::vector<std::vector<int>> &m, int area) {
	int suma = 0, max = 0, sumaIni;

	for (int i = 0; i < area; ++i) {
		for (int j = 0; j < area; ++j) {
			suma += m[i][j];
		}
	}

	max = suma;
	sumaIni = suma;
	//std::cout << suma << '\n';

	for (int i = area; i < m.size(); ++i) {
		for (int j = area; j < m.size(); ++j) {
			for (int k = 0; k < area; ++k) {
				suma += m[i - area + k][j];
				suma -= m[i - area + k][j - area];
			}
			if (suma > max)
				max = suma;
			//std::cout << suma << '\n';
		}
		suma = sumaIni;
		for (int l = 0; l < area; ++l) {
			suma += m[i][l];
			suma -= m[i - area][l];
		}
		sumaIni = suma;
		if (suma > max)
			max = suma;
		//std::cout << suma << '\n';
	}

	int a = m.size();
	for (int n = area; n < m.size(); ++n) {
		for (int o = 0; o < area; ++o) {
			suma += m[m.size() - area + o][n];
			suma -= m[m.size() - area + o][n - area];
		}
		sumaIni = suma;
		if (suma > max)
			max = suma;
		//std::cout << suma << '\n';
	}

	std::cout << max << '\n';
}

bool resuelveCaso() {
	int dimension, area;
	std::cin >> dimension;
	if (!std::cin.fail()) {
		std::cin >> area;
		std::vector<std::vector<int>> m(dimension, std::vector<int>(dimension));
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				std::cin >> m[i][j];
			}
		}
		resolver(m, area);
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

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}