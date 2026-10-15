// funkcje do redukcji kolorów i tworzenia palet
#include "GK2026-Paleta.h"
#include "GK2026-Zmienne.h"
#include "GK2026-Funkcje.h"

void narzuconaV1() {
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++) {
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>5;
            nowyG = G>>5;
            nowyB = B>>6;

            R = nowyR<<5;
            G = nowyG<<5;
            B = nowyB<<6;

            setPixel(x + szerokosc/2, y, R, G, B);
        }
    }
}

void narzuconaV2(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for (int y=0; y<wysokosc/2; y++) {
        for(int x=0; x<szerokosc/2; x++) {
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>5;
            nowyG = G>>5;
            nowyB = B>>6;

            R = nowyR*255.0/7.0;
            G = nowyG*255.0/7.0;
            B = nowyB*255.0/3.0;

            setPixel(x,y + wysokosc/2, R, G, B);
        }
    }
}

void narzuconaV3(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for (int y=0; y<wysokosc/2; y++) {
        for(int x=0; x<szerokosc/2; x++) {
             kolor = getPixel(x, y);

             R = kolor.r;
             G = kolor.g;
             B = kolor.b;

             nowyR = round(R*7.0/255.0);
             nowyG = round(G*7.0/255.0);
             nowyB = round(B*3.0/255.0);

             R = nowyR*255.0/7.0;
             G = nowyG*255.0/7.0;
             B = nowyB*255.0/3.0;

             setPixel(x + szerokosc/2, y + wysokosc/2, R, G, B);
        }
    }
    SDL_UpdateWindowSurface(window);
}

Uint8 z24Kdo8K(SDL_Color kolor) {
    Uint8 kolor8bit;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    nowyR = round(R*7.0/255.0); // (0-7);
    nowyG = round(G*7.0/255.0); // (0-7);
    nowyB = round(B*3.0/255.0); // (0-3);

    kolor8bit = (nowyR<<5) | (nowyG<<2) | nowyB; //RRRGGGBB

    return kolor8bit;
}

SDL_Color z8Kdo24K(Uint8 kolor8bit) {

    SDL_Color kolor;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    nowyR = (kolor8bit&(0b11100000))>>5; // RRRGGGBB -> RRR00000 -> RRR
    nowyG = (kolor8bit&(0b00011100))>>2; // RRRGGGBB -> 000GGG00 -> GGG
    nowyB = (kolor8bit&(0b00000011)); //RRRGGGBB -> 000000BB -> BB

    R = nowyR*255.0/7.0;
    G = nowyG*255.0/7.0;
    B = nowyB*255.0/3.0;

    kolor.r = R;
    kolor.g = G;
    kolor.b = B;

    return kolor;
}

