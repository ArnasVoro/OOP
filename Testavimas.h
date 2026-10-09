#pragma once
#include "Studentas.h"
#include <string>
#include <vector>
#include <chrono>

struct TestoRezultatas {
    int kiekis = 0;
    double nuskaitymoLaikas = 0.0;
    double rikiavimoLaikas = 0.0;
    double dalijimoLaikas = 0.0;
    double vargsiukuIsvedimoLaikas = 0.0;
    double kietiakuIsvedimoLaikas = 0.0;
    double bendrasLaikas = 0.0;
};

TestoRezultatas testuotiVienaFaila(const std::string& failoVardas,
    int kiekis,
    bool suGeneravimu = true);

void testuotiKeliskart(int kiekisPaleidimu);

template <typename F>
double matuoti(F&& f) {
    auto start = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(end - start).count();
}
