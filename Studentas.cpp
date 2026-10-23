#include "Studentas.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using std::sort;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::stringstream;

double skaiciuotiVidurki(const Studentas& A)
{
    if (A.paz.size() <= 1) return 0.0;

    double suma = 0;
    for (size_t i = 0; i < A.paz.size() - 1; i++)
        suma += A.paz[i];

    return suma / (A.paz.size() - 1);
}

double skaiciuotiMediana(const Studentas& A)
{
    if (A.paz.size() <= 1) return 0.0;

    vector<int> nd;
    for (size_t i = 0; i < A.paz.size() - 1; i++)
        nd.push_back(A.paz[i]);

    sort(nd.begin(), nd.end());

    int n = static_cast<int>(nd.size());
    if (n % 2 == 1) return nd[n / 2];

    return (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
}

bool rikiuotiPagalVarda(const Studentas& A, const Studentas& B)
{
    if (A.vardas != B.vardas)
        return A.vardas < B.vardas;

    return A.pavarde < B.pavarde;
}

void skaiciuotiGalutinius(Studentas& A)
{
    if (A.paz.empty()) return;

    int egz = A.paz[A.paz.size() - 1];

    A.galutinisVid = 0.4 * skaiciuotiVidurki(A) + 0.6 * egz;
    A.galutinisMed = 0.4 * skaiciuotiMediana(A) + 0.6 * egz;
}

template <typename Container>
void nuskaityti(const string& failas, Container& grupe)
{
    ifstream f(failas);

    if (!f)
        throw std::runtime_error("Nepavyko atidaryti: " + failas);

    grupe.clear();

    string eilute;
    getline(f, eilute);

    while (getline(f, eilute))
    {
        if (eilute.empty()) continue;

        stringstream ss(eilute);
        Studentas A;

        ss >> A.vardas >> A.pavarde;

        int pazymys;
        while (ss >> pazymys)
            A.paz.push_back(pazymys);

        if (!A.vardas.empty() && !A.pavarde.empty() && !A.paz.empty())
        {
            skaiciuotiGalutinius(A);
            grupe.push_back(A);
        }
    }
}

void nuskaitytiIsFailo(const string& failas, vector<Studentas>& grupe)
{
    nuskaityti(failas, grupe);
}

void nuskaitytiIsFailo(const string& failas, list<Studentas>& grupe)
{
    nuskaityti(failas, grupe);
}

template <typename Container>
void issaugoti(const string& failas, const Container& grupe)
{
    ofstream f(failas);

    if (!f)
        throw std::runtime_error("Nepavyko sukurti: " + failas);

    f << std::left << std::setw(15) << "Pavarde"
        << std::setw(15) << "Vardas"
        << std::setw(20) << "Galutinis (Vid.)"
        << std::setw(20) << "Galutinis (Med.)" << "\n";

    f << string(70, '-') << "\n";

    for (const Studentas& B : grupe)
    {
        f << std::left << std::setw(15) << B.pavarde
            << std::setw(15) << B.vardas
            << std::setw(20) << std::fixed << std::setprecision(2) << B.galutinisVid
            << std::setw(20) << B.galutinisMed << "\n";
    }
}

void issaugotiIFaila(const string& failas, const vector<Studentas>& grupe)
{
    issaugoti(failas, grupe);
}

void issaugotiIFaila(const string& failas, const list<Studentas>& grupe)
{
    issaugoti(failas, grupe);
}
