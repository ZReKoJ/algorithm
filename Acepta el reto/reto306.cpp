#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <sstream>

const int MODULO = 46337;

void resolver(int fibonacci, long long int &fib1, long long int &fib2, long long int &fib3) {
	if (fibonacci > 1) {
		resolver(fibonacci / 2, fib1, fib2, fib3);
		int aux = fib1;
		fib1 = (fib1 * fib1 + fib2 * fib2) % MODULO;
		fib2 = (2 * aux * fib2 + fib2 * fib2) % MODULO;
		fib3 = (fib1 + fib2) % MODULO;
		if (fibonacci % 2 == 1) {
			aux = fib1;
			fib1 = fib2 % MODULO;
			fib2 = (aux + fib2) % MODULO;
			fib3 = (fib1 + fib2) % MODULO;
		}
	}
}

bool resuelveCaso() {
	int fibonacci;
	long long int fib1 = 0, fib2 = 1, fib3 = 1;

	//std::cin >> fibonacci;
	scanf("%d", &fibonacci);
	if (fibonacci != 0) {
		resolver(fibonacci, fib1, fib2, fib3);
		//std::cout << fib2 % MODULO << '\n';
		printf("%d\n", fib2 % MODULO);
		return true;
	}
	else return false;
}

int main() {
	/*srand(time(NULL));
	std::ifstream in("d:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();*/

	while (resuelveCaso()) {}

	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");*/

	return 0;
}