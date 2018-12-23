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
#include <queue>
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

//
//  Grafo.h
//
//  Implementación de grafos no dirigidos y clases que los exploran
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>


using Adys = std::vector<size_t>;  // lista de adyacentes a un vértice
using Path = std::deque<size_t>;   // para representar caminos

class Grafo {

	size_t _V;   // número de vértices
	size_t _E;   // número de aristas
	std::vector<Adys> _adj;   // vector de listas de adyacentes

public:

	/**
	* Crea un grafo con V vértices.
	*/
	Grafo(size_t v) : _V(v), _E(0), _adj(_V) {}

	/**
	* Devuelve el número de vértices del grafo.
	*/
	size_t V() const { return _V; }

	/**
	* Devuelve el número de aristas del grafo.
	*/
	size_t E() const { return _E; }


	/**
	* Añade la arista v-w al grafo.
	* @throws invalid_argument si algún vértice no existe
	*/
	void ponArista(size_t v, size_t w) {
		if (v >= _V || w >= _V)
			throw std::invalid_argument("Vertice inexistente");
		++_E;
		_adj[v].push_back(w);
		_adj[w].push_back(v);
	}


	/**
	* Devuelve la lista de adyacencia de v.
	* @throws invalid_argument si v no existe
	*/
	const Adys& adj(size_t v) const {
		if (v >= _V)
			throw std::invalid_argument("Vertice inexistente");
		return _adj[v];
	}


	/**
	* Muestra el grafo en el stream de salida o (para depurar)
	*/
	void print(std::ostream & o = std::cout) const {
		o << _V << " vértices, " << _E << " aristas\n";
		for (auto v = 0; v < _V; ++v) {
			o << v << ": ";
			for (auto w : _adj[v]) {
				o << w << " ";
			}
			o << "\n";
		}
	}

};

/**
* Para mostrar grafos por la salida estándar.
*/
inline std::ostream& operator<<(std::ostream & o, Grafo const& g) {
	g.print(o);
	return o;
}



/**
* Recorrido en profundidad de un grafo a partir de un vértice origen.
*/
class DepthFirstSearch {
public:
	DepthFirstSearch(Grafo const& G, size_t s) : _count(0), _marked(G.V(), false) {
		dfs(G, s);
	}

	// ¿hay camino del origen a v?
	bool marked(size_t v) const {
		return _marked[v];
	}

	// número de vértices conectados a s (en la misma componente conexa que s)
	size_t count() const {
		return _count;
	}

private:
	std::vector<bool> _marked;  // marked[v] = ¿hay camino de s a v?
	size_t _count;              // número de vértices conectados a s

								// recorrido en profundidad desde v
	void dfs(Grafo const& G, size_t v) {
		++_count;
		_marked[v] = true; // para no repetir vértices
		for (auto w : G.adj(v)) { // recorremos todos los adyacentes a v
			if (!_marked[w]) {
				dfs(G, w);
			}
		}
	}

};


/**
* Recorrido en profundidad de un grafo a partir de un vértice origen.
* Permite recuperar los caminos desde el origen a todos los vértices alcanzables.
*/
class DepthFirstPaths {
public:
	DepthFirstPaths(Grafo const& G, size_t s) : marked(G.V(), false), edgeTo(G.V()), s(s) {
		dfs(G, s);
	}

	// ¿Hay camino del origen a v?
	bool hasPathTo(size_t v) const {
		return marked[v];
	}

	// Devuelve un camino desde el origen a v (vacío si no están conectados)
	Path pathTo(size_t v) const {
		Path path;
		if (!hasPathTo(v))
			return path;
		// recuperamos el camino retrocediendo
		for (auto x = v; x != s; x = edgeTo[x])
			path.push_front(x);
		path.push_front(s);
		return path;
	}


private:
	std::vector<bool> marked;    // marked[v] = ¿hay camino de s a v?
	std::vector<size_t> edgeTo;  // edgeTo[v] = último vértice antes de llegar a v
	size_t s;                    // vértice origen

								 // recorrido en profundidad desde v
	void dfs(Grafo const& G, size_t v) {
		marked[v] = true;
		for (auto w : G.adj(v)) {
			if (!marked[w]) {
				edgeTo[w] = v;
				dfs(G, w);
			}
		}
	}
};


