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

//
//  bintree_eda.h
//
//  Implementación de árboles binarios (con compartición de nodos)
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 20/01/17.
//  Copyright (c) 2017 Alberto Verdejo. All rights reserved.
//

#ifndef bintree_eda_h
#define bintree_eda_h

#include <iostream>
#include <memory>   // shared_ptr, make_shared
#include <stdexcept>
#include <stack>
#include <vector>
#include <queue>

template <typename T>
class bintree {
public:
	// árbol vacío
	bintree() : root_(nullptr) {}

	// árbol hoja
	bintree(T const& e) :
		root_(std::make_shared<TreeNode>(nullptr, e, nullptr)) {}

	// árbol con dos hijos
	bintree(bintree<T> const& l, T const& e, bintree<T> const& r) :
		root_(std::make_shared<TreeNode>(l.root_, e, r.root_)) {}

	// constructora por copia, operador de asignación y destructora por defecto

	// consultar si el árbol está vacío
	bool empty() const { return root_ == nullptr; }

	// consultar la raíz
	T const& root() const {
		if (empty()) throw std::domain_error("El árbol vacío no tiene raíz.");
		else return root_->elem_;
	}

	// consultar el hijo izquierdo
	bintree<T> left() const {
		if (empty()) return bintree();
		else return bintree<T>(root_->left_);
	}

	// consultar el hijo derecho
	bintree<T> right() const {
		if (empty()) return bintree();
		else return bintree(root_->right_);
	}

	T leftE() const {
		if (empty()) throw std::domain_error("El árbol vacío no tiene hijo izquierdo.");
		else return root_->left_->elem;
	}

	T rightE() const {
		if (empty()) throw std::domain_error("El árbol vacío no tiene hijo derecho.");
		else return root_->right_->elem;
	}

	T elem() const {
		return root_->elem_;
	}

protected:
	/*
	Nodo que almacena internamente el elemento (de tipo T),
	y punteros al hijo izquierdo y derecho, que pueden ser
	nullptr si el hijo es vacío (no existe).
	*/
	struct TreeNode;
	using Link = std::shared_ptr<TreeNode>;
	struct TreeNode {
		TreeNode(Link const& l, T const& e, Link const& r) : left_(l), elem_(e), right_(r) {};
		T elem_;
		Link left_, right_;
	};

	// constructora privada
	bintree(Link const& r) : root_(r) {}

	// puntero a la raíz del árbol
	Link root_;


public:

	// recorridos

	std::vector<T> preorder() {
		std::vector<T> pre;
		preorder(root_, pre);
		return pre;
	}

	std::vector<T> inorder() {
		std::vector<T> in;
		inorder(root_, in);
		return in;
	}

	std::vector<T> postorder() {
		std::vector<T> post;
		postorder(root_, post);
		return post;
	}

	std::vector<T> levelorder() {
		std::vector<T> levels;
		if (!empty()) {
			std::queue<Link> pendientes;
			pendientes.push(root_);
			while (!pendientes.empty()) {
				Link sig = pendientes.front();
				pendientes.pop();
				levels.push_back(sig->elem_);
				if (sig->left_ != nullptr)
					pendientes.push(sig->left_);
				if (sig->right_ != nullptr)
					pendientes.push(sig->right_);
			}
		}
		return levels;
	}

protected:
	void preorder(Link a, std::vector<T> & pre) {
		if (a != nullptr) {
			pre.push_back(a->elem_);
			preorder(a->left_, pre);
			preorder(a->right_, pre);
		}
	}

	void inorder(Link a, std::vector<T> & in) {
		if (a != nullptr) {
			inorder(a->left_, in);
			in.push_back(a->elem_);
			inorder(a->right_, in);
		}
	}

	void postorder(Link a, std::vector<T> & post) {
		if (a != nullptr) {
			postorder(a->left_, post);
			postorder(a->right_, post);
			post.push_back(a->elem_);
		}
	}

public:
	// iterador que recorre el árbol en inorden
	class const_iterator {
	public:
		T const& operator*() const { return ptr_->elem_; }

