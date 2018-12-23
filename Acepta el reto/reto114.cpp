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
	int num;
	scanf("%d", &num);

	switch (num) {
	case 0: num = 1; break;
	case 1: num = 1; break;
	case 2: num = 2; break;
	case 3: num = 6; break;
	case 4: num = 4; break;
	default: num = 0;
	}

	printf("%d\n", num);
}

int main() {
	int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	/*int numValores;
	std::cin >> numValores;
	while (numValores != 0) {
	resuelveCaso(numValores);
	std::cin >> numValores;
	}*/

	//system("pause");
	return 0;
}