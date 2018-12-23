#include <iostream>
using namespace std;

const int K = 31543;

int resolver(int base, int exponente) {
	if (exponente == 0)
		return 1;
	else {
		if (exponente % 2 == 1)
			return ((((resolver(base, exponente / 2) % K) * base) % K) * (resolver(base, exponente / 2) % K) % K);
		else
			return ((resolver(base, exponente / 2) % K) * ((resolver(base, exponente / 2) % K)) % K);
	}
}

int main() {
	int base, exponente;

	scanf("%d", &base);
	scanf("%d", &exponente);
	while (!(base == 0 && exponente == 0)) {
		printf("%d\n", resolver(base % K, exponente));
		scanf("%d", &base);
		scanf("%d", &exponente);
	}

	return 0;
}