#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

bool resolver(const std::string palabra) {
	bool a = false, e = false, i = false, o = false, u = false;

	for (int j = 0; j < palabra.size(); ++j) {
		switch (palabra.at(j)) {
		case 'a': a = true; break;
		case 'e': e = true; break;
		case 'i': i = true; break;
		case 'o': o = true; break;
		case 'u': u = true; break;
		}
	}

	return a && e && i && o && u;
}

void resuelveCaso() {
	std::string palabra;
	std::cin >> palabra;
	if (resolver(palabra))
		printf("SI\n");
	else
		printf("NO\n");
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();

	/*int numValores;
	scanf("%d", &numValores);
	while (numValores > 0) {
		resuelveCaso(numValores);
		scanf("%d", &numValores);
	}*/

	//system("pause");
	return 0;
}