#pragma once
#include "Studentas.h"
#include <string>
#include <vector>

void generuotiFaila(const std::string& failas, int kiekis);

void skirstytiIGrupes(const std::vector<Studentas>& grupe,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai,
    int kriterijus = 1);
