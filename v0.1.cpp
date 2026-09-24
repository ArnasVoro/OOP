#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::sort;
using std::ifstream;
using std::getline;
using std::stringstream;


struct studentas
{
    string vardas, pavarde;
    vector<int> paz;
};

double skaiciuotiVidurki(studentas A)
{
    double suma = 0;

    for (int i = 0; i < A.paz.size() - 1; i++)
    {
        suma += A.paz[i];
    }

    return suma / (A.paz.size() - 1);
}

double skaiciuotiMediana(studentas A)
{
    vector<int> nd;

    for (int i = 0; i < A.paz.size() - 1; i++)
    {
        nd.push_back(A.paz[i]);
    }

    sort(nd.begin(), nd.end());

    int n = nd.size();

    if (n % 2 == 1)
        return nd[n / 2];
    else
        return (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
}

bool rikiuotiPagalVarda(studentas A, studentas B)
{
    return A.vardas < B.vardas;
}

int main()
{
    srand(time(0));

    vector<studentas> grupe;
    studentas A;

    int budas;

    cout << "Kaip norite ivesti duomenis?" << endl;cout << "1 - Ivesti duomenis rankiniu budu" << endl;cout << "2 - Nuskaityti duomenis is failo" << endl;cout << "Pasirinkite: ";cin >> budas;

    if (budas != 1 && budas != 2)
    {
        cout << "Tokio pasirinkimo nera." << endl;
        return 0;
    }

    if (budas == 2)
    {
        ifstream failas("kursiokai.txt");

        if (!failas)
        {
            cout << "Nepavyko atidaryti failo kursiokai.txt" << endl;
            return 0;
        }

        string eilute;

        getline(failas, eilute);

        while (getline(failas, eilute))
        {
            stringstream ss(eilute);

            A.paz.clear();

            ss >> A.pavarde >> A.vardas;

            int pazymys;

            while (ss >> pazymys)
            {
                A.paz.push_back(pazymys);
            }

            grupe.push_back(A);
        }

        failas.close();

        cout << "Duomenys sekmingai nuskaityti is failo." << endl;
    }
    else
    {
        cout << "Kiek studentu yra sarase: ";

        int n;
        cin >> n;

        int nd;

        cout << "Ar zinomas namu darbu skaicius?" << endl;cout << "1 - Taip" << endl;cout << "2 - Ne" << endl; cout << "Pasirinkite: "; cin >> nd;

        if (nd != 1 && nd != 2)
        {
            cout << "Tokio pasirinkimo nera." << endl;
            return 0;
        }

        int generuoti;

        cout << "Ar norite atsitiktinai sugeneruoti pazymius?" << endl;
        cout << "1 - Taip" << endl;
        cout << "2 - Ne" << endl;
        cout << "Pasirinkite: ";
        cin >> generuoti;

        for (int i = 0; i < n; i++)
        {
            cout << "Iveskite studento varda ir pavarde: ";
            cin >> A.vardas >> A.pavarde;

            if (generuoti == 1)
            {
                int k;

                if (nd == 1)
                {
                    cout << "Iveskite namu darbu kieki: ";
                    cin >> k;
                }
                else
                {
                    k = rand() % 15 + 1;
                }

                cout << "Sugeneruoti namu darbu pazymiai: ";

                for (int i = 0; i < k; i++)
                {
                    int a = rand() % 10 + 1;

                    A.paz.push_back(a);

                    cout << a << " ";
                }

                cout << endl;

                int egz = rand() % 10 + 1;

                A.paz.push_back(egz);

                cout << "Sugeneruotas egzamino pazymys: " << egz << endl;
            }
            else
            {
                if (nd == 1)
                {
                    int k;

                    cout << "Iveskite namu darbu kieki: ";
                    cin >> k;

                    for (int i = 0; i < k; i++)
                    {
                        int a;

                        do
                        {
                            cout << "Iveskite " << i + 1 << " pazymi (1-10): ";
                            cin >> a;
                        }
                        while (a < 1 || a > 10);

                        A.paz.push_back(a);
                    }
                }
                else
                {
                    string ivestis;
                    int a;

                    cout << "Iveskite namu darbu pazymius (iveskite skaiciu arba 'N' kad sustoti):" << endl;

                    while (true)
                    {
                        cin >> ivestis;

                        if (ivestis == "N" || ivestis == "n")
                            break;

                        a = std::stoi(ivestis);

                        if (a >= 1 && a <= 10)
                            A.paz.push_back(a);
                        else
                            cout << "Pazymys turi buti nuo 1 iki 10." << endl;
                    }
                }

                int egz;

                do
                {
                    cout << "Iveskite egzamino pazymi (1-10): ";
                    cin >> egz;
                }
                while (egz < 1 || egz > 10);

                A.paz.push_back(egz);
            }

            grupe.push_back(A);

            A.vardas.clear();
            A.pavarde.clear();
            A.paz.clear();
        }
    }

    sort(grupe.begin(), grupe.end(), rikiuotiPagalVarda);

    int pasirinkimas;

    cout << endl; cout << "Pasirinkite kaip norit atspausdinti duomenis" << endl; cout << endl;cout << "1 - Vidurkis" << endl;cout << "2 - Mediana" << endl;cout << "3 - Abu" << endl;
    cout << "Pasirinkite: ";
    cin >> pasirinkimas;

    switch (pasirinkimas)
    {
    case 1:
        cout << endl;
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)" << endl;
        cout << "--------------------------------------------------" << endl;

        for (studentas B : grupe)
        {
            double vidurkis = skaiciuotiVidurki(B);
            int egz = B.paz[B.paz.size() - 1];
            double galutinis = 0.4 * vidurkis + 0.6 * egz;

            cout << left << setw(15) << B.pavarde << setw(15) << B.vardas << setw(20) << fixed << setprecision(2) << galutinis << endl;
        }

        break;

    case 2:
        cout << endl;
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Med.)" << endl;
        cout << "--------------------------------------------------" << endl;

        for (studentas B : grupe)
        {
            double mediana = skaiciuotiMediana(B);
            int egz = B.paz[B.paz.size() - 1];
            double galutinis = 0.4 * mediana + 0.6 * egz;

            cout << left << setw(15) << B.pavarde << setw(15) << B.vardas << setw(20) << fixed << setprecision(2) << galutinis << endl;
        }

        break;

    case 3:
        cout << endl;
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
        cout << "---------------------------------------------------------------------" << endl;

        for (studentas B : grupe)
        {
            double vidurkis = skaiciuotiVidurki(B);
            double mediana = skaiciuotiMediana(B);
            int egz = B.paz[B.paz.size() - 1];

            double galutinisVid = 0.4 * vidurkis + 0.6 * egz;
            double galutinisMed = 0.4 * mediana + 0.6 * egz;

            cout << left << setw(15) << B.pavarde << setw(15) << B.vardas << setw(20) << fixed << setprecision(2) << galutinisVid << setw(20) << galutinisMed << endl;
        }

        break;

    default:
        cout << "Neegzistuoja toks pasirinkimas." << endl;
    }

    return 0;
}
