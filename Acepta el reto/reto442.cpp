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

void reconocerString(std::string const& p, std::vector<std::string> &v) {
	int tipo = 0; // 0 = camel 1 = snake 2 = kebab
	for (int i = 0; i < p.size() && tipo == 0; ++i) {
		if (p.at(i) == '-') tipo = 2;
		else if (p.at(i) == '_') tipo = 1;
	}
	int ini = 0;
	if (tipo == 0) {
		std::string pal;
		for (int i = 1; i < p.size(); ++i) {
			if (isupper(p.at(i))) {
				pal = p.substr(ini, i - ini);
				pal.at(0) = tolower(pal.at(0));
				v.emplace_back(pal);
				ini = i;
			}
		}
		pal = p.substr(ini, p.size() - ini);
		pal.at(0) = tolower(pal.at(0));
		v.emplace_back(pal);
	}
	else if (tipo == 1) {
		for (int i = 1; i < p.size(); ++i) {
			if (p.at(i) == '_') {
				v.emplace_back(p.substr(ini, i - ini));
				ini = i + 1;
			}
		}
		v.emplace_back(p.substr(ini, p.size() - ini));
	}
	else {
		for (int i = 1; i < p.size(); ++i) {
			if (p.at(i) == '-') {
				v.emplace_back(p.substr(ini, i - ini));
				ini = i + 1;
			}
		}
		v.emplace_back(p.substr(ini, p.size() - ini));
	}
}

bool resuelveCaso() {
	std::string palabra;
	std::cin >> palabra;
	if (std::cin.fail()) return false;
	else {
		std::string tipo;
		std::cin >> tipo;
		std::vector<std::string> v;
		reconocerString(palabra, v);
		if (tipo == "CamelCase") {
			for (int i = 0; i < v.size(); ++i) {
				v[i].at(0) = toupper(v[i].at(0));
				std::cout << v[i];
			}
		}
		else if (tipo == "snake_case") {
			std::cout << v[0];
			for (int i = 1; i < v.size(); ++i)
				std::cout << "_" << v[i];
		}
		else {
			std::cout << v[0];
			for (int i = 1; i < v.size(); ++i)
				std::cout << "-" << v[i];
		}
		std::cout << "\n";
		return true;
	}
}

#define RKJ
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