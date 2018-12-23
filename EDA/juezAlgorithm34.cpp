// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

/*
Primero se recorre cada una de las ramas haciendo sus calculos correspondientes
Despues ver si es correcto la operacion realizada
Despues ver si se ha conseguido la solucion y se busca el mejor para guardarlo en min
2 Estimaciones
1.- La de sumar lo llevado mas el camino mas corto del lugar actual hasta el final y comparar con el minimo
2.- Sacar el camino mas corto en teoria y comparar con el minimo
3.- Elegir antes de entrar en la recursion la direccion mas rapida
*/

//#define RKJ

typedef struct {
	int iniX;
	int iniY;
	int actX;
	int actY;
	int finX;
	int finY;
} tPos;

bool esValido(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, const tPos &pos, const int &min, const int &menor, const int &valorAnterior) {
	return ((!b[pos.actY][pos.actX]) && (abs(valorAnterior - m[pos.actY][pos.actX]) <= hMax) && (((abs(pos.actX - pos.finX) + abs(pos.actY - pos.finY)) + menor) < min));
}

bool resolverDchInf(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, tPos &pos, int &min, int menor, const int &minTeorico, const int &stage) {
	int valorAnterior, xAnterior, yAnterior;
	bool valido = false;

	for (int i = 0; i < 4; ++i) {
#ifdef RKJ
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				if (b[i][j])
					std::cout << m[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << '\n';
		}
		std::cout << "DchInf " << pos.actY << " " << pos.actX << "  --> " << m[pos.actY][pos.actX] << '\n';
		std::cout << "min: " << min << " - menor: " << menor << " - minTeorico: " << minTeorico << "\n";
		std::cout << "Inicio: " << pos.iniY << " " << pos.iniX << " - Final: " << pos.finY << " " << pos.finX << '\n';
		system("pause");
#endif
		valorAnterior = m[pos.actY][pos.actX];
		xAnterior = pos.actX; yAnterior = pos.actY;

		if (min == minTeorico)
			return true;
		else if (i == 0 && pos.actX < m.size() - 1)
			++pos.actX;
		else if (i == 1 && pos.actY < m.size() - 1)
			++pos.actY;
		else if (i == 2 && pos.actX > 0)
			--pos.actX;
		else if (i == 3 && pos.actY > 0)
			--pos.actY;

		if (esValido(m, b, hMax, pos, min, menor, valorAnterior)) {
			++menor;
			b[pos.actY][pos.actX] = true;
			if (pos.actX == pos.finX && pos.actY == pos.finY) {
				if (menor < min)
					min = menor;
				valido = true;
			}
			else if (menor == stage)
				valido = false;
			else {
				valido = resolverDchInf(m, b, hMax, pos, min, menor, minTeorico, stage) || valido;
			}
			b[pos.actY][pos.actX] = false;
			--menor;
		}

		pos.actX = xAnterior; pos.actY = yAnterior;
	}

	return valido;
}

bool resolverInfIzq(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, tPos &pos, int &min, int menor, const int &minTeorico, const int &stage) {
	int valorAnterior, xAnterior, yAnterior;
	bool valido = false;

	for (int i = 0; i < 4; ++i) {
#ifdef RKJ
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				if (b[i][j])
					std::cout << m[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << '\n';
		}
		std::cout << "InfIzq " << pos.actY << " " << pos.actX << "  --> " << m[pos.actY][pos.actX] << '\n';
		std::cout << "min: " << min << " - menor: " << menor << " - minTeorico: " << minTeorico << "\n";
		std::cout << "Inicio: " << pos.iniY << " " << pos.iniX << " - Final: " << pos.finY << " " << pos.finX << '\n';
		system("pause");
#endif
		valorAnterior = m[pos.actY][pos.actX];
		xAnterior = pos.actX; yAnterior = pos.actY;

		if (min == minTeorico)
			return true;
		else if (i == 0 && pos.actY < m.size() - 1)
			++pos.actY;
		else if (i == 1 && pos.actX > 0)
			--pos.actX;
		else if (i == 2 && pos.actY > 0)
			--pos.actY;
		else if (i == 3 && pos.actX < m.size() - 1)
			++pos.actX;

		if (esValido(m, b, hMax, pos, min, menor, valorAnterior)) {
			++menor;
			b[pos.actY][pos.actX] = true;
			if (pos.actX == pos.finX && pos.actY == pos.finY) {
				if (menor < min)
					min = menor;
				valido = true;
			}
			else if (menor == stage)
				valido = false;
			else {
				valido = resolverInfIzq(m, b, hMax, pos, min, menor, minTeorico, stage) || valido;
			}
			b[pos.actY][pos.actX] = false;
			--menor;
		}

		pos.actX = xAnterior; pos.actY = yAnterior;
	}

	return valido;
}

