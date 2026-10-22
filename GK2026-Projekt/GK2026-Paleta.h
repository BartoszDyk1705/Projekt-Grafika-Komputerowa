// funkcje do redukcji kolorów i tworzenia palet
#ifndef GK2026_PALETA_H_INCLUDED
#define GK2026_PALETA_H_INCLUDED

#include <SDL2/SDL.h>

// --- paleta narzucona (z poprzednich zajec) ---
void narzuconaV1();
void narzuconaV2();
void narzuconaV3();
Uint8 z24Kdo8K(SDL_Color kolor);
SDL_Color z8Kdo24K(Uint8 kolor8bit);
void paletaNarzucona();
void narysujPalete(int px, int py, SDL_Color pal8[]);

Uint8 z24Kdo4K(SDL_Color kolor);
SDL_Color z4Kdo24K(Uint8 kolor4bit);
Uint8 z24Kdo4S(SDL_Color kolor);
SDL_Color z4Sdo24K(Uint8 szary4bit);
void narysujPalete16(int px, int py, SDL_Color pal16[]);
void paletaNarzucona4K();
void paletaNarzucona4S();

// --- dithering Bayera ---
int kwantyzujBayer(double wartosc, int maxPoziom, int x, int y);
Uint8 z24Kdo4S_Bayer(SDL_Color kolor, int x, int y);
Uint8 z24Kdo4K_Bayer(SDL_Color kolor, int x, int y);
Uint8 z24Kdo8K_Bayer(SDL_Color kolor, int x, int y);
Uint8 z24Kdo3S_Bayer(SDL_Color kolor, int x, int y);
SDL_Color z3Sdo24K(Uint8 szary3bit);
void paletaNarzucona4SDithering();
void paletaNarzucona4KDithering();
void paletaNarzucona8KDithering();

// --- paleta wykryta (dedykowana obrazkowi) ---
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int  dodajKolor(SDL_Color kolor);
int  sprawdzKolor(SDL_Color kolor);
void czyscPalete();
void paletaWykryta();            // wersja 4-bitowa (maks. 16 kolorow)

#endif // GK2026_PALETA_H_INCLUDED
