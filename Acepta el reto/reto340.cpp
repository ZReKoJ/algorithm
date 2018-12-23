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

/*void resuelveCaso() {
	int n, m;

}*/

int main() {
	int numCasos, n, m;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++) {
		scanf("%d", &n);
		scanf("%d", &m);
		printf("%d\n", (n*(m + 1) + m*(n + 1)));
	}

	/*int numValores;
	scanf_s("%d", &numValores);
	while (numValores > 0) {
		resuelveCaso(numValores);
		scanf_s("%d", &numValores);
	}*/

	//system("PAUSE");
	return 0;
}