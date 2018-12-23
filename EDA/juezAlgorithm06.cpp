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

const std::string CENTINELA = "XXX";

// funcio?n que resuelve el problema
// comentario sobre el coste, O(f(N))
int resolver(std::string palabra) {
	int alfabeto = 1, max = 1;

	for (int i = 0; i < signed(palabra.length() - 1); i++) {
		if (palabra.at(i) >= palabra.at(i + 1))
			alfabeto = 1;
		else
			alfabeto++;
		if (max < alfabeto)
			max = alfabeto;
	}

	return max;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso(std::string palabra) {
	// leer los datos de la entrada

	int solucion = resolver(palabra);

	// escribir sol

	std::cout << int(palabra.length()) << " " << solucion << std::endl;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("/Users/isabel/Dropbox/XcodePrograms/Prueba/datos1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


	std::string palabra;

	std::cin >> palabra;
	while (palabra != CENTINELA) {
		resuelveCaso(palabra);
		std::cin >> palabra;
	}


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif

	return 0;
}