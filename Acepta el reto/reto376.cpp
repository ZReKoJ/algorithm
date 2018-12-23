#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

//#define RKJ

void resolver(const std::vector<int> &v) {
	int picos = 0;
	for (int i = 1; i < v.size() - 1; ++i) {
		if (v[i] > v[i - 1] && v[i] > v[i + 1])
			++picos;
	}
	if (v[0] > v[1] && v[0] > v[v.size() - 1])
		++picos;
	if (v[v.size() - 1] > v[0] && v[v.size() - 1] > v[v.size() - 2])
		++picos;

	printf("%d\n", picos);
}

bool resuelveCaso() {
	int numValores;
	scanf("%d", &numValores);
	if (numValores != 0) {
		std::vector<int> v(numValores);
		for (int i = 0; i < numValores; ++i)
			scanf("%d", &v[i]);
		resolver(v);
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