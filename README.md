### System Specifications

- **CPU:** AMD Ryzen 7 3800X (8 Cores / 16 Threads)
- **RAM:** 16 GB DDR4 @ 3600 MHz
- **Storage:** 1 TB Samsung 970 EVO M.2 NVMe SSD



#  Studentų pažymių valdymo sistema

##  Projekto aprašymas

Šis projektas – **C++ kalba sukurta studentų pažymių valdymo ir apdorojimo sistema**, skirta studentų akademiniams rezultatams analizuoti, galutiniams įvertinimams apskaičiuoti bei studentams suskirstyti į atitinkamas kategorijas pagal jų mokymosi rezultatus.

Programa leidžia dirbti tiek su nedideliais, rankiniu būdu įvedamais studentų duomenų kiekiais, tiek su dideliais duomenų rinkiniais, nuskaitomais iš tekstinių failų. Taip pat realizuotas atsitiktinių duomenų generavimas, leidžiantis atlikti įvairius našumo testus ir įvertinti programos efektyvumą apdorojant skirtingo dydžio duomenų rinkinius.

Projektas buvo kuriamas palaipsniui, išleidžiant kelias programos versijas. Kiekvienoje versijoje buvo siekiama ne tik papildyti funkcionalumą, bet ir gerinti programos struktūrą, optimizuoti algoritmus bei efektyviau panaudoti C++ standartinės bibliotekos (STL) teikiamas galimybes.



<h1 align="center"> PROJEKTO TIKSLAS</h1>

<p align="center">
  <strong>
    Pagrindinis projekto tikslas – sukurti patogią ir efektyvią studentų pažymių apdorojimo sistemą bei praktiškai išanalizuoti C++ standartinės bibliotekos galimybes.
  </strong>
</p>

<h2> PROJEKTO METU SIEKIAMA:</h2>

<h3> 1. Išmokti naudoti skirtingus C++ konteinerius</h3>

<h3> 2. Pritaikyti STL algoritmus realiai programavimo užduočiai</h3>

<h3> 3. Išanalizuoti skirtingų studentų skirstymo strategijų veikimo principus</h3>

<h3> 4. Palyginti <code>vector</code> ir <code>list</code> konteinerių našumą</h3>

<h3> 5. Išmatuoti skirtingų algoritmų vykdymo laiką</h3>

<h3> 6. Išsiaiškinti, kaip duomenų kiekis veikia programos efektyvumą</h3>

<h3> 7. Optimizuoti programos veikimą dirbant su dideliais duomenų rinkiniais</h3>

<h3> 8. Įvertinti atminties ir vykdymo laiko sąnaudas</h3>







Testuoti penki skirtingi duomenų failai:
1. 1 000 studentų
2. 10 000 studentų
3. 100 000 studentų
4. 1 000 000 studentų
5. 10 000 000 studentų



| Studentų skaičius | Konteineris | Failo nuskaitymas (s) | Rikiavimas (s) | Skirstymas (s) | Vargšiukų failas (s) | Kietiakių failas (s) | Bendras laikas (s) |
|------------------:|-------------|----------------------:|---------------:|---------------:|---------------------:|--------------------:|-------------------:|
| 1 000 | vector | 0.072649 | 0.020637 | 0.006211 | 0.006918 | 0.006579 | 0.112994 |
| 1 000 | list | 0.065522 | 0.001367 | 0.002144 | 0.004779 | 0.007838 | 0.081650 |
| 10 000 | vector | 0.712667 | 0.325492 | 0.067922 | 0.041988 | 0.063003 | 1.211070 |
| 10 000 | list | 0.667887 | 0.016687 | 0.021538 | 0.040585 | 0.060085 | 0.806782 |
| 100 000 | vector | 7.438225 | 4.448669 | 0.601334 | 0.453352 | 0.706324 | 13.647905 |
| 100 000 | list | 7.017563 | 0.225582 | 0.221262 | 0.423269 | 0.667525 | 8.555201 |
| 1 000 000 | vector | 73.156377 | 51.541819 | 6.939718 | 4.241357 | 6.642869 | 142.526139 |
| 1 000 000 | list | 69.817362 | 2.673431 | 3.224230 | 4.251404 | 6.501663 | 85.568090 |
| 10 000 000 | vector | 326.316958 | 267.296125 | 36.084089 | 18.195724 | 27.001418 | 674.890714 |
| 10 000 000 | list | 306.118300 | 13.201357 | 10.069195 | 17.846694 | 27.180364 | 374.415910 |  




Išvados

Atlikus našumo testus su vector ir list konteineriais, naudojant nuo 1 000 iki 10 000 000 studentų įrašų, pastebėta, kad list konteineris buvo efektyvesnis pagal bendrą programos vykdymo laiką visuose testuose.

Didžiausias skirtumas pastebėtas apdorojant 10 000 000 studentų: naudojant vector, bendras vykdymo laikas siekė 674,89 s, o naudojant list – 374,42 s. Taigi, list šį testą atliko maždaug 44,5 % greičiau.

Taip pat pastebėta, kad list konteineris buvo gerokai greitesnis rikiuojant studentus, ypač dideliuose duomenų rinkiniuose. Tuo tarpu failų nuskaitymo ir studentų skirstymo laikai abiejų konteinerių atvejais buvo panašesni.


<img width="324" height="171" alt="image" src="https://github.com/user-attachments/assets/38971e72-8647-4b22-8955-570354ed0904" />
<img width="330" height="177" alt="image" src="https://github.com/user-attachments/assets/166e0020-759b-4074-90f6-65d5f1cd07c4" />
<img width="328" height="171" alt="image" src="https://github.com/user-attachments/assets/a9f91b9e-f566-47e5-9f75-11937795b3a5" />
<img width="366" height="184" alt="image" src="https://github.com/user-attachments/assets/a48c57be-6566-46ed-9324-eff0f027dd6e" />







## Naudojami STL algoritmai

Projekte naudojami ir lyginami šie STL algoritmai:

- `std::copy_if`
- `std::remove_if`
- `std::partition`
- `std::stable_partition`
- `std::find`

Taip pat naudojamos konteinerių operacijos, tokios kaip `erase()` ir `splice()`.


## Skirstymo strategijos

**1 strategija – kopijavimas į du naujus konteinerius**

Studentai nukopijuojami į du atskirus konteinerius:
- Vargšiukai (galutinis pažymys < 5).
- Kietiakai (galutinis pažymys >= 5).

Originalus konteineris išsaugomas.

**2 strategija – kopijavimas ir šalinimas**

Vargšiukai nukopijuojami į atskirą konteinerį, o iš originalaus konteinerio pašalinami.

**3 strategija – optimizuotas skirstymas**

Naudojamos efektyvesnės konteinerių operacijos ir STL algoritmai, siekiant sumažinti vykdymo laiką.

























| Versija | Pakeitimai |
|---|---|
| v0.1 | Pradinė studentų pažymių apdorojimo programa |
| v0.2 | Pridėtas studentų skirstymas į dvi grupes ir greičio testavimas |
| v0.3 | Optimizuotas studentų skirstymas, palyginti vector ir list konteineriai |
| v1.0 | Palygintos skirtingos STL algoritmų realizacijos, atlikti našumo testai |





