
#include "SymulowaneWyzarzanie.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <ctime>
#include <valarray>
#include <limits>
#include <random>
#include <iomanip>

vector<int> SymulowaneWyzarzanie::zastosuj() {


//    std::random_device dev;
//    std::mt19937 rng(dev());
//    std::uniform_int_distribution<std::mt19937::result_type> dist(0, rozmiar - 1); // Zakres od 0 do rozmiar - 1


    std::vector<int> permutacja = algorytmZachlanny(0);
    std::vector<int> nastepna;
    std::vector<int> najlepsze(permutacja);
    //int wynik=obliczSciezke(permutacja);
    std::cout << "KosztGreedy: " << obliczSciezke(permutacja) << endl;
//    for (int i = 0; i < rozmiar; i++) {
//        cout << permutacja[i] << " -> ";
//        if (i % 10 == 0) {
//            cout << endl;
//        }
//    }
    clock_t start;
    int pierwszaDoZamiany;
    int drugaDoZamiany;
    double temperatura = buforTemperatury;
    int kosztNajlepszy = obliczSciezke(permutacja);
    int kosztAktualny = kosztNajlepszy;
    double czas = 0;

    start = clock();

    //nastepna= losowa_permutacja(rozmiar);
    //srand(time(NULL));
    while (true) {
        while (temperatura >= 0.0000001 && czas <= ograniczenieCzasowe) {
            int kroki = (9 * rozmiar);

            //nastepna = permutacja;

            //int kosztNastepnej = obliczSciezke(nastepna);
            //permutacja=permutacjaPoczatkowa(rozmiar);
            for (int i = kroki; i > 0; i--) {
                nastepna = permutacja;
                do {
                    pierwszaDoZamiany = rand() % rozmiar;
                    drugaDoZamiany = rand() % rozmiar;
                } while (pierwszaDoZamiany == drugaDoZamiany);

                std::swap(nastepna[pierwszaDoZamiany], nastepna[drugaDoZamiany]);

                int kosztNastepnej = obliczSciezke(nastepna);

                //cout << kosztNastepnej << endl;
                int roznica = kosztNastepnej - kosztAktualny;

                if (roznica < 0) {
                    kosztAktualny = kosztNastepnej;
                    permutacja = nastepna;


                    if (kosztAktualny < kosztNajlepszy) {
                        kosztNajlepszy = kosztAktualny;
                        najlepsze = permutacja;
                       // std::cout << "Znaleziono lepsze rozwiazanie:" << kosztNajlepszy<<endl;
                        czasZnalezieniaRozwiazania = (clock() - start) / (double) CLOCKS_PER_SEC;
                    }
                } else if (pobierzPrawdopodobienstwo(roznica, temperatura) >
                           (((double) rand()) / (double) (RAND_MAX))) {
                    //cout << "Wykonuje";
                    kosztAktualny = kosztNastepnej;
                    permutacja = nastepna;

                }
//                else {
//                    std::swap(nastepna[pierwszaDoZamiany], nastepna[drugaDoZamiany]);
//                }

                czas = (clock() - start) / (double) CLOCKS_PER_SEC;

                if (czas > ograniczenieCzasowe) {
                    cout << "Sciezka: ";
                    for (int d = 0; d < rozmiar; d++) {
                        cout << najlepsze[d] << " ";
                    }

                    cout << "\nKoszt: " << kosztNajlepszy << endl;
                    cout << "Znaleziono po: " << czasZnalezieniaRozwiazania << " s " << endl;
                    cout << "Temperatura koncowa: " << temperatura << endl;
                    cout << "Exp(-1/Tk): " << std::fixed << std::setprecision(5) << exp(-1 / temperatura) << " s"
                         << endl;

                    cout << endl;
                    rozwiazanie = najlepsze;
                    return najlepsze;

                }
            }
            temperatura *= wspolczynnikChlodzenia;
        }
        resetujStan(temperatura, permutacja);

    }
}

void SymulowaneWyzarzanie::resetujStan(double &temperatura, std::vector<int> &permutacja) {
    temperatura = buforTemperatury;
    permutacja = losowa_permutacja(rozmiar);
}

