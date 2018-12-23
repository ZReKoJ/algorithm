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

//
//  treemap_eda.h
//
//  Implementación de diccionarios <clave, valor> como árboles binarios de búsqueda
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 1/03/17.
//  Copyright (c) 2017 Alberto Verdejo. All rights reserved.
//

#ifndef treemap_eda_h
#define treemap_eda_h

#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>


template <class Clave, class Valor, class Comparador = std::less<Clave>>
class map {
public:
	// parejas (clave, valor)
	struct clave_valor {
		const Clave clave;
		Valor valor;
		clave_valor(Clave const& c, Valor const& v = Valor()) : clave(c), valor(v) {};
	};
	// using clave_valor = std::pair<const Clave, Valor>;
protected:
	using map_t = map<Clave, Valor, Comparador>;

	/*
	Clase nodo que almacena internamente la pareja (clave, valor)
	y punteros al hijo izquierdo y al hijo derecho.
	*/
	struct TreeNode;
	using Link = TreeNode *;
	struct TreeNode {
		clave_valor cv;
		Link iz;
		Link dr;
		TreeNode(clave_valor const& e, Link i = nullptr, Link d = nullptr) : cv(e), iz(i), dr(d) {}
	};

	// puntero a la raíz de la estructura jerárquica de nodos
	Link raiz;

	// número de parejas <clave, valor>
	size_t nelems;

	// objeto función que compara elementos
	Comparador menor;

public:

	map(Comparador c = Comparador()) : raiz(nullptr), nelems(0), menor(c) {}

	map(map_t const& other) {
		raiz = copia(other.raiz);
		nelems = other.nelems;
		menor = other.menor;
	}

	map_t & operator=(map_t const& that) {
		if (this != &that) {
			libera(raiz);
			raiz = copia(that.raiz);
			nelems = that.nelems;
			menor = that.menor;
		}
		return *this;
	}

	~map() {
		libera(raiz);
		raiz = nullptr;
	};

	void insert(clave_valor const& cv) {
		inserta(cv, raiz);
	}

	bool empty() const {
		return raiz == nullptr;
	}

	size_t size() const {
		return nelems;
	}

	bool contains(Clave const& c) const {
		return busca(c, raiz) != nullptr;
	}

	Valor const& at(Clave const& c) const {
		Link p = busca(c, raiz);
		if (p == nullptr)
			throw std::out_of_range("La clave no se puede consultar");
		return p->cv.valor;
	}

	// devuelve el valor asociado a la clave, si existe.
	// Si no existe, crea un nuevo nodo (con valor por defecto) y
	// lo devuelve.
	Valor & operator[](Clave const& c) {
		return corchete(c, raiz);
	}

	void erase(Clave const& c) {
		borra(c, raiz);
	}

	// solo para depurar (gira la cabeza)
	void print(std::ostream& o = std::cout) const {
		if (raiz != nullptr) {
			print(o, 0, raiz);
		}
		else
			o << "vacio\n";
	}

protected:

	static Link copia(Link a) {
		if (a == nullptr) return nullptr;
		else return new TreeNode(a->cv, copia(a->iz), copia(a->dr));
	}

	static void libera(Link a) {
		if (a != nullptr) {
			libera(a->iz);
			libera(a->dr);
			delete a;
		}
	}

	Link busca(Clave const& c, Link a) const {
		if (a == nullptr) {
			return nullptr;
		}
		else if (menor(c, a->cv.clave)) {
			return busca(c, a->iz);
		}
		else if (menor(a->cv.clave, c)) {
			return busca(c, a->dr);
		}
		else { // c == a->cv.clave
			return a;
		}
	}

	void inserta(clave_valor const& cv, Link & a) {
		if (a == nullptr) {
			a = new TreeNode(cv);
			++nelems;
		}
		else if (menor(cv.clave, a->cv.clave)) {
			inserta(cv, a->iz);
		}
		else if (menor(a->cv.clave, cv.clave)) {
			inserta(cv, a->dr);
		}
		else { // la clave ya está, se actualiza el valor asociado
			a->cv.valor = cv.valor;
		}
	}

	Valor & corchete(Clave const& c, Link & a) {
		if (a == nullptr) {
			a = new TreeNode(clave_valor(c));
			++nelems;
			return a->cv.valor;
		}
		else if (menor(c, a->cv.clave)) {
			return corchete(c, a->iz);
		}
		else if (menor(a->cv.clave, c)) {
			return corchete(c, a->dr);
		}
		else { // la clave ya está, se devuelve el valor asociado
			return a->cv.valor;
		}
	}

	void borra(Clave const& c, Link & a) {
		if (a != nullptr) {
			if (menor(c, a->cv.clave)) {
				borra(c, a->iz);
			}
			else if (menor(a->cv.clave, c)) {
				borra(c, a->dr);
			}
			else // c == a->cv.clave
				if (a->iz == nullptr || a->dr == nullptr) {
					Link aux = a;
					a = a->iz == nullptr ? a->dr : a->iz;
					--nelems;
					delete aux;
				}
				else { // tiene dos hijos
					subirMenor(a, a->dr, nullptr);
					--nelems;
				}
		}
	}

	static void subirMenor(Link & a, Link b, Link padre) {
		if (b->iz != nullptr) {
			subirMenor(a, b->iz, b);
		}
		else {
			if (padre != nullptr) {
				padre->iz = b->dr;
				b->dr = a->dr;
			}
			b->iz = a->iz;
			delete a;
			a = b;
		}
	}

