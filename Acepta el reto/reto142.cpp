#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <string>
#include <set>

//#define RKJ

bool resuelveCaso() {
	int numNinos, numero;
	scanf("%d", &numNinos);
	scanf("%d", &numero);
	if (!(numNinos == 0 && numero == 0)) {
		std::vector<int> v(numNinos);
		for (int i = 0; i < numNinos; ++i)
			v[i] = i + 1;
		int i = -1;
		while (v.size() > 1) {
			i = (numero + 1 + i) % v.size();
			v.erase(v.begin() + i);
			--i;
		}
		printf("%d\n", v[0]);
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