bool resolverIzqSup(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, tPos &pos, int &min, int menor, const int &minTeorico, const int &stage) {
	int valorAnterior, xAnterior, yAnterior;
	bool valido = false;

	for (int i = 0; i < 4; ++i) {
#ifdef RKJ
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				if (b[i][j])
					std::cout << m[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << '\n';
		}
		std::cout << "IzqSup " << pos.actY << " " << pos.actX << "  --> " << m[pos.actY][pos.actX] << '\n';
		std::cout << "min: " << min << " - menor: " << menor << " - minTeorico: " << minTeorico << "\n";
		std::cout << "Inicio: " << pos.iniY << " " << pos.iniX << " - Final: " << pos.finY << " " << pos.finX << '\n';
		system("pause");
#endif
		valorAnterior = m[pos.actY][pos.actX];
		xAnterior = pos.actX; yAnterior = pos.actY;

		if (min == minTeorico)
			return true;
		else if (i == 0 && pos.actX > 0)
			--pos.actX;
		else if (i == 1 && pos.actY > 0)
			--pos.actY;
		else if (i == 2 && pos.actX < m.size() - 1)
			++pos.actX;
		else if (i == 3 && pos.actY < m.size() - 1)
			++pos.actY;

		if (esValido(m, b, hMax, pos, min, menor, valorAnterior)) {
			++menor;
			b[pos.actY][pos.actX] = true;
			if (pos.actX == pos.finX && pos.actY == pos.finY) {
				if (menor < min)
					min = menor;
				valido = true;
			}
			else if (menor == stage)
				valido = false;
			else {
				valido = resolverIzqSup(m, b, hMax, pos, min, menor, minTeorico, stage) || valido;
			}
			b[pos.actY][pos.actX] = false;
			--menor;
		}

		pos.actX = xAnterior; pos.actY = yAnterior;
	}

	return valido;
}

bool resolverSupDch(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, tPos &pos, int &min, int menor, const int &minTeorico, const int &stage) {
	int valorAnterior, xAnterior, yAnterior;
	bool valido = false;

	for (int i = 0; i < 4; ++i) {
#ifdef RKJ
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				if (b[i][j])
					std::cout << m[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << '\n';
		}
		std::cout << "SupDch " << pos.actY << " " << pos.actX << "  --> " << m[pos.actY][pos.actX] << '\n';
		std::cout << "min: " << min << " - menor: " << menor << " - minTeorico: " << minTeorico << "\n";
		std::cout << "Inicio: " << pos.iniY << " " << pos.iniX << " - Final: " << pos.finY << " " << pos.finX << '\n';
		system("pause");
#endif
		valorAnterior = m[pos.actY][pos.actX];
		xAnterior = pos.actX; yAnterior = pos.actY;

		if (min == minTeorico)
			return true;
		else if (i == 0 && pos.actY > 0)
			--pos.actY;
		else if (i == 1 && pos.actX < m.size() - 1)
			++pos.actX;
		else if (i == 2 && pos.actY < m.size() - 1)
			++pos.actY;
		else if (i == 3 && pos.actX > 0)
			--pos.actX;

		if (esValido(m, b, hMax, pos, min, menor, valorAnterior)) {
			++menor;
			b[pos.actY][pos.actX] = true;
			if (pos.actX == pos.finX && pos.actY == pos.finY) {
				if (menor < min)
					min = menor;
				valido = true;
			}
			else if (menor == stage)
				valido = false;
			else {
				valido = resolverSupDch(m, b, hMax, pos, min, menor, minTeorico, stage) || valido;
			}
			b[pos.actY][pos.actX] = false;
			--menor;
		}

		pos.actX = xAnterior; pos.actY = yAnterior;
	}

	return valido;
}

