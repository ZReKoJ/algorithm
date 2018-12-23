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
Busqueda binaria + la pos y se comprueba

Coste Implementacion O(n / 2) // Logaritmica respecto al vector
*/

bool resolver(const std::vector<int> &v, int x, int & m, int ini, int fin) {
	m = ((ini + fin) / 2);
	if (ini > fin) // vacio
		return false;
	else if (ini == fin) // 1 elemento
		return v[ini] - m == x;
	else {
		if (v[m] - m == x) return true;
		else if (v[m] - m < x) return resolver(v, x, m, m + 1, fin);
		else resolver(v, x, m, ini, m);
	}
}

void resuelveCaso() {
	int numValores, x, numero;
	std::cin >> numValores >> x;
	std::vector<int> v(numValores);
	for (int &valor : v)
		std::cin >> valor;

	if (resolver(v, x, numero, 0, v.size() - 1))
		std::cout << numero + x << '\n';
	else
		std::cout << "NO\n";
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