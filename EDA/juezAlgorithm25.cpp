// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <sstream>

/*
Recursion final
Guardo los parametros anteriores en fib1 y fib2 y se calcula la suma
Recursion no final
Se llama a la recursion primero, despues se cambia los variables y se devuelve fib2

T(0) = 0; T(1) = 1;  T(n) = T(n - 1); --> O(n)
*/

//Final
long long int resolverFinal(int fibonacci, int cont, long long int fib1, long long int fib2){
	if (cont < fibonacci)
		return resolverFinal(fibonacci, cont + 1, fib2, fib1 + fib2);
	else
		return fib1 + fib2;
}

//No final
long long int resolverNoFinal(int fibonacci, long long int & fib1, long long int & fib2) {
	if (fibonacci > 2)
		resolverNoFinal(fibonacci - 1, fib1, fib2);
	long long int aux = fib1; fib1 = fib2; fib2 = fib1 + aux;
	return fib2;
}

bool resuelveCaso() {
	int fibonacci;
	long long int fib1 = 0, fib2 = 1;

	std::cin >> fibonacci;
	if (!std::cin.fail()) {
		if (fibonacci == 0 || fibonacci == 1)
			std::cout << fibonacci << '\n';
		else {
			std::cout << resolverFinal(fibonacci, 2, fib1, fib2) << '\n';
			//std::cout << resolverNoFinal(fibonacci, fib1, fib2) << '\n';
		}
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()){}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}