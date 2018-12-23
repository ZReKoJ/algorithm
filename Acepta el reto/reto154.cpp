#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

//#define RKJ

const std::vector<char> v = { 'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z' };

int busquedaBin(const std::vector<char> &v, char letra, int ini, int fin) {
	if (ini >= fin) {
		return ini;
	}
	else {
		int medio = (ini + fin) / 2;
		if (v[medio] == letra)
			return medio;
		else if (v[medio] < letra)
			return busquedaBin(v, letra, medio + 1, fin);
		else
			return busquedaBin(v, letra, ini, medio);
	}
}

bool buscarSig(const std::vector<char> &v, char &letra) {
	if (letra == 'Z') {
		letra = 'B';
		return true;
	}
	else {
		letra = v[busquedaBin(v, letra, 0, v.size() - 1) + 1];
		return false;
	}
}

void resolver(int &numero, std::string &palabra) {
	++numero;
	if (numero == 10000) {
		numero = 0000;
		int i = palabra.length() - 1;
		while (buscarSig(v, palabra.at(i))) {
			--i;
		}
	}
}

bool resuelveCaso() {
	int numero;
	std::string palabra;

	std::cin >> numero >> palabra;
	if (!(numero == 9999 && palabra == "ZZZ")) {
		resolver(numero, palabra);
		std::cout << std::setfill('0') << std::setw(4) << numero << " " << palabra << '\n';
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