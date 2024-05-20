#pragma once
#include <vector>
#include <random>
#include "Graf.h"

class SymulowaneWyzarzanie
{

    double buforTemperatury = 0;
    double wspolczynnikChlodzenia = 0;
    double ograniczenieCzasowe = 0;
    int **macierz;
    int rozmiar;

public:

    double czasZnalezieniaRozwiazania;

    std::vector<int> rozwiazanie;
    vector<int> zastosuj();
    vector<int> losowa_permutacja(int rozmiar);
    double obliczTemperature();
    int obliczSciezke(vector<int> sciezka);
    double pobierzPrawdopodobienstwo(double roznica, double temperatura);
    SymulowaneWyzarzanie(Graf graf, int czas, double wspolczynnik);
    ~SymulowaneWyzarzanie();
    //vector<int> algorytmZachlanny();

    vector<int> algorytmZachlanny(int startowyWierzcholek);

   // vector<int> greedy(int wielkosc);

    //int znajdzNajblizszeMiasto(int miasto, const vector<bool> &odwiedzone);

    std::vector<int> getRozwiazanie() const {
        return rozwiazanie;
    }



    void resetujStan(double &temperatura, vector<int> &permutacja);

    double getCzasZnalezienia();

   // vector<int>losowa_permutacja(int _rozmiar, mt19937 &rng, uniform_int_distribution<std::mt19937::result_type> &dist);
};
