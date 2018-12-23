// E26, Zihao Hong
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
#include <math.h>
//
//  queue_eda.h
//
//  Implementación del TAD cola con nodos enlazados
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 6/12/16.
//  Copyright (c) 2016 Alberto Verdejo. All rights reserved.
//

#ifndef queue_eda_h
#define queue_eda_h

#include <stdexcept>

template <class T>
class queue {
public:

	// constructor: cola vacía
	queue() : prim(nullptr), ult(nullptr), nelems(0) {}

	// destructor
	~queue() {
		libera(); prim = ult = nullptr;
	}

	// constructor por copia
	queue(queue<T> const& other) : prim(nullptr), ult(nullptr) {
		copia(other);
	}

	// operador de asignación
	queue<T> & operator=(queue<T> const& other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	// añadir un elemento al final de la cola
	void push(T const& elem) {
		Nodo* nuevo = new Nodo(elem, nullptr);

		if (ult != nullptr)
			ult->sig = nuevo;
		ult = nuevo;
		if (prim == nullptr) // la cola estaba vacía
			prim = nuevo;
		++nelems;
	}

	// consultar el primero de la cola
	T const& front() const {
		if (empty())
			throw std::domain_error("la cola vacia no tiene primero");
		return prim->elem;
	}

	// eliminar el primero de la cola
	void pop() {
		if (empty())
			throw std::domain_error("eliminando de una cola vacia");
		Nodo* a_borrar = prim;
		prim = prim->sig;
		if (prim == nullptr) // la cola se ha quedado vacía
			ult = nullptr;
		delete a_borrar;
		--nelems;
	}

	// consultar si la cola está vacía
	bool empty() const {
		return nelems == 0;
	}

	void invertir(int pos) {
		Nodo *ptr = prim;
		for (int i = 0; i < pos && ptr != nullptr; ++i) {
			ptr = ptr->sig;
		}
		Nodo *ant = ptr, *aux;
		ptr = prim;
		for (int i = 0; i < pos && ptr != nullptr; ++i) {
			aux = ptr->sig;
			ptr->sig = ant;
			ant = ptr;
			ptr = aux;
		}
		prim = ant;
	}

	void print() {
		if (prim == nullptr) {
			std::cout << "{}\n";
		}
		else {
			std::cout << "{" << prim->elem;
			Nodo *ptr = prim->sig;
			while (ptr != nullptr) {
				std::cout << "," << ptr->elem;
				ptr = ptr->sig;
			}
			std::cout << "}\n";
		}
	}

protected:

	/*
	Nodo que almacena internamente el elemento (de tipo T),
	y un puntero al nodo siguiente, que puede ser nullptr si
	el nodo es el último de la lista enlazada.
	*/
	struct Nodo {
		Nodo() : sig(nullptr) {}
		Nodo(T const& elem, Nodo* si = nullptr) : elem(elem), sig(si) {}
		T elem;
		Nodo* sig;
	};

	// punteros al primer y último elemento
	Nodo* prim;
	Nodo* ult;

	// número de elementos en la cola
	size_t nelems;

	void libera() {
		while (prim != nullptr) {
			Nodo* aux = prim;
			prim = prim->sig;
			delete aux;
		}
	}

	void copia(queue const& other) {
		if (other.empty()) {
			prim = ult = nullptr;
			nelems = 0;
		}
		else {
			Nodo* act = other.prim;
			Nodo* ant;
			prim = new Nodo(act->elem);
			ant = prim;
			while (act->sig != nullptr) {
				act = act->sig;
				ant->sig = new Nodo(act->elem);
				ant = ant->sig;
			}
			ult = ant;
			nelems = other.nelems;
		}
	}
};

#endif // queue_eda_h

void resuelveCaso() {
	queue<int> v;
	int valor;
	std::cin >> valor;
	while (valor != -1) {
		v.push(valor);
		std::cin >> valor;
	}
	v.print();
	std::cin >> valor;
	v.invertir(valor);
	v.print();
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}