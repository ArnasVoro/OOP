#pragma once

#include "Studentas.h"

#include <string>
#include <vector>
#include <list>

void generuotiTestiniusFailus(const std::vector<int>& pasirinktiFailai);

void skirstytiIGrupes(
    std::vector<Studentas>& grupe,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai,
    int kriterijus,
    int strategija = 1
);

void skirstytiIGrupes(
    std::list<Studentas>& grupe,
    std::list<Studentas>& vargsiukai,
    std::list<Studentas>& kietiakiai,
    int kriterijus,
    int strategija = 1
);
