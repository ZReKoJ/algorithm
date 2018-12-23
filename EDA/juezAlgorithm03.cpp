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



// funcio?n que resuelve el problema
// comentario sobre el coste, O(f(N))
void resolver(const std::vector<int>& v, int n) {
	int pico = 0, valle = 0;

	for (int i = 1; i < n - 1; i++) {
		if (v[i - 1] > v[i] && v[i] < v[i + 1])
			valle++;
		if (v[i - 1] < v[i] && v[i] > v[i + 1])
			pico++;
	}

	std::cout << pico << " " << valle << std::endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int n;

	std::cin >> n; // Longitud del vector
	std::vector<int> v(n); // Vector
	for (int& valor : v)
		std::cin >> valor; // Valores

	resolver(v, n);
	// escribir sol

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	//std::ifstream in("/Users/isabel/Dropbox/XcodePrograms/Prueba/datos1.txt");
	//auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	//std::cout << "Numero de casos: ";
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	//std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}