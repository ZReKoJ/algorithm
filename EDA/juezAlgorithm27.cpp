// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Recursion final
Comparo el valor en la posicion medio con los de al lado para ver si crece o decrece
y decidir si hay que coger la primera mitad o la segunda
haciendo sus respectivas restricciones de si sale del vector

T(0) = C0; T(n) = T(n / 2) + C1 --> O(log n)
*/

int resolver(const std::vector<int>& v, int medio, int ini, int fin) {
	if (medio < v.size() - 1 && v[medio] >= v[medio + 1])
		return resolver(v, (medio + 1 + fin) / 2, medio + 1, fin);
	else if (medio > 0 && v[medio] >= v[medio - 1])
		return resolver(v, (medio - 1 + ini) / 2, ini, medio - 1);
	else
		return v[medio];
}

bool resuelveCaso() {
	int numValores;

	std::cin >> numValores;
	if (!std::cin.fail()) {
		std::vector<int> v(numValores);

		for (int &valor : v)
			std::cin >> valor;

		int medio = v.size() / 2;

		std::cout << resolver(v, medio, 0, v.size() - 1) << '\n';

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