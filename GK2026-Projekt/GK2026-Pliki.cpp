#include "GK2026-Funkcje.h"
#include "GK2026-Zmienne.h"
#include "GK2026-Paleta.h"
#include "GK2026-MedianCut.h"
#include "GK2026-Pliki.h"

#include <iostream>
using namespace std;

void zapiszPlikv0() {
    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    Uint8 ileBitow = 24;

    cout << "Zapisywanie 'obraz.bin' uzywajac operatora <<" << endl;
    ofstream wyjscie("obraz.bin");

    wyjscie << "DG";
    wyjscie << (Uint8)(szerokoscObrazka) << (Uint8)(szerokoscObrazka >> 8);
    wyjscie << (Uint8)(wysokoscObrazka) << (Uint8)(wysokoscObrazka >> 8);
    wyjscie << ileBitow;

    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            wyjscie << kolor.r << kolor.g << kolor.b;
        }
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

void zapiszPlik() {
    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    Uint8 ileBitow = 24;
    char identyfikator[] = "DG";

    cout << "Zapisywanie'obrazRGB.bin' uzywajac metody write()" << endl;
    ofstream wyjscie("obrazRGB.bin", ios::binary);

    wyjscie.write((char*)&identyfikator, sizeof(char) * 2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            wyjscie.write((char*)&kolor, sizeof(Uint8) * 3);
        }
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

void odczytajPlik() {
    SDL_Color kolor;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = "  ";

    cout << "Odczyt pliku 'obrazRGB.bin' uzywajac metody read()" << endl;
    ifstream wejscie("obrazRGB.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char) * 2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;
    cout << "ile bitow: " << (int)ileBitow << endl;

    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            wejscie.read((char*)&kolor, sizeof(Uint8) * 3);
            setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
        }
    }

    wejscie.close();
    SDL_UpdateWindowSurface(window);
}

void zapiszPlik8() {
    SDL_Color kolor;
    Uint8 kolor8bit;
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    Uint8 ileBitow = 8;
    char identyfikator[] = "DG";

    cout << "Zapisywanie plik 'obraz8.bin' uzywajac metody write()" << endl;
    ofstream wyjscie("obraz8.bin", ios::binary);

    wyjscie.write((char*)&identyfikator, sizeof(char) * 2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            wyjscie.write((char*)&kolor8bit, sizeof(Uint8));
        }
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

void odczytajPlik8() {
    SDL_Color kolor;
    Uint8 kolor8bit = 0;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = "  ";

    cout << "Odczyt pliku 'obraz8.bin' uzywajac metody read()" << endl;
    ifstream wejscie("obraz8.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char) * 2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;
    cout << "ile bitow: " << (int)ileBitow << endl;

    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            wejscie.read((char*)&kolor8bit, sizeof(Uint8));
            kolor = z8Kdo24K(kolor8bit);
            setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
        }
    }

    wejscie.close();
    SDL_UpdateWindowSurface(window);
}

// Tryby:
// 1 - obraz z narzucona paleta kolorowa (4-bit RRGB)
// 2 - obraz z narzucona skala szarosci (4-bit, 16 odcieni)
// 3 - obraz z paleta wykryta (maks. 16 kolorow)
// 4 - obraz z dedykowana skala szarosci (MedianCut 4-bit)
// 5 - obraz z dedykowana paleta kolorowa (MedianCut 4-bit)

