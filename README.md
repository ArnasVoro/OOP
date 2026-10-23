### System Specifications

- **CPU:** AMD Ryzen 7 3800X (8 Cores / 16 Threads)
- **RAM:** 16 GB DDR4 @ 3600 MHz
- **Storage:** 1 TB Samsung 970 EVO M.2 NVMe SSD


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


