#pragma once
#include <string>
#include "Graf.h"
#include "Sciezka.h"

class Menu
{
private:

    std::string menu = "";
    std::string plik = "";
    Graf graf;
    int czas = 0;
    Sciezka sciezka;
    double wspolczynnikTemperatury = 0;

public:

    void uruchom();
    Menu();
    ~Menu();
};
