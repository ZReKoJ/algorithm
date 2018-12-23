#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

void resolver(const std::vector<int>& v, int n) {
	int pico = 0, valle = 0;

	for (int i = 1; i < n - 1; i++) {
		if (v[i - 1] > v[i] && v[i] < v[i + 1])
			valle++;
		if (v[i - 1] < v[i] && v[i] > v[i + 1])
			pico++;
	}

	printf("%d %d\n", pico, valle);
}

void resuelveCaso() {
	int n;
	scanf("%d", &n);
	std::vector<int> v(n); // Vector
	for (int& valor : v)
		scanf("%d", &valor);

	resolver(v, n);
}

int main() {
	int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	/*int numValores;
	scanf("%d", &numValores);
	while (numValores > 0) {
		resuelveCaso(numValores);
		scanf("%d", &numValores);
	}*/

	//system("pause");
	return 0;
}