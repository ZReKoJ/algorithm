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

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resolver(const std::vector<int> &v, int numVagones) {
	int cont = 0, suma = 0, max = 0, posInicial = 0;

	for (int i = 0; i < v.size(); ++i) {
		cont++;
		suma += v[i];
		if (suma >= max) {
			max = suma;
			posInicial = i - cont + 1;
		}
		if (cont == numVagones) {
			cont--;
			suma -= v[i - numVagones + 1];
		}
	}

	std::cout << posInicial << " " << max << '\n';
}

void resuelveCaso() {
	int numValores, numVagones;
	std::cin >> numValores >> numVagones;
	std::vector<int> v(numValores);
	for (int &valor : v)
		std::cin >> valor;

	resolver(v, numVagones);
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
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
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}