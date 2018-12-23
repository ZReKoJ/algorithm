#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>

/*void resolver(const std::vector<int>& v) {
	int ascendente = 0, descendente = 0;

	for (int i = 0; i < v.size() - 1; ++i) {
		if (v[i] < v[i + 1])
			ascendente++;
		else if (v[i] > v[i + 1])
			descendente++;
	}

	printf("%d %d\n", ascendente, descendente);
}*/

/*void resuelveCaso(int &numCasos) {
	int suma = 0, valor;
	for (int i = 0; i < numCasos - 1; ++i) {
		scanf("%d", &valor);
		suma += valor;
	}
	numCasos = (numCasos*(numCasos + 1) / 2);
	printf("%d\n", numCasos - suma);
}*/

int main() {
	/*int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();*/

	int numCasos;
	scanf("%d", &numCasos);
	while (numCasos > 0) {
		int suma = 0, valor;
		for (int i = 0; i < numCasos - 1; ++i) {
			scanf("%d", &valor);
			suma += valor;
		}
		numCasos = (numCasos*(numCasos + 1) / 2);
		printf("%d\n", numCasos - suma);
		scanf("%d", &numCasos);
	}

	//system("PAUSE");
	return 0;
}