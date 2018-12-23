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

/** Especificación
P { cadena.size() > 0 && patron.size() > 0 }

func resolver( string cadena[] , string patron[] ) return int numero

Q { numero = ( #i : 0 <= i <= cadena.size() : ( exists j,k : 0 <= j < (cadena.size() - patron.size() + 1) : subStr(cadena, j ,patron.size()) = patron )) }
donde substr(cadena, j, patron.size()) = { una subcadena de caracteres desde la posicion j hasta patron.size() longitud (es una funcion que ya viene en el visual) }
*/

std::string sacarIntervalo(int pos, int longitud, const std::string &palabra) {
	std::string word;

	for (int i = pos; i < pos + longitud; ++i)
		word.push_back(palabra.at(i));

	return word;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso(std::string palabra) {
	std::string caso;
	int cont = 0;
	getline(std::cin, caso);
	for (int i = 0; i < palabra.size() - caso.size() + 1; ++i)
		if (sacarIntervalo(i, caso.size(), palabra) == caso)
			cont++;

	std::cout << cont << '\n';
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

	std::string palabra;
	getline(std::cin, palabra);
	while (!std::cin.fail()) {
		resuelveCaso(palabra);
		getline(std::cin, palabra);
	}

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << std::endl;
	system("PAUSE");
#endif

	return 0;
}