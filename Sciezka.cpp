//
// Created by maciej.ilow.pwr on 14.12.2023.
//

#include "Sciezka.h"

void Sciezka::zapisz(const vector<int> &sciezka1, const string &nazwaPliku) {
    ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cerr << "Nie można otworzyc pliku do zapisu." << endl;
        return;
    }

    plik << sciezka1.size() << endl;
    for (int miasto : sciezka1) {
        cout << miasto << " -> ";
        plik << miasto << endl;
    }

    cout << "Zapisano sciezke do pliku: " << nazwaPliku << endl;
    plik.close();
}

vector<int> Sciezka::odczytaj(const string &nazwaPliku) {
    ifstream plik(nazwaPliku);
    vector<int> sciezka;

    if (!plik.is_open()) {
        cerr << "Nie można otworzyc pliku do odczytu." << endl;
        return sciezka;
    }

    int wielkoscSciezki;
    plik >> wielkoscSciezki;

    for (int i = 0; i < wielkoscSciezki; ++i) {
        int miasto;
        plik >> miasto;
        sciezka.push_back(miasto);
    }

    cout << "Odczytano sciezke z pliku: " << nazwaPliku << endl;
    plik.close();
    return sciezka;
}

int Sciezka::liczKoszt(vector<int> Najlepsza, Graf &g) {

    int koszt = 0;

    for(int i = 0; i < Najlepsza.size() - 1; ++i){
        koszt += g.pobierzMacierz()[Najlepsza[i]][Najlepsza[i + 1]];
    }
    koszt += g.pobierzMacierz()[Najlepsza[g.liczbaWierzcholkow - 1]][Najlepsza[0]];

    return koszt;
}
