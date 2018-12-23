// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Recursion no final
Divido cada array en dos mitades y de esta a su vez en dos hasta que salga arrays de 1 valor 
de alli se comprueba si los de la izq es menor que la de la dch

T(0) = c0; T(n) = 2T(n / 2) + C0 --> O(2 ^ n)
*/

bool resolver(const std::vector<int>& v, int ini, int fin, int &suma) {
	if (ini == fin) {
		suma = v[ini];
		return true;
	}
	else {
		int medio = (ini + fin) / 2, suma1 = suma, suma2 = suma;
		bool esDegradado = resolver(v, ini, medio, suma1) && resolver(v, medio + 1, fin, suma2);
		esDegradado = esDegradado && (suma1 < suma2);
		suma = suma1 + suma2;
		return esDegradado;
	}
}

bool resuelveCaso() {
	int filas, columnas, valor;

	std::cin >> filas;
	if (!std::cin.fail()) {
		std::cin >> columnas;
		std::vector<std::vector<int>> m(filas, std::vector<int>(columnas));

		for (int i = 0; i < m.size(); ++i)
			for (int j = 0; j < m[i].size(); ++j)
				std::cin >> m[i][j];

		int suma;
		bool esDegradado = true;
		for (int i = 0; i < filas; ++i)
			esDegradado = esDegradado && resolver(m[i], 0, m[i].size() - 1, suma);

		if (esDegradado)
			std::cout << "SI\n";
		else
			std::cout << "NO\n";

		return true;
	}
	else return false;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}