void paletaNarzucona() {
    Uint8 kolor8bit, szary8bit;
    SDL_Color kolor, nowyKolor, nowySzary;

    for (int y=0; y<wysokosc/2; y++){
        for (int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            kolor8bit= z24Kdo8K(kolor);
            nowyKolor = z8Kdo24K(kolor8bit);
            setPixel(x + szerokosc/2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }

    for (int k = 0; k<256; k++) {
    paleta8k[k] = z8Kdo24K(k);
    }
    narysujPalete(0, 210, paleta8k);

    SDL_UpdateWindowSurface(window);
}

void narysujPalete(int px, int py, SDL_Color pal8[]) {
    int x, y;
    for (int k=0; k<256; k++){
        y = k / 32;
        x = k % 32;

        for (int xx=0; xx<10; xx++) {
            for (int yy=0; yy<10; yy++) {
                setPixel(x*18+xx+px, y*18+yy+py, pal8[k].r, pal8[k].g, pal8[k].b);
            }
        }
    }
}
//Zadanie

Uint8 z24Kdo4K(SDL_Color kolor) {
    int R = kolor.r;
    int G = kolor.g;
    int B = kolor.b;

    int nowyR = round(R * 3.0 / 255.0); // 2 bity (zakres 0-3)
    int nowyG = round(G * 1.0 / 255.0); // 1 bit  (zakres 0-1)
    int nowyB = round(B * 1.0 / 255.0); // 1 bit  (zakres 0-1)

    // Składanie w 4 bity: R R G B
    Uint8 kolor4bit = (nowyR << 2) | (nowyG << 1) | nowyB;

    return kolor4bit;
}

SDL_Color z4Kdo24K(Uint8 kolor4bit) {
    SDL_Color kolor;

    int nowyR = (kolor4bit & 0b00001100) >> 2; // bity 3 i 2
    int nowyG = (kolor4bit & 0b00000010) >> 1; // bit 1
    int nowyB = (kolor4bit & 0b00000001);      // bit 0

    kolor.r = round(nowyR * 255.0 / 3.0);
    kolor.g = round(nowyG * 255.0 / 1.0); // da 0 lub 255
    kolor.b = round(nowyB * 255.0 / 1.0); // da 0 lub 255

    return kolor;
}


Uint8 z24Kdo4S(SDL_Color kolor) {
    double Y = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;


    Uint8 szary4bit = round(Y * 15.0 / 255.0);

    return szary4bit;
}

SDL_Color z4Sdo24K(Uint8 szary4bit) {
    SDL_Color kolor;

    Uint8 Y = round(szary4bit * 255.0 / 15.0);

    kolor.r = Y;
    kolor.g = Y;
    kolor.b = Y;

    return kolor;
}

void narysujPalete16(int px, int py, SDL_Color pal16[]) {
    for (int k = 0; k < 16; k++) {
        int y = k / 4; // 4 wiersze
        int x = k % 4; // 4 kolumny

        for (int xx = 0; xx < 25; xx++) {
            for (int yy = 0; yy < 25; yy++) {
                setPixel(x * 28 + xx + px, y * 28 + yy + py, pal16[k].r, pal16[k].g, pal16[k].b);
            }
        }
    }
}

void paletaNarzucona4K() {
    SDL_Color paleta4k[16];

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            SDL_Color kolor = getPixel(x, y);
            Uint8 k4 = z24Kdo4K(kolor);
            SDL_Color nowyKolor = z4Kdo24K(k4);
            setPixel(x + szerokosc / 2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }

    for (int k = 0; k < 16; k++) {
        paleta4k[k] = z4Kdo24K(k);
    }
    narysujPalete16(0, 210, paleta4k);
    SDL_UpdateWindowSurface(window);
}

void paletaNarzucona4S() {
    SDL_Color paleta4s[16];

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            SDL_Color kolor = getPixel(x, y);
            Uint8 s4 = z24Kdo4S(kolor);
            SDL_Color nowyKolor = z4Sdo24K(s4);
            setPixel(x + szerokosc / 2, y + wysokosc / 2, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }

    for (int k = 0; k < 16; k++) {
        paleta4s[k] = z4Sdo24K(k);
    }
    narysujPalete16(150, 210, paleta4s);
    SDL_UpdateWindowSurface(window);
}

// ==================== DITHERING BAYERA 4x4 ====================

// Tablica Bayera 4x4 zgodnie ze skryptem PDF (wartosci 1..16)
const int bayer4x4[4][4] = {
    { 6, 14,  8, 16},
    {10,  2, 12,  4},
    { 7, 15,  5, 13},
    {11,  3,  9,  1}
};

// Funkcja pomocnicza kwantyzujaca pojedyncza skladowa (0..255) do zakresu (0..maxPoziom)
// z wykorzystaniem tablicy Bayera 4x4
int kwantyzujBayer(double wartosc, int maxPoziom, int x, int y) {
    if (wartosc >= 255.0) return maxPoziom;
    if (wartosc <= 0.0) return 0;

    double przedzial = 255.0 / maxPoziom;
    int baza = (int)(wartosc / przedzial);
    if (baza >= maxPoziom) return maxPoziom;

    // Reszta wewnatrz aktualnego przedzialu kwantyzacji
    double lokalna = wartosc - baza * przedzial;
    // Podzial progu (szerokosci przedzialu) przez r*r = 16
    double p = przedzial / 16.0;

    if (lokalna < p * bayer4x4[y % 4][x % 4]) {
        return baza;
    } else {
        return baza + 1;
    }
}

// Konwersja 24-bit -> 4-bit skala szarosci (16 odcieni) z ditheringiem Bayera 4x4
Uint8 z24Kdo4S_Bayer(SDL_Color kolor, int x, int y) {
    double Y = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;
    Uint8 szary4bit = kwantyzujBayer(Y, 15, x, y);
    return szary4bit;
}

// Konwersja 24-bit -> 4-bit kolor RRGB (2-1-1) z ditheringiem Bayera 4x4
Uint8 z24Kdo4K_Bayer(SDL_Color kolor, int x, int y) {
    int nowyR = kwantyzujBayer(kolor.r, 3, x, y); // 2 bity (0-3)
    int nowyG = kwantyzujBayer(kolor.g, 1, x, y); // 1 bit  (0-1)
    int nowyB = kwantyzujBayer(kolor.b, 1, x, y); // 1 bit  (0-1)

    return (nowyR << 2) | (nowyG << 1) | nowyB;
}

// Konwersja 24-bit -> 8-bit kolor RRRGGGBB (3-3-2) z ditheringiem Bayera 4x4
Uint8 z24Kdo8K_Bayer(SDL_Color kolor, int x, int y) {
    int nowyR = kwantyzujBayer(kolor.r, 7, x, y); // 3 bity (0-7)
    int nowyG = kwantyzujBayer(kolor.g, 7, x, y); // 3 bity (0-7)
    int nowyB = kwantyzujBayer(kolor.b, 3, x, y); // 2 bity (0-3)

    return (nowyR << 5) | (nowyG << 2) | nowyB;
}

// Konwersja 24-bit -> 3-bit skala szarosci (8 odcieni z przykladu w PDF) z ditheringiem Bayera 4x4
Uint8 z24Kdo3S_Bayer(SDL_Color kolor, int x, int y) {
    double Y = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;
    Uint8 szary3bit = kwantyzujBayer(Y, 7, x, y);
    return szary3bit;
}

SDL_Color z3Sdo24K(Uint8 szary3bit) {
    SDL_Color kolor;
    Uint8 Y = round(szary3bit * 255.0 / 7.0);
    kolor.r = Y;
    kolor.g = Y;
    kolor.b = Y;
    return kolor;
}

// Zadanie 1: Paleta narzucona szara (4-bit, 16 odcieni) + Dithering Bayera 4x4
void paletaNarzucona4SDithering() {
    SDL_Color paleta4s[16];
    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            SDL_Color kolor = getPixel(x, y);
            Uint8 s4 = z24Kdo4S_Bayer(kolor, x, y);
            SDL_Color nowyKolor = z4Sdo24K(s4);
            setPixel(x + szerokosc / 2, y + wysokosc / 2, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }
    for (int k = 0; k < 16; k++) {
        paleta4s[k] = z4Sdo24K(k);
    }
    narysujPalete16(150, 210, paleta4s);
    SDL_UpdateWindowSurface(window);
}

// Zadanie 2: Paleta narzucona kolorowa (4-bit RRGB) + Dithering Bayera 4x4
void paletaNarzucona4KDithering() {
    SDL_Color paleta4k[16];
    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            SDL_Color kolor = getPixel(x, y);
            Uint8 k4 = z24Kdo4K_Bayer(kolor, x, y);
            SDL_Color nowyKolor = z4Kdo24K(k4);
            setPixel(x + szerokosc / 2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }
    for (int k = 0; k < 16; k++) {
        paleta4k[k] = z4Kdo24K(k);
    }
    narysujPalete16(0, 210, paleta4k);
    SDL_UpdateWindowSurface(window);
}

// Przyklad ze skryptu PDF: RGB 3-3-2 (8-bit) + 8 odcieni szarosci (3-bit) z ditheringiem Bayera 4x4
void paletaNarzucona8KDithering() {
    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            SDL_Color kolor = getPixel(x, y);

            // Prawy gorny rog: kolor 8-bit (3-3-2) z ditheringiem
            Uint8 kolor8bit = z24Kdo8K_Bayer(kolor, x, y);
            SDL_Color nowyKolor = z8Kdo24K(kolor8bit);
            setPixel(x + szerokosc / 2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);

            // Prawy dolny rog: 8 odcieni szarosci (3-bit) z ditheringiem
            Uint8 szary3bit = z24Kdo3S_Bayer(kolor, x, y);
            SDL_Color nowySzary = z3Sdo24K(szary3bit);
            setPixel(x + szerokosc / 2, y + wysokosc / 2, nowySzary.r, nowySzary.g, nowySzary.b);
        }
    }

    for (int k = 0; k < 256; k++) {
        paleta8k[k] = z8Kdo24K(k);
    }
    narysujPalete(0, 210, paleta8k);
    SDL_UpdateWindowSurface(window);
}
