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
std::vector<int> resolver(const std::vector<int>& v) {
	std::vector<int> w;
	int suma = 0;

	for (int valor: v) {
		suma += valor;
		w.emplace_back(suma);
	}

	return w;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int valor;
	std::vector<int> v;

	std::cin >> valor;
	if (valor == 0)
		return false;
	else
		v.emplace_back(valor);

	std::cin >> valor;
	while (valor != 0) {
		v.emplace_back(valor);
		std::cin >> valor;
	}

	std::vector<int> w = resolver(v);

	// escribir sol
	for (int valor : w)
		std::cout << valor << " ";

	std::cout << std::endl;

	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("/Users/isabel/Dropbox/XcodePrograms/Prueba/datos1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif

	return 0;
}