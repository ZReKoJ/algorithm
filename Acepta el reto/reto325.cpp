#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

std::string resolver(int chocolate, int vainilla, std::string palabra) {
	std::string text;
	if (chocolate > 0) {
		palabra.push_back('C');
		chocolate;
		text += resolver(chocolate - 1, vainilla, palabra);
		palabra.pop_back();
	}
	if (vainilla > 0) {
		palabra.push_back('V');
		text += resolver(chocolate, vainilla - 1, palabra);
		palabra.pop_back();
	}
	if (chocolate + vainilla == 0) {
		palabra.push_back(' ');
		text += palabra;
	}

	return text;
}

void resuelveCaso() {
	std::string palabra, text;
	int chocolate, vainilla;
	scanf("%d", &chocolate);
	scanf("%d", &vainilla);
	text += resolver(chocolate, vainilla, palabra);
	text.pop_back();
	std::cout << text << '\n';
}

int main() {
	/*srand(time(NULL));
	std::ifstream in("d:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();*/

	int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();

	/*int numValores;
	//scanf("%d", &numValores);
	std::cin >> numValores;
	while (numValores != 0) {
		resuelveCaso(numValores);
		//scanf("%d", &numValores);
		std::cin >> numValores;
	}*/

	//while (!resuelveCaso()) {}

	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");*/

	return 0;
}