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
#include <stdexcept>

//#define RKJ
//#define MTW

//
//  deque_eda.h
//
//  Implementación del TAD cola doble con nodos doblemente enlazados
//  y nodo fantasma (circular)
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 6/12/16.
//  Copyright (c) 2016 Alberto Verdejo. All rights reserved.
//

#ifndef deque_eda_h
#define deque_eda_h

#include <stdexcept>
#include <cassert>

template <class T>
class deque {
public:

	// constructor: cola doble vacía
	deque() : fantasma(new Nodo()), nelems(0) {
		fantasma->sig = fantasma;
		fantasma->ant = fantasma;
	}

	// destructor
	~deque() {
		libera();
	}

	// constructor por copia
	deque(deque<T> const& other) : fantasma(nullptr) {
		copia(other);
	}

	// operador de asignación
	deque<T> & operator=(deque<T> const& that) {
		if (this != &that) {
			libera();
			copia(that);
		}
		return *this;
	}

	// operador de comparación
	bool operator==(deque<T> const& that) const {
		if (nelems != that.nelems)
			return false;
		Nodo* p1 = fantasma->sig;
		Nodo* p2 = that.fantasma->sig;
		while ((p1 != fantasma) && (p2 != that.fantasma)) {
			if (p1->elem != p2->elem)
				return false;
			p1 = p1->sig;
			p2 = p2->sig;
		}
		return (p1 == fantasma) && (p2 == that.fantasma);
	}

	bool operator!=(deque<T> const& that) const {
		return !(*this == that);
	}

	// añadir un elemento por el principio
	void push_front(const T &e) {
		inserta_elem(e, fantasma, fantasma->sig);
		++nelems;
	}

	// añadir un elemento por el final
	void push_back(const T &e) {
		inserta_elem(e, fantasma->ant, fantasma);
		++nelems;
	}

	// consultar el primer elemento de la dcola
	T const& front() const {
		if (empty())
			throw std::domain_error("la dcola vacia no tiene primero");
		return fantasma->sig->elem;
	}

	// consultar el último elemento de la dcola
	T const& back() const {
		if (empty())
			throw std::domain_error("la dcola vacia no tiene ultimo");
		return fantasma->ant->elem;
	}

	// eliminar el primer elemento
	void pop_front() {
		if (empty())
			throw std::domain_error("eliminando el primero de una dcola vacia");
		borra_elem(fantasma->sig);
		--nelems;
	}

	// elminar el último elemento
	void pop_back() {
		if (empty())
			throw std::domain_error("eliminando el ultimo de una dcola vacia");
		borra_elem(fantasma->ant);
		--nelems;
	}

	// consultar si la dcola está vacía
	bool empty() const {
		return nelems == 0;
	}

	// consultar el tamaño de la dcola
	size_t size() const {
		return nelems;
	}

protected:
	/*
	Nodo que almacena internamente el elemento (de tipo T),
	y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	*/
	struct Nodo {
		Nodo() : ant(nullptr), sig(nullptr) {}
		Nodo(const T &elem, Nodo* ant, Nodo* sig) : elem(elem), ant(ant), sig(sig) {}
		T elem;
		Nodo* ant;
		Nodo* sig;
	};

	// puntero al nodo fantasma
	Nodo* fantasma;

	// número de elementos
	size_t nelems;

	void libera() {
		// primero rompemos la circularidad
		fantasma->ant->sig = nullptr;
		fantasma->ant = nullptr;
		while (fantasma != nullptr) {
			Nodo* aux = fantasma;
			fantasma = fantasma->sig;
			delete aux;
		}
	}

	void copia(deque<T> const& other) {
		fantasma = new Nodo();
		fantasma->sig = fantasma;
		fantasma->ant = fantasma;
		nelems = 0;

		Nodo* act = other.fantasma->sig;
		while (act != other.fantasma) {
			push_back(act->elem);
			act = act->sig;
		}
	}

	// insertar un nuevo nodo entre anterior y siguiente
	static Nodo* inserta_elem(T const& e, Nodo* anterior, Nodo* siguiente) {
		Nodo* nuevo = new Nodo(e, anterior, siguiente);
		anterior->sig = nuevo;
		siguiente->ant = nuevo;
		return nuevo;
	}

	// eliminar el nodo n
	static void borra_elem(Nodo* n) {
		assert(n != nullptr);
		n->ant->sig = n->sig;
		n->sig->ant = n->ant;
		delete n;
	}
};

#endif // deque_eda_h

typedef struct {
	int valor;
	int historial;
} tA;

void mostrar(deque<tA> dq) {
	while (!dq.empty()) {
		std::cout << dq.back().valor << "(" << dq.back().historial << ") ";
		dq.pop_back();
	}
	std::cout << "\n";
}

void resolver(const std::vector<int> &v, int intervalo) {
	deque<tA> dq;
	tA a, m, tmp;
	m.valor = v[0];
	m.historial = 0;
	for (int i = 0; i < v.size(); ++i) {
		a.valor = v[i];
		a.historial = i;
		if (m.valor < a.valor) {
			tmp = a;
			a = m;
			m = tmp;
		}
		while (!dq.empty() && dq.back().valor <= a.valor)
			dq.pop_back();
		dq.push_back(a);
		if (i >= intervalo - 1) {
			if (m.historial < (i - intervalo + 1)) { 
				while (dq.front().historial < (i - intervalo + 1))
					dq.pop_front();
				m = dq.front();
				dq.pop_front();
			}
			if (i == v.size() - 1)
				printf("%d", m.valor);
			//std::cout << m.valor;
			else
				printf("%d ", m.valor);
			//std::cout << m.valor << " ";
#ifdef MTW
			mostrar(dq);
			system("pause");
#endif
		}
#ifdef MTW
		mostrar(dq);
		system("pause");
#endif
	}
	std::cout << '\n';
}																																																																																																																																																																																																																																													

bool resuelveCaso() {
	int numSobres, numComensales;
	scanf("%d", &numSobres);
	scanf("%d", &numComensales);
	//std::cin >> numSobres >> numComensales;
	if (!(numSobres == 0 && numComensales == 0)) {
		std::vector<int> v(numSobres);
		for (int i = 0; i < numSobres; ++i)
			scanf("%d", &v[i]);
			//std::cin >> v[i];
		resolver(v, numComensales);
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