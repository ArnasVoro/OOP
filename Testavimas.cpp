#include "Testavimas.h"
#include "Failai.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <type_traits>
#include <iterator>

using std::cout;
using std::string;
using std::vector;
using std::list;

// Laiko funkcijos vykdymo trukme.

template <typename F>
double matuoti(F&& funkcija)
{
    auto pradzia = std::chrono::steady_clock::now();

    funkcija();

    auto pabaiga = std::chrono::steady_clock::now();

    return std::chrono::duration<double>(
        pabaiga - pradzia
    ).count();
}

// Vienas strategijos testas.

template <typename Container>
double vienasTestas(
    const string& failas,
    int kriterijus,
    int strategija,
    size_t& vargsiukuKiekis,
    size_t& kietiakuKiekis
)
{
    Container studentai, vargsiukai, kietiakiai;

    // Skaitymas nematuojamas.
    nuskaitytiIsFailo(failas, studentai);

    // Matuojamas tik skirstymas.
    double laikas = matuoti([&]()
        {
            skirstytiIGrupes(
                studentai,
                vargsiukai,
                kietiakiai,
                kriterijus,
                strategija
            );
        });

    vargsiukuKiekis = vargsiukai.size();

    if (strategija == 1)
        kietiakuKiekis = kietiakiai.size();
    else
        kietiakuKiekis = studentai.size();

    return laikas;
}

// Atlieka triju strategiju testus pasirinktam konteineriui.

template <typename Container>
void vykdytiStrategijuTestus(
    const string& konteineris,
    const string& failas,
    int kartai,
    int kriterijus
)
{
    cout << "\n========================================\n";
    cout << "Konteineris: " << konteineris << '\n';
    cout << "Failas: " << failas << '\n';
    cout << "========================================\n";

    cout << "Strategija | Vargsiukai | Kietiakai | Laikas (s)\n";

    std::ofstream csv("v1_rezultatai.txt", std::ios::app);

    if (csv.tellp() == 0)
    {
        csv << "konteineris,failas,kriterijus,strategija,"
            "kartai,vargsiukai,kietiakai,vidurkis_s\n";
    }

    for (int strategija = 1; strategija <= 3; strategija++)
    {
        double suma = 0.0;

        size_t vKiekis = 0;
        size_t kKiekis = 0;

        for (int i = 0; i < kartai; i++)
        {
            size_t v = 0;
            size_t k = 0;

            double laikas = vienasTestas<Container>(
                failas,
                kriterijus,
                strategija,
                v,
                k
            );

            suma += laikas;

            vKiekis = v;
            kKiekis = k;
        }

        double vidurkis = suma / kartai;

        cout << "     " << strategija
            << "     | " << vKiekis
            << " | " << kKiekis
            << " | " << std::fixed
            << std::setprecision(6)
            << vidurkis << '\n';

        csv << konteineris << ','
            << failas << ','
            << kriterijus << ','
            << strategija << ','
            << kartai << ','
            << vKiekis << ','
            << kKiekis << ','
            << vidurkis << '\n';
    }
}

// Papildomas vector STL algoritmu palyginimas.

template <typename Predicate>
double testuotiVectorAlgoritma(
    const vector<Studentas>& pradinis,
    Predicate salyga,
    int algoritmas,
    size_t& vargsiukuKiekis
)
{
    // Kopijavimas neatimamas i algoritmo laika.
    vector<Studentas> darbinis = pradinis;

    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;

    double laikas = matuoti([&]()
        {
            if (algoritmas == 1)
            {
                // copy_if: kopijuojame i du atskirus konteinerius.

                std::copy_if(
                    darbinis.begin(),
                    darbinis.end(),
                    std::back_inserter(vargsiukai),
                    salyga
                );

                std::copy_if(
                    darbinis.begin(),
                    darbinis.end(),
                    std::back_inserter(kietiakiai),
                    [&](const Studentas& A)
                    {
                        return !salyga(A);
                    }
                );
            }
            else if (algoritmas == 2)
            {
                // remove_if: vargsiukus nukopijuojame,
                // o is pradinio vektoriaus juos pasaliname.

                std::copy_if(
                    darbinis.begin(),
                    darbinis.end(),
                    std::back_inserter(vargsiukai),
                    salyga
                );

                auto riba = std::remove_if(
                    darbinis.begin(),
                    darbinis.end(),
                    salyga
                );

                darbinis.erase(riba, darbinis.end());
            }
            else if (algoritmas == 3)
            {
                // partition: suskirsto i dvi dalis,
                // bet neisaugo pradines tvarkos.

                auto riba = std::partition(
                    darbinis.begin(),
                    darbinis.end(),
                    salyga
                );

                vargsiukai.assign(
                    darbinis.begin(),
                    riba
                );
            }
            else
            {
                // stable_partition: suskirsto i dvi dalis,
                // islaikydamas pradine tvarka.

                auto riba = std::stable_partition(
                    darbinis.begin(),
                    darbinis.end(),
                    salyga
                );

                vargsiukai.assign(
                    darbinis.begin(),
                    riba
                );
            }
        });

    vargsiukuKiekis = vargsiukai.size();

    return laikas;
}

