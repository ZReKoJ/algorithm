#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

//#define RKJ

bool resuelveCaso() {
	int numero;

	scanf("%d", &numero);
	if (numero == 0)
		return false;
	else {
		for (int i = 0; i < numero; ++i)
			printf("1");
		printf("\n");

		return true;
	}
}

int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
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