		bool operator==(const_iterator const& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!=(const_iterator const& other) const {
			return !(this->operator==(other));
		}

		const_iterator & operator++() {
			next();
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		friend class bintree;
		Link ptr_;
		std::stack<Link> ancestors;

		const_iterator() : ptr_(nullptr) {}
		const_iterator(Link act) { ptr_ = first(act); }

		Link first(Link act) {
			if (act == nullptr) {
				return nullptr;
			}
			else {
				while (act->left_ != nullptr) {
					ancestors.push(act);
					act = act->left_;
				}
				return act;
			}
		}

		void next() {
			if (ptr_ == nullptr) {
				throw std::range_error("El iterador no puede avanzar");
			}
			else if (ptr_->right_ != nullptr) {
				ptr_ = first(ptr_->right_);
			}
			else if (ancestors.empty()) {
				ptr_ = nullptr;
			}
			else {
				ptr_ = ancestors.top();
				ancestors.pop();
			}
		}

	};

	const_iterator begin() const {
		return const_iterator(root_);
	}
	const_iterator end() const {
		return const_iterator(nullptr);
	}

};


#endif // bintree_eda_h

template <typename T>
bintree<T> leerArbol(T vacio) {
	T raiz;
	//scanf("%d", &raiz);
	std::cin >> raiz;
	if (raiz == vacio) { // es un árbol vacío
		return{};
	}
	else { // leer recursivamente los hijos
		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);
		return{ iz, raiz, dr };
	}
}

int altura(bintree<char> const& arbol) {
	if (arbol.empty()) {
		return 0;
	}
	else {
		return std::max(altura(arbol.left()), altura(arbol.right())) + 1;
	}
}

// dado un árbol binario averigua si está equilibrado y calcula su altura
bool equilibrado(bintree<char> const& arbol, int & alt) {
	if (arbol.empty()) {
		alt = 0;
		return true;
	}
	else {
		int alt_iz, alt_dr;
		bool eq_iz = equilibrado(arbol.left(), alt_iz);
		bool eq_dr = equilibrado(arbol.right(), alt_dr);
		alt = std::max(alt_iz, alt_dr) + 1;
		return eq_iz && eq_dr && abs(alt_iz - alt_dr) <= 1;
	}
}

bool equilibrado(bintree<char> const& arbol) {
	if (arbol.empty()) {
		return true;
	}
	else {
		bool eq_iz = equilibrado(arbol.left());
		bool eq_dr = equilibrado(arbol.right());
		return eq_iz && eq_dr &&
			abs(altura(arbol.left()) - altura(arbol.right())) <= 1;
	}
}

//#define RKJ

void resolver(const bintree<int> &s1, const bintree<int> &s2, std::vector<int> &v) {
	if (!(s1.empty() && s2.empty())) {
		int ss1, ss2;
		if (s1.empty()) ss1 = 0;
		else ss1 = s1.elem();
		if (s2.empty()) ss2 = 0;
		else ss2 = s2.elem();
		v.push_back(ss1 + ss2);
		if (!s1.left().empty() || !s2.left().empty())
			resolver(s1.left(), s2.left(), v);
		else v.push_back(-1);
		if (!s1.right().empty() || !s2.right().empty())
			resolver(s1.right(), s2.right(), v);
		else v.push_back(-1);
	}
}

bool resuelveCaso() {
	bintree<int> s1 = leerArbol(-1), s2 = leerArbol(-1);
	if (!(s1.empty() && s2.empty())) {
		std::vector<int> v;
		resolver(s1, s2, v);
		//std::cout << v[0];
		printf("%d", v[0]);
		for (int i = 1; i < v.size(); ++i)
			printf(" %d", v[i]);
			//std::cout << " " << v[i];
		printf("\n");
		//std::cout << "\n";
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
