#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

struct Studentas
{
    string vardas, pavarde;
    vector<int> paz;
    double galutinisVid = 0.0;
    double galutinisMed = 0.0;
};



double skaiciuotiVidurki(const Studentas& A);
double skaiciuotiMediana(const Studentas& A);
bool   rikiuotiPagalVarda(const Studentas& A, const Studentas& B);


void   skaiciuotiGalutinius(Studentas& A);
void   nuskaitytiIsFailo(const string& failas, vector<Studentas>& grupe);
void   issaugotiIFaila(const string& failas, const vector<Studentas>& grupe);
