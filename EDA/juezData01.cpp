// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <stdexcept>

class t {
private:
	int hora, minuto, segundo;
public:
	t() {}
	t(int h, int m, int s) {
		if ((0 <= h && h < 24) && (0 <= m && m < 60) && (0 <= s && s < 60)) {
			hora = h; minuto = m; segundo = s;
		}
		else throw std::domain_error("ERROR");
	}
	bool operator<= (const t &that) const {
		if (hora == that.hora) {
			if (minuto == that.minuto)
				return segundo <= that.segundo;
			else return minuto < that.minuto;
		}
		else return hora < that.hora;
	}
	void print(std::ostream & out = std::cout) const {
		out << std::setfill('0') << std::setw(2) << hora << ":" << std::setw(2) << minuto << ":" << std::setw(2) << segundo;
	}
};

inline std::ostream & operator<<(std::ostream & out, t const& rhs) {
	rhs.print(out);
	return out;
}

void resolver(const std::vector<t> &v) {
	int h, m, s;
	char residuo;
	std::cin >> h >> residuo >> m >> residuo >> s;
	try {
		t tiempo = t(h, m, s);
		int i = 0;
		while (i < v.size() && !(tiempo <= v[i])) {
			++i;
		}
		if (i == v.size())
			std::cout << "NO\n";
		else
			std::cout << v[i] << '\n';
	}
	catch (const std::domain_error &e) {
		std::cout << e.what() << '\n';
	}
}

bool resuelveCaso() {
	int numTrenes, numHorarios;
	std::cin >> numTrenes >> numHorarios;
	if (!(numTrenes == 0 && numHorarios == 0)) {
		std::vector<t> v(numTrenes);
		int h, m, s;
		char residuo;
		for (int i = 0; i < numTrenes; ++i) {
			std::cin >> h >> residuo >> m >> residuo >> s;
			v[i] = t(h, m, s);
		}
		for (int i = 0; i < numHorarios; ++i)
			resolver(v);
		std::cout << "---\n";

		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}