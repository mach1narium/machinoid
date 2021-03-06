//*********************************************************************************************//
//                                      Plik paletka.cpp                                       //
//*********************************************************************************************//

#include "paletka.h"
#include "globals.h"

// Dwie zmienne ktore zaleznie od klawisza zwiekszaja lub zmiejszaja swoja wartosc
float xm, ym;

//*********************************************************************************************//
//                                  handle_input - Eventy                                      //
//*********************************************************************************************//
void Paletka :: handle_input()
{
	if(event.type == SDL_KEYDOWN)
	{
		switch( event.key.keysym.sym )
        {
			case SDLK_LEFT: xm -= 1; break;
            case SDLK_RIGHT: xm += 1; break;  
        }
	}
}

//*********************************************************************************************//
//                                  DrawPaletka - Rysuje paletke                               //
//*********************************************************************************************//
void Paletka :: DrawPaletka(unsigned int *ptr)
{
	int color;
	int kr = (int)(250);
	int kg = (int)(100);
	int kb = (int)(50);
	int c = 0;	

	for(int i = (int)y; i < (int)y+sz; i++, c+=5)
	{
		for(int j = (int)x; j < (int)x+dl; j++)
		{
			color = (kr - c << 16 ) + ( kg + c << 8 ) + ( kb  );
			ptr[1024*i + j] = color;
		}
	}
}

//*********************************************************************************************//
//                                MovePaletka - Porusza paletka                                //
//*********************************************************************************************//
void Paletka :: MovePaletka()
{
	x += xm;
	
//*********************************************************************************************//
//                       JESLI PALETKA DOTKNIE LEWEJ SCIANY TO SIE ZATRZYMUJE                  //
//*********************************************************************************************//	
	if(x <= 0)
	{
		xm = 0;
		x = xm;
	}

//*********************************************************************************************//
//                       JESLI PALETKA DOTKNIE PRAWEJ SCIANY TO SIE ZATRZYMUJE                 //
//*********************************************************************************************//
	if(x + 150 >= 1024)
	{
		xm = 0;
		x = 1024 - 150;
	}
}

//*********************************************************************************************//
//                                      Plik paletka.cpp                                       //
//*********************************************************************************************//