/**
* Recorrido en anchura de un grafo a partir de un vértice origen.
* Permite recuperar los caminos más cortos desde el origen a todos los vértices alcanzables.
*/
class BreadthFirstPaths {
public:
	BreadthFirstPaths(Grafo const& G, size_t s)
		: marked(G.V(), false), edgeTo(G.V()), distTo(G.V()), s(s) {
		bfs(G, s);
	}

	// ¿Hay camino del origen a v?
	bool hasPathTo(size_t v) const {
		return marked[v];
	}

	// Devuelve el camino más corto desde el origen a v (vacío si no están conectados)
	Path pathTo(size_t v) const {
		Path path;
		if (!hasPathTo(v))
			return path;
		// recuperamos el camino retrocediendo
		for (auto x = v; x != s; x = edgeTo[x])
			path.push_front(x);
		path.push_front(s);
		return path;
	}

	// Devuelve el número de aristas en el camino más corto a v
	size_t distance(size_t v) const {
		return distTo[v];
	}

private:
	std::vector<bool> marked;     // marked[v] = ¿hay camino de s a v?
	std::vector<size_t> edgeTo;   // edgeTo[v] = último vértice antes de llegar a v
	std::vector<size_t> distTo;   // distTo[v] = número de aristas en el camino s-v más corto
	size_t s;                     // vértice origen

	void bfs(Grafo const& G, size_t s) {
		std::queue<size_t> q;
		distTo[s] = 0;
		marked[s] = true;
		q.push(s);
		while (!q.empty()) {
			auto v = q.front(); q.pop();
			for (auto w : G.adj(v)) {
				if (!marked[w]) {
					edgeTo[w] = v;
					distTo[w] = distTo[v] + 1;
					marked[w] = true;
					q.push(w);
				}
			}
		}
	}

};

#endif /* GRAFO_H_ */


bool distSalto(int salto, std::pair<int, int> a, std::pair<int, int> b) {
	int first = std::abs(a.first - b.first);
	int second = std::abs(a.second - b.second);
	return (first * first) + (second * second) <= (salto * salto);
}

bool resuelveCaso() {
	int alto;
	std::cin >> alto;
	if (std::cin.fail()) return false;
	else {
		int ancho, salto, numArboles, y, x;
		std::cin >> ancho >> salto >> numArboles;
		++alto; ++ancho;
		std::vector<std::pair<int, int>> arboles = { { 0, 0 },{ alto - 1, ancho - 1 } }, readOrder;
		Grafo g(alto * ancho);
		for (int i = 0; i < numArboles; ++i) {
			std::cin >> y >> x;
			arboles.emplace_back(std::pair<int, int>({ y, x }));
			readOrder.emplace_back(std::pair<int, int>({ y, x }));
		}
		std::sort(arboles.begin(), arboles.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.first > b.first; });
		
		for (int i = 0; i < arboles.size(); ++i)
			for (int j = i + 1; j < arboles.size() && arboles[i].first <= arboles[j].first + salto; ++j)
				if (distSalto(salto, arboles[i], arboles[j]))
					g.ponArista((arboles[i].first * ancho) + arboles[i].second, (arboles[j].first * ancho) + arboles[j].second);
		
		ConjuntosDisjuntos g2(alto * ancho);
		std::vector<bool> marked(alto * ancho, false);
		marked[0] = true;
		marked[(alto * ancho) - 1] = true;
		std::pair<int, int> arbol, arbolDisconnect;
		int v;
		bool found = false;
		for (int i = readOrder.size() - 1; i >= 0 && !found; --i) {
			arbol = readOrder[i];
			v = (arbol.first * ancho) + arbol.second;
			for (auto w : g.adj(v)) {
				if (marked[w]) {
					g2.unir(v, w);
					if (g2.unidos(0, (alto * ancho) - 1)) {
						arbolDisconnect = arbol;
						found = true;
					}
				}
			}
			marked[v] = true;
		}

		if (found) std::cout << arbolDisconnect.first << " " << arbolDisconnect.second << "\n";
		else std::cout << "NUNCA SE PUDO\n";
		return true;
	}
}

/* El coste de este algoritmo es de
O(n * log n) // Supongo que de cada arbol se puede saltar a un numero constante de arboles
	n es el numero de arboles
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