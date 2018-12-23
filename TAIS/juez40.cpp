// TAIS19, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <list>
#include <climits>
#include <limits.h>
#include <limits>
#include "PriorityQueue.h"

/*
Se dan tres casos: la cara de la izq, la cara de la dch o no se graba
y recorrer todas las ramas

estimacion:
ordenarlas por (duracion/valoracion)
ver que la maxima valoracion de la duracion que cabe no supera el mejor
*/

struct Cancion {
	int dur;
	int val;
};

bool operator<(Cancion const& p1, Cancion const& p2) {
	double pt1 = (p1.dur / double(p1.val));
	double pt2 = (p2.dur / double(p2.val));
	if (pt1 < pt2) return true;
	else if (pt1 > pt2) return false;
	else return p1.dur < p2.dur;
}

struct Nodo {
	int k;
	int izq;
	int dch;
	int val;
	int est;
};

int estimar(Nodo n, int const& total, std::vector<Cancion> const& v) {
	int durTotal = n.izq + n.dch, stage = n.k + 1, totall = total + total, est = n.val;
	while (stage < v.size() && durTotal < totall) {
		durTotal += v[stage].dur;
		est += v[stage].val;
		++stage;
	}
	return est;
}

bool operator>(Nodo const& a, Nodo const&b) {
	if (a.est == b.est) return a.val > b.val;
	else return a.est > b.est;
}

int ramificacionYPoda(std::vector<Cancion> const& v, int const& total) {
	int mejor = 0;
	PriorityQueue<Nodo, std::greater<Nodo>> pq;
	Nodo n = { -1, 0, 0, 0, 0 }, nn;
	n.est = estimar(n, total, v);
	pq.push(n);
	while (!pq.empty() && pq.top().est > mejor) {
		n = pq.top(); pq.pop();
		if (n.k < int(v.size()) - 1) {
			nn = n;
			nn.k++;
			nn.val += v[nn.k].val;
			if (total >= nn.izq + v[nn.k].dur) {
				nn.izq += v[nn.k].dur;
				nn.est = estimar(nn, total, v);
				pq.push(nn);
				nn.izq -= v[nn.k].dur;
			}
			nn.dch += v[nn.k].dur;
			nn.est = estimar(nn, total, v);
			if (n.izq != n.dch && total >= nn.dch && nn.est > mejor) {
				pq.push(nn);
			}
			nn.dch -= v[nn.k].dur;
			nn.val -= v[nn.k].val;
			nn.est = estimar(nn, total, v);
			if (nn.est > mejor)
				pq.push(nn);
		}
		else mejor = std::max(mejor, n.val);
	}
	return mejor;
}

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (num == 0) return false;
	else {
		int dur;  std::cin >> dur;
		std::vector<Cancion> v(num);
		for (int i = 0; i < num; ++i)
			std::cin >> v[i].dur >> v[i].val;
		std::sort(v.begin(), v.end());
		std::cout << ramificacionYPoda(v, dur) << "\n";
		return true;
	}
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}