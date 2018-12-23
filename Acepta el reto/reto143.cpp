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

void resolver(std::vector<int> &v, int numTortitas) {
	int izq = v.size() - numTortitas, dch = v.size() - 1, i = 0, aux;
	while ((izq + i) < (dch - i)) {
		aux = v[izq + i];
		v[izq + i] = v[dch - i];
		v[dch - i] = aux;
		++i;
	}
}

bool resuelveCaso() {
	int tortitas, numCasos, numTortitas;
	scanf("%d", &tortitas);
	if (tortitas != -1) {
		std::vector<int> v;
		while (tortitas != -1) {
			v.emplace_back(tortitas);
			scanf("%d", &tortitas);
		}
		scanf("%d", &numCasos);
		for (int i = 0; i < numCasos; ++i) {
			scanf("%d", &numTortitas);
			resolver(v, numTortitas);
		}
		printf("%d\n", v[v.size() - 1]);
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