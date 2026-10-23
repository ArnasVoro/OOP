#include "Studentas.h"
#include "Failai.h"
#include "Testavimas.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <limits>

using std::string;
using std::vector;
using std::list;
using std::cout;
using std::endl;
using std::cin;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

template <typename Container>
void rikiuotiStudentus(Container& grupe)
{
    if constexpr (std::is_same_v<Container, vector<Studentas>>)
        std::sort(grupe.begin(), grupe.end(), rikiuotiPagalVarda);
    else
        grupe.sort(rikiuotiPagalVarda);
}

template <typename Container>
void spausdintiStudentus(const Container& grupe, int pasirinkimas)
{
    cout << endl;

    if (pasirinkimas == 1)
    {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
            << setw(20) << "Galutinis (Vid.)" << endl;
        cout << "--------------------------------------------------" << endl;

        for (const Studentas& B : grupe)
            cout << left << setw(15) << B.pavarde << setw(15) << B.vardas
            << setw(20) << fixed << setprecision(2) << B.galutinisVid << endl;
    }
    else if (pasirinkimas == 2)
    {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
            << setw(20) << "Galutinis (Med.)" << endl;
        cout << "--------------------------------------------------" << endl;

        for (const Studentas& B : grupe)
            cout << left << setw(15) << B.pavarde << setw(15) << B.vardas
            << setw(20) << fixed << setprecision(2) << B.galutinisMed << endl;
    }
    else if (pasirinkimas == 3)
    {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
            << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
        cout << "---------------------------------------------------------------------" << endl;

        for (const Studentas& B : grupe)
            cout << left << setw(15) << B.pavarde << setw(15) << B.vardas
            << setw(20) << fixed << setprecision(2) << B.galutinisVid
            << setw(20) << B.galutinisMed << endl;
    }
    else
        cout << "Neegzistuoja toks pasirinkimas." << endl;
}

