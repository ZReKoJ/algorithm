/*
 * ejercicio.cpp
 *
 *  Created on: 25/2/2017
 *      Author: usraux
 */


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
// B
typedef struct{
    int magenta;
    int amarillo;
    int cian;
}paleta;
namespace std {

}

bool resolver(paleta &p){
    std::string s;
    cin >> s;
    for(int i = 0; i < s.length(); ++i) {
        switch(s.at(i)){
            case 'M':
                p.magenta--;
                break;
            case 'C':
                p.cian--;
                break;
            case 'A':
                p.amarillo--;
                break;
            case 'N':
                p.amarillo--;
                p.magenta--;
                p.cian--;
                break;
            case 'R':
                p.magenta--;
                p.amarillo--;
                break;
            case 'V':
                p.amarillo--;
                p.cian--;
                break;
            case 'L':
                p.magenta--;
                p.cian--;
                break;
        }
    }
    return p.magenta >=0 && p.amarillo >=0 && p.cian >=0;
}
void resuelvecaso(){
    paleta p;
    cin >> p.magenta >> p.amarillo >> p.cian;
	scanf("%d", &p.magenta);
	scanf("%d", &p.amarillo);
	scanf("%d", &p.cian);
    if(resolver(p)){
        //cout << "SI " << p.magenta << " " << p.amarillo << " " << p.cian << endl;
		printf("SI %d %d %d\n", p.magenta, p.amarillo, p.cian);
    }
    else printf("NO\n");
       // cout << "NO" << endl;
}
int main(int argc, char** argv) {
#ifdef OPTC
    std::ifstream in();
    auto cinbuf = std::cin.rdbuf(in.rdbuf("/home/usraux/NetBeansProjects/ejercicio/ejercicio.txt"));
#endif
    int numcasos;
    cin >> numcasos;
    for(int i = 0; i < numcasos;++i){
        resuelvecaso();
    }
#ifdef OPTC
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}




