#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

//#define RKJ

void resolver(std::vector<int> &v) {
	int pos = v.size() - 1;
	bool fin = false;
	while (pos > 0 && !fin) {
		if (v[pos] - v[pos - 1] == 0) {
			++v[pos];
			fin = true;
		}
		else if (v[pos] - v[pos - 1] == 1)
			--pos;
	}

	if (!fin) {
		int valor = v[0] + 1;
		for (int i = 0; i < v.size(); ++i)
			v[i] = valor;
	}
}

bool resuelveCaso() {
	int numValores;
	scanf("%d", &numValores);
	if (numValores != 0) {
		std::vector<int> v(numValores);
		for (int i = 0; i < v.size(); ++i)
			scanf("%d", &v[i]);

		resolver(v);
		printf("%d", v[0]);
		for (int i = 1; i < v.size(); ++i)
			printf(" %d", v[i]);
		printf("\n");
		return true;
	}
	else return false;
}

int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifdef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}