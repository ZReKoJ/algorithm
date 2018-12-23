#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

long long int resolver(const std::vector<int>& v) {
	long long int sol = 0;
	long long int suma = 0;

	for (int i = 0; i < v.size(); ++i) {
		sol += (suma * v[i]);
		suma += v[i];
	}

	return sol;
}

void resuelveCaso(int numValores) {
	std::vector<int> v(numValores);
	for (int &valor : v)
		scanf("%d", &valor);
	
	long long int solucion = resolver(v);
	printf("%lld\n", solucion);
}

int main() {
	/*int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();*/

	int numValores;
	scanf("%d", &numValores);
	while (numValores > 0) {
		resuelveCaso(numValores);
		scanf("%d", &numValores);
	}

	//system("pause");
	return 0;
}