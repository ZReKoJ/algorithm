#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstring>
#include <set>

//#define RKJ

std::string resolver(const std::string &xPrimaPrima) {
	std::string xPrima, x;
	for (int i = 0; i < xPrimaPrima.size(); i += 2)
		xPrima.push_back(xPrimaPrima.at(i));
	int posUltima;
	if (xPrimaPrima.size() % 2 == 0) posUltima = xPrimaPrima.size() - 1;
	else posUltima = xPrimaPrima.size() - 2;
	for (int i = posUltima; i > 0; i -= 2)
		xPrima.push_back(xPrimaPrima.at(i));
	int z = 0, y;
	for (int i = 0; i < xPrima.size(); ++i) {
		if (std::strchr("aeiouAEIOU", xPrima.at(i))) {
			y = i - 1;
			while (y >= z) {
				x.push_back(xPrima.at(y));
				--y;
			}
			x.push_back(xPrima.at(i));
			z = i + 1;
		}
	}
	y = xPrima.size() - 1;
	while (y >= z) {
		x.push_back(xPrima.at(y));
		--y;
	}
	return x;
}

bool resuelveCaso() {
	std::string texto;
	getline(std::cin, texto);
	if (!std::cin.fail()) {
		std::cout << texto << " => " << resolver(texto) << '\n';
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