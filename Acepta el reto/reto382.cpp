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

typedef struct{
    int entrada;
    int rango;
}wifi;
typedef wifi a[1000];
bool resolver(a v, int max, int min, int antenas, int tunel){
    bool solucion;
    for(int i = 0; i < antenas; ++i){
        if(max >= v[i].entrada - v[i].rango){
            solucion = true;
            if(max < v[i].entrada + v[i].rango){
                max = v[i].entrada + v[i].rango;
                
            }
            if(min > v[i].entrada - v[i].rango ){
                min = v[i].entrada - v[i].rango;
            }
        }
        else {
            solucion = false;
            
        }

    }
    if(max < tunel){
        return false;
    }
    if(min > 0){
        return false;
    }
    return solucion;
}
void resuelvecaso(){
    int tunel;
	scanf("%d", &tunel);
    int antenas;
	scanf("%d", &antenas);
    a v;
	scanf("%d", &v[0].entrada);
	scanf("%d", &v[0].rango);
    bool principio, fin;
    int min = v[0].entrada - v[0].rango;
    int max = v[0].entrada + v[0].rango;
    for(int i = 1; i < antenas; ++i){
		scanf("%d", &v[i].entrada);
		scanf("%d", &v[i].rango);
    }
    
    if(resolver(v, max, min, antenas, tunel)){
        printf("SI\n");
    }
    else{
        printf("NO\n");
    }
}
int main(int argc, char** argv) {
    #ifndef DOMJUDGE
    std::ifstream in("/home/usraux/NetBeansProjects/B/sample.in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numcasos;
    scanf("%d", &numcasos);
    for(int i = 0; i < numcasos; ++i)
        resuelvecaso();
    
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    #endif
    return 0;
}

