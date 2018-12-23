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

int buscar(const std::vector<int> &v, int num, int iIni) {
	int i = iIni;
	while (v[i] != num)
		++i;
	return i - iIni;
}

void resolver(const std::vector<int> &inorden, int iIni, int iFin, const std::vector<int> &postorden, int pIni, int pFin, std::vector<int> &preorden) {
	if (pIni < pFin) {
		int pivote = postorden[pFin], pos;
		pos = buscar(inorden, pivote, iIni);
		preorden.emplace_back(inorden[iIni + pos]);
		resolver(inorden, iIni, iIni + pos - 1, postorden, pIni, pIni + pos - 1, preorden);
		resolver(inorden, iIni + pos + 1, iFin, postorden, pIni + pos, pFin - 1, preorden);
	}
	else if (iIni == iFin) preorden.emplace_back(inorden[iIni]);
}

bool resuelveCaso() {
	int valor;
	//std::cin >> valor;
	scanf("%d", &valor);
	if (valor != 0) {
		std::vector<int> preorden, inorden(valor), postorden(valor);
		for (int i = 0; i < valor; ++i)
			scanf("%d", &inorden[i]);
			//std::cin >> inorden[i];
		for (int i = 0; i < valor; ++i)
			scanf("%d", &postorden[i]);
			//std::cin >> postorden[i];
		resolver(inorden, 0, inorden.size() - 1, postorden, 0, postorden.size() - 1, preorden);
		printf("%d", preorden[0]);
		for (int i = 1; i < preorden.size(); ++i)
			printf(" %d", preorden[i]);
		printf("\n");
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