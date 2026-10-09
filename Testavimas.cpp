#include "Testavimas.h"
#include "Failai.h"
#include <iostream>
#include <algorithm>

using std::cout; using std::endl;
using std::string; using std::vector;

TestoRezultatas testuotiVienaFaila(const string& failoVardas,
    int kiekis,
    bool suGeneravimu)
{
    TestoRezultatas r;
    r.kiekis = kiekis;

    if (suGeneravimu)
        generuotiFaila(failoVardas, kiekis);

    vector<Studentas> grupe;

    
    r.nuskaitymoLaikas = matuoti([&] {
        nuskaitytiIsFailo(failoVardas, grupe);
        });
    cout << "Failas uzdaritas" << endl;
    cout << "Failo is " << kiekis << " irasu nuskaitymo laikas: "
        << r.nuskaitymoLaikas << endl;

    
    r.rikiavimoLaikas = matuoti([&] {
        std::sort(grupe.begin(), grupe.end(), rikiuotiPagalVarda);
        });
    cout << kiekis << " irasu rusiavimas didejimo tvarka laikas, su sort funkcija: "
        << r.rikiavimoLaikas << endl;

    
    vector<Studentas> vargsiukai, kietiakiai;
    r.dalijimoLaikas = matuoti([&] {
        skirstytiIGrupes(grupe, vargsiukai, kietiakiai, 1);
        });
    cout << kiekis << " irasu dalijimo i dvi grupes laikas, panaikinant pradini Vektor: "
        << r.dalijimoLaikas << endl;

    
    r.vargsiukuIsvedimoLaikas = matuoti([&] {
        issaugotiIFaila("vargsiukai_" + failoVardas, vargsiukai);
        });
    cout << kiekis << " irasu nelaimingu irasu isvedimo i faila laikas: "
        << r.vargsiukuIsvedimoLaikas << endl;

    
    r.kietiakuIsvedimoLaikas = matuoti([&] {
        issaugotiIFaila("kietiakiai_" + failoVardas, kietiakiai);
        });
    cout << kiekis << " irasu keteku irasu isvedimo i faila laikas: "
        << r.kietiakuIsvedimoLaikas << endl;

    
    r.bendrasLaikas = r.nuskaitymoLaikas + r.rikiavimoLaikas
        + r.dalijimoLaikas + r.vargsiukuIsvedimoLaikas
        + r.kietiakuIsvedimoLaikas;
    cout << kiekis << " irasu testo laikas: " << r.bendrasLaikas << endl;

    return r;
}

void testuotiKeliskart(int kiekisPaleidimu)
{
    vector<std::pair<string, int>> failai = {
        {"studentai_1000.txt",      1000},
        {"studentai_10000.txt",     10000},
        {"studentai_100000.txt",    100000},
        {"studentai_1000000.txt",   1000000},
        {"studentai_10000000.txt",  10000000}
    };

    for (int p = 1; p <= kiekisPaleidimu; ++p)
    {
        cout << "\n########## PALEIDIMAS " << p
            << " ##########\n" << endl;

        bool gen = (p == 1); 

        for (auto& [vardas, kiekis] : failai)
        {
            testuotiVienaFaila(vardas, kiekis, gen);

            cout << "Press any key to continue . . .";
            std::cin.get();
            cout << endl;
        }
    }
}
