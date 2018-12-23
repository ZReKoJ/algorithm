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

//
//  hashmap_eda.h
//
//  Implementación de diccionarios <clave, valor> como tablas hash abiertas
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 9/03/17.
//  Copyright (c) 2017 Alberto Verdejo. All rights reserved.
//

#ifndef hashmap_eda_h
#define hashmap_eda_h

#include <algorithm>
#include <functional>  // std::hash, std::equal_to
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>


template <class Clave, class Valor, class Hash = std::hash<Clave>, class Pred = std::equal_to<Clave>>
class unordered_map {
public:
	// parejas (clave, valor)
	struct clave_valor {
		const Clave clave;
		Valor valor;
		clave_valor(Clave const& c, Valor const& v = Valor()) : clave(c), valor(v) {};
	};

protected:
	using umap_t = unordered_map<Clave, Valor, Hash, Pred>;

	/*
	Clase nodo que almacena internamente la pareja (clave, valor)
	y un puntero al siguiente.
	*/
	struct ListNode;
	using Link = ListNode *;
	struct ListNode {
		clave_valor cv;
		Link sig;
		ListNode(clave_valor const& e, Link s = nullptr) : cv(e), sig(s) {}
	};

	// vector de listas (el tamaño se ajustará a la carga)
	std::vector<Link> array;

	static const size_t TAM_INICIAL = 17; // tamaño inicial de la tabla
	static const size_t MAX_CARGA = 75;   // máxima ocupación permitida

										  // número de parejas <clave, valor>
	size_t nelems;

	// objeto función para hacer el hash de las claves
	Hash hash;

	// objeto función para comparar claves
	Pred pred;

public:

	unordered_map(size_t n = TAM_INICIAL, Hash h = Hash(), Pred p = Pred()) :
		array(n, nullptr), nelems(0), hash(h), pred(p) {}

	unordered_map(umap_t const& other) {
		copia(other);
	}

	umap_t & operator=(umap_t const& that) {
		if (this != &that) {
			libera();
			copia(that);
		}
		return *this;
	}

	~unordered_map() {
		libera();
	};

	void insert(clave_valor const& cv) {
		if (muy_llena())
			amplia();
		size_t i = hash(cv.clave) % array.size();
		Link ant, pos = array[i];
		if (localizar(cv.clave, ant, pos)) {
			pos->cv.valor = cv.valor;
		}
		else {
			array[i] = new ListNode(cv, array[i]);
			++nelems;
		}
	}

	bool empty() const {
		return nelems == 0;
	}

	size_t size() const {
		return nelems;
	}

	bool contains(Clave const& c) const {
		size_t i = hash(c) % array.size();
		Link ant, pos = array[i];
		return localizar(c, ant, pos);
	}

	Valor const& at(Clave const& c) const {
		size_t i = hash(c) % array.size();
		Link ant, pos = array[i];
		if (localizar(c, ant, pos))
			return pos->cv.valor;
		else
			throw std::out_of_range("La clave no se puede consultar");
	}

	// devuelve el valor asociado a la clave, si existe.
	// Si no existe, crea un nuevo nodo (con valor por defecto) y
	// lo devuelve.
	Valor & operator[](Clave const& c) {
		size_t i = hash(c) % array.size();
		Link ant, pos = array[i];
		if (localizar(c, ant, pos)) {
			return pos->cv.valor;
		}
		else {
			if (muy_llena()) {
				amplia();
				i = hash(c) % array.size();
			}
			array[i] = new ListNode(c, array[i]);
			++nelems;
			return array[i]->cv.valor;
		}
	}

	void erase(Clave const& c) {
		size_t i = hash(c) % array.size();
		Link ant, pos = array[i];
		if (localizar(c, ant, pos)) {
			if (ant == nullptr)
				array[i] = pos->sig;
			else
				ant->sig = pos->sig;
			delete pos;
			--nelems;
		}
	}

protected:

	void copia(umap_t const& other) {
		array.resize(other.array.size());
		for (size_t i = 0; i < array.size(); ++i) {
			array[i] = nullptr;
			Link act = other.array[i];
			while (act != nullptr) {
				array[i] = new ListNode(act->cv, array[i]);
				act = act->sig;
			}
		}
		nelems = other.nelems;
		hash = other.hash;
		pred = other.pred;
	}

	void libera() {
		for (size_t i = 0; i < array.size(); ++i) {
			// liberamos los nodos de la lista array[i]
			Link act = array[i];
			while (act != nullptr) {
				Link a_borrar = act;
				act = act->sig;
				delete a_borrar;
			}
			array[i] = nullptr;
		}
	}

