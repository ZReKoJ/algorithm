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
Compara cada columna para ver si son los mismos
Y despues calcular el maximo contador

Coste Implementacion f(filas * columnas); // Lineal
*/

void resolver(const std::vector<std::vector<int>>& m) {
	bool igual = true;
	int value = -1, cont = 0, max = 0;
	for (int i = 0; i < m[0].size(); ++i) {
		if (value != m[0][i] || !igual)
			cont = 0;
		igual = true;
		value = m[0][i];
		for (int j = 1; j < m.size() && igual; ++j)
			igual = igual && (value == m[j][i]);

		if (igual)
			cont++;
		if (cont > max)
			max = cont;
	}

	std::cout << max << '\n';
}

bool resuelveCaso() {
	bool stop = false;
	int filas, columnas;
	std::cin >> filas;
	if (!std::cin.fail()) {
		std::cin >> columnas;
		std::vector<std::vector<int>> m(filas, std::vector<int>(columnas));
		for (int i = 0; i < filas; ++i)
			for (int j = 0; j < columnas; ++j)
				std::cin >> m[i][j];
		resolver(m);
	}
	else
		stop = true;

	return stop;
}

int main() {
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (!resuelveCaso()){}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}