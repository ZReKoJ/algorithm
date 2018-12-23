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

template <class T>
class set {
public:
	set(size_t tam = TAM_INICIAL); // constructor
	set(set<T> const& other); // constructor por copia
	set<T> & operator=(set<T> const& other); // operador de asignación
	~set(); // destructor
	void insert(T e);
	bool contains(T e) const;
	void erase(T e);
	bool empty() const;
	size_t size() const;
	void eliminarMenor();
	T consultarMenor();
	void mostrar();
private:
	const static size_t TAM_INICIAL = 8;
	size_t contador;
	size_t capacidad;
	T * datos;
	void amplia();
	void libera();
	void copia(set<T> const& other);
};

template <class T>
set<T>::set(size_t tam) : contador(0), capacidad(tam), datos(new T[capacidad]) {}

template <class T>
set<T>::~set() { libera(); }

template <class T>
void set<T>::libera() { delete[] datos; datos = nullptr; }

/** Constructor por copia */
template <class T>
set<T>::set(set<T> const& other) {
	copia(other);
}

/** Operador de asignación */
template <class T>
set<T> & set<T>::operator=(set<T> const& other) {
	if (this != &other) {
		libera();
		copia(other);
	}
	return *this;
}

template <class T>
void set<T>::copia(set<T> const& other) {
	capacidad = other.capacidad;
	contador = other.contador;
	datos = new T[capacidad];
	for (size_t i = 0; i < contador; ++i)
		datos[i] = other.datos[i];
}

template <class T>
void set<T>::insert(T e) {
	if (!contains(e)) {
		if (contador == capacidad)
			amplia();
		int ini = 0, fin = contador - 1, mitad;
		while (ini <= fin) {
			mitad = (ini + fin) / 2;
			// Lo de == no hace falta porque lo restringe contains
			if (e > datos[mitad])
				fin = mitad - 1;
			else ini = mitad + 1;
		}
		++contador;
		for (int i = contador - 1; i > ini; --i)
			datos[i] = datos[i - 1];
		datos[ini] = e;
	}
}

template <class T>
bool set<T>::contains(T e) const {
	size_t i = 0;
	while (i < contador && datos[i] != e)
		++i;
	return i < contador;
}

template <class T>
void set<T>::amplia() {
	T * nuevos = new T[2 * capacidad];
	for (size_t i = 0; i < capacidad; ++i)
		nuevos[i] = std::move(datos[i]);
	delete[] datos;
	datos = nuevos;
	capacidad *= 2;
}

template <class T>
void set<T>::erase(T e) {
	size_t i = 0;
	while (i < contador && datos[i] != e)
		++i;
	if (i < contador) {
		datos[i] = datos[contador - 1];
		--contador;
	}
	else
		throw std::domain_error("El elemento no esta");
}


template <class T>
bool set<T>::empty() const {
	return contador == 0;
}

template <class T>
size_t set<T>::size() const {
	return contador;
}

template <class T>
T set<T>::consultarMenor() {
	return datos[contador - 1];
}

template <class T>
void set<T>::eliminarMenor() {
	--contador;
}

template <class T>
void set<T>::mostrar() {
	for (int i = contador - 1; i >= 0; --i)
		std::cout << datos[i] << " ";
	std::cout << '\n';
}

bool resuelveCaso() {
	char tipo;
	std::cin >> tipo;
	if (!std::cin.fail()) {
		int valor;
		std::cin >> valor;
		if (tipo == 'P') {
			set<std::string> cjto;
			std::string elemento;
			std::cin >> elemento;
			while (elemento != "FIN") {
				cjto.insert(elemento);
				if (cjto.size() > valor)
					cjto.eliminarMenor();
				std::cin >> elemento;
			}
			cjto.mostrar();
		}
		else {
			set<int> cjto;
			int elemento;
			std::cin >> elemento;
			while (elemento != -1) {
				cjto.insert(elemento);
				if (cjto.size() > valor)
					cjto.eliminarMenor();
				std::cin >> elemento;
			}
			cjto.mostrar();
		}
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

	while (resuelveCaso()){}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}