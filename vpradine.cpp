#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;
struct studentas
{
    string vardas, pavarde;
    vector<int> paz;
    int exam;
    double galutinis;
};

void printas(studentas A);

int main()
{
    int k;
    vector<studentas> grupe;
    studentas A;

    std::cout << "Kiek studentu yra sarase: ";
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Iveskite studento varda ir pavarde: ";
        cin >> A.vardas >> A.pavarde;

        cout << "Iveskite semestro pazymiu kieki: ";
        cin >> k;

        for (int i = 0; i < k; i++)
        {
            int a;
            cout << "Iveskite " << i + 1 << " pazymi: ";
            cin >> a;
            A.paz.push_back(a);
        }

        cout << "Iveskite egzamino pazymi: ";
        cin >> A.exam;

        double suma = 0;

        for (int i = 0; i < A.paz.size(); i++)
        {
            suma += A.paz[i];
        }

        double vidurkis =suma/A.paz.size();

        A.galutinis =0.4*vidurkis + 0.6*A.exam;

        grupe.push_back(A);

        A.vardas.clear();
        A.pavarde.clear();
        A.paz.clear();
    }

    cout <<endl;
    cout <<left <<setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" <<endl;
    cout << "---------------------------------------------\n";

    for (studentas B : grupe)
    {
        printas(B);
    }

    return 0;
}

void printas(studentas A)
{
    cout << left << std::setw(15) << A.pavarde << setw(15) << A.vardas <<fixed <<setprecision(2) << A.galutinis << endl;
}
