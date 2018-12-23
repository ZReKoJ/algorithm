#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

//#define RKJ

bool resolver(std::vector<bool> &v, int numero) {
	bool booleano;
	if (numero < 8)
		return v[numero];
	else {
		if (v[numero]) {
			if (numero % 3 == 0) {
				if (resolver(v, numero / 3))
					booleano = true;
				else
					booleano = resolver(v, numero - 5);
			}
			else booleano = resolver(v, numero - 5);

			v[numero] = booleano;
			return booleano;
		}
		else return false;
	}
}

bool resuelveCaso() {
	int numero;

	scanf("%d", &numero);
	if (numero != 0) {
		int variable = numero;
		if (numero < 7)
			variable = 7;
		std::vector<bool> v(variable + 1, true);
		v[0] = false; v[2] = false; v[4] = false; v[5] = false; v[7] = false;
		if (resolver(v, numero))
			printf("SI\n");
		else printf("NO\n");
		return true;
	}
	else return false;
}

int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifdef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}