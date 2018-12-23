#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <list>
#include <climits>
#include <limits.h>
#include <limits>
#include <queue>
#include <map>

bool resuelveCaso() {
	char tipo1, tipo2, residuo;
	int num1, num2;
	std::cin >> tipo1 >> residuo >> num1 >> tipo2 >> residuo >> num2;
	std::map<char, int> m;
	m[tipo1] = num1;
	m[tipo2] = num2;
	if (m.count('D') == 0) std::cout << "D=" << m['T'] * m['V'] << "\n";
	else if (m.count('V') == 0) std::cout << "V=" << m['D'] / m['T'] << "\n";
	else std::cout << "T=" << m['D'] / m['V'] << "\n";
	return true;
}

#define RKJ
int main() {
#ifdef RKJ
	std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i)
		resuelveCaso();
	//while (resuelveCaso()) {}

#ifdef RKJ
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}