#include "Failai.h"

template <typename Container>
void skirstyti(const Container& grupe, Container& vargsiukai,
    Container& kietiakiai, int kriterijus)
{
    vargsiukai.clear();
    kietiakiai.clear();

    for (const Studentas& A : grupe)
    {
        double balas = (kriterijus == 2)
            ? A.galutinisMed
            : A.galutinisVid;

        if (balas < 5.0)
            vargsiukai.push_back(A);
        else
            kietiakiai.push_back(A);
    }
}

void skirstytiIGrupes(const std::vector<Studentas>& grupe,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai,
    int kriterijus)
{
    skirstyti(grupe, vargsiukai, kietiakiai, kriterijus);
}

void skirstytiIGrupes(const std::list<Studentas>& grupe,
    std::list<Studentas>& vargsiukai,
    std::list<Studentas>& kietiakiai,
    int kriterijus)
{
    skirstyti(grupe, vargsiukai, kietiakiai, kriterijus);
}
