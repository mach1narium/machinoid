//*********************************************************************************************//
//                                      Plik klocki.cpp                                        //
//*********************************************************************************************//

#include "klocki.h"


//*********************************** -= Kostruktor =- ****************************************//
Klocki :: Klocki(Klocki *k, int ile)
{
	k->klocki = new Klocek[ile];
	k->ile = ile;
	
}

//*********************************************************************************************//
//                                 UstawKlocki - Ustawia klocki                                //
//*********************************************************************************************//
void Klocki :: UstawKlocki(Klocki *k)
{
	Klocek *kl;
	int prz = 0;
	int przy = 0;
	int przx = 0;
	
		for(int i = 0; i < k->ile; i++)
		{
			if(i >= 0 && i < 20)
			{
				
				kl = &k->klocki[i];
				kl->x = k->klocki->x+prz;
				prz+=50;
			}
			
			if(i >= 20)
			{
				kl = &k->klocki[i];
				kl->x = k->klocki->x+przy;
				kl->y = k->klocki->y+60;
				przy+=50;
			}

			if(i >= 40)
			{
				kl = &k->klocki[i];
				kl->x = k->klocki->x+przx;
				kl->y = k->klocki->y+120;
				przx+=50;
			}
			
		}
}

//*********************************************************************************************//
//                                   DrawKlocek - Rysuje klocek                                //
//*********************************************************************************************//
void Klocki :: DrawKlocek(Klocek *k, unsigned int *ptr)
{
	int color;
	int kr = (int)(50);
	int kg = (int)(180);
	int kb = (int)(10);
	int c = 0;

	for(int i = (int)k->y; i < (int)k->y+k->sz; i++, c+=5)
		for(int j = (int)k->x; j < (int)k->x+k->dl; j++)
			{
				
				color = (kr + c << 16 ) + ( kg - c << 8 ) + ( kb + c );
					
				ptr[1024*i + j] = color;
			}
}

//*********************************************************************************************//
//                                   DrawKlocki - Rysuje klocki                                //
//*********************************************************************************************//
void Klocki :: DrawKlocki(Klocki *k, unsigned int *ptr)
{
	for( int i = 0; i < k->ile; i++)
	{		
		DrawKlocek(&k->klocki[i], ptr);
	}
}

//*********************************************************************************************//
//                                  DeleteKlocek - Kasuje klocek                               //
//*********************************************************************************************//
void Klocki :: DeleteKlocek(Klocki &k, int i)
{
	
	//k.klocki[i].~Klocek();
	klocki[i].~Klocek();
	//k.ile--;
	ile--;
	//k.klocki[i] = k.klocki[k.ile];
	klocki[i] = klocki[ile];
	
}

//*********************************************************************************************//
//                                Koniec pliku klocki.cpp                                      //
//*********************************************************************************************//
