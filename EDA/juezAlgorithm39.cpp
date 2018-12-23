// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <climits>

/*
Vuelta Atras
Se dan tres casos: la cara de la izq, la cara de la dch o no se graba
y recorrer todas las ramas
*/

typedef struct {
	int duracion;
	int valoracion;
} tPuntuacion;

bool operator < (const tPuntuacion &p1, const tPuntuacion &p2) {
	double pt1 = (p1.duracion / double(p1.valoracion));
	double pt2 = (p2.duracion / double(p2.valoracion));
	if (pt1 < pt2) return true;
	else if (pt1 > pt2) return false;
	else return p1.duracion < p2.duracion;
}

class comparador {
public:
	bool operator()(tPuntuacion a, tPuntuacion b) {
		return a < b;
	}
};

void resolver(const std::vector<tPuntuacion> &v, int izq, int dch, const int &duracion, int &mejor, int valoracion, int stage) {
	if (stage < v.size()) {
		if (duracion >= izq + v[stage].duracion)
			resolver(v, izq + v[stage].duracion, dch, duracion, mejor, valoracion + v[stage].valoracion, stage + 1);
		if (izq != dch && duracion >= dch + v[stage].duracion)
			resolver(v, izq, dch + v[stage].duracion, duracion, mejor, valoracion + v[stage].valoracion, stage + 1);
		resolver(v, izq, dch, duracion, mejor, valoracion, stage + 1);
	}
	else {
		if (valoracion > mejor)
			mejor = valoracion;
	}
}

bool resuelveCaso() {
	int numCanciones, duracion;
	std::cin >> numCanciones;
	if (numCanciones != 0) {
		std::cin >> duracion;
		std::vector<tPuntuacion> v(numCanciones);
		int mejor = 0;
		for (int i = 0; i < numCanciones; ++i) {
			std::cin >> v[i].duracion;
			std::cin >> v[i].valoracion;
		}
		sort(v.begin(), v.end(), comparador());
		resolver(v, 0, 0, duracion, mejor, 0, 0);
		std::cout << mejor << '\n';
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock(), tParcial = t;
#endif 

	while (resuelveCaso()) {
#ifndef DOMJUDGE
		tParcial = clock() - tParcial;
		std::cout << ((float)tParcial / CLOCKS_PER_SEC) << '\n';
		tParcial = clock();
#endif
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}