//double SymulowaneWyzarzanie::randomFormalDouble(){
//    std::random_device rd;
//    std::mt19937 rng(rd());
//    std::uniform_real_distribution<> distr(0.0,1.0);
//    return distr(rng);
//}
vector<int> SymulowaneWyzarzanie::algorytmZachlanny(int startowyWierzcholek) {
    const int INF = std::numeric_limits<int>::max();
    vector<int> sciezka;
    vector<bool> odwiedzone(rozmiar, false);
    int obecnyWierzcholek = startowyWierzcholek;

    sciezka.push_back(obecnyWierzcholek);
    odwiedzone[obecnyWierzcholek] = true;

    while (sciezka.size() < rozmiar) {
        int najblizszyWierzcholek = -1;
        int najkrotszaOdleglosc = INF;

        for (int i = 0; i < rozmiar; ++i) {
            if (!odwiedzone[i] && macierz[obecnyWierzcholek][i] < najkrotszaOdleglosc) {
                najblizszyWierzcholek = i;
                najkrotszaOdleglosc = macierz[obecnyWierzcholek][i];
            }
        }

        if (najblizszyWierzcholek == -1) { // Nie znaleziono żadnej nieodwiedzonej krawędzi
            break;
        }

        sciezka.push_back(najblizszyWierzcholek);
        odwiedzone[najblizszyWierzcholek] = true;
        obecnyWierzcholek = najblizszyWierzcholek;
    }

    return sciezka;
}

//vector<int> SymulowaneWyzarzanie::greedy(int wielkosc) {
//    vector<int> sciezkaZachlanna;
//    sciezkaZachlanna.push_back(0);  // Dodaj pierwsze miasto do ścieżki
//
//    vector<bool> odwiedzone(wielkosc, false);
//    odwiedzone[0] = true;
//
//    for (int i = 1; i < wielkosc; ++i) {
//        int aktualneMiasto = sciezkaZachlanna.back();
//        int najblizszeMiasto = znajdzNajblizszeMiasto(aktualneMiasto, odwiedzone);
//        sciezkaZachlanna.push_back(najblizszeMiasto);
//        odwiedzone[najblizszeMiasto] = true;
//    }
//
//    return sciezkaZachlanna;
//}

//int SymulowaneWyzarzanie::znajdzNajblizszeMiasto(int miasto, const vector<bool> &odwiedzone) {
//    int najblizszeMiasto = -1;
//    int najkrotszaOdleglosc = numeric_limits<int>::max();
//    for (int i = 0; i < rozmiar; ++i) {
//        if (!odwiedzone[i] && i != miasto && macierz[miasto][i] < najkrotszaOdleglosc) {
//            najblizszeMiasto = i;
//            najkrotszaOdleglosc = macierz[miasto][i];
//        }
//    }
//    return najblizszeMiasto;
//}

vector<int> SymulowaneWyzarzanie::losowa_permutacja(int rozmiar) {
    std::vector<int> temp;
    temp.reserve(rozmiar);

    for (int i = 0; i < rozmiar; i++) {
        temp.push_back(i);
    }

    random_shuffle(temp.begin(), temp.end());
    return temp;
}

double SymulowaneWyzarzanie::obliczTemperature() {
    vector<int> sciezkaT;

    int pierwszaDoZamiany;
    int drugiDoZamiany;

    int delta = 0;
    int suma = 0;

    for (int i = 0; i < 100; i++) {
        do {
            pierwszaDoZamiany = rand() % rozmiar;
            drugiDoZamiany = rand() % rozmiar;
        } while (pierwszaDoZamiany == drugiDoZamiany);

        sciezkaT = losowa_permutacja(rozmiar);
        vector<int> sasiad(sciezkaT);

        std::swap(sasiad[pierwszaDoZamiany], sasiad[drugiDoZamiany]);

        delta = fabs(obliczSciezke(sciezkaT) - obliczSciezke(sasiad));
        suma += delta;

    }

    suma /= 100;

    return (-1 * suma) / log(0.25);

}

int SymulowaneWyzarzanie::obliczSciezke(vector<int> sciezka) {
    int koszt = 0;

    for (int i = 0; i < sciezka.size() - 1; ++i) {
        koszt += macierz[sciezka[i]][sciezka[i + 1]];
    }
    koszt += macierz[sciezka[rozmiar - 1]][sciezka[0]];

    return koszt;
}

double SymulowaneWyzarzanie::pobierzPrawdopodobienstwo(double roznica, double temperatura) {

    return exp(-roznica / temperatura);
}

double SymulowaneWyzarzanie::getCzasZnalezienia() {
    return czasZnalezieniaRozwiazania;
}

SymulowaneWyzarzanie::SymulowaneWyzarzanie(Graf graf, int czas, double wspolczynnik) {
    macierz = graf.pobierzMacierz();
    rozmiar = graf.pobierzLiczbeWierzcholkow();
    ograniczenieCzasowe = czas;
    wspolczynnikChlodzenia = wspolczynnik;
    buforTemperatury = obliczTemperature();
   // cout << obliczTemperature();
}

SymulowaneWyzarzanie::~SymulowaneWyzarzanie() {
}

//double SymulowaneWyzarzanie::getCzasZnalezienia() {
//    return czasZnalezieniaRozwiazania;
//}


