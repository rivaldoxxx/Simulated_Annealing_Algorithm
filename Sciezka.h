//
// Created by maciej.ilow.pwr on 14.12.2023.
//

#ifndef E2_SCIEZKA_H
#define E2_SCIEZKA_H

#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <ctime>
#include <valarray>
#include <limits>
#include <fstream>
#include "Graf.h"

using namespace std;

class Sciezka {

public:
    void zapisz(const vector<int>& sciezka1, const string& nazwaPliku);

    vector<int> odczytaj(const string& nazwaPliku);

    int liczKoszt(vector<int> Najlepsza,Graf& g);
};


#endif //E2_SCIEZKA_H
