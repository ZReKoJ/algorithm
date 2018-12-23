#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>

std::string resolver(int numero, const std::string &text, std::string &palabraReves) {
	std::string palabra;

	if (numero >= 0) {
		palabraReves.push_back(text.at(numero));
		palabra = resolver(numero - 1, text, palabraReves);
		palabra.push_back(text.at(numero));
		return palabra;
	}
	else return "";
}

void resuelveCaso(const std::string &text) {
	std::string palabra, palabraReves = "", textModified = "";

	for (int i = 0; i < text.length(); ++i) {
		if (text.at(i) != ' ') {
			textModified.push_back(tolower(text.at(i)));
		}
	}

	palabra = resolver(textModified.length() - 1, textModified, palabraReves);

	if (palabra == palabraReves)
		printf("SI\n");
	else printf("NO\n");
}

int main() {
	// Hay que comentarlo para acepta el reto
	/*srand(time(NULL));
	std::ifstream in("d:/Processing/C++/Acepta el Reto/Acepta el Reto/datosReto.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();//*/

	std::string text = "";
	getline(std::cin, text);
	while (text != "XXX") {
		resuelveCaso(text);
		getline(std::cin, text);
	}

	// Hay que comentarlo para acepta el reto
	/*std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';

	system("PAUSE");//*/

	return 0;
}