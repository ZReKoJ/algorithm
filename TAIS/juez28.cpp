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
#include <queue>

/*
tesoro(i, j) = maxima cantidad de oro que se puede conseguir dados los cofres de 0 a i y j segundos que tiene la bombona
tesoro(i, j) = {
	tesoro(i - 1, j) si no hay tantos segundos para coger el cofre en la posicion i
	el maximo de (tesoro(i - 1, j) y tesoro(i - 1, j - x) + su valor) si existe tantos segundos para coger el cofre en la posicion i  // donde x es el valor del cofre en la posicion i
}
El tiempo es O(numOros * segundos) // Donde el numOros es el numero de cofres y segundos es segundos que tiene la bombona
El espacio es O(numOros * segundos) // Donde el numOros es el numero de cofres y segundos es segundos que tiene la bombona
*/

bool resuelveCaso() {
	int segundos;
	std::cin >> segundos;
	if (std::cin.fail()) return false;
	else {
		int numOros;
		std::cin >> numOros;
		std::vector<std::pair<int, int>> v(numOros);
		for (int i = 0; i < numOros; ++i)
			std::cin >> v[i].first >> v[i].second;
		std::vector<std::vector<int>> m(numOros + 1, std::vector<int>(segundos + 1, 0));
		int s;
		for (int i = 1; i < m.size(); ++i) {
			for (int j = 1; j < m[i].size(); ++j) {
				s = v[i - 1].first * 3;
				if (s > j) m[i][j] = m[i - 1][j];
				else m[i][j] = std::max(m[i - 1][j], m[i - 1][j - s] + v[i - 1].second);
			}
		}
		int valor = m[numOros][segundos], cont = 0, resto = segundos;
		std::vector<bool> b(numOros, false);
		for (int i = numOros; i > 0; --i) {
			if (m[i][resto] != m[i - 1][resto]) {
				++cont;
				b[i - 1] = true;
				resto -= v[i - 1].first * 3;
			}
		}
		std::cout << valor << "\n" << cont << "\n";
		for (int i = 0; i < b.size(); ++i)
			if (b[i]) std::cout << v[i].first << " " << v[i].second << "\n";
		std::cout << "----\n";
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