#ifndef GLOBALS_H
#define GLOBALS_H

//*********************************************************************************************//
//                                      Plik globals.h                                         //
//*********************************************************************************************//

#include <SDL/SDL.h>
#include "paletka.h"

extern SDL_Surface *screen;
extern SDL_Surface *gscreen;
extern SDL_Surface *temp;
extern SDL_Surface *texture;
extern SDL_Surface *grid;
extern SDL_Surface *czas;

extern SDL_Event event;

extern SDL_Rect offset;

extern Paletka paletka;

extern void render();

//*********************************************************************************************//
//                                   Koniec pliku globals.h                                    //
//*********************************************************************************************//
#endif

