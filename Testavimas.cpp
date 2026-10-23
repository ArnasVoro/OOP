#include "Testavimas.h"
#include "Failai.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>
#include <list>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::fixed;

template <typename Container, typename Comparator>
void rikiuoti(Container& grupe, Comparator palyginti)
{
    if constexpr (std::is_same_v<Container, vector<Studentas>>)
        std::sort(grupe.begin(), grupe.end(), palyginti);
    else
        grupe.sort(palyginti);
}

template <typename Container>
TestoRezultatas testuoti(
    const string& failoVardas,
    int kiekis,
    const string& konteinerioPav,
    int kriterijus,
    int rikiavimoKriterijus)
{
    TestoRezultatas r;
    r.kiekis = kiekis;

    Container grupe;

    r.nuskaitymoLaikas = matuoti([&]() {
        nuskaitytiIsFailo(failoVardas, grupe);
        });

    r.kiekis = static_cast<int>(grupe.size());

    Container vargsiukai, kietiakiai;
    int skirstymoKriterijus = (kriterijus == 1) ? 2 : 1;

    r.dalijimoLaikas = matuoti([&]() {
        skirstytiIGrupes(
            grupe, vargsiukai, kietiakiai, skirstymoKriterijus);
        });

    auto palyginti = [rikiavimoKriterijus, kriterijus](
        const Studentas& A, const Studentas& B)
        {
            if (rikiavimoKriterijus == 1)
            {
                if (A.vardas != B.vardas)
                    return A.vardas < B.vardas;

                return A.pavarde < B.pavarde;
            }

            if (rikiavimoKriterijus == 2)
            {
                if (A.pavarde != B.pavarde)
                    return A.pavarde < B.pavarde;

                return A.vardas < B.vardas;
            }

            double balasA = (kriterijus == 1)
                ? A.galutinisMed : A.galutinisVid;

            double balasB = (kriterijus == 1)
                ? B.galutinisMed : B.galutinisVid;

            if (balasA != balasB)
                return balasA < balasB;

            if (A.pavarde != B.pavarde)
                return A.pavarde < B.pavarde;

            return A.vardas < B.vardas;
        };

    r.rikiavimoLaikas = matuoti([&]() {
        rikiuoti(grupe, palyginti);
        rikiuoti(vargsiukai, palyginti);
        rikiuoti(kietiakiai, palyginti);
        });

    string prefiksas = (konteinerioPav == "vector")
        ? "vector_" : "list_";

    r.vargsiukuIsvedimoLaikas = matuoti([&]() {
        issaugotiIFaila(
            prefiksas + "vargsiukai_" + failoVardas, vargsiukai);
        });

    r.kietiakuIsvedimoLaikas = matuoti([&]() {
        issaugotiIFaila(
            prefiksas + "kietiakiai_" + failoVardas, kietiakiai);
        });

    r.bendrasLaikas = r.nuskaitymoLaikas
        + r.dalijimoLaikas
        + r.rikiavimoLaikas
        + r.vargsiukuIsvedimoLaikas
        + r.kietiakuIsvedimoLaikas;

    cout << "Failas " << failoVardas << " nuskaitytas per "
        << r.nuskaitymoLaikas << " sekundziu." << endl;

    cout << "Studentai suskirstyti i dvi grupes per "
        << r.dalijimoLaikas << " sekundziu." << endl;

    cout << "Studentai surusiuoti pagal pasirinkta kriteriju per "
        << r.rikiavimoLaikas << " sekundziu." << endl;

    cout << "Failu rasymas uztruko "
        << r.vargsiukuIsvedimoLaikas
        + r.kietiakuIsvedimoLaikas
        << " sekundziu." << endl;

    cout << "Bendras laikas: "
        << r.bendrasLaikas << " sekundziu." << endl;

    return r;
}

TestoRezultatas testuotiVienaFailaVector(
    const string& failoVardas,
    int kiekis,
    int kriterijus,
    int rikiavimoKriterijus)
{
    return testuoti<vector<Studentas>>(
        failoVardas, kiekis, "vector", kriterijus, rikiavimoKriterijus);
}

TestoRezultatas testuotiVienaFailaList(
    const string& failoVardas,
    int kiekis,
    int kriterijus,
    int rikiavimoKriterijus)
{
    return testuoti<std::list<Studentas>>(
        failoVardas, kiekis, "list", kriterijus, rikiavimoKriterijus);
}

