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

typedef struct {
	int coeficiente;
	int exponente;
} tMonomio;

class polinomio {
private:
	std::vector<tMonomio> p;
public:
	polinomio(){}
	void anadirMonomio(const tMonomio &m) {
		p.emplace_back(m);
	}
	long long int evaluar(int x) {
		long long int suma = 0;
		for (int i = 0; i < p.size(); ++i)
			suma += p[i].coeficiente * pow(x, p[i].exponente);
		return suma;
	}
};

bool resuelveCaso() {
	tMonomio m;
	std::cin >> m.coeficiente;
	if (!std::cin.fail()) {
		std::cin >> m.exponente;
		polinomio p = polinomio();
		while (!(m.coeficiente == 0 && m.exponente == 0)) {
			p.anadirMonomio(m);
			std::cin >> m.coeficiente >> m.exponente;
		}
		int numCasos, x;
		std::cin >> numCasos;
		for (int i = 0; i < numCasos; ++i) {
			std::cin >> x;
			std::cout << p.evaluar(x) << " ";
		}
		std::cout << '\n';
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