void palygintiVectorAlgoritmus(
    int kiekisPaleidimu,
    const string& failoVardas,
    int kriterijus
)
{
    vector<Studentas> pradinis;

    nuskaitytiIsFailo(failoVardas, pradinis);

    cout << "\nPapildomas vector STL algoritmu palyginimas\n";
    cout << "Failas: " << failoVardas << '\n';

    cout << "Algoritmas | Vargsiukai | Laikas (s)\n";

    const string pavadinimai[] =
    {
        "copy_if",
        "remove_if",
        "partition",
        "stable_partition"
    };

    std::ofstream csv(
        "v1_vector_algoritmai.txt",
        std::ios::app
    );

    if (csv.tellp() == 0)
        csv << "failas,algoritmas,kartai,vargsiukai,vidurkis_s\n";

    for (int alg = 1; alg <= 4; alg++)
    {
        double suma = 0.0;

        size_t kiekis = 0;

        for (int i = 0; i < kiekisPaleidimu; i++)
        {
            size_t v = 0;

            double laikas = testuotiVectorAlgoritma(
                pradinis,
                [kriterijus](const Studentas& A)
                {
                    double balas;

                    if (kriterijus == 2)
                        balas = A.galutinisMed;
                    else
                        balas = A.galutinisVid;

                    return balas < 5.0;
                },
                alg,
                v
            );

            suma += laikas;
            kiekis = v;
        }

        double vidurkis = suma / kiekisPaleidimu;

        cout << pavadinimai[alg - 1]
            << " | " << kiekis
            << " | " << std::fixed
            << std::setprecision(6)
            << vidurkis << '\n';

        csv << failoVardas << ','
            << pavadinimai[alg - 1] << ','
            << kiekisPaleidimu << ','
            << kiekis << ','
            << vidurkis << '\n';
    }
}

// Pagrindine testavimo funkcija.

void testuotiKeliskart(int kiekisPaleidimu)
{
    const string failai[] =
    {
        "studentai_1000.txt",
        "studentai_10000.txt",
        "studentai_100000.txt",
        "studentai_1000000.txt",
        "studentai_10000000.txt"
    };

    // 1. Failu pasirinkimas.

    cout << "\nPasirinkite, kuriuos failus norite tirti:\n";

    for (int i = 0; i < 5; i++)
        cout << i + 1 << " - " << failai[i] << '\n';

    cout << "0 - Visi failai\n";

    cout << "\nIveskite numerius, atskirtus tarpais (pvz. 1 3 5): ";

    string pasirinkimai;

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::getline(std::cin, pasirinkimai);

    vector<int> pasirinktiFailai;

    std::stringstream ss(pasirinkimai);

    int pasirinkimas;

    while (ss >> pasirinkimas)
    {
        if (pasirinkimas == 0)
        {
            pasirinktiFailai.clear();

            for (int i = 0; i < 5; i++)
                pasirinktiFailai.push_back(i);

            break;
        }

        if (pasirinkimas < 1 || pasirinkimas > 5)
        {
            cout << "Neteisingas failo numeris: "
                << pasirinkimas << '\n';

            return;
        }

        int indeksas = pasirinkimas - 1;

        if (std::find(
            pasirinktiFailai.begin(),
            pasirinktiFailai.end(),
            indeksas
        ) == pasirinktiFailai.end())
        {
            pasirinktiFailai.push_back(indeksas);
        }
    }

    if (pasirinktiFailai.empty())
    {
        cout << "Nepasirinktas ne vienas failas.\n";
        return;
    }

    // 2. Kriterijaus pasirinkimas.

    int kriterijus;

    cout << "\nSkirstymo kriterijus:\n";
    cout << "1 - Galutinis vidurkis\n";
    cout << "2 - Galutine mediana\n";
    cout << "Pasirinkite: ";

    std::cin >> kriterijus;

    if (kriterijus != 1 && kriterijus != 2)
    {
        cout << "Tokio pasirinkimo nera.\n";
        return;
    }

    // 3. Konteinerio pasirinkimas.

    int konteineris;

    cout << "\nPasirinkite konteineri:\n";
    cout << "1 - vector\n";
    cout << "2 - list\n";
    cout << "3 - Abu\n";
    cout << "Pasirinkite: ";

    std::cin >> konteineris;

    if (konteineris < 1 || konteineris > 3)
    {
        cout << "Tokio pasirinkimo nera.\n";
        return;
    }

    // 4. Generuojami testiniai failai.
    // Generuojami visi penki failai, bet tiriami tik pasirinkti.

    cout << "\nGeneruojami testiniai failai. Palaukite...\n";

    generuotiTestiniusFailus(pasirinktiFailai);

    // 5. Vykdomi pasirinkti testai.

    for (int idx : pasirinktiFailai)
    {
        if (konteineris == 1 || konteineris == 3)
        {
            vykdytiStrategijuTestus<vector<Studentas>>(
                "vector",
                failai[idx],
                kiekisPaleidimu,
                kriterijus
            );

            palygintiVectorAlgoritmus(
                kiekisPaleidimu,
                failai[idx],
                kriterijus
            );
        }

        if (konteineris == 2 || konteineris == 3)
        {
            vykdytiStrategijuTestus<list<Studentas>>(
                "list",
                failai[idx],
                kiekisPaleidimu,
                kriterijus
            );
        }
    }

    cout << "\nTestavimas baigtas.\n";
    cout << "Rezultatai irasyti i txt failus.\n";
}
