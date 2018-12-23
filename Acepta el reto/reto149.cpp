#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>

/*int resolver(const std::vector<int>& v) {
	int max = 0;

	for (int valor : v)
		if (valor > max)
			max = valor;

	return max;
}*/

/*void resuelveCaso(int numValores) {
	std::vector<int> v(numValores);
	for (int &valor : v)
		scanf("%d", &valor);
	
	int solucion = resolver(v);
	printf("%d\n", solucion);
}*/

int main() {
	/*int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();*/

	/*int numValores;
	scanf_s("%d", &numValores);
	while (numValores > 0) {
		resuelveCaso(numValores);
		scanf_s("%d", &numValores);
	}*/
	long int casos, max = 0, dato;
	while (scanf("%d", &casos) == 1) {
		for (int i = 0; i< casos; i++) {
			scanf("%d", &dato);
			if (dato > max)
				max = dato;
		}
		printf("%d\n", max);
		max = 0;
	}
	//system("pause");
	return 0;
}