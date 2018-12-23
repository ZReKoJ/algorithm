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

bool resuelvecaso(){
    int num;
  	scanf("%d", &num);
    if(num != 0){
        int suma = 0;
        int valor;
        for(int i = 0; i < num; ++i){
 		 	scanf("%d", &valor);
            suma += valor;
        }
        printf("%d\n", suma);
        return true;
    }
    else return false;
}
int main(int argc, char** argv) {
    #ifndef DOMJUDGE
    std::ifstream in("");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while(resuelvecaso());
    
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    #endif
    return 0;
}

