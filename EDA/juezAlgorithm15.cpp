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
Dado una matriz va recorriendo los valores sin guardarlo en un array de tamano n*m, sino que solo va cogiendo
los valores y comparandolo con la fila en que esta, si es igual se suma uno en el contador.

Coste Implementacion f(n*m); // Lineal
*/

int resolver(int filas, int columnas) {
	int contador = 0, valor;

	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			std::cin >> valor;
			if (valor == i)
				contador++;
		}
	}

	return contador;
}

bool resuelveCaso() {
	bool stop = false;
	int filas, columnas;
	std::cin >> filas;
	if (!std::cin.fail()) {
		std::cin >> columnas;
		std::cout << resolver(filas, columnas) << '\n';
	}
	else
		stop = true;

	return stop;
}

int main() {
#ifndef DOMJUDGE
	srand(time(NULL));
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