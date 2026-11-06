#include "Failai.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <utility>

using std::vector;
using std::list;
using std::string;

void generuotiTestiniusFailus(const std::vector<int>& pasirinktiFailai)
{
    const int dydziai[] = {
        1000, 10000, 100000, 1000000, 10000000
    };

    const string vardai[] = {
        "Jonas", "Petras", "Ona", "Ieva", "Lukas",
        "Mantas", "Greta", "Aiste", "Tomas", "Rokas"
    };

    const string pavardes[] = {
        "Kazlauskas", "Petrauskas", "Jankauskas",
        "Stankevicius", "Vasiliauskas", "Zukauskas",
        "Butkus", "Paulauskas", "Urbonas", "Savickas"
    };

    std::mt19937 gen(2026);

    std::uniform_int_distribution<int> pazymys(1, 10);
    std::uniform_int_distribution<int> indeksas(0, 9);
    std::uniform_int_distribution<int> ndKiekis(5, 10);

    for (int pasirinkimas : pasirinktiFailai)
    {
        int n = dydziai[pasirinkimas];

        string failoVardas =
            "studentai_" + std::to_string(n) + ".txt";

        std::ofstream f(failoVardas);

        if (!f)
            throw std::runtime_error(
                "Nepavyko sugeneruoti failo: " + failoVardas
            );

        f << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 "
            "ND6 ND7 ND8 ND9 ND10 Egzaminas\n";

        for (int i = 0; i < n; i++)
        {
            f << vardai[indeksas(gen)] << ' '
                << pavardes[indeksas(gen)];

            int kiek = ndKiekis(gen);

            for (int j = 0; j < kiek; j++)
                f << ' ' << pazymys(gen);

            f << ' ' << pazymys(gen) << '\n';
        }

        f.close();

        std::cout << "Sugeneruotas failas: "
            << failoVardas << '\n';
    }
}

static double galutinis(const Studentas& A, int kriterijus)
{
    if (kriterijus == 2)
        return A.galutinisMed;

    return A.galutinisVid;
}



template <typename Container>
void strategija1(
    const Container& grupe,
    Container& vargsiukai,
    Container& kietiakiai,
    int kriterijus
)
{
    vargsiukai.clear();
    kietiakiai.clear();

    for (const Studentas& A : grupe)
    {
        if (galutinis(A, kriterijus) < 5.0)
            vargsiukai.push_back(A);
        else
            kietiakiai.push_back(A);
    }
}



void strategija2(
    vector<Studentas>& grupe,
    vector<Studentas>& vargsiukai,
    int kriterijus
)
{
    vargsiukai.clear();

    for (auto it = grupe.begin(); it != grupe.end();)
    {
        if (galutinis(*it, kriterijus) < 5.0)
        {
            vargsiukai.push_back(*it);
            it = grupe.erase(it);
        }
        else
            ++it;
    }
}

void strategija2(
    list<Studentas>& grupe,
    list<Studentas>& vargsiukai,
    int kriterijus
)
{
    vargsiukai.clear();

    for (auto it = grupe.begin(); it != grupe.end();)
    {
        if (galutinis(*it, kriterijus) < 5.0)
        {
            vargsiukai.push_back(*it);
            it = grupe.erase(it);
        }
        else
            ++it;
    }
}



void strategija3(
    vector<Studentas>& grupe,
    vector<Studentas>& vargsiukai,
    int kriterijus
)
{
    vargsiukai.clear();

    auto riba = std::stable_partition(
        grupe.begin(),
        grupe.end(),
        [kriterijus](const Studentas& A)
        {
            return galutinis(A, kriterijus) < 5.0;
        }
    );

    vargsiukai.reserve(
        static_cast<size_t>(std::distance(grupe.begin(), riba))
    );

    std::move(
        grupe.begin(),
        riba,
        std::back_inserter(vargsiukai)
    );

    grupe.erase(grupe.begin(), riba);
}

void strategija3(
    list<Studentas>& grupe,
    list<Studentas>& vargsiukai,
    int kriterijus
)
{
    vargsiukai.clear();

    for (auto it = grupe.begin(); it != grupe.end();)
    {
        auto dabartinis = it++;

        if (galutinis(*dabartinis, kriterijus) < 5.0)
        {
            vargsiukai.splice(
                vargsiukai.end(),
                grupe,
                dabartinis
            );
        }
    }
}

void skirstytiIGrupes(
    vector<Studentas>& grupe,
    vector<Studentas>& vargsiukai,
    vector<Studentas>& kietiakiai,
    int kriterijus,
    int strategija
)
{
    kietiakiai.clear();

    if (strategija == 1)
        strategija1(grupe, vargsiukai, kietiakiai, kriterijus);
    else if (strategija == 2)
        strategija2(grupe, vargsiukai, kriterijus);
    else if (strategija == 3)
        strategija3(grupe, vargsiukai, kriterijus);
    else
        throw std::invalid_argument("Neteisingas strategijos numeris.");
}

void skirstytiIGrupes(
    list<Studentas>& grupe,
    list<Studentas>& vargsiukai,
    list<Studentas>& kietiakiai,
    int kriterijus,
    int strategija
)
{
    kietiakiai.clear();

    if (strategija == 1)
        strategija1(grupe, vargsiukai, kietiakiai, kriterijus);
    else if (strategija == 2)
        strategija2(grupe, vargsiukai, kriterijus);
    else if (strategija == 3)
        strategija3(grupe, vargsiukai, kriterijus);
    else
        throw std::invalid_argument("Neteisingas strategijos numeris.");
}
