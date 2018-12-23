// TAIS19, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <list>
#include <climits>
#include <limits.h>
#include <limits>

//
//  ConjuntosDisjuntos.h
//
//  Implementación de estructuras de partición o conjuntos disjuntos
//  con unión por tamaño y compresión de caminos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/9/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef CONJUNTOSDISJUNTOS_H_
#define CONJUNTOSDISJUNTOS_H_

#include <vector>
#include <iostream>

class ConjuntosDisjuntos {
public:

	// crea una estructura de partición con los elementos 0..N-1, cada uno en un conjunto
	ConjuntosDisjuntos(size_t N) : _size(N), _count(_size), id(_size, -1) {}

	// devuelve el número de conjuntos disjuntos
	size_t count() const { return _count; }

	//  devuelve el identificador del conjunto que contiene a p
	size_t buscar(size_t p) const {
		if (id.at(p) < 0) // es una raíz
			return p;
		else
			return id[p] = int(buscar(id[p]));
	}

	// unir los conjuntos que contengan a p y q
	void unir(size_t p, size_t q) {
		auto i = buscar(p);
		auto j = buscar(q);
		if (i == j) return;
		if (id[i] < id[j]) { // i es la raíz del mayor árbol
			id[i] += id[j]; id[j] = int(i);
		}
		else {
			id[j] += id[i]; id[i] = int(j);
		}
		_count--;
	}

	size_t size(size_t p) const {
		return -id[buscar(p)];
	}

	bool unidos(size_t p, size_t q) const {
		return buscar(p) == buscar(q);
	}

protected:
	size_t _size;            // los elementos son 0 .. _size-1
	size_t _count;           // número de conjuntos disjuntos
	mutable std::vector<int> id;  // si id[i]>=0 es el padre de i, si no es el tamaño del conjunto de i

};


#endif


void resolver(std::vector<std::vector<char>> const& m, std::vector<std::vector<bool>> & b, int y, int x, int & counter, std::vector<std::pair<int, int>> const& dir, ConjuntosDisjuntos & g) {
	b[y][x] = true;
	++counter;
	int y2, x2;
	for (auto d : dir) {
		y2 = y + d.first; x2 = x + d.second;
		if (m.size() > 0 && y2 >= 0 && y2 < m.size() && x2 >= 0 && x2 < m[0].size() && m[y2][x2] == '#') {
			g.unir((y * m[0].size()) + x, (y2 * m[0].size()) + x2);
			if (!b[y2][x2])
				resolver(m, b, y2, x2, counter, dir, g);
		}
	}
}

bool resuelveCaso() {
	int ancho, alto;
	std::cin >> alto;
	if (std::cin.fail())
		return false;
	else {
		std::cin >> ancho;
		std::vector<std::vector<char>> m(alto, std::vector<char>(ancho));
		std::string line;
		getline(std::cin, line);
		for (int i = 0; i < alto; ++i) {
			getline(std::cin, line);
			for (int j = 0; j < ancho; ++j)
				m[i][j] = line.at(j);
		}

		std::vector<std::vector<bool>> b(alto, std::vector<bool>(ancho, false));
		std::vector<std::pair<int, int>> dir = { { -1, -1 },{ -1, 0 },{ -1, 1 },{ 0, -1 },{ 0, 1 },{ 1, -1 },{ 1, 0 },{ 1, 1 } };
		ConjuntosDisjuntos g(alto * ancho);

		int max = 0, counter = 0;

		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m[i].size(); ++j) {
				if (m[i][j] == '#' && !b[i][j]) {
					resolver(m, b, i, j, counter, dir, g);
					if (counter > max) max = counter;
					counter = 0;
				}
			}
		}
		std::cout << max;

		int num, x, y, x2, y2;
		std::cin >> num;
		for (int i = 0; i < num; ++i) {
			std::cin >> y >> x;
			y--; x--;
			if (m[y][x] != '#') {
				m[y][x] = '#';
				for (auto d : dir) {
					y2 = y + d.first; x2 = x + d.second;
					if (m.size() > 0 && y2 >= 0 && y2 < m.size() && x2 >= 0 && x2 < m[0].size() && m[y2][x2] == '#')
						g.unir((y * m[0].size()) + x, (y2 * m[0].size()) + x2);
				}
			}
			counter = g.size((y * m[0].size()) + x);
			if (counter > max) max = counter;
			std::cout << " " << max;
		}
		std::cout << "\n";
		return true;
	}
}

/* El coste de este algoritmo es de
O((n * m) + y)
	n es el ancho
	m es el alto
	y es el numero de nuevas celdas contaminadas
*/
#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	/*
	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i)
	resuelveCaso();*/
	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}