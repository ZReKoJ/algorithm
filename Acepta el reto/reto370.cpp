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
	int num1, num2;
	char a;
	scanf("%d", &num1);
	scanf("%c", &a);
	scanf("%d", &num2);
	if (num1 > num2) {
		int aux = num1;
		num1 = num2;
		num2 = aux;
	}
	if (num1 % 2 == 0 && num1 == num2 - 1)
		printf("SI\n");
	else
		printf("NO\n");
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