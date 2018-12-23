
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
void resolver(vector <int> & v, int & i, int &mejor, int &act) {
	int hijo;
	scanf("%d", &hijo);
	//cin >> hijo;
	v.push_back(hijo);
	if (v[i] == 0) {
		mejor = 0;
		act = 0;
	}
	else if (v[i] == 1) {
		int mej1;
		i++;
		resolver(v, i, mej1, act);
		mejor = mej1;
		act = 0;
	}
	else {
		int yo = i;
		int hijo1 = i + 1;
		int hijo2;
		int mej1, mej2;
		int act1, act2;
		i++;
		resolver(v, i, mej1, act1);
		hijo2 = i;
		i++;
		resolver(v, i, mej2, act2);
		if (mej1 > mej2) {
			mejor = mej1;
		}
		else
			mejor = mej2;
		if (act1 < act2) {
			act = act1;
		}
		else act = act2;
		if (v[yo] == 2) {
			act++;
			if (mejor < act) {
				mejor = act;
			}

		}
	}
}


void resuelvecaso() {
	vector <int> v;
	int mejor = 0;
	int i = 0;
	int act = 0;
	resolver(v, i, mejor, act);
	//cout << mejor << endl;
	printf("%d\n", mejor);
}
int main(int argc, char** argv) {
#ifdef OoPTC
	std::ifstream in();
	auto cinbuf = std::cin.rdbuf(in.rdbuf("/home/usraux/NetBeansProjects/ejercicio/ejercicio.txt.txt"));
#endif
	int num;
	cin >> num;
	for (int i = 0; i < num; ++i) {
		resuelvecaso();
	}

	//while (resuelvecaso()){}
#ifdef oOPTC
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