	// imprime el árbol (solo para depurar)
	static void print(std::ostream & o, int indent, Link r) {
		if (r != nullptr) {
			print(o, indent + 2, r->dr);
			o << std::string(indent, ' ');
			o << '(' << r->cv.clave << ',' << r->cv.valor << ")\n";
			print(o, indent + 2, r->iz);
		}
	}

protected:
	// iteradores que recorren los pares <clave, valor> de menor a mayor clave
	template <class Apuntado>
	class Iterador {
	public:
		Apuntado & operator*() const {
			if (act == nullptr) throw std::out_of_range("No hay elemento a consultar");
			return act->cv;
		}

		Apuntado * operator->() const {
			return &operator*();
		}

		Iterador & operator++() {  // ++ prefijo
			next();
			return *this;
		}

		bool operator==(Iterador const& that) const {
			return act == that.act;
		}

		bool operator!=(Iterador const& that) const {
			return !(this->operator==(that));
		}

	protected:
		friend class map;
		Link act;
		std::stack<Link> ancestros;  // antecesores no visitados

									 // construye el iterador al primero
		Iterador(Link r) { act = first(r); }

		// construye el iterador al último
		Iterador() : act(nullptr) {}

		// construye el iterador a una clave concreta (para find)
		Iterador(map_t const* m, Clave const& c) {
			act = m->raiz;
			bool encontrado = false;
			while (act != nullptr && !encontrado) {
				if (m->menor(c, act->cv.clave)) {
					ancestros.push(act);
					act = act->iz;
				}
				else if (m->menor(act->cv.clave, c)) {
					act = act->dr;
				}
				else
					encontrado = true;
			}
			if (!encontrado) { // vaciamos la pila
				ancestros = std::stack<Link>();
			}
		}

		Link first(Link ptr) {
			if (ptr == nullptr) {
				return nullptr;
			}
			else { // buscamos el nodo más a la izquierda
				while (ptr->iz != nullptr) {
					ancestros.push(ptr);
					ptr = ptr->iz;
				}
				return ptr;
			}
		}

		void next() {
			if (act == nullptr) {
				throw std::out_of_range("El iterador no puede avanzar");
			}
			else if (act->dr != nullptr) { // primero del hijo derecho
				act = first(act->dr);
			}
			else if (ancestros.empty()) { // hemos llegado al final
				act = nullptr;
			}
			else { // podemos retroceder
				act = ancestros.top();
				ancestros.pop();
			}
		}
	};

public:
	// iterador que no permite modificar el elemento apuntado
	using const_iterator = Iterador<clave_valor const>;

	const_iterator cbegin() const {
		return const_iterator(raiz);
	}
	const_iterator begin() const {
		return cbegin();
	}

	const_iterator cend() const {
		return const_iterator();
	}
	const_iterator end() const {
		return cend();
	}

	const_iterator find(Clave const& c) const {
		return const_iterator(this, c);
	}

	// iterador que sí permite modificar el elemento apuntado (su valor)
	using iterator = Iterador<clave_valor>;

	iterator begin() {
		return iterator(raiz);
	}

	iterator end() {
		return iterator();
	}

	iterator find(Clave const& c) {
		return iterator(this, c);
	}

};


template <class Clave, class Valor, class Comparador>
inline std::ostream& operator<<(std::ostream & o, map<Clave, Valor, Comparador> const& a) {
	a.print(o);
	return o;
}

#endif // treemap_eda_h

std::vector<std::string> split(const std::string &str, char separator)
{
	std::vector<std::string> result;
	size_t pos1 = 0;
	size_t pos2 = 0;
	if (str != "") {
		while (pos2 != str.npos)
		{
			pos2 = str.find(separator, pos1);
			if (pos2 != str.npos)
			{
				if (pos2 > pos1)
					result.push_back(str.substr(pos1, pos2 - pos1));
				pos1 = pos2 + 1;
			}
		}
		result.push_back(str.substr(pos1, str.size() - pos1));
	}
	return result;
}

void resuelveCaso() {
	std::string texto;
	std::vector<std::string> v;
	map<std::string, std::string> m1, m2;
	getline(std::cin, texto);
	v = split(texto, ' ');
	for (int i = 0; i < v.size(); i += 2)
		m1[v[i]] = v[i + 1];
	getline(std::cin, texto);
	v = split(texto, ' ');
	for (int i = 0; i < v.size(); i += 2)
		m2[v[i]] = v[i + 1];

	std::vector<std::string> x, y ,z;
	for (auto const& cv : m2) {
		if (!m1.contains(cv.clave)) {
			x.emplace_back(cv.clave);
		}
		else {
			if (cv.valor != m1.at(cv.clave))
				z.emplace_back(cv.clave);
		}
	}
	for (auto const& cv : m1) {
		if (!m2.contains(cv.clave)) {
			y.emplace_back(cv.clave);
		}
	}
	if (x.size() == 0 && y.size() == 0 && z.size() == 0)
		std::cout << "Sin cambios\n";
	else {
		if (x.size() != 0) {
			std::cout << "+";
			for (std::string s : x) std::cout << " " << s;
			std::cout << "\n";
		}
		if (y.size() != 0) {
			std::cout << "-";
			for (std::string s : y) std::cout << " " << s;
			std::cout << "\n";
		}
		if (z.size() != 0) {
			std::cout << "*";
			for (std::string s : z) std::cout << " " << s;
			std::cout << "\n";
		}
	}
	std::cout << "----\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos;
	std::string r;
	std::cin >> numCasos;
	getline(std::cin, r);
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