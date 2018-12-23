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
//  GrafoDirigidoValorado.h
//
//  Implementación de grafos dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef GRAFODIRIGIDOVALORADO_H_
#define GRAFODIRIGIDOVALORADO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template <typename Valor>
class AristaDirigida_impl;

template <typename Valor>
class AristaDirigida {
public:
	AristaDirigida();
	AristaDirigida(size_t v, size_t w, Valor valor);
	size_t from() const;
	size_t to() const;
	Valor valor() const;
	void print(std::ostream & o = std::cout) const;
private:
	std::shared_ptr<AristaDirigida_impl<Valor>> pimpl;
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, AristaDirigida<Valor> const& ar) {
	ar.print(o);
	return o;
}

template <typename Valor>
inline bool operator<(AristaDirigida<Valor> const& a, AristaDirigida<Valor> const& b)
{
	return a.valor() < b.valor();
}


template <typename Valor>
using AdysDirVal = std::vector<AristaDirigida<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoDirigidoValorado {
public:

	/**
	* Crea un grafo con V vértices.
	*/
	GrafoDirigidoValorado(size_t v) : _V(v), _E(0), _adj(_V) {}

	/**
	* Devuelve el número de vértices del grafo.
	*/
	size_t V() const { return _V; }

	/**
	* Devuelve el número de aristas del grafo.
	*/
	size_t E() const { return _E; }

	/**
	* Añade la arista dirigida v-w al grafo.
	* @throws invalid_argument si algún vértice no existe
	*/
	void ponArista(AristaDirigida<Valor> arista);

	/**
	* Comprueba si hay arista de v a w.
	*/
	bool hayArista(size_t v, size_t w) const;

	/**
	* Devuelve la lista de adyacencia de v.
	* @throws invalid_argument si v no existe
	*/
	AdysDirVal<Valor> const& adj(size_t v) const;

	/**
	* Devuelve el grafo dirigido inverso.
	*/
	GrafoDirigidoValorado<Valor> reverse() const;

	/**
	* Muestra el grafo en el stream de salida o
	*/
	void print(std::ostream& o = std::cout) const;

private:
	size_t _V;   // número de vértices
	size_t _E;   // número de aristas
	std::vector<AdysDirVal<Valor>> _adj;   // vector de listas de adyacentes

};

/**
* Para mostrar grafos por la salida estándar.
*/
template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, const GrafoDirigidoValorado<Valor>& g) {
	g.print(o);
	return o;
}


// IMPLEMENTACIÓN

template <typename Valor>
AristaDirigida<Valor>::AristaDirigida()
	: pimpl(nullptr) {}

template <typename Valor>
AristaDirigida<Valor>::AristaDirigida(size_t v, size_t w, Valor valor)
	: pimpl(std::make_shared<AristaDirigida_impl<Valor>>(v, w, valor)) {}

template <typename Valor>
size_t AristaDirigida<Valor>::from() const { return pimpl->from(); }

template <typename Valor>
size_t AristaDirigida<Valor>::to() const { return pimpl->to(); }

template <typename Valor>
Valor AristaDirigida<Valor>::valor() const { return pimpl->valor(); }

template <typename Valor>
void AristaDirigida<Valor>::print(std::ostream & o) const { pimpl->print(o); }


template <typename Valor>
class AristaDirigida_impl {
public:
	AristaDirigida_impl(size_t v, size_t w, Valor valor) : v(v), w(w), _valor(valor) {};
	size_t from() const { return v; }
	size_t to() const { return w; }
	Valor valor() const { return _valor; }
	void print(std::ostream& o) const {
		o << "(" << v << ", " << w << ", " << _valor << ")";
	}
private:
	size_t v, w;
	Valor _valor;
};


template <typename Valor>
void GrafoDirigidoValorado<Valor>::ponArista(AristaDirigida<Valor> arista) {
	size_t v = arista.from();
	size_t w = arista.to();
	if (v >= _V || w >= _V) throw std::invalid_argument("Vertice inexistente");
	++_E;
	_adj[v].push_back(arista);
}

template <typename Valor>
bool GrafoDirigidoValorado<Valor>::hayArista(size_t v, size_t w) const {
	for (auto a : _adj[v])
		if (a.to() == w) return true;
	return false;
}

template <typename Valor>
AdysDirVal<Valor>  const& GrafoDirigidoValorado<Valor>::adj(size_t v) const {
	if (v >= _V) throw std::invalid_argument("Vertice inexistente");
	return _adj[v];
}

template <typename Valor>
GrafoDirigidoValorado<Valor> GrafoDirigidoValorado<Valor>::reverse() const {
	GrafoDirigidoValorado R(_V);
	for (auto v = 0; v < _V; ++v) {
		for (auto a : _adj[v]) {
			R.ponArista(AristaDirigida<Valor>(a.to(), a.from(), a.valor()));
		}
	}
	return R;
}

template <typename Valor>
void GrafoDirigidoValorado<Valor>::print(std::ostream& o) const {
	o << _V << " vértices, " << _E << " aristas\n";
	for (auto v = 0; v < _V; ++v) {
		o << v << ": ";
		for (auto a : _adj[v]) {
			o << a << " ";
		}
		o << "\n";
	}
}


#endif /* GRAFODIRIGIDOVALORADO_H_ */

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

class ShortestPath {
public:
	ShortestPath(GrafoDirigidoValorado<int> const& g, size_t v) {
		min = std::vector<int>(g.V(), INT_MAX);
		min[v] = 0;
		q = IndexPQ<int>(g.V());
		q.push(v, 0);
		while (!q.empty()) {
			auto v = q.top().elem;
			q.pop();
			for (auto w : g.adj(v)) {
				if (min[w.from()] + w.valor() < min[w.to()]) {
					min[w.to()] = min[w.from()] + w.valor();
					q.update(w.to(), min[w.to()]);
				}
			}
		}
	}

	int minTo(int w) {
		if (min[w] == INT_MAX) throw std::domain_error("Numero no actualizado");
		else return min[w];
	}

private:
	std::vector<int> min;
	IndexPQ<int> q = IndexPQ<int>(0);
};

bool resuelveCaso() {
	int numCasas;
	std::cin >> numCasas;
	if (std::cin.fail()) return false;
	else {
		int numRutas;
		std::cin >> numRutas;
		GrafoDirigidoValorado<int> g(numCasas);
		int from, to, valor;
		for (int i = 0; i < numRutas; ++i) {
			std::cin >> from >> to >> valor;
			g.ponArista({ size_t(from - 1), size_t(to - 1), valor });
		}
		int casa, paquete, numPaquetes;
		std::cin >> casa >> numPaquetes;
		--casa;
		ShortestPath sp(g, casa), sp2(g.reverse(), casa);
		int suma = 0;
		bool posible = true;
		for (int i = 0; i < numPaquetes; ++i) {
			std::cin >> paquete;
			try { suma += (sp.minTo(paquete - 1) + sp2.minTo(paquete - 1)); }
			catch (std::domain_error &err) { posible = false; }
		}
		if (posible) std::cout << suma << "\n";
		else std::cout << "Imposible\n";
		return true;
	}
}

/* El coste de este algoritmo es de
O((V + E) + (E * log V)) // Lo de  V + E es por lo de reverse
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