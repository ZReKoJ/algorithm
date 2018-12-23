
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
// H
//#define OPTC

bool resolver(vector <vector <bool> > &m, int & contador, int stage, int a) {
	for (int i = 1; i < m.size(); ++i) {
		for (int j = 1; j < m[0].size(); ++j) {
			if (i != j && !m[i][j]) {
				m[i][j] = true;
#ifdef OPTC
				for (int x = 1; x < m.size(); ++x) {
					for (int y = 1; y < m[0].size(); ++y) {
						cout << m[x][y] << " ";
					}
					cout << endl;
				}
				cout << endl;
#endif
				if (!m[i][0] && !m[0][j]) {
					m[i][0] = true;
					m[0][j] = true;
					if (stage < m.size() - 2) {
						if (!resolver(m, contador, stage + 1, a))
							return false;
					}
					else {
						if (contador < m.size() - a)
							contador++;
						else return false;
#ifdef OPTC
						cout << "kjdsbs\n";
#endif
					}
					m[i][0] = false;
					m[0][j] = false;
				}
				m[i][j] = false;

			}
		}
	}
	return true;
}

bool resuelvecaso() {
	int p, a;
	cin >> p;
	cin >> a;
	if (a == 0 && p == 0)
		return false;
	vector <vector <bool> > m(p + 1, vector <bool>(p + 1));
#ifdef OPTC
	for (int x = 1; x < m.size(); ++x) {
		for (int y = 1; y < m[0].size(); ++y) {
			cout << m[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif
	int pos1, pos2;
	for (int i = 0; i < a; ++i) {
		scanf("%d", &pos1);
		scanf("%d", &pos2);
		//cin >> pos1 >> pos2;
		m[pos1][pos2] = true;
		m[pos1][0] = true;
		m[0][pos2] = true;
	}
	int contador = 0;
	if (resolver(m, contador, a, a))
		printf("SI\n");
		//cout << "SI\n";
	else printf("NO\n");
		//cout << "NO\n";
	return true;
}
int main(int argc, char** argv) {
#ifdef OoPTC
	std::ifstream in();
	auto cinbuf = std::cin.rdbuf(in.rdbuf("/home/usraux/NetBeansProjects/ejercicio/ejercicio.txt.txt"));
#endif
	/*int num;
	cin >> num;
	for(int i = 0; i < num; ++i){
	resuelvecaso();
	}*/

	while (resuelvecaso()) {}
#ifdef oOPTC
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

