#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

int resolver(std::vector<int> &v, int peso) {
	int inicio = 0, cont = 0, max = 0;
	for (int i = 0; i < v.size(); ++i){
		if (v[i] >= peso) {
			++cont;
		}
		if (cont == 6) {
			while (v[inicio] < peso)
				++inicio;
			++inicio;
			--cont;
		}
		if (i - inicio > max)
			max = i - inicio;
	}

	return max + 1;
}

void resuelveCaso() {
	int peso, numValores;

	scanf("%d", &peso);
	scanf("%d", &numValores);
	std::vector<int> v(numValores);
	for (int &valor : v)
		scanf("%d", &valor);

	int franja = resolver(v, peso);
	printf("%d\n", franja);
}

int main() {
	/*std::ifstream in("D:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
	clock_t t = clock();//*/

	int numCasos;
	scanf("%d", &numCasos);
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// Para restablecer entrada. Comentar para acepta el reto
	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");//*/

	return 0;
}