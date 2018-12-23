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
	int huevos, olla;

	scanf("%d", &huevos);
	scanf("%d", &olla);
	if (huevos == 0 && olla == 0)
		return false;
	else {
		int sol = 0;
		sol = huevos / olla;
		if (huevos % olla > 0)
			++sol;
		sol *= 10;
		printf("%d\n", sol);
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