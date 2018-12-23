// Grupo E, Diego Acuña Berger y Zihao Hong
// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N))
int resolver(vector<int> const & v, int &max ) {
	max = v[0];
	int sol = 1;
	for (int i = 1; i < v.size(); i++){
		if (max < v[i]){
			max = v[i];
			sol = 1;
		}
		else if (max == v[i]){
			sol++;
		}
	}
	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int num_elementos;
	int elemento_v;
	int max;
	std::cin >> num_elementos;
	vector<int> v(num_elementos);
	for (int i = 0; i < v.size(); i++){
		std::cin >> elemento_v;
		v[i] = elemento_v;
	}
	int sol = resolver(v, max);
	// escribir sol
	cout << max << " " << sol << endl;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("c:/users/usuario_local/documents/visual studio 2013/projects/project1/project1/01EntradaEjemplo.txt");
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