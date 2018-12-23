// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <sstream>

/*
Recursion final
En los casos bases (0, b) (a, 0) (a, a) los igualo a 1
y en los demas casos hago 2 recursiones para cada comando
todo se guarda en la matriz
y a la vuelta se muesta la el valor de las posiciones dadas

T(a, 0) = 1; T(0, b) = 1;  T(a, a) = 1; T(a, b) = 2T(n - 1) + C0 --> O(2 ^ n)
*/

void resolver(std::vector<std::vector<long long int>> & m, int a, int b) {
	if (m[a][b] == -1) {
		if (a == 0 || b == 0)
			m[a][b] = 1;
		else if (a == b)
			m[a][b] = 1;
		else {
			resolver(m, a - 1, b - 1);
			resolver(m, a - 1, b);
			m[a][b] = m[a - 1][b - 1] + m[a - 1][b];
		}
	}
}

bool resuelveCaso() {
	int a, b;

	std::cin >> a;
	if (!std::cin.fail()) {
		std::cin >> b;
		std::vector<std::vector<long long int>> m(a + 1, std::vector<long long int>(b + 1));
		for (int i = 0; i <= a; ++i)
			for (int j = 0; j <= b; ++j)
				m[i][j] = -1;
		resolver(m, a, b);
		std::cout << m[a][b] << '\n';
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
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