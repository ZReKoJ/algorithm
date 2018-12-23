
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <climits>

using namespace std;
// I
//#define OPTC

int rec(int n) {
	if (n < 10)
		return n;
	else {
		return (n % 10) + rec(n / 10);
	}
}

bool resolver(int n) {
	int modulo = n % 3;
	int suma = 0;
	for (int i = 0; i < modulo; ++i) {
		suma += rec(n - i);
	}

	return (suma % 3) == 0;
}
void resuelvecaso() {

	int n;
	scanf("%d", &n);
	if (resolver(n)) printf("SI\n");
	else printf("NO\n");
}
int main(int argc, char** argv) {
#ifdef OPTC
	std::ifstream in();
	auto cinbuf = std::cin.rdbuf(in.rdbuf("/home/usraux/NetBeansProjects/ejercicio/ejercicio.txt.txt"));
#endif
	int numcasos;
	cin >> numcasos;
	for (int i = 0; i < numcasos; ++i) {
		resuelvecaso();
	}
#ifdef OPTC
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

