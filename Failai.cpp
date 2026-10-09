#include "Failai.h"
#include <fstream>
#include <random>
#include <stdexcept>

using std::ofstream;

void generuotiFaila(const std::string& failas, int kiekis)
{
    ofstream f(failas);
    if (!f) throw std::runtime_error("Nepavyko sukurti: " + failas);

    
    f << "Vardas Pavarde";
    for (int i = 1; i <= 15; ++i) f << " ND" << i;
    f << " Egz\n";

    std::mt19937 gen(42);
    std::uniform_int_distribution<int> paz(1, 10);

    for (int i = 1; i <= kiekis; ++i)
    {
        f << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < 15; ++j) f << " " << paz(gen);   
        f << " " << paz(gen) << "\n";                         
    }
    f.close();
}

void skirstytiIGrupes(const std::vector<Studentas>& grupe,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai,
    int kriterijus)
{
    vargsiukai.clear();
    kietiakiai.clear();

    for (const Studentas& A : grupe)
    {
        double balas = (kriterijus == 2) ? A.galutinisMed : A.galutinisVid;
        if (balas < 5.0)
            vargsiukai.push_back(A);
        else
            kietiakiai.push_back(A);
    }
}
