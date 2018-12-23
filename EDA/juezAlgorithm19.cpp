// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

/*
filas: mediante un auxiliar se intercambia valores
columnas: mediante un auxiliar se intercambia valores
cruz: se hace 4 casos, de los cuales se sumao se resta hasta que llega al tope descrito
rotarFila: se rota mediante un auxiliar
rotarCol: se rota mediante un auxiliar

Coste Implementacion lineal
*/

void filas(std::vector<std::vector<int>>& m) {
	int a, b, aux;
	std::cin >> a >> b;
	--a; --b;

	for (int i = 0; i < m[0].size(); ++i) {
		aux = m[a][i];
		m[a][i] = m[b][i];
		m[b][i] = aux;
	}
}

void columnas(std::vector<std::vector<int>>& m) {
	int a, b, aux;
	std::cin >> a >> b;
	--a; --b;

	for (int i = 0; i < m.size(); ++i) {
		aux = m[i][a];
		m[i][a] = m[i][b];
		m[i][b] = aux;
	}
}

void cruz(std::vector<std::vector<int>>& m) {
	int f, c, d, fAux, cAux;
	std::cin >> f >> c >> d;
	--f; --c;

	m[f][c] = d;
	fAux = f; cAux = c;
	while (fAux != 0 && cAux != 0) {
		--fAux; --cAux;
		m[fAux][cAux] = d;
	}
	fAux = f; cAux = c;
	while (fAux != m.size() - 1 && cAux != m[0].size() - 1) {
		++fAux; ++cAux;
		m[fAux][cAux] = d;
	}
	fAux = f; cAux = c;
	while (fAux != 0 && cAux != m[0].size() - 1) {
		--fAux; ++cAux;
		m[fAux][cAux] = d;
	}
	fAux = f; cAux = c;
	while (fAux != m.size() - 1 && cAux != 0) {
		++fAux; --cAux;
		m[fAux][cAux] = d;
	}
}

void rotarFila(std::vector<std::vector<int>>& m) {
	int f, aux;
	std::cin >> f;

	if (f > 0) {
		--f;
		aux = m[f][m[f].size() - 1];
		for (int i = m[f].size() - 2; i >= 0; --i)
			m[f][i + 1] = m[f][i];
		m[f][0] = aux;
	}
	else if (f < 0) {
		f *= -1;
		--f;
		aux = m[f][0];
		for (int i = 1; i < m[f].size(); ++i)
			m[f][i - 1] = m[f][i];
		m[f][m[f].size() - 1] = aux;
	}
}

void rotarCol(std::vector<std::vector<int>>& m) {
	int c, aux;
	std::cin >> c;

	if (c > 0) {
		--c;
		aux = m[m.size() - 1][c];
		for (int i = m.size() - 2; i >= 0; --i)
			m[i + 1][c] = m[i][c];
		m[0][c] = aux;
	}
	else if (c < 0) {
		c *= -1;
		--c;
		aux = m[0][c];
		for (int i = 1; i < m.size(); ++i)
			m[i - 1][c] = m[i][c];
		m[m.size() - 1][c] = aux;
	}
}

void resolver(std::vector<std::vector<int>>& m) {
	int numCasos;
	std::string operacion;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) {
		std::cin >> operacion;
		if (operacion == "filas")
			filas(m);
		else if (operacion == "columnas")
			columnas(m);
		else if (operacion == "cruz")
			cruz(m);
		else if (operacion == "rotarFila")
			rotarFila(m);
		else if (operacion == "rotarCol")
			rotarCol(m);
#ifndef DOMJUDGE
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m[0].size(); ++j) {
				std::cout << m[i][j] << " ";
			}
			std::cout << '\n';
		}
		std::cout << "---\n";
#endif
	}
}

void resuelveCaso(int filas, int columnas) {
	std::vector<std::vector<int>> m(filas, std::vector<int>(columnas));
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			std::cin >> m[i][j];
		}
	}
#ifndef DOMJUDGE
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			std::cout << m[i][j] << " ";
		}
		std::cout << '\n';
	}
	std::cout << "---\n";
#endif
	resolver(m);
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			std::cout << m[i][j] << " ";
		}
		std::cout << '\n';
	}
	std::cout << "---\n";
}

int main() {
#ifndef DOMJUDGE
	//srand(time(NULL));
	std::ifstream in("d:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	int filas, columnas;
	std::cin >> filas >> columnas;
	while (filas + columnas != 0) {
		resuelveCaso(filas, columnas);
		std::cin >> filas >> columnas;
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}