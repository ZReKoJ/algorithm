#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <string>
#include <set>

//#define RKJ

int resolver(int diaN, int mesN, int anioN, int diaA, int mesA, int anioA) {
	std::vector<int> meses = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
	int nacimiento = meses[mesN - 1] + diaN;
	int actual = meses[mesA - 1] + diaA;
	if (anioA == anioN)
		return actual - nacimiento;
	else {
		int anios = anioA - anioN - 1;
		int dias = 365 - nacimiento + actual;
		dias += (anios * 364);
		if (mesN < mesA)
			--dias;
		else if (mesN == mesA) {
			if (diaN <= diaA)
				--dias;
		}
		return dias;
	}
}

bool resuelveCaso() {
	int diaN, mesN, anioN, diaA, mesA, anioA;
	scanf("%d", &diaN);
	scanf("%d", &mesN);
	scanf("%d", &anioN);
	scanf("%d", &diaA);
	scanf("%d", &mesA);
	scanf("%d", &anioA);
	//std::cin >> diaN >> mesN >> anioN >> diaA >> mesA >> anioA;
	if (!(diaN == 0 && mesN == 0 && anioN == 0 && diaA == 0 && mesA == 0 && anioA == 0)) {
		if (diaN == diaA && mesN == mesA)
			printf("0\n");
			//std::cout << "0\n";
		else
			printf("%d\n", resolver(diaN, mesN, anioN, diaA, mesA, anioA));
			//std::cout << resolver(diaN, mesN, anioN, diaA, mesA, anioA) << '\n';
		return true;
	}
	else return false;
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