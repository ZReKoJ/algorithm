#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

/*void resolver(std::vector<int>& v) {
	int sol = 0, maxInv = 0, min = abs(v[v.size() - 1]), absoluto;

	for (int j = v.size() - 1; j >= 1; --j) {
		maxInv += ((v[j] - v[j - 1]) * -1);
		absoluto = abs(maxInv + v[j - 1]);
		if (absoluto <= min) {
			min = absoluto;
			sol = j;
		}
	}
	if (abs(v[v.size() - 1]) <= min)
		sol = 0;
	printf("%d\n", sol);
}*/

void resuelveCaso(int numValores) {
	int valor1 = -1, valor2 = -1;
	bool crec = true;
	for (int i = 0; i < numValores; ++i) {
		scanf("%d", &valor2);
		if (valor2 <= valor1)
			crec = false;
		else
			valor1 = valor2;
	}

	if (crec)
		printf("SI\n");
	else
		printf("NO\n");
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