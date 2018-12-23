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
	std::string palabra;
	std::cin >> palabra;
	if (!std::cin.fail()) {
		int sol = 0;
		if (palabra.length() > 4) {
			sol *= 10;
			sol += int(palabra.at(palabra.length() - 5)) - 48;
		}
		if (palabra.length() > 3) {
			sol *= 10;
			sol += int(palabra.at(palabra.length() - 4)) - 48;
		}
		if (palabra.length() > 2) {
			sol *= 10;
			sol += int(palabra.at(palabra.length() - 3)) - 48;
		}
		if (palabra.length() > 1) {
			sol *= 10;
			sol += int(palabra.at(palabra.length() - 2)) - 48;
		}
		sol *= 10;
		sol += int(palabra.at(palabra.length() - 1)) - 48;
		sol %= 16;
		if (sol == 0 || sol == 1 || sol == 4 || sol == 9)
			printf("NO SE\n");
		else
			printf("IMPERFECTO\n");
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