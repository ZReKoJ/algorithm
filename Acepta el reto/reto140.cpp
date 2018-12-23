#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

void resolver(int numero, int &suma) {
	if (numero >= 10) {
		resolver(numero / 10, suma);
		int resto = numero % 10;
		suma += resto;
		printf(" + %d", resto);
	}
	else {
		printf("%d", numero);
		suma = numero;
	}
}

bool resuelveCaso() {
	int num, suma;
	scanf("%d", &num);

	if (num >= 0) {
		resolver(num, suma);
		printf(" = %d\n", suma);
		return true;
	}
	else return false;
}

int main() {
	while (resuelveCaso()){}

	return 0;
}