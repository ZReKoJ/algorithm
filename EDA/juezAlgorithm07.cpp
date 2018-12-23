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

const std::string BLANCO = "FFFFFF"; // blanco

									 // funcio?n que resuelve el problema
									 // comentario sobre el coste, O(f(N)) coste lineal
/*
P = {0 <= n}
func xxxx (std::string a[], int n, int& inicio, int& final)
Q = {(0 <= inicio <= final < n) ^ mayorIntervalo(a, n, inicio, final) ^ (forall cont: inicio <= cont <= final : a[cont] = "FFFFFF")}
donde mayorIntervalo(a, n, inicio, final) = 
{ forall u, w : u != inicio ^ w != final ^ (0 <= u <= w < n) ^ (forall cont: u <= cont <= w : a[cont] = "FFFFFF"): (w - u) < (final - inicio)}
*/
void resolver(const std::vector<std::string>& v) {
	bool inicio = false;
	int contador = 0, max = 0, finall;
	// Se trata de una funcio que dependiendo del booleano va calculando en contador y el maximo intervalo
	// El booleano indica si se ha roto la cadena
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == BLANCO && !inicio) {
			contador = 1;
			inicio = true;
		}
		else if (v[i] == BLANCO && inicio)
			contador++;
		else if (v[i] != BLANCO && inicio) {
			if (contador > max) {
				max = contador;
				finall = i - 1;
			}
			inicio = false;
		}
		else
			inicio = false;
	}

	if (contador > max) {
		max = contador;
		finall = v.size() - 1;
	}
	if (max == 0)
		std::cout << "0 -1" << std::endl;
	else
		std::cout << finall + 1 - max << " " << finall << std::endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso(int numVariables) {
	// leer los datos de la entrada
	std::vector<std::string> v(numVariables);
	for (std::string& color : v)
		std::cin >> color;

	resolver(v);

	// escribir sol
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

											  //std::cout << "Numero de casos: ";
	int numCasos, numVariables;
	std::cin >> numCasos;
	while (!std::cin.fail()) {
		std::cin >> numVariables;
		for (int i = 0; i < numCasos; ++i)
			resuelveCaso(numVariables);
		std::cin >> numCasos;
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