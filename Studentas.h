#pragma once

#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

struct Studentas
{
    string vardas, pavarde;
    vector<int> paz;
    double galutinisVid = 0.0;
    double galutinisMed = 0.0;
};

double skaiciuotiVidurki(const Studentas& A);
double skaiciuotiMediana(const Studentas& A);
bool rikiuotiPagalVarda(const Studentas& A, const Studentas& B);
void skaiciuotiGalutinius(Studentas& A);
