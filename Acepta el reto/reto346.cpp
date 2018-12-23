#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

int resolver(const std::vector<int> &v, int periodo) {
	int max = 0, suma = 0, ini = 0, fin = 0;

	while (fin < v.size()) {
		if (v[fin] - v[ini] < periodo) {
			++suma;
			if (suma > max)
				max = suma;
			++fin;
		}
		else {
			--suma;
			++ini;
		}
	}

	return max;
}

bool resuelveCaso() {
	int numValores, periodo;

	//std::cin >> numValores >> periodo;
	scanf("%d", &numValores);
	scanf("%d", &periodo);
	if (numValores == 0 && periodo == 0)
		return false;
	else {
		std::vector<int> v(numValores);
		for (int &valor : v)
			scanf("%d", &valor);
		int max = resolver(v, periodo);
		printf("%d\n", max); 
		return true;
	}
}

int main() {
	// Hay que comentarlo para acepta el reto
	/*srand(time(NULL));
	std::ifstream in("d:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();//*/

	while (resuelveCaso()){}

	// Hay que comentarlo para acepta el reto
	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';

	system("PAUSE");//*/

	return 0;
}