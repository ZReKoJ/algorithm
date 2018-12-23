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
#include <cstring>

class pila {
private:
	std::vector<int> v;
public:
	pila() {}
	void anadir(int valor) {
		v.emplace_back(valor);
	}
	int op(char operacion) {
		int op2 = v[v.size() - 1];
		v.pop_back();
		int op1 = v[v.size() - 1];
		v.pop_back();
		int resultado;
		switch (operacion) {
		case '+': resultado = op1 + op2; break;
		case '-': resultado = op1 - op2; break;
		case '*': resultado = op1 * op2; break;
		case '/':
			if (op2 != 0)
				resultado = op1 / op2;
			else
				throw std::domain_error("ERROR");
			break;
		}
		return resultado;
	}
	int get() {
		return v[0];
	}
};

class cola {
private:
	std::vector<int> v;
public:
	cola() {}
	void anadir(int valor) {
		v.emplace_back(valor);
	}
	int op(char operacion) {
		int op2 = v[0];
		v.erase(v.begin() + 0);
		int op1 = v[0];
		v.erase(v.begin() + 0);
		int resultado;
		switch (operacion) {
		case '+': resultado = op1 + op2; break;
		case '-': resultado = op1 - op2; break;
		case '*': resultado = op1 * op2; break;
		case '/':
			if (op2 != 0)
				resultado = op1 / op2;
			else
				throw std::domain_error("ERROR");
			break;
		}
		return resultado;
	}
	int get() {
		return v[0];
	}
};

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
		if (empty()) throw std::domain_error("El árbol vacío no tiene hijo izquierdo.");
		else return bintree<T>(root_->left_);
	}

	// consultar el hijo derecho
	bintree<T> right() const {
		if (empty()) throw std::domain_error("El árbol vacío no tiene hijo derecho.");
		else return bintree(root_->right_);
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

bintree<char> leerArbol(int &i, const std::string &palabra) {
	if (i >= 0) {
		char raiz = palabra.at(i);
		--i;
		if (!strchr("+-*/%", raiz)) { // es un árbol vacío
			return{ raiz };
		}
		else { // leer recursivamente los hijos
			auto dr = leerArbol(i, palabra);
			auto iz = leerArbol(i, palabra);
			return{ iz, raiz, dr };
		}
	}
	else return{};
}

#endif // bintree_eda_h

//#define RKJ
//#define MTW

#ifdef MTW
void resolver(const std::string &pl, const std::string &cl) {
	bool correctoP = true, correctoC = true;
	pila p;
	for (int i = 0; i < pl.size() && correctoP; ++i) {
		if (pl.at(i) == '+' || pl.at(i) == '-' || pl.at(i) == '*' || pl.at(i) == '/') {
			try {
				p.anadir(p.op(pl.at(i)));
			}
			catch (const std::domain_error &e) {
				correctoP = false;
			}
		}
		else p.anadir(int(pl.at(i) - 48));
	}
	cola c;
	for (int i = 0; i < cl.size() && correctoC; ++i) {
		if (cl.at(i) == '+' || cl.at(i) == '-' || cl.at(i) == '*' || cl.at(i) == '/') {
			try {
				c.anadir(c.op(cl.at(i)));
			}
			catch (const std::domain_error &e) {
				correctoC = false;
			}
		}
		else c.anadir(int(cl.at(i) - 48));
	}

	if (correctoP && correctoC) {
		int pi = p.get(), co = c.get();
		if (pi == co) {
			std::cout << pi << " = " << co << '\n';
		}
		else {
			std::cout << pi << " != " << co << '\n';
		}
	}
	else if (correctoP && !correctoC)
		std::cout << p.get() << " != ERROR\n";
	else if (!correctoP && correctoC)
		std::cout << "ERROR != " << c.get() << '\n';
	else std::cout << "ERROR = ERROR\n";
}
#endif

bool resuelveCaso() {
	std::string palabra;
	getline(std::cin, palabra);
	if (!std::cin.fail()) {
		int i = palabra.size() - 1;
		bintree<char> t = leerArbol(i, palabra);
		std::vector<char> v = t.levelorder();
		for (int i = v.size() - 1; i >= 0; --i)
			printf("%c", v[i]);
		printf("\n");
#ifdef MTW
		std::string palabra2;
		/*for (int i = 0; i < v.size(); ++i)
			palabra2.push_back(v[i]);*/
		for (int i = v.size() - 1; i >= 0; --i)
			palabra2.push_back(v[i]);
		resolver(palabra, palabra2);
#endif
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