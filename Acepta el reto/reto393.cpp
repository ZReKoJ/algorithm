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

typedef struct {
	std::string linea;
	int num;
} tSopaDeLetras;

bool operator < (const tSopaDeLetras &p1, const tSopaDeLetras &p2) {
	return p1.linea < p2.linea;
}

class comp {
public:
	bool operator()(tSopaDeLetras a, tSopaDeLetras b) {
		return a < b;
	}
};

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

	void root(T elem) {
		if (empty()) throw std::domain_error("El árbol vacío no tiene raíz.");
		else root_->elem_ = elem;
	}

	// consultar el hijo izquierdo
	bintree<T> left() const {
		if (empty()) throw std::domain_error("El árbol vacío no tiene hijo izquierdo.");
		else return bintree<T>(root_->left_);
	}

	void left(T elem) const {
		if (left().empty()) root_->left_ = std::make_shared<TreeNode>(nullptr, elem, nullptr);
		else {
			bintree<T> t = bintree(root_->left_);
			t.root(elem);
		}
	}

	// consultar el hijo derecho
	bintree<T> right() const {
		if (empty()) throw std::domain_error("El árbol vacío no tiene hijo derecho.");
		else return bintree(root_->right_);
	}

	void right(T elem) const {
		if (right().empty()) root_->right_ = std::make_shared<TreeNode>(nullptr, elem, nullptr);
		else {
			bintree<T> t = bintree(root_->right_);
			t.root(elem);
		}
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

template <class T>
bintree<T> leerArbol(T valor, int stage, const int &stageMax) {
	if (stage < stageMax) {
		auto iz = leerArbol(valor, stage + 1, stageMax);
		auto dr = leerArbol(valor, stage + 1, stageMax);
		return{ iz, valor, dr };
	}
	else return{};
}

template <class T>
void up(const bintree<T> &t, const std::vector<std::string> &b, int i, int j, std::vector<tSopaDeLetras> &v) {
	if (!t.empty() && i >= 0) {
		if (t.root() != 0)
			++v[t.root() - 1].num;
		--i;
		if (i >= 0) {
			if (b[i].at(j) == '1')
				up(t.right(), b, i, j, v);
			else up(t.left(), b, i, j, v);
		}
	}
}

template <class T>
void down(const bintree<T> &t, const std::vector<std::string> &b, int i, int j, std::vector<tSopaDeLetras> &v) {
	if (!t.empty() && i < b.size()) {
		if (t.root() != 0)
			++v[t.root() - 1].num;
		++i;
		if (i < b.size()) {
			if (b[i].at(j) == '1')
				down(t.right(), b, i, j, v);
			else down(t.left(), b, i, j, v);
		}
	}
}

template <class T>
void left(const bintree<T> &t, const std::vector<std::string> &b, int i, int j, std::vector<tSopaDeLetras> &v) {
	if (!t.empty() && j >= 0) {
		if (t.root() != 0)
			++v[t.root() - 1].num;
		--j;
		if (j >= 0) {
			if (b[i].at(j) == '1')
				left(t.right(), b, i, j, v);
			else  left(t.left(), b, i, j, v);
		}
	}
}

template <class T>
void right(const bintree<T> &t, const std::vector<std::string> &b, int i, int j, std::vector<tSopaDeLetras> &v) {
	if (!t.empty() && j < b[i].size()) {
		if (t.root() != 0)
			++v[t.root() - 1].num;
		++j;
		if (j < b[i].size()) {
			if (b[i].at(j) == '1')
				right(t.right(), b, i, j, v);
			else  right(t.left(), b, i, j, v);
		}
	}
}

template <class T>
void upLeft(const bintree<T> &t, const std::vector<std::string> &b, int i, int j, std::vector<tSopaDeLetras> &v) {
	if (!t.empty() && i >= 0 && j >= 0) {
		if (t.root() != 0)
			++v[t.root() - 1].num;
		--i; --j;
		if (i >= 0 && j >= 0) {
			if (b[i].at(j) == '1')
				upLeft(t.right(), b, i, j, v);
			else  upLeft(t.left(), b, i, j, v);
		}
	}
}

template <class T>
void upRight(const bintree<T> &t, const std::vector<std::string> &b, int i, int j, std::vector<tSopaDeLetras> &v) {
	if (!t.empty() && i >= 0 && j < b[i].size()) {
		if (t.root() != 0)
			++v[t.root() - 1].num;
		--i; ++j;
		if (i >= 0 && j < b[i].size()) {
			if (b[i].at(j) == '1')
				upRight(t.right(), b, i, j, v);
			else  upRight(t.left(), b, i, j, v);
		}
	}
}

template <class T>
void downLeft(const bintree<T> &t, const std::vector<std::string> &b, int i, int j, std::vector<tSopaDeLetras> &v) {
	if (!t.empty() && i < b.size() && j >= 0) {
		if (t.root() != 0)
			++v[t.root() - 1].num;
		++i; --j;
		if (i < b.size() && j >= 0) {
			if (b[i].at(j) == '1')
				downLeft(t.right(), b, i, j, v);
			else  downLeft(t.left(), b, i, j, v);
		}
	}
}
template <class T>
void downRight(const bintree<T> &t, const std::vector<std::string> &b, int i, int j, std::vector<tSopaDeLetras> &v) {
	if (!t.empty() && i < b.size() && j < b[i].size()) {
		if (t.root() != 0)
			++v[t.root() - 1].num;
		++i; ++j;
		if (i < b.size() && j < b[i].size()) {
			if (b[i].at(j) == '1')
				downRight(t.right(), b, i, j, v);
			else  downRight(t.left(), b, i, j, v);
		}
	}
}

void crearArbol(const bintree<int> &t, int &i, int j, const std::vector<tSopaDeLetras> &tx) {
	if (i < tx.size()) {
		if (j < tx[i].linea.length() - 1) {
			if (tx[i].linea.at(j) == '0') {
				if (t.left().empty()) {
					t.left(0);
				}
				crearArbol(t.left(), i, j + 1, tx);
			}
			else if (tx[i].linea.at(j) == '1') {
				if (t.right().empty()) {
					t.right(0);
				}
				crearArbol(t.right(), i, j + 1, tx);
			}
		}
		else if (j == tx[i].linea.length() - 1) {
			if (tx[i].linea.at(j) == '0') {
				t.left(i + 1);
				crearArbol(t, i, j + 1, tx);
			}
			else if (tx[i].linea.at(j) == '1') {
				t.right(i + 1);
				crearArbol(t, i, j + 1, tx);
			}

		}
		else {
			if (i + 1 < tx.size()) {
				if (tx[i + 1].linea.substr(0, tx[i].linea.length() - 1) == tx[i].linea.substr(0, tx[i].linea.length() - 1)) {
					++i;
					crearArbol(t, i, j - 1, tx);
				}
			}
		}
	}
}

void creAr(bintree<int> &t, const std::vector<tSopaDeLetras> &tx) {
	int i = 0;
	while (i < tx.size()) {
		crearArbol(t, i, 0, tx);
		++i;
	}
}

#endif // bintree_eda_h

void resolver(const bintree<int> &t, const std::vector<std::string> &b, std::vector<tSopaDeLetras> &v) {
	for (int i = 0; i < b.size(); ++i) {
		for (int j = 0; j < b[i].size(); ++j) {
			if (b[i].at(j) == '1') {
				up(t.right(), b, i, j, v);
				down(t.right(), b, i, j, v);
				left(t.right(), b, i, j, v);
				right(t.right(), b, i, j, v);
				upLeft(t.right(), b, i, j, v);
				upRight(t.right(), b, i, j, v);
				downLeft(t.right(), b, i, j, v);
				downRight(t.right(), b, i, j, v);
			}
			else {
				up(t.left(), b, i, j, v);
				down(t.left(), b, i, j, v);
				left(t.left(), b, i, j, v);
				right(t.left(), b, i, j, v);
				upLeft(t.left(), b, i, j, v);
				upRight(t.left(), b, i, j, v);
				downLeft(t.left(), b, i, j, v);
				downRight(t.left(), b, i, j, v);
			}
		}
	}
}

#define DOMJUDGE

bool resuelveCaso() {
	int fil, col, numCasos;
	std::cin >> col;
	if (!std::cin.fail()) {
		std::cin >> fil;
		std::vector<std::string> b(fil);
		for (int i = 0; i < fil; ++i)
			std::cin >> b[i];
		std::cin >> numCasos;
		std::vector<tSopaDeLetras> tx(numCasos);
		std::string palabra;
		int max = 0;
		for (int i = 0; i < numCasos; ++i) {
			std::cin >> palabra;
			if (palabra.length() > max)
				max = palabra.length();
			tx[i].linea = palabra;
		}
		sort(tx.begin(), tx.end(), comp());
		/*for (int i = 0; i < tx.size(); ++i)
		std::cout << tx[i].linea << "\n";
		std::cout << "---\n";*/
		bintree<int> t(-1);
		creAr(t, tx);
		for (int i = 0; i < numCasos; ++i)
			tx[i].num = 0;
		resolver(t, b, tx);
		for (int i = 0; i < numCasos; ++i)
			if (tx[i].linea.length() == 1)
				tx[i].num /= 8;
		for (int i = 0; i < numCasos; ++i)
			if (tx[i].num != 0)
				//std::cout << tx[i].linea << " " << tx[i].num << "\n";
				printf("%s %d\n", tx[i].linea.c_str(), tx[i].num);
		//std::cout << "---\n";
		printf("---\n");
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