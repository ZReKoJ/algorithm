// TAIS19, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <list>
#include <climits>
#include <limits.h>
#include <limits>
#include <queue>
#include "PriorityQueue.h"

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (num == 0) return false;
	else {
		std::vector<std::pair<int, int>> v(num);
		for (int i = 0; i < num; ++i)
			std::cin >> v[i].first >> v[i].second;
		std::sort(v.begin(), v.end());
		PriorityQueue<int, std::less<int>> pq;
		int max = 0;
		for (int i = 0; i < v.size(); ++i) {
			while (!pq.empty() && v[i].first >= pq.top())
				pq.pop();
			pq.push(v[i].second);
			max = std::max(max, int(pq.size()));
		}
		std::cout << max << "\n";
		return true;
	}
}

/* El coste de este algoritmo es de
O(n * log n)
n es el numero de conferencias
*/
int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	/*
	int num;
	std::cin >> num;
	for (int i = 0; i < num; ++i)
	resuelveCaso();*/
	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}