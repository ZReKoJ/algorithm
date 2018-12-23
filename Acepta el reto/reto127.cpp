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

void resuelveCaso() {
	std::string nombre;
	std::vector<std::string> v;
	std::cin >> nombre;
	while (nombre != "F") {
		v.emplace_back(nombre);
		std::cin >> nombre;
	}
	int numCamas, numCanciones;
	std::cin >> numCamas >> numCanciones;
	if (numCamas == 0)
		std::cout << "NADIE TIENE CAMA\n";
	else if (v.size() > numCamas) {
		int i = -1;
		while (v.size() > numCamas) {
			i = (numCanciones + i) % v.size();
			v.erase(v.begin() + i);
			--i;
		}
		std::cout << v[0];
		for (int i = 1; i < v.size(); ++i)
			std::cout << ' ' << v[i];
		std::cout << '\n';
	}
	else std::cout << "TODOS TIENEN CAMA\n";
}

int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos;
	std::cin >> numCasos;
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