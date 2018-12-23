// TAIS19, Zihao Hong
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

const int INFINITO = INT_MAX - 10000000;

#ifndef DOMJUDGE
const int ESPACIO = 3;
#endif

bool posibilidad(int longitud, const std::vector<std::pair<int, int>> &v) {
	std::vector<std::vector<bool>> m(v.size() + 1, std::vector<bool>(longitud + 1, false));
	m[0][0] = true;
	for (int i = 1; i < m.size(); ++i) {
		m[i][0] = true;
		for (int j = 1; j < m[i].size(); ++j) {
			if (j >= v[i - 1].first) 
				m[i][j] = m[i - 1][j] || m[i - 1][j - v[i - 1].first];
			else m[i][j] = m[i - 1][j];
		}
	}

#ifndef DOMJUDGE
	std::cout << std::setw(ESPACIO * 2) << " ";
	for (int i = 0; i <= longitud; ++i)
		std::cout << std::setw(ESPACIO) << i;
	std::cout << "\n";
	for (int i = 0; i < m.size(); ++i) {
		if (i == 0) std::cout << std::setw(ESPACIO) << "0" << std::setw(ESPACIO) << "0";
		else std::cout << std::setw(ESPACIO) << v[i - 1].first << std::setw(ESPACIO) << v[i - 1].second;
		for (int j = 0; j < m[i].size(); ++j)
			std::cout << std::setw(ESPACIO) << (m[i][j] ? "T" : "F");
		std::cout << "\n";
	}
#endif

	return m[v.size()][longitud];
}

long long int matematico(int longitud, const std::vector<std::pair<int, int>> &v) {
	std::vector<std::vector<long long int>> m(v.size() + 1, std::vector<long long int>(longitud + 1, 0));
	m[0][0] = 1;
	for (int i = 1; i < m.size(); ++i) {
		m[i][0] = 1;
		for (int j = 1; j < m[i].size(); ++j) {
			if (j >= v[i - 1].first)
				m[i][j] = m[i - 1][j] + m[i - 1][j - v[i - 1].first];
			else m[i][j] = m[i - 1][j];
		}
	}

#ifndef DOMJUDGE
	std::cout << "MATEMATICO\n" << std::setw(ESPACIO * 2) << " ";
	for (int i = 0; i <= longitud; ++i)
		std::cout << std::setw(ESPACIO) << i;
	std::cout << "\n";
	for (int i = 0; i < m.size(); ++i) {
		if (i == 0) std::cout << std::setw(ESPACIO) << "0" << std::setw(ESPACIO) << "0";
		else std::cout << std::setw(ESPACIO) << v[i - 1].first << std::setw(ESPACIO) << v[i - 1].second;
		for (int j = 0; j < m[i].size(); ++j)
			std::cout << std::setw(ESPACIO) << m[i][j];
		std::cout << "\n";
	}
#endif

	return m[v.size()][longitud];
}

int ingeniero(int longitud, const std::vector<std::pair<int, int>> &v) {
	std::vector<std::vector<int>> m(v.size() + 1, std::vector<int>(longitud + 1, 0));
	for (int i = 1; i <= longitud; ++i) m[0][i] = INFINITO;
	for (int i = 1; i < m.size(); ++i) {
		for (int j = 1; j < m[i].size(); ++j) {
			if (j >= v[i - 1].first)
				m[i][j] = std::min(m[i - 1][j], m[i - 1][j - v[i - 1].first] + 1);
			else m[i][j] = m[i - 1][j];
		}
	}

#ifndef DOMJUDGE
	std::cout << "INGENIERO\n" << std::setw(ESPACIO * 2) << " ";
	for (int i = 0; i <= longitud; ++i)
		std::cout << std::setw(ESPACIO) << i;
	std::cout << "\n";
	for (int i = 0; i < m.size(); ++i) {
		if (i == 0) std::cout << std::setw(ESPACIO) << "0" << std::setw(ESPACIO) << "0";
		else std::cout << std::setw(ESPACIO) << v[i - 1].first << std::setw(ESPACIO) << v[i - 1].second;
		for (int j = 0; j < m[i].size(); ++j)
			if (m[i][j] >= INFINITO) std::cout << std::setw(ESPACIO) << "#";
			else std::cout << std::setw(ESPACIO) << m[i][j];
		std::cout << "\n";
	}
#endif

	return m[v.size()][longitud];
}

int economista(int longitud, const std::vector<std::pair<int, int>> &v) {
	std::vector<std::vector<int>> m(v.size() + 1, std::vector<int>(longitud + 1, 0));
	for (int i = 1; i <= longitud; ++i) m[0][i] = INFINITO;
	for (int i = 1; i < m.size(); ++i) {
		for (int j = 1; j < m[i].size(); ++j) {
			if (j >= v[i - 1].first)
				m[i][j] = std::min(m[i - 1][j], m[i - 1][j - v[i - 1].first] + v[i - 1].second);
			else m[i][j] = m[i - 1][j];
		}
	}

#ifndef DOMJUDGE
	std::cout << "ECONOMISTA\n" << std::setw(ESPACIO * 2) << " ";
	for (int i = 0; i <= longitud; ++i)
		std::cout << std::setw(ESPACIO) << i;
	std::cout << "\n";
	for (int i = 0; i < m.size(); ++i) {
		if (i == 0) std::cout << std::setw(ESPACIO) << "0" << std::setw(ESPACIO) << "0";
		else std::cout << std::setw(ESPACIO) << v[i - 1].first << std::setw(ESPACIO) << v[i - 1].second;
		for (int j = 0; j < m[i].size(); ++j)
			if (m[i][j] >= INFINITO) std::cout << std::setw(ESPACIO) << "#";
			else std::cout << std::setw(ESPACIO) << m[i][j];
			std::cout << "\n";
	}
#endif

	return m[v.size()][longitud];
}

bool resuelveCaso() {
	int n;
	std::cin >> n;
	if (std::cin.fail()) return false;
	else {
		int longitud;
		std::cin >> longitud;
		std::vector<std::pair<int, int>> v(n);
		for (int i = 0; i < n; ++i)
			std::cin >> v[i].first >> v[i].second;
		if (posibilidad(longitud, v)) {
			long long int m = matematico(longitud, v);
			int i = ingeniero(longitud, v);
			int e = economista(longitud, v);
			std::cout << "SI " << m << " " << i << " " << e << "\n";
		}
		else std::cout << "NO\n";
		return true;
	}
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	/*
	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i)
	resuelveCaso();*/
	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}