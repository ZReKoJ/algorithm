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
#include <cstdio>
#include <cmath>
#include <climits>
using namespace std;

#define DOMJUDGE

unsigned int mcd(unsigned int a, unsigned int b){
    if (b == 0) return a;
    else return mcd(b , a % b);
}
bool resuelvecaso(){
    int num;
	scanf("%d", &num);
    if (num != 0){
        int anterior;
        int valor;
        int sol;
		scanf("%d", &anterior);
        for (int i = 1; i < num; ++i){
            cin >> valor;
            sol = anterior * valor / mcd(anterior, valor);
            anterior = sol;
        }
        
        printf("%d\n", sol);
        
        return true;
    }
    else return false;
}
int main(int argc, char** argv) {
    #ifndef DOMJUDGE
    std::ifstream in("/home/usraux/NetBeansProjects/C/sample.in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    
        while(resuelvecaso());
    
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    #endif
    return 0;
}

