#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

int resolver(const std::vector<int> &v, int carga) {
	int cont = 0, ini = 0, fin = v.size() - 1;

	while (ini < fin) {
		if (v[ini] + v[fin] >= carga) {
			++cont;
			++ini;
			--fin;
		}
		else ++ini;
	}

	return cont;
}

void resuelveCaso() {
	int numValores, carga;
	scanf("%d", &numValores);
	scanf("%d", &carga);
	std::vector<int> v(numValores);
	for (int i = 0; i < numValores; ++i)
		scanf("%d", &v[i]);
	sort(v.begin(), v.end());
	int contador = resolver(v, carga);
	printf("%d\n", contador);
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