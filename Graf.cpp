#include "Graf.h"
#include <fstream>
#include <time.h>
#include <string>
//#include "tinyxml2.h"
#include <iostream>
#include <sstream>
#include <msxml.h>

//using namespace tinyxml2;

//Graf::Graf() : liczbaWierzcholkow(0), macierz(nullptr) {}
//bool Graf::wczytajZPlikuXML(const std::string& nazwaPliku) {
//    tinyxml2::XMLDocument doc;
//    XMLError result = doc.LoadFile(nazwaPliku.c_str());
//
//    if (result != XML_SUCCESS) {
//        std::cerr << "Nie można wczytać pliku XML" << std::endl;
//        return false;
//    }
//
//    XMLElement* root = doc.FirstChildElement("graph");
//    if (!root) {
//        std::cerr << "Nieprawidłowy format pliku XML" << std::endl;
//        return false;
//    }
//
//    for (XMLElement* e = root->FirstChildElement("edge"); e != nullptr; e = e->NextSiblingElement("edge")) {
//        int from, to, weight;
//        e->QueryIntAttribute("from", &from);
//        e->QueryIntAttribute("to", &to);
//        e->QueryIntAttribute("weight", &weight);
//
//        // Tutaj dodaj logikę do dodawania krawędzi do grafu
//        // Na przykład: addEdge(from, to, weight);
//    }
//
//    return true;
//}
bool Graf::czytajGraf(string plik)
{

    int **temp;
    opis = "";
    string tempOpis = "";

    ifstream fin;
    fin.open(plik);

    if (fin.fail() || fin.eof())
    {
        return false;
    }

//    if (liczbaWierzcholkow && macierz != nullptr)
    if (liczbaWierzcholkow && macierz != nullptr)
    {
        for (int i = 0; i < liczbaWierzcholkow; i++)
        {
            delete[] macierz[i];
        }

        delete[] macierz;
    }

    getline(fin, tempOpis);

    opis.append(tempOpis + "\n");

    getline(fin, tempOpis);

    opis.append(tempOpis + "\n");

    getline(fin, tempOpis);

    opis.append(tempOpis + "\n");

    fin >> tempOpis;

    opis.append(tempOpis);

    fin >> liczbaWierzcholkow;



    opis.append(to_string(liczbaWierzcholkow) + "\n");



    getline(fin, tempOpis);
    getline(fin, tempOpis);
    getline(fin, tempOpis);
    getline(fin, tempOpis);

    temp = new int *[liczbaWierzcholkow];

    for (int i = 0; i < liczbaWierzcholkow; i++)
    {
        temp[i] = new int[liczbaWierzcholkow];
    }

    for (int i = 0; i < liczbaWierzcholkow; i++)
    {
        for (int j = 0; j < liczbaWierzcholkow; j++)
        {
            fin >> temp[i][j];
        }
    }

    fin.close();

    macierz = temp;
    return true;
}

string Graf::getOpis()
{
    if (!liczbaWierzcholkow)
    {
        return "Brak danych\n";
    }
    else
    {
        return opis;
    }

}




bool Graf::ustawNieskonczonoscNaPrzekatnej()
{
    if (!liczbaWierzcholkow)
        return false;
    else
    {
        for (int i = 0; i < liczbaWierzcholkow; i++)
        {
            macierz[i][i] = NIESKONCZONOSC;
        }
        return true;
    }
}


int Graf::pobierzLiczbeWierzcholkow()
{
    return liczbaWierzcholkow;
}

Graf::Graf() //: macierz(nullptr)
{

}
Graf::~Graf()
{
//    if (macierz== nullptr)
//        return;
//
//    for (int i = 0; i < liczbaWierzcholkow; i++)
//    {
//        delete[] macierz[i];
//    }
//
//    delete[] macierz;
}

//Graf::~Graf() {
//    czyśćMacierz();
//}
//void Graf::czyśćMacierz() {
//    if (macierz) {
//        for (int i = 0; i < liczbaWierzcholkow; ++i) {
//            delete[] macierz[i];
//        }
//        delete[] macierz;
//        macierz = nullptr;
//    }
//}
int** Graf::pobierzMacierz()
{
    return macierz;
}