bool resolverDchSup(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, tPos &pos, int &min, int menor, const int &minTeorico, const int &stage) {
	int valorAnterior, xAnterior, yAnterior;
	bool valido = false;

	for (int i = 0; i < 4; ++i) {
#ifdef RKJ
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				if (b[i][j])
					std::cout << m[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << '\n';
		}
		std::cout << "DchSup " << pos.actY << " " << pos.actX << "  --> " << m[pos.actY][pos.actX] << '\n';
		std::cout << "min: " << min << " - menor: " << menor << " - minTeorico: " << minTeorico << "\n";
		std::cout << "Inicio: " << pos.iniY << " " << pos.iniX << " - Final: " << pos.finY << " " << pos.finX << '\n';
		system("pause");
#endif
		valorAnterior = m[pos.actY][pos.actX];
		xAnterior = pos.actX; yAnterior = pos.actY;

		if (min == minTeorico)
			return true;
		else if (i == 0 && pos.actX < m.size() - 1)
			++pos.actX;
		else if (i == 1 && pos.actY > 0)
			--pos.actY;
		else if (i == 2 && pos.actX > 0)
			--pos.actX;
		else if (i == 3 && pos.actY < m.size() - 1)
			++pos.actY;

		if (esValido(m, b, hMax, pos, min, menor, valorAnterior)) {
			++menor;
			b[pos.actY][pos.actX] = true;
			if (pos.actX == pos.finX && pos.actY == pos.finY) {
				if (menor < min)
					min = menor;
				valido = true;
			}
			else if (menor == stage)
				valido = false;
			else {
				valido = resolverDchSup(m, b, hMax, pos, min, menor, minTeorico, stage) || valido;
			}
			b[pos.actY][pos.actX] = false;
			--menor;
		}

		pos.actX = xAnterior; pos.actY = yAnterior;
	}

	return valido;
}

bool resolverSupIzq(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, tPos &pos, int &min, int menor, const int &minTeorico, const int &stage) {
	int valorAnterior, xAnterior, yAnterior;
	bool valido = false;

	for (int i = 0; i < 4; ++i) {
#ifdef RKJ
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				if (b[i][j])
					std::cout << m[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << '\n';
		}
		std::cout << "SupIzq " << pos.actY << " " << pos.actX << "  --> " << m[pos.actY][pos.actX] << '\n';
		std::cout << "min: " << min << " - menor: " << menor << " - minTeorico: " << minTeorico << "\n";
		std::cout << "Inicio: " << pos.iniY << " " << pos.iniX << " - Final: " << pos.finY << " " << pos.finX << '\n';
		system("pause");
#endif
		valorAnterior = m[pos.actY][pos.actX];
		xAnterior = pos.actX; yAnterior = pos.actY;

		if (min == minTeorico)
			return true;
		else if (i == 0 && pos.actY > 0)
			--pos.actY;
		else if (i == 1 && pos.actX > 0)
			--pos.actX;
		else if (i == 2 && pos.actY < m.size() - 1)
			++pos.actY;
		else if (i == 3 && pos.actX < m.size() - 1)
			++pos.actX;

		if (esValido(m, b, hMax, pos, min, menor, valorAnterior)) {
			++menor;
			b[pos.actY][pos.actX] = true;
			if (pos.actX == pos.finX && pos.actY == pos.finY) {
				if (menor < min)
					min = menor;
				valido = true;
			}
			else if (menor == stage)
				valido = false;
			else {
				valido = resolverSupIzq(m, b, hMax, pos, min, menor, minTeorico, stage) || valido;
			}
			b[pos.actY][pos.actX] = false;
			--menor;
		}

		pos.actX = xAnterior; pos.actY = yAnterior;
	}

	return valido;
}

bool resolverIzqInf(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, tPos &pos, int &min, int menor, const int &minTeorico, const int &stage) {
	int valorAnterior, xAnterior, yAnterior;
	bool valido = false;

	for (int i = 0; i < 4; ++i) {
#ifdef RKJ
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				if (b[i][j])
					std::cout << m[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << '\n';
		}
		std::cout << "IzqInf " << pos.actY << " " << pos.actX << "  --> " << m[pos.actY][pos.actX] << '\n';
		std::cout << "min: " << min << " - menor: " << menor << " - minTeorico: " << minTeorico << "\n";
		std::cout << "Inicio: " << pos.iniY << " " << pos.iniX << " - Final: " << pos.finY << " " << pos.finX << '\n';
		system("pause");
#endif
		valorAnterior = m[pos.actY][pos.actX];
		xAnterior = pos.actX; yAnterior = pos.actY;

		if (min == minTeorico)
			return true;
		else if (i == 0 && pos.actX > 0)
			--pos.actX;
		else if (i == 1 && pos.actY < m.size() - 1)
			++pos.actY;
		else if (i == 2 && pos.actX < m.size() - 1)
			++pos.actX;
		else if (i == 3 && pos.actY > 0)
			--pos.actY;

		if (esValido(m, b, hMax, pos, min, menor, valorAnterior)) {
			++menor;
			b[pos.actY][pos.actX] = true;
			if (pos.actX == pos.finX && pos.actY == pos.finY) {
				if (menor < min)
					min = menor;
				valido = true;
			}
			else if (menor == stage)
				valido = false;
			else {
				valido = resolverIzqInf(m, b, hMax, pos, min, menor, minTeorico, stage) || valido;
			}
			b[pos.actY][pos.actX] = false;
			--menor;
		}

		pos.actX = xAnterior; pos.actY = yAnterior;
	}

	return valido;
}

