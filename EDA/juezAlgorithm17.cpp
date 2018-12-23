// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

/*
Voy contando mediante 2 contadores los numeros de r y z
y voy a su vez quitandolos para controlar el tamano
entonces con otro contador cuento cuantas veces cumple el requisito mediante un if

Coste Implementacion f(2n - tamano); // Lineal
*/

void resolver(const std::vector<char>& v, int tamano, int numR, int numZ) {
	int contR = 0, contZ = 0, cont = 0;

	for (int i = 0; i < tamano; ++i) {
		switch (v[i]) {
		case 'r': contR++; break;
		case 'z': contZ++; break;
		}
	}

	if (contR >= numR && contZ >= numZ)
		cont++;

	for (int i = tamano; i < v.size(); ++i) {
		switch (v[i - tamano]) {
		case 'r': contR--; break;
		case 'z': contZ--; break;
		}

		switch (v[i]) {
		case 'r': contR++; break;
		case 'z': contZ++; break;
		}

		if (contR >= numR && contZ >= numZ)
			cont++;
	}

	std::cout << cont << '\n';
}

void resuelveCaso() {
	int numValores, tamano, numR, numZ;
	std::cin >> numValores >> tamano >> numR >> numZ;
	std::vector<char> v(numValores);
	for (char &valor : v)
		std::cin >> valor;
	resolver(v, tamano, numR, numZ);
}

int main() {
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}