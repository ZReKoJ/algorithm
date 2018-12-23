#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

//#define RKJ

void resuelveCaso() {
	std::string palabra;
	std::cin >> palabra;
	char letra;
	for (int i = 0; i < palabra.length(); ++i) {
		if (islower(palabra.at(i)))
			letra = tolower(palabra.at(palabra.length() - i - 1));
		else
			letra = toupper(palabra.at(palabra.length() - i - 1));
		printf("%c", letra);
	}
	printf("\n");
}

int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int numCasos;
	scanf("%d", &numCasos);
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