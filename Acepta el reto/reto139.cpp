#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <set>

//#define RKJ

int sig(int n) {
	if (n < 10)
		return n * n * n;
	else {
		int mod = n % 10;
		return sig(n / 10) + (mod * mod * mod);
	}
}

bool resolver(int n) {
	std::set<int> cj;
	while (n != 1 && cj.count(n) == 0) {
		cj.insert(n);
		n = sig(n);
		printf(" - %d", n);
		//std::cout << " - " << n;
	}
	return n == 1;
}

bool resuelveCaso() {
	int numero;
	//std::cin >> numero;
	scanf("%d", &numero);
	if (numero != 0) {
		printf("%d", numero);
		//std::cout << numero;
		if (resolver(numero))
			printf(" -> cubifinito.\n");
			//std::cout << " -> cubifinito.\n";
		else
			printf(" -> no cubifinito.\n");
			//std::cout << " -> no cubifinito.\n";
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