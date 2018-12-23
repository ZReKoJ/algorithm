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
#include <climits>

#ifndef DOMJUDGE
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif
#endif

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

class t {
private:
	int hora, minuto, segundo;
public:
	t() {}
	t(int h, int m, int s) {
		if ((0 <= h && h < 24) && (0 <= m && m < 60) && (0 <= s && s < 60)) {
			hora = h; minuto = m; segundo = s;
		}
		else throw std::domain_error("ERROR");
	}
	bool operator<= (const t &that) const {
		if (hora == that.hora) {
			if (minuto == that.minuto)
				return segundo <= that.segundo;
			else return minuto < that.minuto;
		}
		else return hora < that.hora;
	}
	bool operator< (const t &that) const {
		if (hora == that.hora) {
			if (minuto == that.minuto)
				return segundo < that.segundo;
			else return minuto < that.minuto;
		}
		else return hora < that.hora;
	}
	bool operator== (const t &that) const {
		return (hora == that.hora && minuto == that.minuto && segundo == that.segundo);
	}
	t operator+ (const t &that) const {
		int hr, mn, sc, a;
		sc = (segundo + that.segundo) % 60;
		a = (segundo + that.segundo) / 60;
		mn = (minuto + that.minuto + a) % 60;
		a = (minuto + that.minuto + a) / 60;
		hr = hora + that.hora + a;
		if (hr < 24)
			return t(hr, mn, sc);
		else
			throw std::domain_error("ERROR: Dia siguiente");
	}
	void print(std::ostream & out = std::cout) const {
		out << std::setfill('0') << std::setw(2) << hora << ":" << std::setw(2) << minuto << ":" << std::setw(2) << segundo;
	}
};
inline std::ostream & operator<<(std::ostream & out, t const& rhs) {
	rhs.print(out);
	return out;
}

template <class T>
class queueImpar : public queue<T> {
	using Nodo = typename queue<T>::Nodo; // para poder usar Nodo aquí
public:
	void print(std::ostream & o = std::cout) const {
		Nodo *act;
		act = this->prim;
		while (act != nullptr) {
			std::cout << act->elem << " ";
			act = act->sig;
		}
	}

	void quitarPar() {
		Nodo *act = this->prim, *ant = this->prim;
		int i = 1;
		while (act != nullptr) {
			if (i % 2 == 0) {
				ant->sig = act->sig;
				delete act;
				--this->nelems;
				act = ant->sig;
			}
			else {
				ant = act;
				act = act->sig;
			}
			++i;
		}
		this->ult = ant;
	}
};

bool resuelveCaso() {
	int numValores;
	std::cin >> numValores;
	if (numValores != 0) {
		queueImpar<t> cola;
		int h, m, s;
		char residuo;
		for (int i = 0; i < numValores; ++i) {
			std::cin >> h >> residuo >> m >> residuo >> s;
			cola.push(t(h, m, s));
		}
		cola.quitarPar();
		cola.print();
		std::cout << "\n";
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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