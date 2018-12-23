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

/*std::string sacarIntervalo(int pos, int longitud, const std::string &palabra) {
	std::string word;

	for (int i = pos; i < pos + longitud; ++i)
		word.push_back(palabra.at(i));

	return word;
}*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso() {
	int numValores, ceros = 0, unos = 0, valor, sol = -1;
	std::cin >> numValores;
	for (int i = 0; i < numValores; ++i) {
		std::cin >> valor;
		if (valor == 0)
			ceros++;
		else if (valor == 1)
			unos++;
		if (ceros == unos)
			sol = i;
	}

	std::cout << sol << '\n';
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datos.txt");
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