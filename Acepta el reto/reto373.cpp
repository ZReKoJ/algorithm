#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

//#define RKJ

void resuelveCaso() {
	long long int num;
	scanf("%lld", &num);

	long long int sol = 0;
	sol += num * num * 2;
	long long int medio = num - 2;
	if (medio > 0) {
		sol += medio * num * 2;
		sol += medio * medio * 2;
	}
	printf("%lld\n", sol);
}

int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifdef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}