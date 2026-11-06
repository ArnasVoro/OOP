#include "Studentas.h"
#include "Failai.h"
#include "Testavimas.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <utility>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::list;

// Iprastas rezimas.

template <typename Container>
void iprastasRezymas(Container& studentai)
{
    cout << "\n1 - Nuskaityti is kursiokai.txt\n";
    cout << "2 - Ivesti studentus rankiniu budu\n";
    cout << "Pasirinkite: ";

    int budas;
    cin >> budas;

    if (budas == 1)
    {
        nuskaitytiIsFailo("kursiokai.txt", studentai);
    }
    else if (budas == 2)
    {
        int n;

        cout << "Studentu skaicius: ";
        cin >> n;

        if (n <= 0)
            return;

        for (int i = 0; i < n; i++)
        {
            Studentas A;

            cout << "\nVardas ir pavarde: ";
            cin >> A.vardas >> A.pavarde;

            int kiek;

            cout << "Namu darbu pazymiu skaicius: ";
            cin >> kiek;

            for (int j = 0; j < kiek; j++)
            {
                int p;

                do
                {
                    cout << "Pazymys (1-10): ";
                    cin >> p;
                } while (p < 1 || p > 10);

                A.paz.push_back(p);
            }

            int egz;

            do
            {
                cout << "Egzamino pazymys (1-10): ";
                cin >> egz;
            } while (egz < 1 || egz > 10);

            A.paz.push_back(egz);

            skaiciuotiGalutinius(A);

            studentai.push_back(std::move(A));
        }
    }
    else
    {
        cout << "Tokio pasirinkimo nera.\n";
        return;
    }

    int kriterijus;

    cout << "\nSkirstyti pagal:\n";
    cout << "1 - Galutini vidurki\n";
    cout << "2 - Galutine mediana\n";
    cout << "Pasirinkite: ";

    cin >> kriterijus;

    if (kriterijus != 1 && kriterijus != 2)
    {
        cout << "Tokio pasirinkimo nera.\n";
        return;
    }

    int strategija;

    cout << "\nPasirinkite skirstymo strategija:\n";
    cout << "1 - Kopijuoti i du naujus konteinerius\n";
    cout << "2 - Kopijuoti vargsiukus ir istrinti is pradinio\n";
    cout << "3 - Optimizuotas skirstymas\n";
    cout << "Pasirinkite: ";

    cin >> strategija;

    if (strategija < 1 || strategija > 3)
    {
        cout << "Tokio pasirinkimo nera.\n";
        return;
    }

    Container vargsiukai;
    Container kietiakiai;

    skirstytiIGrupes(
        studentai,
        vargsiukai,
        kietiakiai,
        kriterijus,
        strategija
    );

    issaugotiIFaila("vargsiukai.txt", vargsiukai);

    if (strategija == 1)
        issaugotiIFaila("kietiakiai.txt", kietiakiai);
    else
        issaugotiIFaila("kietiakiai.txt", studentai);

    cout << "\nStudentai suskirstyti.\n";
    cout << "Rezultatai issaugoti:\n";
    cout << "vargsiukai.txt\n";
    cout << "kietiakiai.txt\n";
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    cout << "========== STUDENTU PROGRAMA v1.0 ==========\n\n";

    cout << "1 - Iprastas rezimas\n";
    cout << "2 - Testavimo rezimas\n";

    cout << "\nPasirinkite rezima: ";

    int rezimas;
    cin >> rezimas;

    try
    {
        if (rezimas == 1)
        {
            int konteineris;

            cout << "\nPasirinkite konteineri:\n";
            cout << "1 - vector\n";
            cout << "2 - list\n";
            cout << "Pasirinkite: ";

            cin >> konteineris;

            if (konteineris == 1)
            {
                vector<Studentas> studentai;
                iprastasRezymas(studentai);
            }
            else if (konteineris == 2)
            {
                list<Studentas> studentai;
                iprastasRezymas(studentai);
            }
            else
            {
                cout << "Tokio pasirinkimo nera.\n";
            }
        }
        else if (rezimas == 2)
        {
            int kartai;

            cout << "\nKiek kartu kartoti kiekviena testa? ";
            cin >> kartai;

            if (kartai <= 0)
            {
                cout << "Testu skaicius turi buti teigiamas.\n";
                return 0;
            }

            testuotiKeliskart(kartai);
        }
        else
        {
            cout << "Tokio pasirinkimo nera.\n";
        }
    }
    catch (const std::exception& e)
    {
        cout << "\nKLAIDA: " << e.what() << '\n';
    }

    return 0;
}
