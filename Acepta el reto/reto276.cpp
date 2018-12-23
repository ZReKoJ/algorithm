// TAIS19, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <list>
#include <climits>
#include <limits.h>
#include <limits>
#include <queue>

class Pelicula {
public:
	Pelicula() : hora(0), min(0), dur(0) {}
	Pelicula(int h, int m, int d) : hora(h), min(m), dur(d) {}

	int getIni() {
		return ini;
	}

	int getFin() {
		return fin;
	}

	bool operator<(Pelicula const& that) const {
		return fin < that.fin;
	}

	bool operator>(Pelicula const& that) const {
		return fin > that.fin;
	}

	void read(std::istream& i = std::cin) {
		char residuo;
		i >> hora >> residuo >> min >> dur;
		ini = (hora * 60) + min;
		fin = ini + dur;
	}
private:
	int hora;
	int min;
	int dur;
	int ini;
	int fin;
};

inline std::istream& operator>>(std::istream & i, Pelicula & a) {
	a.read(i);
	return i;
}

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (num == 0) return false;
	else {
		std::vector<Pelicula> v(num);
		for (int i = 0; i < num; ++i)
			std::cin >> v[i];
		std::sort(v.begin(), v.end());
		int tiempo = 0, cont = 0;
		for (int i = 0; i < v.size(); ++i) {
			if (v[i].getIni() >= tiempo) {
				++cont;
				tiempo = v[i].getFin() + 10;
			}
		}
		std::cout << cont << "\n";
		return true;
	}
}

#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	/*
	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i)
	resuelveCaso();*/
	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}