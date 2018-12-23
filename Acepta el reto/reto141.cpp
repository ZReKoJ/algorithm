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

bool resolver(const std::string & palabra) {
	std::vector<char> w;
	bool valido = true;
	for (int i = 0; i < palabra.size() && valido; ++i) {
		if (palabra.at(i) == '(' || palabra.at(i) == '{' || palabra.at(i) == '[' || palabra.at(i) == ']' || palabra.at(i) == '}' || palabra.at(i) == ')') {
			if (palabra.at(i) == '(' || palabra.at(i) == '{' || palabra.at(i) == '[')
				w.emplace_back(palabra.at(i));
			else if (w.size() > 0 && palabra.at(i) == ')' && w[w.size() - 1] == '(')
				w.pop_back();
			else if (w.size() > 0 && palabra.at(i) == ']' && w[w.size() - 1] == '[')
				w.pop_back();
			else if (w.size() > 0 && palabra.at(i) == '}' && w[w.size() - 1] == '{')
				w.pop_back();
			else
				valido = false;
		}
	}
	return valido && (w.size() == 0);
}

bool resuelveCaso() {
	std::string palabra;
	getline(std::cin, palabra);
	if (!std::cin.fail()) {
		if (resolver(palabra))
			std::cout << "YES\n";
		else std::cout << "NO\n";

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