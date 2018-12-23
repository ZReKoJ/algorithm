// E26, Zihao Hong
// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

// función que resuelve el problema
// comentario sobre el coste, O(f(N)) coste lineal(n) (solo una vez)
int resolver(const std::vector<int>& v) {
	int max = v[0], sumatorio = v[0], contador = 1;

	for (int i = 1; i < v.size(); ++i){
		if (v[i] > max){
			max = v[i];
			contador = 1;
		}
		else if (v[i] == max)
			contador++;
		
		sumatorio += v[i];
	}

	sumatorio -= (max * contador);

	return sumatorio;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	int numValores;
	std::cin >> numValores;
	std::vector<int> v(numValores);
	for (int &valor : v)
		std::cin >> valor;

	int sumatorio = resolver(v);
	std::cout << sumatorio << '\n';
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("C:/hlocal/ZihaoHong/datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
	clock_t t = clock();
#endif 


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}