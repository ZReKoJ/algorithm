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
//  GrafoValorado.h
//
//  Implementación de grafos no dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef GRAFOVALORADO_H_
#define GRAFOVALORADO_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

template <typename Valor>
class Arista_impl;

template <typename Valor>
class Arista {
public:
	Arista();
	Arista(size_t v, size_t w, Valor valor);
	size_t uno() const;
	size_t otro(size_t vert) const;
	Valor valor() const;
	void print(std::ostream & o = std::cout) const;
private:
	std::shared_ptr<Arista_impl<Valor>> pimpl;
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, Arista<Valor> const& ar) {
	ar.print(o);
	return o;
}

template <typename Valor>
inline bool operator<(Arista<Valor> const& a, Arista<Valor> const& b)
{
	return a.valor() < b.valor();
}

template <typename Valor>
inline bool operator>(Arista<Valor> const& a, Arista<Valor> const& b)
{
	return a.valor() > b.valor();
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoValorado {
public:

	/**
	* Crea un grafo valorado con V vértices, sin aristas.
	*/
	GrafoValorado(size_t v) : _V(v), _E(0), _adj(_V) { }

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
	void ponArista(Arista<Valor> const& arista);

	/**
	* Devuelve la lista de adyacencia de v.
	* @throws invalid_argument si v no existe
	*/
	AdysVal<Valor> const& adj(size_t v) const;

	/**
	* Muestra el grafo en el stream de salida o
	*/
	void print(std::ostream& o = std::cout) const;

private:
	size_t _V;   // número de vértices
	size_t _E;   // número de aristas
	std::vector<AdysVal<Valor>> _adj;   // vector de listas de adyacentes

};

/**
* Para mostrar grafos por la salida estándar.
*/
template <typename Valor>
std::ostream& operator<<(std::ostream & o, GrafoValorado<Valor> const& g);



// IMPLEMENTACIÓN

template <typename Valor>
Arista<Valor>::Arista()
	: pimpl(nullptr) {}

template <typename Valor>
Arista<Valor>::Arista(size_t v, size_t w, Valor valor)
	: pimpl(std::make_shared<Arista_impl<Valor>>(v, w, valor)) {}

template <typename Valor>
size_t Arista<Valor>::uno() const { return pimpl->uno(); }

template <typename Valor>
size_t Arista<Valor>::otro(size_t vert) const { return pimpl->otro(vert); }

template <typename Valor>
Valor Arista<Valor>::valor() const { return pimpl->valor(); }

template <typename Valor>
void Arista<Valor>::print(std::ostream & o) const { pimpl->print(o); }


template <typename Valor>
class Arista_impl {
public:
	Arista_impl(size_t v, size_t w, Valor valor) : v(v), w(w), _valor(valor) {};
	size_t uno() const { return v; }
	size_t otro(size_t vert) const { return (vert == v) ? w : v; }
	Valor valor() const { return _valor; }
	void print(std::ostream& o = std::cout) const {
		o << "(" << v << ", " << w << ", " << _valor << ")";
	}
private:
	size_t v, w;
	Valor _valor;
};


template <typename Valor>
void GrafoValorado<Valor>::ponArista(Arista<Valor> const& arista) {
	size_t v = arista.uno();
	size_t w = arista.otro(v);
	if (v >= _V || w >= _V) throw std::invalid_argument("Vertice inexistente");
	++_E;
	_adj[v].push_back(arista);
	_adj[w].push_back(arista);
}

template <typename Valor>
AdysVal<Valor> const& GrafoValorado<Valor>::adj(size_t v) const {
	if (v >= _V) throw std::invalid_argument("Vertice inexistente");
	return _adj[v];
}

template <typename Valor>
void GrafoValorado<Valor>::print(std::ostream & o) const {
	o << _V << " vértices, " << _E << " aristas\n";
	for (auto v = 0; v < _V; ++v) {
		o << v << ": ";
		for (auto const& w : _adj[v]) {
			o << w << " ";
		}
		o << "\n";
	}
}

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, GrafoValorado<Valor> const& g) {
	g.print(o);
	return o;
}


#endif /* GRAFOVALORADO_H_ */

//
//  IndexPQ.h
//
//  Implementación de colas con prioridad mediante montículos.
//  Los elementos son enteros de 0 a N-1 que tienen asociada una prioridad
//  dentro de la cola. La prioridad de un elemento puede ser modificada
//  con coste en O(log N).
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef INDEXPQ_H_
#define INDEXPQ_H_

#include <iostream>
#include <stdexcept>
#include <vector>


// T es el tipo de las prioridades
// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class IndexPQ {
public:
	// registro para las parejas < elem, prioridad >
	struct Par {
		size_t elem;
		T prioridad;
	};

private:
	// vector que contiene los datos (pares < elem, prio >)
	std::vector<Par> array;     // primer elemento en la posición 1

								// vector que contiene las posiciones en array de los elementos
	std::vector<size_t> posiciones;   // un 0 indica que el elemento no está

									  // número de elementos en el montículo
	size_t numElems;

	/* Objeto función que sabe comparar prioridades.
	antes(a,b) es cierto si a es más prioritario que b */
	Comparator antes;

