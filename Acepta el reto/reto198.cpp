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
#include <stdexcept>

//#define RKJ

class pila {
private:
	std::vector<int> v;
public:
	pila() {}
	void anadir(int valor) {
		v.emplace_back(valor);
	}
	int op(char operacion) {
		int op2 = v[v.size() - 1];
		v.pop_back();
		int op1 = v[v.size() - 1];
		v.pop_back();
		int resultado;
		switch (operacion) {
		case '+': resultado = op1 + op2; break;
		case '-': resultado = op1 - op2; break;
		case '*': resultado = op1 * op2; break;
		case '/':
			if (op2 != 0)
				resultado = op1 / op2;
			else
				throw std::domain_error("ERROR");
				break;
		}
		return resultado;
	}
	int get() {
		return v[0];
	}
};

class cola {
private:
	std::vector<int> v;
public:
	cola() {}
	void anadir(int valor) {
		v.emplace_back(valor);
	}
	int op(char operacion) {
		int op2 = v[0];
		v.erase(v.begin() + 0);
		int op1 = v[0];
		v.erase(v.begin() + 0);
		int resultado;
		switch (operacion) {
		case '+': resultado = op1 + op2; break;
		case '-': resultado = op1 - op2; break;
		case '*': resultado = op1 * op2; break;
		case '/':
			if (op2 != 0)
				resultado = op1 / op2;
			else
				throw std::domain_error("ERROR");
			break;
		}
		return resultado;
	}
	int get() {
		return v[0];
	}
};

void resolver(const std::string &operaciones) {
	bool correctoP = true, correctoC = true;
	pila p;
	for (int i = 0; i < operaciones.size() && correctoP; ++i) {
		if (operaciones.at(i) == '+' || operaciones.at(i) == '-' || operaciones.at(i) == '*' || operaciones.at(i) == '/') {
			try {
				p.anadir(p.op(operaciones.at(i)));
			}
			catch (const std::domain_error &e) {
				correctoP = false;
			}
		}
		else p.anadir(int(operaciones.at(i) - 48));
	}
	cola c;
	for (int i = 0; i < operaciones.size() && correctoC; ++i) {
		if (operaciones.at(i) == '+' || operaciones.at(i) == '-' || operaciones.at(i) == '*' || operaciones.at(i) == '/') {
			try {
				c.anadir(c.op(operaciones.at(i)));
			}
			catch (const std::domain_error &e) {
				correctoC = false;
			}
		}
		else c.anadir(int(operaciones.at(i) - 48));
	}
	
	if (correctoP && correctoC) {
		int pi = p.get(), co = c.get();
		if (pi == co) {
			std::cout << pi << " = " << co << '\n';
		}
		else {
			std::cout << pi << " != " << co << '\n';
		}
	}
	else if (correctoP && !correctoC)
		std::cout << p.get() << " != ERROR\n";
	else if (!correctoP && correctoC)
		std::cout << "ERROR != " << c.get() << '\n';
	else std::cout << "ERROR = ERROR\n";
}

bool resuelveCaso() {
	std::string operaciones;
	std::cin >> operaciones;
	if (!std::cin.fail()) {
		resolver(operaciones);
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