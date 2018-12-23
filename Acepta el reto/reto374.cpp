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
	long long int num, max, min;
	int contMax = 0, contMin = 0;
	scanf("%lld", &num);
	max = num;
	min = num;
	while (num != 0) {
		if (num > max) {
			max = num;
			contMax = 0;
		}
		if (num < min) {
			min = num;
			contMin = 0;
		}
		if (num == max)
			++contMax;
		if (num == min)
			++contMin;
		scanf("%lld", &num);
	}

	printf("%lld %d %lld %d\n", min, contMin, max, contMax);
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