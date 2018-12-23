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
bool resolver(std::string palabra) {
	bool orden = true;

	for (int i = 0; i < signed(palabra.length() - 1)&& orden; i++)
		if (palabra.at(i) >= palabra.at(i + 1))
			orden = false;

	return orden;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso(std::string palabra) {
	// leer los datos de la entrada

	bool solucion = resolver(palabra);

	// escribir sol
	if (solucion)
		std::cout << "SI";
	else
		std::cout << "NO";

	std::cout << std::endl;

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