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

estimacion:
	ordenarlas por (duracion/valoracion)
	ver que la maxima valoracion de la duracion que cabe no supera el mejor
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

int estimacion(const std::vector<tPuntuacion> &v, int duracionTotal, const int &duracion, int stage) {
	int valoracion = 0;
	while (stage < v.size() - 1 && duracionTotal < duracion) {
		++stage;
		duracionTotal += v[stage].duracion;
		valoracion += v[stage].valoracion;
	}
	return valoracion;
}

void resolver(const std::vector<tPuntuacion> &v, int izq, int dch, const int &duracion, int &mejor, int valoracion, int stage) {
	if (stage < v.size()) {
			if (duracion >= izq + v[stage].duracion)
				resolver(v, izq + v[stage].duracion, dch, duracion, mejor, valoracion + v[stage].valoracion, stage + 1);
			if (izq != dch && duracion >= dch + v[stage].duracion && estimacion(v, izq + dch + v[stage].duracion, duracion + duracion, stage) + valoracion + v[stage].valoracion > mejor)
				resolver(v, izq, dch + v[stage].duracion, duracion, mejor, valoracion + v[stage].valoracion, stage + 1);
			if (estimacion(v, izq + dch, duracion + duracion, stage) + valoracion > mejor)
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
		/*
		std::vector<int> sumaPoint(numCanciones);
		std::vector<int> duracionMin(numCanciones);
		sumaPoint[v.size() - 1] = v[v.size() - 1].valoracion;
		duracionMin[v.size() - 1] = v[v.size() - 1].duracion;
		int min = v[v.size() - 1].duracion;
		for (int i = v.size() - 2; i >= 0; --i) {
			sumaPoint[i] = v[i].valoracion + sumaPoint[i + 1];
			if (v[i].duracion < min)
				min = v[i].duracion;
			duracionMin[i] = min;
		}
		*/
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