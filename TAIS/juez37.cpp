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

/*
pelicula(i) = es el tiempo mas largo que puede estar viendo peliculas que comienzan en algun punto de 0 a i
pelicula(i) = {
	pelicula(i - 1) si no hay ninguna pelicula que empiece en ese tiempo - (su duracion + 10)
	el maximo de (pelicula(i) y pelicula(i - dur) + dur) si existe una pelicula que empiece en ese tiempo - (su duracion + 10)
}
El tiempo es O(n^2) // Donde n es 1451
El espacio es O(n) // Donde n es 1451
*/

class Pelicula {
public:
	Pelicula() : hora(0), min(0), dur(0) {
		ini = 0;
		fin = 0;
	}
	Pelicula(int h, int m, int d) : hora(h), min(m), dur(d) {
		ini = (hora * 60) + min;
		fin = ini + dur;
	}

	int getIni() {
		return ini;
	}

	int getFin() {
		return fin;
	}

	int getDur() {
		return dur;
	}

	bool operator<(Pelicula const& that) {
		if (ini == that.ini) return fin < that.fin;
		else return ini < that.ini;
	}

	bool operator>(Pelicula const& that) {
		if (ini == that.ini) return fin > that.fin;
		else return ini > that.ini;
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
		int minutoDia = 24 * 60;
		std::vector<int> t(minutoDia + 11, 0);
		int max, j;
		Pelicula p;
		for (int i = 0; i < v.size(); ++i) {
			p = v[i];
			j = p.getFin() + 10;
			max = std::max(t[p.getIni()] + p.getDur(), t[j]);
			while (j < t.size() && t[j] < max) {
				t[j] = max; 
				++j;
			}
		}
		std::cout << t[t.size() - 1] << "\n";
		return true;
	}
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