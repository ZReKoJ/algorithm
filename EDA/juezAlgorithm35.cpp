// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Vuelta atras
Se recorre cada una de las ramas que son las cuatro operaciones aritmeticas
y cuando se llega al final es decir hecha las cuatro operaciones comprueba si es cierta la comprobacion
si es cierta devuelve el resultado rompiendo el proceso y si no sigue el proceso
*/

//#define RKJ

#ifdef RKJ
#include <sstream>

bool resolver(const std::vector<int> &v, int valor, int resultado, int stage, int maxStage, std::ostringstream &s) {
	int valorAnterior;
	bool div = true, valido = false;
	std::string ant;

	for (int i = 0; i < 4; ++i) {
		valorAnterior = resultado;
		ant = s.str();

		switch (i) {
		case 0: resultado += v[stage]; s << " + " << v[stage]; break;
		case 1: resultado -= v[stage]; s << " - " << v[stage]; break;
		case 2: resultado *= v[stage]; s << " * " << v[stage]; break;
		case 3:
			if (v[stage] != 0 && (resultado % v[stage]) == 0) {
				resultado /= v[stage]; s << " / " << v[stage];
			}
			else div = false;
			break;
		}

		if (div) {
			if (stage == maxStage) {
				s << " = " << std::setw(5) << resultado;
				std::cout << s.str() << " " << valor << '\n';
				valido = valido || resultado == valor;
				//system("pause");
			}
			else {
				if (resolver(v, valor, resultado, stage + 1, maxStage, s))
					return true;
			}
		}

		resultado = valorAnterior;
		s.str("");
		s.clear();
		s << ant;
	}

	return valido;
}
#endif

#ifndef RKJ
bool resolver(const std::vector<int> &v, int valor, int resultado, int stage, int maxStage) {
	int valorAnterior;
	bool div = true, valido = false;

	for (int i = 0; i < 4; ++i) {
		valorAnterior = resultado;

		switch (i) {
		case 0: resultado += v[stage]; break;
		case 1: resultado -= v[stage]; break;
		case 2: resultado *= v[stage]; break;
		case 3: 
			if (v[stage] != 0 && (resultado % v[stage]) == 0)
				resultado /= v[stage];
			else div = false;
			break;
		}

		if (div) {
			if (stage == maxStage)
				valido = valido || resultado == valor;
			else {
				if (resolver(v, valor, resultado, stage + 1, maxStage))
					return true;
			}
		}

		resultado = valorAnterior;
	}

	return valido;
}
#endif

bool resuelveCaso() {
	int numero;

	std::cin >> numero;
	if (!std::cin.fail()) {
		std::vector<int> v(5);
		
		for (int i = 0; i < 5; ++i)
			std::cin >> v[i];

#ifdef RKJ
		std::ostringstream s;
		s << v[0];
		if (resolver(v, numero, v[0], 1, 4, s))
			std::cout << "SI\n";
		else
			std::cout << "NO\n";
		system("pause");
#endif
#ifndef RKJ
		if (resolver(v, numero, v[0], 1, 4))
			std::cout << "SI\n";
		else
			std::cout << "NO\n";
#endif

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