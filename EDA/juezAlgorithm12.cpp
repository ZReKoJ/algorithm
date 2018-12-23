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
void resolver(const std::vector<int> &v, int limite) {
	int cont = 0, posFinal = 0, max = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] > limite)
			cont++;
		else
			cont = 0;
		if (cont > max) {
			max = cont;
			posFinal = i;
		}
	}

	std::cout << posFinal - max + 1 << " " << posFinal << '\n';
}

void resuelveCaso() {
	int numValores, limite;
	std::cin >> numValores >> limite;
	std::vector<int> v(numValores);
	for (int &valor : v)
		std::cin >> valor;

	resolver(v, limite);
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
	std::cout << ((float)t / CLOCKS_PER_SEC) << std::endl;
	system("PAUSE");
#endif

	return 0;
}