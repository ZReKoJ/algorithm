#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

int resolver(const std::vector<int>& v, int numBurros) {
	int valor = v[0], cont = 1, contTotal = 0;

	for (int i = 1; i < v.size(); ++i) {
		if (v[i] == valor)
			++cont;
		else {
			contTotal += cont / 2;
			cont = 1;
			valor = v[i];
		}
	}

	return contTotal + (cont / 2);
}

void resuelveCaso() {
	int numBurros, numValores;
	scanf("%d", &numBurros);
	scanf("%d", &numValores);
	std::vector<int> v(numValores);
	for (int &valor : v)
		scanf("%d", &valor);
	sort(v.begin(), v.end());

	int cont = resolver(v, numBurros);
	if (cont > numBurros)
		cont = numBurros;
	printf("%d\n", cont);
}

int main() {
	int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++)
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