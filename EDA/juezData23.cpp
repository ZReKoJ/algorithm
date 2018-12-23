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
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <list>

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

struct l {
	std::string nombre;
	int numEjemplares;
	int numVentas;
	std::list<std::string>::iterator it;
};

class Libro {
protected:
	std::map<std::string, l*> libros;
	std::map<int, std::list<std::string>> ventas;
public:
	void nuevoLibro(std::string const& libro, int const& n) {
		if (!estaLibro(libro)) libros[libro] = new l{ libro, n, 0 };
		else libros[libro]->numEjemplares += n;
	}

	void comprar(std::string const& libro) {
		if (!estaLibro(libro)) throw std::invalid_argument("Libro no existente");
		else {
			l *lib = libros[libro];
			if (lib->numEjemplares > 0) {
				--lib->numEjemplares;
				if (lib->numVentas != 0)
					ventas[lib->numVentas].erase(lib->it);
				++lib->numVentas;
				ventas[lib->numVentas].push_front(lib->nombre);
				lib->it = ventas[lib->numVentas].begin();
			}
			else throw std::out_of_range("No hay ejemplares");
		}
	}

	bool estaLibro(std::string const& libro) {
		return libros.count(libro) != 0;
	}

	void elimLibro(std::string const& libro) {
		if (estaLibro(libro)) {
			l *lib = libros[libro];
			ventas[lib->numVentas].erase(lib->it);
			delete lib;
			libros.erase(libro);
		}
	}

	int numEjemplares(std::string const& libro) {
		if (!estaLibro(libro)) throw std::invalid_argument("Libro no existente");
		else return libros[libro]->numEjemplares;
	}

	std::vector<std::string> top10() {
		std::vector<std::string> v;
		int i = 0;
		std::map<int, std::list<std::string>>::reverse_iterator it = ventas.rbegin();
		std::list<std::string>::iterator it2;
		while (i < 10 && it != ventas.rend()) {
			it2 = it->second.begin();
			while (i < 10 && it2 != it->second.end()) {
				v.emplace_back(*it2);
				++it2;
				++i;
			}
			++it;
		}
		return v;
	}

	~Libro() {
		for (std::map<std::string, l*>::iterator it = libros.begin(); it != libros.end(); ++it)
			delete it->second;
	}
};

bool resuelveCaso() {
	int numCasos;
	std::cin >> numCasos;
	if (!std::cin.fail()) {
		Libro lib;
		std::string caso, libro;
		int num;
		for (int i = 0; i < numCasos; ++i) {
			try {
				std::cin >> caso;
				if (caso == "nuevoLibro") {
					std::cin >> num;
					std::cin.get();
					getline(std::cin, libro);
					lib.nuevoLibro(libro, num);
				}
				else if (caso == "comprar") {
					std::cin.get();
					getline(std::cin, libro);
					lib.comprar(libro);
				}
				else if (caso == "estaLibro") {
					std::cin.get();
					getline(std::cin, libro);
					if (lib.estaLibro(libro)) std::cout << "El libro " << libro << " esta en el sistema\n";
					else std::cout << "No existe el libro " << libro << " en el sistema\n";
					std::cout << "---\n";
				}
				else if (caso == "elimLibro") {
					std::cin.get();
					getline(std::cin, libro);
					lib.elimLibro(libro);
				}
				else if (caso == "numEjemplares") {
					std::cin.get();
					getline(std::cin, libro);
					try {
						num = lib.numEjemplares(libro);
						std::cout << "Existen " << num << " ejemplares del libro " << libro << "\n";
					}
					catch (std::invalid_argument &err) {
						std::cout << "No existe el libro " << libro << " en el sistema\n";
					}
					std::cout << "---\n";
				}
				else if (caso == "top10") {
					std::vector<std::string> v = lib.top10();
					for (int i = 0; i < 10 && i < v.size(); ++i)
						std::cout << v[i] << "\n";
					std::cout << "---\n";
				}
				else {}
			}
			catch (std::out_of_range &err) {
				std::cout << err.what() << "\n---\n";
			}
			catch (std::invalid_argument &err) {
				std::cout << err.what() << "\n---\n";
			}
		}
		std::cout << "------\n";
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