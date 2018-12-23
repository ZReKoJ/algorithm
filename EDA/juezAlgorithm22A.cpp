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
Busqueda binaria con intervalos

Coste Implementacion O(n / 2) // Logaritmico respecto al vector
*/

int resolver(const std::vector<int> &v, int primero, int ultimo) {
	int medio = (primero + ultimo) / 2;
	if (primero == ultimo)
		return medio;
	else if (v[medio - v[0]] == medio)
		return resolver(v, medio + 1, ultimo);
	else
		return resolver(v, primero, medio);
}

void resuelveCaso() {
	int primero, ultimo;
	char letra;
	std::cin >> letra;
	primero = int(letra);
	std::cin >> letra;
	ultimo = int(letra);
	std::vector<int> v(ultimo - primero);
	for (int i = 0; i < v.size(); ++i) {
		std::cin >> letra;
		v[i] = int(letra);
	}
	if (v[0] != primero)
		std::cout << char(primero) << '\n';
	else if (v[v.size() - 1] != ultimo)
		std::cout << char(ultimo) << '\n';
	else
		std::cout << char(resolver(v, primero, ultimo)) << '\n';
}

int main() {
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
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