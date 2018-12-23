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
//  PriorityQueue.h
//
//  Implementación de colas con prioridad de mínimos (el elemento más
//  prioritario es el menor) mediante montículos binarios
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

const size_t TAM_INICIAL = 20;

// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class PriorityQueue {

	// vector que contiene los datos
	std::vector<T> array;     // primer elemento en la posición 1

							  // número de elementos en el montículo
	size_t numElems;

	/* Objeto función que sabe comparar elementos.
	antes(a,b) es cierto si a es más prioritario que b (a debe salir antes que b) */
	Comparator antes;

public:

	PriorityQueue(size_t t = TAM_INICIAL, Comparator c = Comparator()) :
		array(t + 1), numElems(0), antes(c) {}

	/* Constructor a partir de un vector de elementos */
	PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator()) :
		array(2 * v_ini.size()), numElems(v_ini.size()), antes(c) {
		for (auto i = 0; i < v_ini.size(); ++i)
			array[i + 1] = v_ini[i];
		monticulizar();
	}

	PriorityQueue(PriorityQueue<T, Comparator> const&) = default;

	PriorityQueue<T, Comparator> & operator=(PriorityQueue<T, Comparator> const&) = default;

	~PriorityQueue() = default;


	/* Insertar el elemento x (que incluye su prioridad).
	Si no hay espacio, el array se agranda. */
	void push(T const& x) {
		if (numElems == array.size() - 1)  // si el array se ha llenado se aumenta el tamaño
			array.resize(array.size() * 2);
		++numElems;
		array[numElems] = x;
		flotar(numElems);
	}

	/* Devuelve el número de elementos en la cola. */
	size_t size() const { return numElems; }

	/* Averigua si la cola con prioridad está vacía. */
	bool empty() const { return (numElems == 0); }

	/* Si la cola no es vacía, devuelve el elemento más prioritario. */
	T const& top()  const {
		if (empty()) throw std::domain_error("La cola vacia no tiene top");
		else return array[1];
	}

	/* Si la cola no es vacía, elimina el elemento más prioritario. */
	void pop() {
		if (empty())
			throw std::domain_error("Imposible eliminar el primero de una cola vacia");
		else {
			array[1] = std::move(array[numElems]);
			--numElems;
			hundir(1);
		}
	}

	/* Si la cola no es vacía, elimina y devuelve el elemento más prioritario. */
	void pop(T & prim) {
		if (empty())
			throw std::domain_error("Imposible eliminar el primero de una cola vacia");
		else {
			prim = std::move(array[1]);
			array[1] = std::move(array[numElems]);
			--numElems;
			hundir(1);
		}
	}

	/* Muestra el montículo por la salida o (solo para depurar) */
	void print(std::ostream & o) const {
		for (auto i = 1; i <= numElems; ++i)
			o << array[i] << " ";
	}

private:

	/* Flota el elemento situado en la posición n del montículo. */
	void flotar(size_t n) {
		T elem = std::move(array[n]);
		size_t hueco = n;
		while (hueco != 1 && antes(elem, array[hueco / 2])) {
			array[hueco] = std::move(array[hueco / 2]);
			hueco /= 2;
		}
		array[hueco] = std::move(elem);
	}

	/* Hunde el elemento situado en la posición n del montículo. */
	void hundir(size_t n) {
		T elem = std::move(array[n]);
		size_t hueco = n;
		size_t hijo = 2 * hueco; // hijo izquierdo, si existe
		while (hijo <= numElems) {
			// cambiar al hijo derecho si existe y va antes que el izquierdo
			if (hijo < numElems && antes(array[hijo + 1], array[hijo]))
				++hijo;
			// flotar el hijo si va antes que el elemento hundiéndose
			if (antes(array[hijo], elem)) {
				array[hueco] = std::move(array[hijo]);
				hueco = hijo; hijo = 2 * hueco;
			}
			else break;
		}
		array[hueco] = std::move(elem);
	}

	/* Convierte un vector en un montículo. */
	void monticulizar() {
		for (auto i = numElems / 2; i > 0; --i)
			hundir(i);
	}
};

template <typename T, typename Comparator>
inline std::ostream& operator<<(std::ostream & o, PriorityQueue<T, Comparator> const& a) {
	a.print(o);
	return o;
}


/** Función para construir una cola con prioridad cuyo Comparator es una lambda. */
template<typename T, typename Comparator> // el tipo Comparator se deduce a partir de c
inline PriorityQueue<T, Comparator> make_priorityqueue(Comparator c, size_t tam = TAM_INICIAL)
{
	return PriorityQueue<T, Comparator>(tam, c);
}

#endif /* PRIORITYQUEUE_H_ */

typedef struct {
	int instrumentos;
	int partituras;
} tOrquesta;

class cmp {
public:
	bool operator()(tOrquesta const& a, tOrquesta const& b) {
		double aa = a.instrumentos / double(a.partituras);
		double bb = b.instrumentos / double(b.partituras);
		return aa > bb;
	}
};

void resolver(PriorityQueue<tOrquesta, cmp> & q, int partituras) {
	tOrquesta top;
	while (partituras > 0) {
		top = q.top();
		q.pop();
		top.partituras++;
		q.push(top);
		--partituras;
	}
}

bool resuelveCaso() {
	int partituras, instrumentos;
	std::cin >> partituras;
	if (std::cin.fail()) return false;
	else {
		scanf("%d", &instrumentos);
		PriorityQueue<tOrquesta, cmp> q;
		int num;
		for (int i = 0; i < instrumentos; ++i) {
			//std::cin >> num;
			scanf("%d", &num);
			q.push({ num, 1 });
		}
		resolver(q, partituras - q.size());
		auto res = q.top();
		int r = res.instrumentos / res.partituras;
		if (res.instrumentos % res.partituras != 0) r++;
		//std::cout << r << "\n";
		printf("%d\n", r);
		return true;
	}
}

#define RKJ

int main() {
#ifndef RKJ
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {};

#ifndef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}