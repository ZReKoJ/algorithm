// TAIS19, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <list>
#include <climits>
#include <limits.h>
#include <limits>

/*
aibofobia(i, j) = menor numero de letras que hacen falta anadir para que la palabra sea palindromo dado la letra de comienzo i y la letra de final j
aibofobia(i, j) = {
	aibofobia(i + 1, j - 1) si la primera y la ultima letra es la misma
	el minimo de (aibofobia(i, j - 1) y aibofobia(i + 1, j)) + 1 si la primera y la ultima letra no es la misma
}
El tiempo es O(l^2) // Donde l es la longitud de la palabra, se usa solo la mitad
El espacio es O(l^2) // Donde l es la longitud de la palabra, se usa solo la mitad
*/

bool resuelveCaso() {
	std::string palabra;
	std::cin >> palabra;
	if (std::cin.fail()) return false;
	else {
		// filas como ini, columnas como fin
		std::vector<std::vector<int>> v(palabra.length(), std::vector<int>(palabra.length(), 0));
		for (int i = 1; i < palabra.length(); ++i) {
			for (int j = 0; j < palabra.length() - i; ++j) {
				if (palabra.at(j) == palabra.at(i + j))
					v[j][i + j] = v[j + 1][i + j - 1];
				else v[j][i + j] = std::min(v[j + 1][i + j], v[j][i + j - 1]) + 1;
			}
		}
		std::cout << v[0][palabra.length() - 1] << "\n";
		return true;
	}
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	/*
	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i)
	resuelveCaso();*/
	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}