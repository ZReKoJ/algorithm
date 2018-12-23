#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

/*int resolver(const std::vector<int>& v) {
	int inferior, superior;

	std::cin >> inferior;
	std::cin >> superior;

	return v[superior] - v[inferior - 1];
}*/

void resuelveCaso() {
	std::string palabra;
	std::cin >> palabra;
	std::cin >> palabra;
	std::cout << "Hola, " << palabra << "." << std::endl;
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();

	/*int numValores;
	std::cin >> numValores;
	while (numValores > 0) {
		resuelveCaso(numValores);
	}*/

	//system("pause");
	return 0;
}