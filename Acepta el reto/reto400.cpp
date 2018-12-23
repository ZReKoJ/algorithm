
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
/*string s;
cin >> s;
if(cin.fail())
return false;
int actual = 0;
int acumulado = 0;
bool b = false;
bool pared = false;
int contador = 0;
for(int i = 0; i < s.size(); ++i){
if(s.at(i) == '.'){
if(!b){
actual = 0;
if(i == 0 || i == s.size()-1){
pared = true;
}
b = true;
}
else
actual++;
}
else{
contador++;
if(acumulado < actual / 2 && !pared){
acumulado = actual / 2;
}
else if(acumulado < actual && pared){
acumulado = actual;
}
b = false;
pared = false;
}
}
if( contador == 0){
acumulado = actual;
}
cout << acumulado << endl;*/



bool resuelvecaso() {
	string s;
	cin >> s;
	if (cin.fail())
		return false;
	int x = 0, y = 0, ini = 0;
	int max = 0;
	while (ini < s.size() && s.at(ini) == '.') {
		++ini;
	}
	y = ini;
	max = ini - 1;
	for (int i = ini + 1; i < s.size(); ++i) {
		if (s.at(i) != '.') {
			x = y;
			y = i;
			if (max < ((y - x) / 2) - 1) {
				max = ((y - x) / 2) - 1;
			}
		}
	}
	x = y;
	y = s.size() - 1;
	if (max < ((y - x)) - 1) {
		max = ((y - x)) - 1;
	}
	//cout << max << endl;
	printf("%d\n", max);
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

