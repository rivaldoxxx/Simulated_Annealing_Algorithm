#pragma once
#include <string>
#define NIESKONCZONOSC 9999

using namespace std;

class Graf
{
private:

    int **macierz= nullptr;

    void czyśćMacierz();

    string opis = "";

public:
    bool wczytajZPlikuXML(const std::string& nazwaPliku);
    string getOpis();

    bool ustawNieskonczonoscNaPrzekatnej();

    bool czytajGraf(string plik);

    int pobierzLiczbeWierzcholkow();
    int** pobierzMacierz();
    void generujLosowy(int rozmiar);
    Graf();
    ~Graf();

    int liczbaWierzcholkow;

    string wypiszGraf();
};
