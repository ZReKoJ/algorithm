// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Recursion no final
Divido cada array en dos mitades y de esta a su vez en dos hasta que salga arrays de 1 valor
y de alli se hace merge ordenandolos y contar los cambios, hice los de cambios / 2 porque cada movimiento significa el cambio en la posicion de 2 numeros

T(0) = c0; T(n) = 2T(n / 2) + 2n --> O(2 ^ n)
*/

long long int mergee(std::vector<int> &v, int ini1, int fin1, int ini2, int fin2, std::vector<int> &aux) {
	int izq = ini1, dch = ini2;
	long long int cambios = 0;

	for (int x = 0; x < aux.size(); ++x) {
		if (izq > fin1) {
			aux[x] = v[dch];
			cambios += abs(x + ini1 - dch);
			++dch;
		}
		else if (dch > fin2) {
			aux[x] = v[izq];
			cambios += abs(x + ini1 - izq);
			++izq;
		}
		else {
			if (v[izq] <= v[dch]) {
				aux[x] = v[izq];
				cambios += abs(x + ini1 - izq);
				++izq;
			}
			else {
				aux[x] = v[dch];
				cambios += abs(x + ini1 - dch);
				++dch;
			}
		}
	}

	return cambios / 2;
}


long long int resolver(std::vector<int> &v, int ini, int fin) {
	if (fin <= ini) return 0;
	else {
		int mitad = (fin + ini) / 2;
		long long int invIzq = resolver(v, ini, mitad);
		long long int invDch = resolver(v, mitad + 1, fin);
		std::vector<int> aux(fin - ini + 1);
		long long int inv = mergee(v, ini, mitad, mitad + 1, fin, aux);
		copy(aux.begin(), aux.end(), v.begin() + ini);
		return invIzq + invDch + inv;
	}
}

bool resuelveCaso() {
	int numValores;

	std::cin >> numValores;
	if (!std::cin.fail()) {
		std::vector<int> v(numValores);

		for (int i = 0; i < numValores; ++i)
			std::cin >> v[i];

		long long int cambios = resolver(v, 0, v.size() - 1);
		std::cout << cambios << '\n';

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