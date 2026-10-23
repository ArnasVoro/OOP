#pragma once

#include "Studentas.h"
#include <vector>
#include <list>

void skirstytiIGrupes(const std::vector<Studentas>& grupe,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai,
    int kriterijus = 1);

void skirstytiIGrupes(const std::list<Studentas>& grupe,
    std::list<Studentas>& vargsiukai,
    std::list<Studentas>& kietiakiai,
    int kriterijus = 1);
