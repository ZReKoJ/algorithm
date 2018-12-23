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
Hago un vector auxiliar donde se coloca los minimos del vector en ese momento desde la ultima posicion a la primera
despues con el vector original voy calculando el max de izq a dch y comparando con la pos sig del vector auxiliar para calcular los valores

Coste Implementacion lineal f(3 * n)
*/

void resolver(const std::vector<int> &v) {
	std::vector<int> w(v.size());
	int min = v[v.size() - 1];
	w[w.size() - 1] = min;

	for (int i = v.size() - 2; i >= 0; --i) {
		if (v[i] < min)
			min = v[i];
		w[i] = min;
	}

	int max = 0;
	for (int i = 0; i < v.size() - 1; ++i) {
		if (v[i] > max)
			max = v[i];
		if (max < w[i + 1])
			std::cout << i << " ";
	}

	std::cout << '\n';
}

void resuelveCaso() {
	int numValores;
	std::cin >> numValores;
	std::vector<int> v(numValores);
	for (int &valor : v)
		std::cin >> valor;
	resolver(v);
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