bool resolverInfDch(const std::vector<std::vector<int>> &m, std::vector<std::vector<bool>> &b, const int &hMax, tPos &pos, int &min, int menor, const int &minTeorico, const int &stage) {
	int valorAnterior, xAnterior, yAnterior;
	bool valido = false;

	for (int i = 0; i < 4; ++i) {
#ifdef RKJ
		for (int i = 0; i < m.size(); ++i) {
			for (int j = 0; j < m.size(); ++j) {
				if (b[i][j])
					std::cout << m[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << '\n';
		}
		std::cout << "InfDch " << pos.actY << " " << pos.actX << "  --> " << m[pos.actY][pos.actX] << '\n';
		std::cout << "min: " << min << " - menor: " << menor << " - minTeorico: " << minTeorico << "\n";
		std::cout << "Inicio: " << pos.iniY << " " << pos.iniX << " - Final: " << pos.finY << " " << pos.finX << '\n';
		system("pause");
#endif
		valorAnterior = m[pos.actY][pos.actX];
		xAnterior = pos.actX; yAnterior = pos.actY;

		if (min == minTeorico)
			return true;
		else if (i == 0 && pos.actY < m.size() - 1)
			++pos.actY;
		else if (i == 1 && pos.actX < m.size() - 1)
			++pos.actX;
		else if (i == 2 && pos.actY > 0)
			--pos.actY;
		else if (i == 3 && pos.actX > 0)
			--pos.actX;

		if (esValido(m, b, hMax, pos, min, menor, valorAnterior)) {
			++menor;
			b[pos.actY][pos.actX] = true;
			if (pos.actX == pos.finX && pos.actY == pos.finY) {
				if (menor < min)
					min = menor;
				valido = true;
			}
			else if (menor == stage)
				valido = false;
			else {
				valido = resolverInfDch(m, b, hMax, pos, min, menor, minTeorico, stage) || valido;
			}
			b[pos.actY][pos.actX] = false;
			--menor;
		}

		pos.actX = xAnterior; pos.actY = yAnterior;
	}

	return valido;
}

bool resuelveCaso() {
	int numValores, hMax;
	tPos pos;

	std::cin >> numValores;
	if (!std::cin.fail()) {
		std::cin >> hMax >> pos.iniY >> pos.iniX >> pos.finY >> pos.finX; // Leyendo variables primera fila
		pos.actX = pos.iniX; pos.actY = pos.iniY;

		std::vector<std::vector<int>> m(numValores, std::vector<int>(numValores)); // Matriz de valores
		std::vector<std::vector<bool>> b(numValores, std::vector<bool>(numValores)); // Matriz de booleanos

		for (int i = 0; i < numValores; ++i) {
			for (int j = 0; j < numValores; ++j) {
				std::cin >> m[i][j]; // Leyendo variables matriz
			}
		}

		int min = numValores * numValores, stage = min; // Dando el minimo maximo
		b[pos.actY][pos.actX] = true;
		int minTeorico = abs(pos.finX - pos.iniX) + abs(pos.finY - pos.iniY) + 1; // El camino mas corto en teoria
		bool valido;

		if (pos.finX > pos.iniX && pos.finY > pos.iniY)
			valido = resolverInfDch(m, b, hMax, pos, min, 1, minTeorico, stage);
		else if (pos.finX > pos.iniX && pos.finY == pos.iniY)
			valido = resolverDchInf(m, b, hMax, pos, min, 1, minTeorico, stage);
		else if (pos.finX > pos.iniX && pos.finY < pos.iniY)
			valido = resolverSupDch(m, b, hMax, pos, min, 1, minTeorico, stage);
		else if (pos.finX == pos.iniX && pos.finY > pos.iniY)
			valido = resolverInfDch(m, b, hMax, pos, min, 1, minTeorico, stage);
		else if (pos.finX == pos.iniX && pos.finY == pos.iniY) {
			valido = true; min = 1;
		}
		else if (pos.finX == pos.iniX && pos.finY < pos.iniY)
			valido = resolverSupIzq(m, b, hMax, pos, min, 1, minTeorico, stage);
		else if (pos.finX < pos.iniX && pos.finY > pos.iniY)
			valido = resolverInfIzq(m, b, hMax, pos, min, 1, minTeorico, stage);
		else if (pos.finX < pos.iniX && pos.finY == pos.iniY)
			valido = resolverIzqSup(m, b, hMax, pos, min, 1, minTeorico, stage);
		else if (pos.finX < pos.iniX && pos.finY < pos.iniY)
			valido = resolverSupIzq(m, b, hMax, pos, min, 1, minTeorico, stage);

		if (valido)
			std::cout << min << '\n';
		else
			std::cout << "NO\n";

		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}