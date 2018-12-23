// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Divide y venceras
Se acumula el cont de num pares
Se llama recursion de mitades y se comprueba a su vez la validez

T(0) = c0; T(n) = 2T(n / 2) + 2C1 --> O(n)
*/
bool resolver(const std::vector <int> &v, int ini, int fin, int &cont) {
	if (ini == fin) {
		if (abs(cont) <= 2) {
			if (v[ini] % 2 == 0)
				cont++;
			return true;
		}
		else return false;
	}
	else {
		int mitad = (ini + fin) / 2;
		int contIzq = 0, contDer = 0;
		bool izq = resolver(v, ini, mitad, contIzq);
		bool der = resolver(v, mitad + 1, fin, contDer);
		if (izq && der && abs(contIzq - contDer) <= 2) {
			cont = contIzq + contDer;
			return true;
		}
		else return false;
	}

}

bool resuelveCaso() {
	int numero;
	std::cin >> numero;
	if (numero == 0)
		return false;
	std::vector<int> v;
	while (numero != 0) {
		v.emplace_back(numero);
		std::cin >> numero;
	}
	int ini = 0, fin = v.size() - 1, contador = 0;
	bool sol = resolver(v, ini, fin, contador);

	if (sol)
		std::cout << "SI\n";
	else
		std::cout << "NO\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()){}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}