	bool localizar(Clave const& c, Link & ant, Link & pos) const {
		ant = nullptr;
		while (pos != nullptr) {
			if (pred(c, pos->cv.clave))
				return true;
			else {
				ant = pos; pos = pos->sig;
			}
		}
		return false;
	}

	bool muy_llena() const {
		return 100.0 * nelems / array.size() > MAX_CARGA;
	}

	static size_t siguiente_primo(size_t a) {
		bool primo = false;
		while (!primo) {
			++a;
			primo = true;
			for (size_t j = 2; j < a && primo; ++j) {
				primo = a % j != 0;
			}
		}
		return a;
	}

	void amplia() {
		std::vector<Link> nuevo(siguiente_primo(array.size() * 2), nullptr);
		for (size_t i = 0; i < array.size(); ++i) {
			Link act = array[i];
			while (act != nullptr) {
				Link a_mover = act;
				act = act->sig;
				size_t i = hash(a_mover->cv.clave) % nuevo.size();
				a_mover->sig = nuevo[i];
				nuevo[i] = a_mover;
			}
		}
		swap(array, nuevo);
	}

protected:
	// iteradores que recorren los pares <clave, valor> de la tabla (no ordenados)
	template <class Apuntado, class Tabla>
	class Iterador {
	public:
		Apuntado & operator*() const {
			if (act == nullptr)
				throw std::out_of_range("No hay elemento a consultar");
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
		friend class unordered_map;
		Tabla * tabla;   // la tabla que se está recorriendo
		Link act;        // nodo actual
		size_t ind;      // índice de la lista actual

						 // iterador al primer elemento o al último
		Iterador(Tabla * t, bool first = true) : tabla(t) {
			if (first) {
				ind = 0;
				while (ind < tabla->array.size() && tabla->array[ind] == nullptr) {
					++ind;
				}
				act = (ind < tabla->array.size() ? tabla->array[ind] : nullptr);
			}
			else {
				act = nullptr;
				ind = tabla->array.size();
			}
		}

		// iterador a una clave
		Iterador(Tabla * t, Clave const& c) : tabla(t) {
			ind = tabla->hash(c) % tabla->array.size();
			Link ant;
			act = tabla->array[ind];
			if (!tabla->localizar(c, ant, act)) { // se devuelve iterador al final
				act = nullptr; ind = tabla->array.size();
			}
		}

		void next() {
			if (act == nullptr)
				throw std::out_of_range("El iterador no puede avanzar");
			act = act->sig;
			while (act == nullptr && ++ind < tabla->array.size()) {
				act = tabla->array[ind];
			}
		}
	};

public:
	// iterador que no permite modificar el elemento apuntado
	using const_iterator = Iterador<clave_valor const, umap_t const>;

	const_iterator cbegin() const {
		return const_iterator(this);
	}
	const_iterator begin() const {
		return cbegin();
	}

	const_iterator cend() const {
		return const_iterator(this, false);
	}
	const_iterator end() const {
		return cend();
	}

	const_iterator find(Clave const& c) const {
		return const_iterator(this, c);
	}

	// iterador que sí permite modificar el elemento apuntado (su valor)
	using iterator = Iterador<clave_valor, umap_t>;

	iterator begin() {
		return iterator(this);
	}

	iterator end() {
		return iterator(this, false);
	}

	iterator find(Clave const& c) {
		return iterator(this, c);
	}

};



#endif // hashmap_eda_h

typedef struct {
	std::string clave;
	int valor;
} tcv;

bool operator < (const tcv &p1, tcv &p2) {
	if (p1.valor == p2.valor)
		return p1.clave < p2.clave;
	else return p1.valor > p2.valor;
}

class comp {
public:
	bool operator()(tcv a, tcv b) {
		return a < b;
	}
};

bool resuelveCaso() {
	std::string t, deporte, indice;
	std::cin >> t;
	if (!std::cin.fail()) {
		unordered_map<std::string, int> n;
		//map<std::string, int> n;
		std::vector<tcv> d;
		tcv a;
		while (t != "_FIN_") {
			if (isupper(t[0])) {
				deporte = t;
				a.clave = deporte;
				a.valor = 0;
				d.emplace_back(a);
			}
			else {
				if (n.contains(t)) {
					if (n[t] != -1 && d[n[t]].clave != deporte) {
						--d[n[t]].valor;
						n[t] = -1;
					}
				}
				else {
					n[t] = d.size() - 1;
					++d[n[t]].valor;
				}
			}
			std::cin >> t;
		}
		sort(d.begin(), d.end(), comp());
		for (auto cv : d) std::cout << cv.clave << " " << cv.valor << "\n";
		std::cout << "***\n";
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