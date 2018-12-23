#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

int resolver(const std::vector<int>& v, int n) {
	int solucion = 1, montana = v[n - 1];

	for (int i = n - 2; i >= 0; --i) {
		if (v[i] > montana) {
			solucion++;
			montana = v[i];
		}
	}

	return solucion;
}

void resuelveCaso(int n) {
	int solucion;

	std::vector<int> v(n);
	for (int& valor : v)
		scanf("%d", &valor);

	solucion = resolver(v, n);
	printf("%d\n", solucion);
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