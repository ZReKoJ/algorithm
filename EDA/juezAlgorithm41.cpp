// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <climits>

/*
Divide y venceras
Dependiendo de las comparaciones de los dos valores se llama a la recursion de las mitades del array

T(0) = C0; T(n) = T(n / 2) + C1 --> O(log n)
*/

int resolver(const std::vector<int> &v, int ini, int fin) {
	if (ini >= fin)
		return v[ini];
	else {
		int medio = (ini + fin) / 2;
		if (v[medio] < v[medio + 1])
			return v[medio];
		else if (v[ini] < v[medio])
			return resolver(v, ini, medio);
		else
			return resolver(v, medio + 1, fin);
	}
}

bool resuelveCaso() {
	int numValores;
	std::cin >> numValores;
	if (!std::cin.fail()) {
		std::vector<int> v(numValores);
		for (int i = 0; i < numValores; ++i)
			std::cin >> v[i];

		int sol = resolver(v, 0, v.size() - 1);
		std::cout << sol << '\n';
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}