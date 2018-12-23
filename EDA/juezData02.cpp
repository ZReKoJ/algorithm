// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <stdexcept>

class t {
private:
	int hora, minuto, segundo;
public:
	t() {}
	t(int h, int m, int s) {
		if ((0 <= h && h < 24) && (0 <= m && m < 60) && (0 <= s && s < 60)) {
			hora = h; minuto = m; segundo = s;
		}
		else throw std::domain_error("ERROR");
	}
	bool operator<= (const t &that) const {
		if (hora == that.hora) {
			if (minuto == that.minuto)
				return segundo <= that.segundo;
			else return minuto < that.minuto;
		}
		else return hora < that.hora;
	}
	bool operator< (const t &that) const {
		if (hora == that.hora) {
			if (minuto == that.minuto)
				return segundo < that.segundo;
			else return minuto < that.minuto;
		}
		else return hora < that.hora;
	}
	bool operator== (const t &that) const {
		return (hora == that.hora && minuto == that.minuto && segundo == that.segundo);
	}
	t operator+ (const t &that) const {
		int hr, mn, sc, a;
		sc = (segundo + that.segundo) % 60;
		a = (segundo + that.segundo) / 60;
		mn = (minuto + that.minuto + a) % 60;
		a = (minuto + that.minuto + a) / 60;
		hr = hora + that.hora + a;
		if (hr < 24)
			return t(hr, mn, sc);
		else
			throw std::domain_error("ERROR: Dia siguiente");
	}
	void print(std::ostream & out = std::cout) const {
		out << std::setfill('0') << std::setw(2) << hora << ":" << std::setw(2) << minuto << ":" << std::setw(2) << segundo;
	}
};
inline std::ostream & operator<<(std::ostream & out, t const& rhs) {
	rhs.print(out);
	return out;
}

class pelicula {
private:
	t horario, duracion, duracionFin;
	std::string titulo;
public:
	pelicula() {}
	pelicula(t h, t d, std::string titulo) : horario(h), duracion(d), titulo(titulo) {
		duracionFin = horario + duracion;
	}
	bool operator< (const pelicula &that) {
		if (duracionFin == that.duracionFin)
			return titulo < that.titulo;
		else return duracionFin < that.duracionFin;
	}
	void printFin() {
		std::cout << duracionFin << " " << titulo << '\n';
	}
};

void resolver(std::vector<pelicula> &v, int i) {
	int h, m, s;
	char residuo;
	std::cin >> h >> residuo >> m >> residuo >> s;
	t horario = t(h, m, s);
	std::cin >> h >> residuo >> m >> residuo >> s;
	t duracion = t(h, m, s);
	std::string palabra;
	getline(std::cin, palabra);
	v[i] = pelicula(horario, duracion, palabra);
}

bool resuelveCaso() {
	int numPeliculas;
	std::cin >> numPeliculas;
	if (numPeliculas != 0) {
		std::vector<pelicula> v(numPeliculas);
		for (int i = 0; i < numPeliculas; ++i)
			resolver(v, i);
		sort(v.begin(), v.end());
		for (int i = 0; i < numPeliculas; ++i)
			v[i].printFin();
		std::cout << "---\n";
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