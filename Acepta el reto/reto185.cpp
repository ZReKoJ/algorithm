#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <set>

//#define RKJ

bool resuelveCaso() {
	int numCasos;
	std::cin >> numCasos;
	if (numCasos != 0) {
		std::set<std::string> si, no;
		std::string palabra;
		for (int i = 0; i < numCasos; ++i) {
			std::cin >> palabra;
			if (palabra == "SI:") {
				std::cin >> palabra;
				while (palabra != "FIN") {
					si.insert(palabra);
					std::cin >> palabra;
				}
			}
			else {
				std::cin >> palabra;
				while (palabra != "FIN") {
					no.insert(palabra);
					std::cin >> palabra;
				}
			}
		}
		bool escrito = false;
		for (std::set<std::string>::iterator i = no.begin(); i != no.end(); ++i) {
			if (si.count(*i) == 0) {
				if (escrito)
					std::cout << ' ' << *i;
				else {
					std::cout << *i;
					escrito = true;
				}
			}
		}
		std::cout << '\n';
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