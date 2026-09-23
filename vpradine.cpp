#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

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

struct studentas
{
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};

double skaiciuotiVidurki(studentas A)
{
    double suma = 0;

    for (int i = 0; i < A.paz.size(); i++)
    {
        suma += A.paz[i];
    }

    return suma / A.paz.size();
}

double skaiciuotiMediana(studentas A)
{
    sort(A.paz.begin(), A.paz.end());

    int n = A.paz.size();

    if (n % 2 == 1)
        return A.paz[n / 2];
    else
        return (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
}

int main()
{
    vector<studentas> grupe;
    studentas A;

    cout << "Kiek studentu yra sarase: ";
    int n;
    cin >> n;

    int nd;
    cout << "Ar zinomas namu darbu skaicius?" << endl; cout << "1 - Taip" << endl; cout << "2 - Ne" << endl; cout << "Pasirinkite: "; cin >> nd;
    

    for (int i = 0; i < n; i++)
    {
        
        cout << "Iveskite studento varda ir pavarde: ";
        cin >> A.vardas >> A.pavarde;

        if (nd==1)
        {
            int k;
            cout << "Iveskite namu darbu kieki: ";
            cin >> k;

            for (int i=0; i <k; i++)
            {
                int a;
                cout << "Iveskite " << i + 1 << " pazymi: ";
                cin >> a;
                A.paz.push_back(a);
            }
        }
        else if (nd== 2)
        {
            string ivestis;
            int a;

            cout << "Iveskite namu darbu pazymius(veskite skaiciu ir spauskite enter arba 'N' kad sustoti) :" <<endl;

            while (true)
            {
                cin >> ivestis;

                if (ivestis == "N" || ivestis == "n")
                    break;

                a = std::stoi(ivestis);
                A.paz.push_back(a);
            }
        }
       

        cout << "Iveskite egzamino pazymi: ";
        cin >> A.exam;

        grupe.push_back(A);

        A.vardas.clear();
        A.pavarde.clear();
        A.paz.clear();
    }

    int pasirinkimas;
    cout << "pasirinkite kaip norit atspausdint duomenis" << endl;
    cout << endl; cout << "1 - Vidurkis" << endl; cout << "2 - Mediana" << endl; cout << "3 - Abu" << endl; cout << "Pasirinkite: "; cin >> pasirinkimas;

    switch (pasirinkimas)
    {
        case 1:
            cout << endl;
            cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
            cout << "---------------------------------------------\n";

            for (studentas B : grupe)
            {
                double vidurkis = skaiciuotiVidurki(B);
                double galutinis = 0.4 * vidurkis + 0.6 * B.exam;

                cout << left << setw(15) << B.pavarde << setw(15) << B.vardas << fixed << setprecision(2) << galutinis << endl;
            }
            break;

        case 2:
            cout << endl;
            cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
            cout << "---------------------------------------------\n";

            for (studentas B : grupe)
            {
                double mediana = skaiciuotiMediana(B);
                double galutinis = 0.4 * mediana + 0.6 * B.exam;

                cout << left << setw(15) << B.pavarde << setw(15) << B.vardas << fixed << setprecision(2) << galutinis << endl;
            }
            break;

        case 3:
            cout << endl;
            cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
            cout << "-------------------------------------------------------------\n";

            for (studentas B : grupe)
            {
                double vidurkis = skaiciuotiVidurki(B);
                double mediana = skaiciuotiMediana(B);

                double galutinisVid = 0.4 * vidurkis + 0.6 * B.exam;
                double galutinisMed = 0.4 * mediana + 0.6 * B.exam;

                cout << left << setw(15) << B.pavarde << setw(15) << B.vardas << setw(20) << fixed << setprecision(2) << galutinisVid << setw(20) << galutinisMed << endl;
            }
            break;

        default:
            cout << "Neegzistuoja toks pasirinkimas." << endl;
    }

    return 0;
}
