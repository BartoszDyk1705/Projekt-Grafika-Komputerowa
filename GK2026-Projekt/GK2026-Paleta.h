// funkcje do redukcji kolorów i tworzenia palet
#ifndef GK2026_PALETA_H_INCLUDED
#define GK2026_PALETA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

void narzuconaV1();
void narzuconaV2();
void narzuconaV3();

Uint8 z24Kdo8K(SDL_Color kolor);
SDL_Color z8Kdo24K(Uint8 kolor8bit);
void narysujPalete(int px, int py, SDL_Color pal8[]);
void paletaNarzucona();

Uint8 z24Kdo4K(SDL_Color kolor);
SDL_Color z4Kdo24K(Uint8 kolor4bit);
Uint8 z24Kdo4S(SDL_Color kolor);
SDL_Color z4Sdo24K(Uint8 szary4bit);
void narysujPalete16(int px, int py, SDL_Color pal16[]);

void paletaNarzucona4K();
void paletaNarzucona4S();

int kwantyzujBayer(double wartosc, int maxPoziom, int x, int y);
Uint8 z24Kdo4S_Bayer(SDL_Color kolor, int x, int y);
Uint8 z24Kdo4K_Bayer(SDL_Color kolor, int x, int y);
Uint8 z24Kdo8K_Bayer(SDL_Color kolor, int x, int y);
Uint8 z24Kdo3S_Bayer(SDL_Color kolor, int x, int y);
SDL_Color z3Sdo24K(Uint8 szary3bit);

void paletaNarzucona4SDithering();
void paletaNarzucona4KDithering();
void paletaNarzucona8KDithering();

#endif // GK2026_PALETA_H_INCLUDED
