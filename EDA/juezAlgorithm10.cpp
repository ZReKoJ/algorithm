// E26, Zihao Hong
// Comentario general sobre la solucio?n,
// explicando co?mo se resuelve el problema
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

// funcio?n que resuelve el problema
// comentario sobre el coste, O(f(N)) coste lineal

void resolver(std::vector<long long int>& v, int numArrays) {
	int valor, pos = 0;

	for (int i = 0; i < numArrays; ++i) {
		std::cin >> valor;
		while (valor != 0) {
			while (pos < v.size() && valor >= v[pos]) {
				if (valor == v[pos])
					std::cin >> valor;
				else
					v[pos] = -1;
				pos++;
			}
			if (valor != 0)
				std::cin >> valor;
		}
		while (pos < v.size()) {
			v[pos] = -1;
			pos++;
		}
		pos = 0;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso() {
	int numArrays, valor;
	std::cin >> numArrays;
	std::vector<long long int> v;
	v.reserve(10000);
	std::cin >> valor;
	while (valor != 0) {
		v.emplace_back(valor);
		std::cin >> valor;
	}

	resolver(v, numArrays - 1);

	for (int i = 0; i < v.size(); ++i)
		if (v[i] != -1) {
			if (i != v.size() - 1)
				std::cout << v[i] << " ";
			else
				std::cout << v[i];
		}
	std::cout << '\n';
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datos1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
	clock_t t = clock();
#endif 

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << std::endl;
	system("PAUSE");
#endif

	return 0;
}