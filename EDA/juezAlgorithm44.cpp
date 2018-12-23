// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <climits>

/*
Vuelta Atras
se coge un intervalo y se prueban los intervalos despues de la pos del intervalo a probar
cada vez que se valide
introducimos el vector aux en todasSol
lo de r se controla despues de todas las sol
*/

struct intervalo {
	int ini, fin;
};

std::istream& operator>> (std::istream& in, intervalo& p) {
	in >> p.ini >> p.fin;
	return in;
}

bool operator== (intervalo const& p1, intervalo const& p2) {
	return p1.ini == p2.ini && p1.fin == p2.fin;
}

class comp {
public:
	bool operator()(std::vector<intervalo> const& v1, std::vector<intervalo> const& v2) {
		int i = 0;
		while (i < v1.size() && i < v2.size() && v1[i] == v2[i]) ++i;
		if (i < v1.size() && i < v2.size() && !(v1[i] == v2[i])) {
			if (v1[i].ini < v2[i].ini) return true;
			else if (v1[i].ini > v2[i].ini) return false;
			else if (v1[i].fin < v2[i].fin) return true;
			else if (v1[i].fin >= v2[i].fin) return false;
		}
		if (i < v1.size() || v1.size() == v2.size()) return false;
		else return true;
	}
};

void resolver(const std::vector<intervalo> &v, std::vector<intervalo> &aux, std::vector<std::vector<intervalo>> &todasSol, int stage) {
	for (int i = stage; i < v.size(); ++i) {
		aux.emplace_back(v[i]);
		if (aux[aux.size() - 2].fin < aux[aux.size() - 1].ini) {
				todasSol.emplace_back(aux);
			if (v[i].fin < v[v.size() - 1].ini) {
				resolver(v, aux, todasSol, i + 1);
			}
		}
		aux.pop_back();
	}
}

bool resuelveCaso() {
	int numConjuntos, r;
	std::cin >> numConjuntos;
	if (!std::cin.fail()) {
		std::cin >> r;
		std::vector<intervalo> v(numConjuntos);
		for (int i = 0; i < numConjuntos; ++i) {
			std::cin >> v[i].ini;
			std::cin >> v[i].fin;
		}
		std::vector<std::vector<intervalo>> todasSol;
		std::vector<intervalo> aux = { { -1, -1} };
		todasSol.emplace_back(aux);
		
		resolver(v, aux, todasSol, 0);

		sort(todasSol.begin(), todasSol.end(), comp());

		for (int i = todasSol.size() - 1; i > 0; --i) {
			if (todasSol[i].size() - 1 < r)
				todasSol.erase(todasSol.begin() + i);
		}

		std::cout << todasSol.size() - 1 << '\n';
		for (int i = 1; i < todasSol.size(); ++i) {
			for (int j = 1; j < todasSol[i].size(); ++j) {
				std::cout << "[" << todasSol[i][j].ini << "," << todasSol[i][j].fin << "]";
			}
			std::cout << '\n';
		}
		
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock(), tParcial = t;
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