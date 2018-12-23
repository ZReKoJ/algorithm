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

class persona {
private:
	int _edad;
	std::string _nombre;
public:
	persona() {}
	persona(int ed, std::string no) : _edad(ed), _nombre(no) {}
	int edad() const { return _edad; }
	std::string nombre() { return _nombre; }
	void scanf(std::istream &in = std::cin) {
		in >> _edad;
		in.get();
		getline(in, _nombre);
	}
	void print(std::ostream &out = std::cout) const { out << _nombre; }
};

inline std::istream & operator>>(std::istream &in, persona &i) {
	i.scanf(in);
	return in;
}

inline std::ostream & operator<<(std::ostream &out, const persona &o) {
	o.print(out);
	return out;
}

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

//
//  list_eda.h
//
//  Implementación del TAD lista heredando de colas dobles
//  y con iteradores
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 6/12/16.
//  Copyright (c) 2016 Alberto Verdejo. All rights reserved.
//

#ifndef list_eda_h
#define list_eda_h

#include <stdexcept>
#include <cassert>

template <class T>
class list : public deque<T> {
	using Nodo = typename deque<T>::Nodo;
public:

	template <class Predicate>
	void remove_if(Predicate pred) {
		Nodo *aux = this->fantasma->sig;
		while (aux != this->fantasma) {
			if (pred(aux->elem)) {
				aux->ant->sig = aux->sig;
				aux->sig->ant = aux->ant;
				--this->nelems;
			}
			aux = aux->sig;
		}
	}

	void print() {
		Nodo *aux = this->fantasma->sig;
		while (aux != this->fantasma) {
			std::cout << aux->elem << '\n';
			aux = aux->sig;
		}
	}
public:

	// constructor: lista vacía
	list() {}

	// consultar el elemento en la posición ind, si existe (numeradas desde 0)
	T const& at(size_t ind) const {
		if (ind >= this->nelems)
			throw std::out_of_range("posicion fuera de la lista");

		Nodo *aux = this->fantasma->sig;
		for (size_t i = 0; i < ind; ++i)
			aux = aux->sig;

		return aux->elem;
	}

	/*
	Iteradores que permiten recorrer la lista pero no cambiar sus elementos.
	*/
	class const_iterator {
	public:

		T const& operator*() const {
			if (act == fan) throw std::out_of_range("fuera de la lista");
			return act->elem;
		}

		const_iterator & operator++() {
			if (act == fan) throw std::out_of_range("fuera de la lista");
			act = act->sig;
			return *this;
		}

		const_iterator operator++(int) {
			const_iterator ret(*this);
			operator++();
			return ret;
		}

		bool operator==(const_iterator const& that) const {
			return act == that.act;
		}

		bool operator!=(const_iterator const& that) const {
			return !(*this == that);
		}

	protected:
		// list pueda construir objetos del tipo iterador
		friend class list;

		const_iterator(Nodo* ac, Nodo* fa) : act(ac), fan(fa) {}

		// puntero al nodo actual del recorrido
		Nodo* act;
		// puntero al nodo fantasma (para saber cuándo estamos fuera)
		Nodo* fan;
	};

	// devuelve un iterador constante al principio de la lista
	const_iterator cbegin() const {
		return const_iterator(this->fantasma->sig, this->fantasma);
	}

	// devuelve un iterador constante al final del recorrido y fuera de este
	const_iterator cend() const {
		return const_iterator(this->fantasma, this->fantasma);
	}

	/*
	Iteradores que permiten recorrer la lista y cambiar sus elementos
	*/
	class iterator : public const_iterator {
	public:
		T & operator*() {
			if (this->act == this->fan) throw std::out_of_range("fuera de la lista");
			return this->act->elem;
		}
	protected:
		// list pueda construir objetos del tipo iterador
		friend class list;
		iterator(Nodo* ac, Nodo* fa) : const_iterator(ac, fa) {}
	};

	// devuelve un iterador al principio de la lista
	iterator begin() {
		return iterator(this->fantasma->sig, this->fantasma);
	}
	const_iterator begin() const {
		return const_iterator(this->fantasma->sig, this->fantasma);
	}

	// devuelve un iterador al final del recorrido y fuera de este
	iterator end() {
		return iterator(this->fantasma, this->fantasma);
	}
	const_iterator end() const {
		return const_iterator(this->fantasma, this->fantasma);
	}

	// inserta un elemento delante del apuntado por el iterador
	iterator insert(iterator const& it, T const& elem) {
		Nodo* nuevo = this->inserta_elem(elem, it.act->ant, it.act);
		++this->nelems;
		return iterator(nuevo, this->fantasma);
	}

	// elimina el elemento apuntado por el iterador
	iterator erase(iterator const& it) {
		if (it.act == this->fantasma)
			throw std::out_of_range("fuera de la lista");

		iterator next(it.act->sig, this->fantasma);
		this->borra_elem(it.act);
		--this->nelems;
		return next;
	}
};

#endif // list_eda_h

class Predicado {
private:
	int _min, _max;
public:
	Predicado(int min, int max) : _min(min), _max(max) {}

	bool operator()(persona const& p) {
		return _min > p.edad() || p.edad() > _max;
	}
};


bool resuelveCaso() {
	int numCasos, min, max;
	std::cin >> numCasos >> min >> max;
	if (!(numCasos == 0 && min == 0 && max == 0)) {
		list<persona> v;
		persona p;
		for (int i = 0; i < numCasos; ++i) {
			std::cin >> p;
			v.insert(v.end(), p);
		}
		v.remove_if(Predicado(min, max));
		v.print();
		std::cout << "---\n";
		return true;
	}
	else return false;
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