void testuotiKeliskart(
    int kiekisPaleidimu,
    int konteineris,
    int failoPasirinkimas)
{
    vector<std::pair<string, int>> failai = {
        {"studentai_1000.txt", 1000},
        {"studentai_10000.txt", 10000},
        {"studentai_100000.txt", 100000},
        {"studentai_1000000.txt", 1000000},
        {"studentai_10000000.txt", 10000000}
    };

    string failoVardas;
    int studentuKiekis = 0;

    if (failoPasirinkimas >= 1 && failoPasirinkimas <= 5)
    {
        failoVardas = failai[failoPasirinkimas - 1].first;
        studentuKiekis = failai[failoPasirinkimas - 1].second;
    }
    else if (failoPasirinkimas == 6)
    {
        cout << "Iveskite failo pavadinima: ";
        cin >> failoVardas;
    }
    else
    {
        cout << "Tokio pasirinkimo nera." << endl;
        return;
    }

    std::ifstream f(failoVardas);

    if (!f)
    {
        cout << "Nepavyko atidaryti failo: "
            << failoVardas << endl;
        return;
    }

    f.close();

    int kriterijus;
    cout << "Pagal ka norite skirstyti studentus? "
        << "(1 - mediana, 2 - vidurkis): ";
    cin >> kriterijus;

    if (kriterijus != 1 && kriterijus != 2)
    {
        cout << "Tokio pasirinkimo nera." << endl;
        return;
    }

    int rikiavimoKriterijus;
    cout << "Pagal ka norite rusiuoti studentus? "
        << "(1 - vardas, 2 - pavarde, 3 - galutinis): ";
    cin >> rikiavimoKriterijus;

    if (rikiavimoKriterijus < 1 || rikiavimoKriterijus > 3)
    {
        cout << "Tokio pasirinkimo nera." << endl;
        return;
    }

    double skaitymas = 0.0, rikiavimas = 0.0, skirstymas = 0.0;
    double vargsiukai = 0.0, kietiakiai = 0.0, bendras = 0.0;

    string konteinerioPav = (konteineris == 1)
        ? "vector" : "list";

    for (int i = 1; i <= kiekisPaleidimu; i++)
    {
        cout << endl << "========== TESTAS " << i << " / "
            << kiekisPaleidimu << " ==========" << endl;

        TestoRezultatas r;

        if (konteineris == 1)
            r = testuotiVienaFailaVector(
                failoVardas, studentuKiekis,
                kriterijus, rikiavimoKriterijus);
        else
            r = testuotiVienaFailaList(
                failoVardas, studentuKiekis,
                kriterijus, rikiavimoKriterijus);

        if (studentuKiekis == 0)
            studentuKiekis = r.kiekis;

        skaitymas += r.nuskaitymoLaikas;
        rikiavimas += r.rikiavimoLaikas;
        skirstymas += r.dalijimoLaikas;
        vargsiukai += r.vargsiukuIsvedimoLaikas;
        kietiakiai += r.kietiakuIsvedimoLaikas;
        bendras += r.bendrasLaikas;
    }

    double daliklis = static_cast<double>(kiekisPaleidimu);

    cout << endl;
    cout << "========== TESTU VIDURKIAI ==========" << endl;
    cout << "Konteineris: " << konteinerioPav << endl;
    cout << "Failas: " << failoVardas << endl;
    cout << "Studentu skaicius: " << studentuKiekis << endl;

    cout << fixed << std::setprecision(6);

    cout << "Failo nuskaitymas: "
        << skaitymas / daliklis << " s" << endl;

    cout << "Studentu rikiavimas: "
        << rikiavimas / daliklis << " s" << endl;

    cout << "Studentu skirstymas: "
        << skirstymas / daliklis << " s" << endl;

    cout << "Vargsiuku failo rasymas: "
        << vargsiukai / daliklis << " s" << endl;

    cout << "Kietiakiu failo rasymas: "
        << kietiakiai / daliklis << " s" << endl;

    cout << "Bendras laikas: "
        << bendras / daliklis << " s" << endl;

    std::ofstream out("v03_rezultatai.csv", std::ios::app);

    if (out)
    {
        out << konteinerioPav << ','
            << failoVardas << ','
            << studentuKiekis << ','
            << kriterijus << ','
            << rikiavimoKriterijus << ','
            << skaitymas / daliklis << ','
            << rikiavimas / daliklis << ','
            << skirstymas / daliklis << ','
            << vargsiukai / daliklis << ','
            << kietiakiai / daliklis << ','
            << bendras / daliklis << '\n';
    }
}
