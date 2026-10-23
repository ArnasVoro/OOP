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
