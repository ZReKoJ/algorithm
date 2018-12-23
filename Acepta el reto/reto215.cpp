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

void resolver(const std::vector<int> &preorden, int pIni, int pFin, const std::vector<int> &inorden, int iIni, int iFin, std::vector<int> &postorden) {
	if (pIni < pFin) {
		int pivote = preorden[pIni], pos;
		pos = buscar(inorden, pivote, iIni);
		resolver(preorden, pIni + 1, pIni + pos, inorden, iIni, iIni + pos - 1, postorden);
		resolver(preorden, pIni + pos + 1, pFin, inorden, iIni + pos + 1, iFin, postorden);
		postorden.emplace_back(inorden[iIni + pos]);
	}
	else if (iIni == iFin) postorden.emplace_back(inorden[iIni]);
}

bool resuelveCaso() {
	int valor;
	//std::cin >> valor;
	scanf("%d", &valor);
	if (valor != -1) {
		std::vector<int> preorden, inorden, postorden;
		while (valor != -1) {
			preorden.emplace_back(valor);
			//std::cin >> valor;
			scanf("%d", &valor);
		}
		//std::cin >> valor;
		scanf("%d", &valor);
		while (valor != -1) {
			inorden.emplace_back(valor);
			//std::cin >> valor;
			scanf("%d", &valor);
		}
		resolver(preorden, 0, preorden.size() - 1, inorden, 0, inorden.size() - 1, postorden);
		printf("%d", postorden[0]);
		for (int i = 1; i < postorden.size(); ++i)
			printf(" %d", postorden[i]);
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