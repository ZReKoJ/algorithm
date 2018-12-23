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
int resolver(vector <int> const & v){
    vector <int> w(v.size());
    int min = v[v.size() -1];
    w[v.size()-1] = min;
    for(int i = v.size() - 2; i >= 0; --i){
        if(v[i] < min){
            min = v[i];
        }
        w[i] = min;
    }
    int max = v[0] - w[1];
    for(int i = 1; i < w.size() - 1; ++i){
        if(v[i] - w[i+1] > max){
            max = v[i] - w[i+1];
        }
    }
    return max;
}
void resuelvecaso(){
    int n;
    scanf("%d", &n);
    vector <int> v(n);
    for(int i = 0; i < n; ++i){
		scanf("%d", &v[i]);
    }
    int sol = resolver(v);
    printf("%d\n", sol);
    
}
int main(int argc, char** argv) {
    #ifndef DOMJUDGE
    std::ifstream in("/home/usraux/NetBeansProjects/D/sample.in.txt");
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

