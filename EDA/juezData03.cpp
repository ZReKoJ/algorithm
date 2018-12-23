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

class complejo {
private:
	float real, imaginaria;
public:
	complejo(){}
	complejo(float r, float im) : real(r), imaginaria(im) {}
	complejo operator+ (const complejo &that) {
		float r = real + that.real;
		float im = imaginaria + that.imaginaria;
		return complejo(r, im);
	}
	complejo operator* (const complejo &that) {
		float r = (real * that.real) - (imaginaria * that.imaginaria);
		float im = (real * that.imaginaria) + (that.real * imaginaria);
		return complejo(r, im);
	}
	float mod() {
		float r = real * real;
		float im = imaginaria * imaginaria;
		float mod = r + im;
		return sqrt(mod);
	}
};

void resuelveCaso() {
	float real, imaginaria;
	int iteraciones;
	std::cin >> real >> imaginaria >> iteraciones;
	complejo c = complejo(real, imaginaria), cp = complejo(0, 0);
	int i = 0;
	while (i < iteraciones && cp.mod() <= 2) {
		cp = (cp * cp) + c;
		++i;
	}
	if (i == iteraciones)
		std::cout << "SI\n";
	else std::cout << "NO\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos; 
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}