void zapiszPlik4(Uint8 tryb) {
    SDL_Color kolor;
    Uint8 wartosc4bit = 0;
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    Uint8 ileBitow = 4;
    char identyfikator[] = "DG";

    if (tryb == 3) {
        paletaWykryta();
        if (ileKolorow > 16) {
            cout << "Obrazek ma wiecej niz 16 kolorow (" << ileKolorow
                 << ") - zapis w trybie 3 (paleta wykryta) wymaga obrazka <= 16 kolorow" << endl;
            return;
        }
    } else if (tryb == 4) {
        paletaMedianCutBW();
    } else if (tryb == 5) {
        paletaMedianCut();
    }

    cout << endl << "Zapisywanie pliku 'obraz4.bin' (4-bit, tryb: " << (int)tryb << ")..." << endl;
    ofstream wyjscie("obraz4.bin", ios::binary);

    wyjscie.write((char*)&identyfikator, sizeof(char) * 2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));
    wyjscie.write((char*)&tryb, sizeof(Uint8));

    if (tryb == 3) {
        for (int k = 0; k < 16; k++) {
            wyjscie.write((char*)&paleta8[k], sizeof(Uint8) * 3);
        }
    } else if (tryb == 4) {
        for (int k = 0; k < 16; k++) {
            wyjscie.write((char*)&paleta8s[k], sizeof(Uint8) * 3);
        }
    } else if (tryb == 5) {
        for (int k = 0; k < 16; k++) {
            wyjscie.write((char*)&paleta8k[k], sizeof(Uint8) * 3);
        }
    }

    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = getPixel(x, y);

            switch (tryb) {
                case 1: // Narzucona kolorowa 4-bit
                    wartosc4bit = z24Kdo4K(kolor);
                    break;
                case 2: // Narzucona szara 4-bit
                    wartosc4bit = z24Kdo4S(kolor);
                    break;
                case 3: // Paleta wykryta
                    wartosc4bit = (Uint8)sprawdzKolor(kolor);
                    break;
                case 4: { // MedianCut skala szarosci
                    Uint8 szary = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;
                    wartosc4bit = (Uint8)znajdzSasiadaBW(szary);
                    break;
                }
                case 5: // MedianCut kolor
                    wartosc4bit = (Uint8)znajdzSasiada(kolor);
                    break;
            }

            wyjscie.write((char*)&wartosc4bit, sizeof(Uint8));
        }
    }

    wyjscie.close();
    cout << "Zapis zakonczony." << endl;
}

void odczytajPlik4() {
    SDL_Color kolor;
    Uint8 wartosc4bit = 0;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    Uint8 tryb = 0;
    char identyfikator[] = "  ";
    SDL_Color paletaOdczytana[16];

    cout << endl << "Odczyt pliku 'obraz4.bin' uzywajac metody read()..." << endl;
    ifstream wejscie("obraz4.bin", ios::binary);

    if (!wejscie.is_open()) {
        cout << "Nie mozna otworzyc pliku 'obraz4.bin'" << endl;
        return;
    }

    wejscie.read((char*)&identyfikator, sizeof(char) * 2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));
    wejscie.read((char*)&tryb, sizeof(Uint8));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;
    cout << "ile bitow: " << (int)ileBitow << endl;
    cout << "tryb: " << (int)tryb << endl;

    if (tryb == 3 || tryb == 4 || tryb == 5) {
        for (int k = 0; k < 16; k++) {
            wejscie.read((char*)&paletaOdczytana[k], sizeof(Uint8) * 3);
        }
    } else if (tryb == 1) {
        for (int k = 0; k < 16; k++) {
            paletaOdczytana[k] = z4Kdo24K(k);
        }
    } else if (tryb == 2) {
        for (int k = 0; k < 16; k++) {
            paletaOdczytana[k] = z4Sdo24K(k);
        }
    }

    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            wejscie.read((char*)&wartosc4bit, sizeof(Uint8));

            if (tryb == 1) {
                kolor = z4Kdo24K(wartosc4bit);
            } else if (tryb == 2) {
                kolor = z4Sdo24K(wartosc4bit);
            } else {
                kolor = paletaOdczytana[wartosc4bit & 0x0F];
            }

            setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
        }
    }

    wejscie.close();

    if (tryb == 2 || tryb == 4) {
        narysujPalete16(150, 210, paletaOdczytana);
    } else {
        narysujPalete16(0, 210, paletaOdczytana);
    }

    SDL_UpdateWindowSurface(window);
}
