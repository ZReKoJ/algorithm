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

void resuelveCaso() {
	int numValores, valor, cont = 0;

	scanf("%d", &numValores);
	for (int i = 0; i < numValores; ++i) {
		scanf("%d", &valor);
		if ((valor % 2) == 0)
			cont++;
	}
	printf("%d\n", cont);
}

int main() {
	int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();

	/*int numValores;
	scanf_s("%d", &numValores);
	while (numValores > 0) {
		resuelveCaso(numValores);
		scanf_s("%d", &numValores);
	}*/

	//system("PAUSE");
	return 0;
}