template <typename Container>
void vykdytiIprastaRezyma(Container& grupe)
{
    int budas;
    cout << "Kaip norite ivesti duomenis?" << endl;
    cout << "1 - Ivesti duomenis rankiniu budu" << endl;
    cout << "2 - Nuskaityti duomenis is failo (kursiokai.txt)" << endl;
    cout << "Pasirinkite: ";
    cin >> budas;

    if (budas != 1 && budas != 2)
    {
        cout << "Tokio pasirinkimo nera." << endl;
        return;
    }

    if (budas == 2)
    {
        try
        {
            nuskaitytiIsFailo("kursiokai.txt", grupe);
            cout << "Duomenys sekmingai nuskaityti is failo." << endl;
        }
        catch (const std::exception& e)
        {
            cout << e.what() << endl;
            return;
        }
    }
    else
    {
        int n;
        cout << "Kiek studentu yra sarase: ";
        cin >> n;

        if (n <= 0)
        {
            cout << "Studentu skaicius turi buti teigiamas." << endl;
            return;
        }

        int nd;
        cout << "Ar zinomas namu darbu skaicius?" << endl;
        cout << "1 - Taip" << endl;
        cout << "2 - Ne" << endl;
        cout << "Pasirinkite: ";
        cin >> nd;

        if (nd != 1 && nd != 2)
        {
            cout << "Tokio pasirinkimo nera." << endl;
            return;
        }

        int generuoti;
        cout << "Ar norite atsitiktinai sugeneruoti pazymius?" << endl;
        cout << "1 - Taip" << endl;
        cout << "2 - Ne" << endl;
        cout << "Pasirinkite: ";
        cin >> generuoti;

        if (generuoti != 1 && generuoti != 2)
        {
            cout << "Tokio pasirinkimo nera." << endl;
            return;
        }

        for (int i = 0; i < n; i++)
        {
            Studentas A;
            cout << "Iveskite studento varda ir pavarde: ";
            cin >> A.vardas >> A.pavarde;

            if (generuoti == 1)
            {
                int k;

                if (nd == 1)
                {
                    cout << "Iveskite namu darbu kieki: ";
                    cin >> k;
                    if (k < 0) k = 0;
                }
                else
                    k = rand() % 15 + 1;

                cout << "Sugeneruoti namu darbu pazymiai: ";
                for (int j = 0; j < k; j++)
                {
                    int paz = rand() % 10 + 1;
                    A.paz.push_back(paz);
                    cout << paz << " ";
                }
                cout << endl;

                int egz = rand() % 10 + 1;
                A.paz.push_back(egz);
                cout << "Sugeneruotas egzamino pazymys: " << egz << endl;
            }
            else
            {
                if (nd == 1)
                {
                    int k;
                    cout << "Iveskite namu darbu kieki: ";
                    cin >> k;
                    if (k < 0) k = 0;

                    for (int j = 0; j < k; j++)
                    {
                        int paz;
                        do
                        {
                            cout << "Iveskite " << j + 1 << " pazymi (1-10): ";
                            cin >> paz;
                        } while (paz < 1 || paz > 10);

                        A.paz.push_back(paz);
                    }
                }
                else
                {
                    string ivestis;
                    cout << "Iveskite namu darbu pazymius (skaicius arba N, kad sustoti):" << endl;

                    while (true)
                    {
                        cin >> ivestis;
                        if (ivestis == "N" || ivestis == "n")
                            break;

                        try
                        {
                            size_t poz;
                            int paz = std::stoi(ivestis, &poz);

                            if (poz != ivestis.size() || paz < 1 || paz > 10)
                                cout << "Pazymys turi buti sveikasis skaicius nuo 1 iki 10." << endl;
                            else
                                A.paz.push_back(paz);
                        }
                        catch (...)
                        {
                            cout << "Iveskite skaiciu nuo 1 iki 10 arba N." << endl;
                        }
                    }
                }

                int egz;
                do
                {
                    cout << "Iveskite egzamino pazymi (1-10): ";
                    cin >> egz;
                } while (egz < 1 || egz > 10);

                A.paz.push_back(egz);
            }

            skaiciuotiGalutinius(A);
            grupe.push_back(A);
            cout << "Studento objekto adresas konteineryje: " << &grupe.back() << endl;
        }
    }

    rikiuotiStudentus(grupe);

    int pasirinkimas;
    cout << endl;
    cout << "Pasirinkite kaip norite atspausdinti duomenis" << endl;
    cout << "1 - Vidurkis" << endl;
    cout << "2 - Mediana" << endl;
    cout << "3 - Abu" << endl;
    cout << "Pasirinkite: ";
    cin >> pasirinkimas;

    spausdintiStudentus(grupe, pasirinkimas);

    cout << endl;
    cout << "Ar skirstyti i vargsiukus/kietiakius? (1-Taip, 2-Ne): ";
    int sk;
    cin >> sk;

    if (sk == 1)
    {
        Container vargsiukai, kietiakiai;
        skirstytiIGrupes(grupe, vargsiukai, kietiakiai, 1);
        issaugotiIFaila("vargsiukai.txt", vargsiukai);
        issaugotiIFaila("kietiakiai.txt", kietiakiai);

        cout << "Issaugota: vargsiukai.txt (" << vargsiukai.size()
            << "), kietiakiiai.txt (" << kietiakiai.size() << ")" << endl;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    cout << "1 - Rankinis / failo rezimas" << endl;
    cout << "2 - Testavimo rezimas (vector ir list)" << endl;
    cout << "Pasirinkite: ";

    int rez;
    cin >> rez;

    try
    {
        if (rez == 2)
        {
            int konteineris, failoPasirinkimas, kiek;

            cout << "Pasirinkite konteinerio tipa (1 - vector, 2 - list): ";
            cin >> konteineris;

            if (konteineris != 1 && konteineris != 2)
            {
                cout << "Tokio pasirinkimo nera." << endl;
                return 0;
            }

            cout << "Kuri faila norite tirti?" << endl;
            cout << "1 - studentai_1000.txt" << endl;
            cout << "2 - studentai_10000.txt" << endl;
            cout << "3 - studentai_100000.txt" << endl;
            cout << "4 - studentai_1000000.txt" << endl;
            cout << "5 - studentai_10000000.txt" << endl;
            cout << "6 - ivesti savo failo pavadinima" << endl;
            cout << "Pasirinkite: ";
            cin >> failoPasirinkimas;

            if (failoPasirinkimas < 1 || failoPasirinkimas > 6)
            {
                cout << "Tokio pasirinkimo nera." << endl;
                return 0;
            }

            cout << "Kiek kartu atlikti testa? ";
            cin >> kiek;

            if (kiek <= 0)
            {
                cout << "Testu skaicius turi buti teigiamas." << endl;
                return 0;
            }

            testuotiKeliskart(kiek, konteineris, failoPasirinkimas);
            return 0;
        }

        if (rez != 1)
        {
            cout << "Tokio pasirinkimo nera." << endl;
            return 0;
        }

        int konteineris;
        cout << "Pasirinkite konteineri:" << endl;
        cout << "1 - vector" << endl;
        cout << "2 - list" << endl;
        cout << "Pasirinkite: ";
        cin >> konteineris;

        if (konteineris == 1)
        {
            vector<Studentas> grupe;
            vykdytiIprastaRezyma(grupe);
        }
        else if (konteineris == 2)
        {
            list<Studentas> grupe;
            vykdytiIprastaRezyma(grupe);
        }
        else
            cout << "Tokio pasirinkimo nera." << endl;
    }
    catch (const std::exception& e)
    {
        cout << "Klaida: " << e.what() << endl;
    }

    return 0;
}
