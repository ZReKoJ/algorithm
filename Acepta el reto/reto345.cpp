#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

bool check(std::vector<bool>& v) {
	bool correcto = true;

	for (int i = 0; i < 9; ++i) {
		correcto = correcto && v[i];
		v[i] = false;
	}

	return correcto;
}

void resolver(const std::vector<std::vector<int>>& m) {
	std::vector<bool> v(9);
	v = { false, false, false, false, false, false, false, false, false };
	bool correcto = true;

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			v[m[i][j] - 1] = true;
		}
		correcto = correcto && check(v);
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			v[m[j][i] - 1] = true;
		}
		correcto = correcto && check(v);
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				v[m[((i % 3) * 3) + j][((i / 3) * 3) + k] - 1] = true;
			}
		}
		correcto = correcto && check(v);
	}

	if (correcto)
		printf("SI\n");
	else
		printf("NO\n");
}

void resuelveCaso() {
	std::vector<std::vector<int>> m(9, std::vector<int>(9));
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			scanf("%d", &m[i][j]);

	resolver(m);
}

int main() {
	/*std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
	clock_t t = clock();*/

	int numCasos;
	scanf("%d", &numCasos);
	//std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	/*int numValores;
	scanf("%d", &numValores);
	while (numValores > 0) {
	resuelveCaso(numValores);
	scanf("%d", &numValores);
	}*/

	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << std::endl;
	system("PAUSE");*/
	return 0;
}