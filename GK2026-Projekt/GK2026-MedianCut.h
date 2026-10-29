#ifndef GK2026_MEDIANCUT_H_INCLUDED
#define GK2026_MEDIANCUT_H_INCLUDED

#include <SDL2/SDL.h>

void paletaMedianCutBW();
void MedianCutBW(int start, int koniec, int iteracja);
void sortujKubelekBW(int start, int koniec);
int znajdzSasiadaBW(Uint8 wartosc);

void paletaMedianCut();
void MedianCut(int start, int koniec, int iteracja);
Uint8 najwiekszaRoznica(int start, int koniec);
void sortujKubelek(int start, int koniec, Uint8 sortowanie);
int znajdzSasiada(SDL_Color kolor);

#endif // GK2026_MEDIANCUT_H_INCLUDED
