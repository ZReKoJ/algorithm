
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
// K
//#define OPTC



/*bool resolver(int n){

}*/
bool resuelvecaso() {
	vector <int> v;
	int num;
	//cin >> num;
	scanf("%d", &num);
	if (num == 0)
		return false;
	while (num != 0) {
		v.push_back(num);
		//cin >> num;
		scanf("%d", &num);
	}
	sort(v.begin(), v.end());
	if (v.size() % 2 == 1) {
		bool b = true;
		vector <int> w;
		for (int i = 0; i < v.size() - 1 && b; i += 2) {
			if (v[i] == v[i + 1]) {
				w.push_back(v[i]);
			}
			else
				b = false;
		}
		if (b) {
			for (int i = 0; i < w.size(); ++i) {
				printf("%d ", w[i]);
				//cout << w[i] << " ";
			}
			cout << v[v.size() - 1];
			for (int i = w.size() - 1; i >= 0; i--) {
				printf(" %d", w[i]);
				//cout << " " << w[i];
			}
			printf("\n");
		}
		else {
			printf("NO\n");
		}
	}
	else {
		printf("NO\n");
	}

	return true;
}
int main(int argc, char** argv) {
#ifdef OPTC
	std::ifstream in();
	auto cinbuf = std::cin.rdbuf(in.rdbuf("/home/usraux/NetBeansProjects/ejercicio/ejercicio.txt.txt"));
#endif
	while (resuelvecaso()) {};
#ifdef OPTC
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

