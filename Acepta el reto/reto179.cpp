#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

int resolver(const std::vector<int>& v) {
	int inferior, superior;

	scanf("%d", &inferior);
	scanf("%d", &superior);

	return v[superior] - v[inferior - 1];
}

void resuelveCaso(int n) {
	int solucion, numCasos, sumatorio = 0, valor;

	std::vector<int> v(n + 1);
	//for (int& valor : v)
	v[0] = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &valor);
		sumatorio += valor;
		v[i] = sumatorio;
	}

	scanf("%d", &numCasos);
	for (int j = 0; j < numCasos; ++j) {
		solucion = resolver(v);
		printf("%d\n", solucion);
	}
}

int main() {
	/*int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)*/

	int numValores;
	scanf("%d", &numValores);
	while (numValores > 0) {
		resuelveCaso(numValores);
		scanf("%d", &numValores);
	}

	//system("pause");
	return 0;
}