#pragma once

#include "Studentas.h"
#include <string>
#include <chrono>

struct TestoRezultatas
{
    int kiekis = 0;
    double nuskaitymoLaikas = 0.0;
    double rikiavimoLaikas = 0.0;
    double dalijimoLaikas = 0.0;
    double vargsiukuIsvedimoLaikas = 0.0;
    double kietiakuIsvedimoLaikas = 0.0;
    double bendrasLaikas = 0.0;
};

TestoRezultatas testuotiVienaFailaVector(
    const std::string& failoVardas,
    int kiekis,
    int kriterijus,
    int rikiavimoKriterijus);

TestoRezultatas testuotiVienaFailaList(
    const std::string& failoVardas,
    int kiekis,
    int kriterijus,
    int rikiavimoKriterijus);

void testuotiKeliskart(
    int kiekisPaleidimu,
    int konteineris,
    int failoPasirinkimas);

template <typename F>
double matuoti(F&& f)
{
    auto start = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration<double>(end - start).count();
}
