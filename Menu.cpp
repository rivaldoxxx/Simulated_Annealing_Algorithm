#include "Menu.h"
#include <iostream>
#include <Windows.h>

#include "SymulowaneWyzarzanie.h"
#include "Sciezka.h"


void Menu::uruchom()
{
    int opcja = 0;
    vector<int>sciezkaSA;
    bool algorytmWykonany = false;
    while (true)

    {
        std::cout << "[1] Ustaw czas: " << czas << " s\n";
        std::cout << "[2] Ustaw wspolczynnik dT: " << wspolczynnikTemperatury << "\n";
        std::cout << graf.getOpis();
        std::cout << "Wybierz opcje:\n";
        std::cout << "1. Zmien czas\n";
        std::cout << "2. Zmien wspolczynnik dT\n";
        std::cout << "3. Wczytaj dane grafu\n";
        std::cout << "4. Uruchom Symulowane Wyzarzanie\n";
        std::cout << "5. Zapisz sciezke rozwiazania do pliku\n";
        std::cout << "6. Odczytaj sciezke z pliku i oblicz koszt\n";
        std::cout << "7. Wyjscie\n";
        std::cout << "> ";

        cin >> opcja;

        switch (opcja)
        {
            case 1:
                std::cout << "Podaj nowy czas [s]: ";
                cin >> czas;
                break;

            case 2:
                std::cout << "Podaj nowy wspolczynnik dT: ";
                cin >> wspolczynnikTemperatury;
                break;

            case 3:
                std::cout << "Wybierz plik do wczytania:\n";
                std::cout << "1. ftv55.atsp\n";
                std::cout << "2. ftv170.atsp\n";
                std::cout << "3. rgb358.atsp\n";
                std::cout << "> ";
                int wyborPliku;
                cin >> wyborPliku;
                switch (wyborPliku) {
                    case 1:
                        plik = "C:\\Users\\fizyk\\CLionProjects\\PEA_PROJ2\\files\\ftv47.atsp";
                        break;
                    case 2:
                        plik = "C:\\Users\\fizyk\\CLionProjects\\PEA_PROJ2\\files\\ftv170.atsp";
                        break;
                    case 3:
                        plik = "C:\\Users\\fizyk\\CLionProjects\\PEA_PROJ2\\files\\rbg403.atsp";
                        break;
                    default:
                        std::cout << "Nieprawidlowy wybor, sprobuj ponownie.\n";
                        continue;
                }
                graf.czytajGraf(plik);
                break;

            case 4: {
                if (!czas || !wspolczynnikTemperatury) {
                    std::cout << "Brakuje danych (czas/wspolczynnik dT)!";
                    cin.get();
                } else {
                    SymulowaneWyzarzanie sa(graf, czas, wspolczynnikTemperatury);
                    sa.zastosuj();
                    sciezkaSA = sa.getRozwiazanie();
                    cin.get();
                    //int wybor;
//                    cout << "Czy chcesz zapisac sciezke do pliku? 1)tak 2)nie" << endl;
//                    cin >> wybor;
//                    if (wybor == 1) {
//                        string nazwa;
//                        do {
//                            cout << "Podaj nazwe pliku: ";
//                            cin >> nazwa;
//                        } while (nazwa == "");
//                        sciezka.zapisz(sa.getRozwiazanie(), nazwa);
//                    }
//                    else {
//                        cerr << "Prosze uzupelnic brakujace dane (ograniczenie czasowe, wspolczynnik temp.)" << endl;
//                    }
                }
                std::cout << "5. Zapisz sciezke rozwiązania do pliku\n";
                std::cout << "6. Odczytaj sciezke z pliku i oblicz koszt\n";
                algorytmWykonany = true; // Ustawienie stanu na wykonany po zakończeniu algorytmu
                break;
            }
            case 5:
            {
                SymulowaneWyzarzanie sa(graf, czas, wspolczynnikTemperatury);

                if (algorytmWykonany) // Sprawdzenie, czy algorytm został wykonany
                {
                    std::string nazwaPliku;
                    std::cout << "Podaj nazwe pliku do zapisu: ";
                    cin >> nazwaPliku;
                    sciezka.zapisz(sciezkaSA, nazwaPliku);
                }
                {
                    std::cout << "Najpierw uruchom algorytm symulowanego wyzarzania (opcja 4)." << std::endl;
                }
                break;
            }
            case 6:
            {
                if (algorytmWykonany) // Sprawdzenie, czy algorytm został wykonany
                {
                    std::string nazwaPlikuOdczytu;
                    string sciezkaa;
                    std::cout << "Podaj nazwe pliku do odczytu: ";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, sciezkaa);
                    vector<int> wczytanaSciezka = sciezka.odczytaj(sciezkaa);
                    int koszt = sciezka.liczKoszt(wczytanaSciezka, graf);
                    std::cout << "Koszt wczytanej sciezki: " << koszt << std::endl;
                    std::cout << "Droga sciezki: ";
                    for (int i = 0; i < wczytanaSciezka.size(); ++i) {
                        std::cout << wczytanaSciezka[i];
                        if (i < wczytanaSciezka.size() - 1) {
                            std::cout << " -> ";
                        }
                    }
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << "Najpierw uruchom algorytm symulowanego wyzarzania (opcja 4)." << std::endl;
                }
                break;
            }
            case 7:
            {
                if (!czas || !wspolczynnikTemperatury || graf.pobierzLiczbeWierzcholkow() == 0)
                {
                    std::cout << "Brakuje danych (czas/wspolczynnik dT) lub graf nie zostal wczytany!" << std::endl;
                }
                else
                {
                    SymulowaneWyzarzanie sa(graf, czas, wspolczynnikTemperatury);
                    std::cout << "Uruchamianie testowania algorytmu...\n";
                    for (int h= 0; h < 10; ++h)
                    {
                        string sciezkaa;
                        sa.zastosuj();
                        vector<int> rozwiazanie = sa.getRozwiazanie();
                        //vector<int> rozwiazanie=sciezka.odczytaj(sciezkaa);
                        int koszt = sciezka.liczKoszt(rozwiazanie, graf);
                        double czasZnalezienia = sa.getCzasZnalezienia();

                        std::cout << "Test " << (h + 1) << ": Koszt = " << koszt << ", Czas znalezienia = " << czasZnalezienia << " s" << std::endl;
                    }
                    std::cin.get();
                }
                //cin.get();
                break;
            }
            case 8:
                std::cout << "Koniec programu.";
                return;

            default:
                std::cout << "Nieprawidlowa opcja, sprobuj ponownie.";
                break;
        }

        cin.ignore();
        system("cls");
    }
}



Menu::Menu()
{

}

Menu::~Menu()
{

}