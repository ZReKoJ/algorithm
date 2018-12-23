// Grupo E, Zihao Hong
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
int resolver(const std::vector<int>& v) {
	int mayor = v[0], mayorL = mayor, sol = 0;

	for (int i = 1; i < v.size(); i++) {
		if (v[i] <= mayor) {
			sol = i;
			mayor = mayorL;
		}
		if (v[i] > mayorL)
			mayorL = v[i];
	}

	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int numVariables;
	std::cin >> numVariables;
	std::vector<int> v(numVariables);
	for (int& color : v)
		std::cin >> color;

	int solucion = resolver(v);

	// escribir sol
	std::cout << solucion << std::endl;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datos1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}