#ifndef PALETKA_H
#define PALETKA_H

//*********************************************************************************************//
//                                      Plik paletka.h                                         //
//*********************************************************************************************//

//********************************   Definicja klasy Paletka   ********************************//

class Paletka
{
	public:
			float x, y;
			int dl, sz;

			Paletka(){ x = 1024/2 - 50; y = 733; dl = 150; sz = 15;};
			void handle_input();
			void DrawPaletka(unsigned int *ptr);
			void MovePaletka();
};

//*********************************************************************************************//
//                               Koniec pliku paletka.h                                        //
//*********************************************************************************************//
#endif


