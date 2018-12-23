#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

void resolver(std::vector<int>& v, int copias) {
	int valor, contTotal = 0, contCopias = 0;
	std::vector<int> w(100000);
	std::vector<bool> x(100000);

	if (copias > v.size())
		copias = v.size();
	
	for (int i = 0; i < copias; ++i) {
		valor = v[i] - 1;
		if (!x[valor])
			x[valor] = true;
		else ++contTotal;
		if (w[valor] > 0)
			++contCopias;
		++w[valor];
	}

	for (int i = copias; i < v.size(); ++i) {
		valor = v[i] - 1;
		if (!x[valor])
			x[valor] = true;
		else ++contTotal;
		if (w[valor] > 0)
			++contCopias;
		--w[v[i - copias] - 1];
		++w[valor];
	}

	printf("%d %d\n", contTotal, contCopias);
}

bool resuelveCaso() {
	int numValores, copias;
	std::cin >> numValores;
	if (!std::cin.fail()) {
		scanf("%d", &copias);
		std::vector<int> v(numValores);
		for (int &valor : v)
			scanf("%d", &valor);
		resolver(v, copias);
		return true;
	}
	else return false;
}

int main() {
	/*srand(time(NULL));
	std::ifstream in("d:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();*/

	/*int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++)
	resuelveCaso();*/

	/*int numValores;
	scanf("%d", &numValores);
	while (numValores > 0) {
	resuelveCaso(numValores);
	scanf("%d", &numValores);
	}*/

	while (resuelveCaso()) {}

	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");*/

	return 0;
}