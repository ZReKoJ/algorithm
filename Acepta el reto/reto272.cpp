#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

int resolver(int valor) {
	if (valor >= 6) {
		int resto = valor % 6;
		return resolver(valor / 6) * 10 + resto;
	}
	else return valor;
}

void resuelveCaso() {
	int valor;
	scanf("%d", &valor);
	valor = resolver(valor);
	printf("%d\n", valor);
}

int main() {
	// Hay que comentarlo para acepta el reto
	/*srand(time(NULL));
	std::ifstream in("d:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();//*/

	int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// Hay que comentarlo para acepta el reto
	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';

	system("PAUSE");//*/

	return 0;
}