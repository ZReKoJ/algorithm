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

void resolver(const std::vector<int> &v) {
	int max = -1, i = 0, j = 0, k = 0, suma = 0;
	for (int x = 0; x < v.size(); ++x) {
		suma += v[x];
		if (suma <= 0) {
			suma = 0;
			k = x + 1;
		}
		if (suma > max) {
			max = suma;
			j = x;
			i = k;
		}
		if (suma == max && j - i > x - k) {
			j = x;
			i = k;
		}
	}
	printf("%d %d\n", i + 1, j + 1);
	//std::cout << i + 1 << " " << j + 1 << "\n";
}

void resuelveCaso() {
	int numValores;
	scanf("%d", &numValores);
	//std::cin >> numValores;
	std::vector<int> v(numValores);
	for (int i = 0; i < numValores; ++i)
		scanf("%d", &v[i]);
		//std::cin >> v[i];
	resolver(v);
}

int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifdef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}
