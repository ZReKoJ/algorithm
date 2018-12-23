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

void resolver(const std::string &texto) {
	std::string t;
	int cursor = 0;
	for (int i = 0; i < texto.size(); ++i) {
		if (texto.at(i) == '-' || texto.at(i) == '+' || texto.at(i) == '*' || texto.at(i) == '3') {
			switch (texto.at(i)) {
			case '-': cursor = 0; break;
			case '+': cursor = t.size(); break;
			case '*': if (cursor != t.size()) ++cursor; break;
			case '3': if (cursor >= 0 && cursor < t.size()) t.erase(t.begin() + cursor); break;
			}

		}
		else {
			t.insert(t.begin() + cursor, texto.at(i));
			++cursor;
		}
	}
	std::cout << t << '\n';
}

bool resuelveCaso() {
	std::string texto;
	//std::cin >> texto;
	getline(std::cin, texto);
	if (!std::cin.fail()) {
		resolver(texto);
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
