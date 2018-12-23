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

void resuelveCaso(int numValores) {
	numValores %= 2;
	if (numValores == 1)
		printf("IZQUIERDA\n");
	else
		printf("DERECHA\n");
}

int main() {
	/*int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; i++)
	resuelveCaso();*/

	int numValores;
	scanf("%d", &numValores);
	while (numValores != 0) {
		resuelveCaso(numValores);
		scanf("%d", &numValores);
	}

	//system("pause");
	return 0;
}