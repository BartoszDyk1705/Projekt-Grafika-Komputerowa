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

    SDL_Color
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

}
