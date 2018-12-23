#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

int resolver(int numVariables) {
	int valor, sol = 1;
	//std::cin >> valor;
	scanf("%d", &valor);
	int mayor = valor, mayorL = mayor;

	for (int i = 1; i < numVariables; i++) {
		scanf("%d", &valor);
		if (valor <= mayor) {
			sol = i + 1;
			mayor = mayorL;
		}
		if (valor > mayorL)
			mayorL = valor;
	}

	return sol;
}

void resuelveCaso(int numVariables) {
	int solucion = resolver(numVariables);

	// escribir sol
	//std::cout << solucion << std::endl;
	printf("%d\n", solucion);
}

int main() {
	// Hay que comentarlo para acepta el reto
	/*srand(time(NULL));
	std::ifstream in("d:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();*/

	/*int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++)
	resuelveCaso();*/

	int numValores;
	scanf("%d", &numValores);
	//std::cin >> numValores;
	while (numValores != 0) {
		resuelveCaso(numValores);
		scanf("%d", &numValores);
		//std::cin >> numValores;
	}

	//while (resuelveCaso()) {}

	// Hay que comentarlo para acepta el reto
	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';

	system("PAUSE");*/

	return 0;
}