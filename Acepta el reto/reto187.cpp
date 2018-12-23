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

//#define RKJ

typedef struct {
	int valor;
	char tipo;
} tCarta;

void quitar(std::vector<tCarta> &w, std::vector<tCarta> &pila) {
	bool sigue = true;
	while (sigue && w.size() > 0) {
		int i = 0;
		while (i < pila.size() && pila[i].tipo != w[w.size() - 1].tipo)
			++i;
		if (w[w.size() - 1].valor == pila[i].valor) {
			w.pop_back();
			++pila[i].valor;
		}
		else sigue = false;
	}
}

bool resolver(const std::vector<tCarta> &v, std::vector<tCarta> &pila) {
	std::vector<tCarta> w;
	for (int i = 0; i < v.size(); i += 2) {
		w.emplace_back(v[i]);
		if (i + 1 < v.size())
			w.emplace_back(v[i + 1]);
		quitar(w, pila);
	}
	if (w.size() == 0)
		return true;
	else {
		if (w.size() == v.size())
			return false;
		else return resolver(w, pila);
	}
}

bool resuelveCaso() {
	int numero;
	std::cin >> numero;
	if (numero != 0) {
		std::vector<tCarta> v(numero * 10);
		tCarta carta;
		for (int i = 0; i < v.size(); ++i) {
			std::cin >> carta.valor >> carta.tipo;
			if (carta.valor >= 10)
				carta.valor -= 2;
			v[i] = carta;
		}
		std::vector<tCarta> pila = { {1, 'O'}, {1, 'C'}, {1, 'E'}, {1, 'B'} };
		if (resolver(v, pila))
			std::cout << "GANA\n";
		else std::cout << "PIERDE\n";
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