public:
	IndexPQ(size_t t, Comparator c = Comparator()) :
		array(t + 1), posiciones(t, 0), numElems(0), antes(c) {}

	IndexPQ(IndexPQ<T, Comparator> const&) = default;

	IndexPQ<T, Comparator>& operator=(IndexPQ<T, Comparator> const&) = default;

	~IndexPQ() = default;

	// e debe ser uno de los posibles elementos
	void push(size_t e, T const& p) {
		if (posiciones.at(e) != 0)
			throw std::invalid_argument("No se pueden insertar elementos repetidos.");
		else {
			++numElems;
			array[numElems].elem = e; array[numElems].prioridad = p;
			posiciones[e] = numElems;
			flotar(numElems);
		}
	}

	void update(size_t e, T const& p) {
		auto i = posiciones.at(e);
		if (i == 0) // el elemento e se inserta por primera vez
			push(e, p);
		else {
			array[i].prioridad = p;
			if (i != 1 && antes(array[i].prioridad, array[i / 2].prioridad))
				flotar(i);
			else // puede hacer falta hundir a e
				hundir(i);
		}
	}

	bool empty() const { return (numElems == 0); }

	Par const& top() const {
		if (numElems == 0)
			throw std::domain_error("No se puede consultar el primero de una cola vacia");
		else return array[1];
	}

	void pop() {
		if (numElems == 0) throw std::domain_error("No se puede eliminar el primero de una cola vacía.");
		else {
			posiciones[array[1].elem] = 0; // para indicar que no está
			if (numElems > 1) {
				array[1] = std::move(array[numElems]);
				posiciones[array[1].elem] = 1;
				--numElems;
				hundir(1);
			}
			else
				--numElems;
		}
	}

	// solo para depurar
	void print(std::ostream& o = std::cout) const {
		for (auto i = 1; i <= numElems; ++i)
			o << i << ":" << array[i].elem << "," << array[i].prioridad << " | ";
		o << '\n';
		for (auto i = 1; i < posiciones.size(); ++i)
			o << i << ":" << posiciones[i] << " | ";
		o << '\n';
	}


private:

	void flotar(size_t n) {
		Par parmov = std::move(array[n]);
		size_t hueco = n;
		while (hueco != 1 && antes(parmov.prioridad, array[hueco / 2].prioridad)) {
			array[hueco] = std::move(array[hueco / 2]); posiciones[array[hueco].elem] = hueco;
			hueco /= 2;
		}
		array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
	}

	void hundir(size_t n) {
		Par parmov = std::move(array[n]);
		size_t hueco = n;
		size_t hijo = 2 * hueco; // hijo izquierdo, si existe
		while (hijo <= numElems) {
			// cambiar al hijo derecho de i si existe y va antes que el izquierdo
			if (hijo < numElems && antes(array[hijo + 1].prioridad, array[hijo].prioridad))
				++hijo;
			// flotar el hijo si va antes que el elemento hundiéndose
			if (antes(array[hijo].prioridad, parmov.prioridad)) {
				array[hueco] = std::move(array[hijo]); posiciones[array[hueco].elem] = hueco;
				hueco = hijo; hijo = 2 * hueco;
			}
			else break;
		}
		array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
	}

};


template <typename T, typename Comparator>
inline std::ostream& operator<<(std::ostream & o, IndexPQ<T, Comparator> const& a) {
	a.print(o);
	return o;
}



#endif /* INDEXPQ_H_ */


class CaminoMinimo {
public:
	CaminoMinimo(GrafoValorado<int> const& g) {
		minimo = INT_MAX;
		vecesMin = 0;
		min = std::vector<int>(g.V(), INT_MAX);
		min[0] = 0;
		veces = std::vector<int>(g.V(), 0);
		veces[0] = 1;
		q = IndexPQ<int>(g.V());
		q.push(0, 0);
		exec(g);
		minimo = min[g.V() - 1];
		vecesMin = veces[g.V() - 1];
	}

	int getNumMin() { return vecesMin; }
private:
	int minimo;
	int vecesMin;
	std::vector<int> min;
	std::vector<int> veces;
	IndexPQ<int> q = IndexPQ<int>(0);

	void exec(GrafoValorado<int> const& g) {
		int v, w, res;
		while (!q.empty()) {
			auto e = q.top(); q.pop();
			v = e.elem;
			for (auto edge : g.adj(v)) {
				w = edge.otro(v);
				res = min[v] + edge.valor();
				if (res < min[w]) {
					min[w] = res;
					veces[w] = veces[v];
					q.update(w, min[w]);
				}
				else if (res == min[w]) {
					veces[w] += veces[v];
					q.update(w, min[w]);
				}
			}
		}
	}
};

bool resuelveCaso() {
	int numIntersecciones;
	std::cin >> numIntersecciones;
	if (std::cin.fail()) return false;
	else {
		int numCalles, from, to, valor;
		std::cin >> numCalles;
		GrafoValorado<int> g(numIntersecciones);
		for (int i = 0; i < numCalles; ++i) {
			std::cin >> from >> to >> valor;
			g.ponArista(Arista<int>({ size_t(from - 1), size_t(to - 1), valor }));
		}
		CaminoMinimo cm(g);
		std::cout << cm.getNumMin() << "\n";
		return true;
	}
}

/* El coste de este algoritmo es de
O(E * log V)
	E es el numero de aristas
	V es el numero de vertices
*/
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