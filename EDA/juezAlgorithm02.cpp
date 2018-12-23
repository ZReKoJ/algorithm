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
bool resolver(const std::vector<int>& v, int n, int p) {
	bool sol = true;
	int max = v[0];

	for (int i = 1; i <= p && sol; i++)
		if (max < v[i]) max = v[i];
		
	for (int j = p + 1; j < n && sol; j++)
		if (max >= v[j]) sol = false;

	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int n, p;

	//std::cout << "Longitud del vector: ";
	std::cin >> n;
	//std::cout << "Incognita p: ";
	std::cin >> p;
	std::vector<int> v(n);
	//std::cout << "Valores: ";
	for (int& valor : v)
		std::cin >> valor;

	bool sol = resolver(v, n, p);
	// escribir sol
	if (sol) std::cout << "SI";
	else std::cout << "NO";
	std::cout << std::endl;

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