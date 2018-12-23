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
//  Implementaci�n de colas con prioridad de m�nimos (el elemento m�s
//  prioritario es el menor) mediante mont�culos binarios
//
//  Facultad de Inform�tica
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

// Comparator dice cu�ndo un valor de tipo T es m�s prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class PriorityQueue {

	// vector que contiene los datos
	std::vector<T> array;     // primer elemento en la posici�n 1

							  // n�mero de elementos en el mont�culo
	size_t numElems;

	/* Objeto funci�n que sabe comparar elementos.
	antes(a,b) es cierto si a es m�s prioritario que b (a debe salir antes que b) */
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
		if (numElems == array.size() - 1)  // si el array se ha llenado se aumenta el tama�o
			array.resize(array.size() * 2);
		++numElems;
		array[numElems] = x;
		flotar(numElems);
	}

	/* Devuelve el n�mero de elementos en la cola. */
	size_t size() const { return numElems; }

	/* Averigua si la cola con prioridad est� vac�a. */
	bool empty() const { return (numElems == 0); }

	/* Si la cola no es vac�a, devuelve el elemento m�s prioritario. */
	T const& top()  const {
		if (empty()) throw std::domain_error("La cola vacia no tiene top");
		else return array[1];
	}

	/* Si la cola no es vac�a, elimina el elemento m�s prioritario. */
	void pop() {
		if (empty())
			throw std::domain_error("Imposible eliminar el primero de una cola vacia");
		else {
			array[1] = std::move(array[numElems]);
			--numElems;
			hundir(1);
		}
	}

	/* Si la cola no es vac�a, elimina y devuelve el elemento m�s prioritario. */
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

	/* Muestra el mont�culo por la salida o (solo para depurar) */
	void print(std::ostream & o) const {
		for (auto i = 1; i <= numElems; ++i)
			o << array[i] << " ";
	}

private:

	/* Flota el elemento situado en la posici�n n del mont�culo. */
	void flotar(size_t n) {
		T elem = std::move(array[n]);
		size_t hueco = n;
		while (hueco != 1 && antes(elem, array[hueco / 2])) {
			array[hueco] = std::move(array[hueco / 2]);
			hueco /= 2;
		}
		array[hueco] = std::move(elem);
	}

	/* Hunde el elemento situado en la posici�n n del mont�culo. */
	void hundir(size_t n) {
		T elem = std::move(array[n]);
		size_t hueco = n;
		size_t hijo = 2 * hueco; // hijo izquierdo, si existe
		while (hijo <= numElems) {
			// cambiar al hijo derecho si existe y va antes que el izquierdo
			if (hijo < numElems && antes(array[hijo + 1], array[hijo]))
				++hijo;
			// flotar el hijo si va antes que el elemento hundi�ndose
			if (antes(array[hijo], elem)) {
				array[hueco] = std::move(array[hijo]);
				hueco = hijo; hijo = 2 * hueco;
			}
			else break;
		}
		array[hueco] = std::move(elem);
	}

	/* Convierte un vector en un mont�culo. */
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


/** Funci�n para construir una cola con prioridad cuyo Comparator es una lambda. */
template<typename T, typename Comparator> // el tipo Comparator se deduce a partir de c
inline PriorityQueue<T, Comparator> make_priorityqueue(Comparator c, size_t tam = TAM_INICIAL)
{
	return PriorityQueue<T, Comparator>(tam, c);
}

#endif /* PRIORITYQUEUE_H_ */


typedef struct {
	int id;
	int interval;
	int prio;
} tUsuarios;

class comp {
public:
	bool operator()(tUsuarios const& a, tUsuarios const& b) {
		if (a.prio != b.prio) return a.prio < b.prio;
		else return a.id < b.id;
	}
};

bool resuelveCaso() {
	int numValores;
	std::cin >> numValores;
	if (numValores != 0) {
		tUsuarios u;
		PriorityQueue<tUsuarios, comp> q;
		for (int i = 0; i < numValores; ++i) {
			std::cin >> u.id >> u.prio;
			u.interval = u.prio;
			q.push(u);
		}
		std::cin >> numValores;
		for (int i = 0; i < numValores; ++i) {
			u = q.top();
			q.pop();
			std::cout << u.id << "\n";
			u.prio += u.interval;
			q.push(u);
		}
		std::cout << "----\n";
		return true;
	}
	else return false;
}

/* El coste de este algoritmo es de
O((k + r)(log r)) 
	k es el numero de envios
	r es el numero de registros
*/
#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {};

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}