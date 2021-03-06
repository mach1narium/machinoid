//*********************************************************************************************//
//                                      Plik kulka.cpp                                         //
//*********************************************************************************************//

#include "kulka.h"
#include "globals.h"


// *tempbuf - wskaznik do tablicy [1024*768]
unsigned int *tempbuf = new unsigned int[1024*768];

// Dwie zmienne do poruszania kulki
float gox, goy;

// l - licznik zliczajacy kolizje z klockami
static int l = 0;


//*******************************   Konstruktor domyslny   ************************************//
Kulka :: Kulka()
{
	x = (rand() % 32768) - 16384.0f;
    y = (rand() % 32768) - 16384.0f;
    z = (rand() % 32768) - 16384.0f;

    float len = (float)sqrt(x * x + y * y + z * z);
    
	if (len != 0)
    {
		x /= len;
		y /= len;
		z /= len;
    }
  	
	r = 2;
	c = 0x7f7f7f;
	kolizja = false;
}

//*******************************   Konstruktor z parametrami   *******************************//
Kulka :: Kulka(float _x, float _y, float _r, int _c, bool _kolizja)
{
	x = _x;
	y = _y;
	r = _r;
	c = _c;
	kolizja = _kolizja;

	for(int i = 0; i < 20; i++)
	{
		particles[i] = new Particle();
		particles[i]->x = x - 15 + (rand() % 25);
		particles[i]->y = y - 15 + (rand() % 25);
		particles[i]->z = 600;
	}
}

//*********************************************************************************************//
//                                       handle_input - Eventy                                 //
//*********************************************************************************************//
void Kulka :: handle_input()
{
	if( event.type == SDL_MOUSEMOTION )
	{
		if (event.motion.state & SDL_BUTTON(1))
 		{
    		x = event.button.x;
			y = event.button.y;
			
			gox = event.motion.xrel;
			goy = event.motion.yrel;
 		}
	}
}

//*********************************************************************************************//
//                               handle_collision() - kolizje                                  //
//*********************************************************************************************//
bool Kulka :: handle_collision(Paletka &pl, Particles *p, Klocki &kk)
{
//*********************************************************************************************//
//                                   ODBICIE OD BOCZNYCH SCIANEK                               //
//*********************************************************************************************//
	if( x - r <= 0 || x + r >= 1024 )
	{
		gox = -gox;
		x += gox;
	} 

//*********************************************************************************************//
//                               ODBICIE OD LEWEJ POLOWY PALETKI                               //
//*********************************************************************************************//
	if( y + r  >= pl.y && x >= pl.x && x <= pl.x + pl.dl/2)
	{
		// jesli z prawej strony leci kulka to sie odbija
		if(gox > 0)
		{
			x += gox;
			gox = -gox;
			goy = -goy;
			y += goy;
		}

		// jesli z lewej strony leci kulka to odbija sie spowrotem
		if(gox < 0)
		{
			x += gox;
			goy = -goy;
			y += goy;
		}
	}

//*********************************************************************************************//
//                                ODBICIE OD PRAWEJ POLOWY PALETKI                             //
//*********************************************************************************************//
	if( y + r  >= pl.y && x > pl.x+pl.dl/2 && x <= pl.x+pl.dl)
	{
		// jesli z prawej strony leci kulka to sie odbija
		if(gox > 0)
		{
			gox = -gox;
			x += gox;
			gox = -gox;
			goy = -goy;
			y += goy;
		}

		// jesli z lewej strony leci kulka to odbija sie spowrotem
		if(gox < 0)
		{
			gox = -gox;
			x += gox;
			goy = -goy;
			y += goy;
		}
	}
	
//*********************************************************************************************//
//                                   ODBICIE OD DOLNEJ SCIANKI                                 //
//*********************************************************************************************//
	if( y + r >= 768)
	{
		goy = -goy;
		y += goy;
	}

//*********************************************************************************************//
//                                   ODBICIE OD GORNEJ SCIANKI                                 //
//*********************************************************************************************//
	if( y - r <= 0)
	{
		
		goy = -goy;
		y += goy;
	}

//*********************************************************************************************//
//                                  KOLIZJE Z KLOCKAMI I WYBUCHY                               //
//*********************************************************************************************//	
	
for(int i = 0; i < kk.ile; i++)
{
//*********************************************************************************************//
//                                  ODBICIE OD DOLU KLOCKA                                     //
//*********************************************************************************************//	
	if( y - r <= kk.klocki[i].y + kk.klocki[i].sz  &&
		y - r/2 > kk.klocki[i].y + kk.klocki[i].sz  &&
		x + r/2 > kk.klocki[i].x && x - r/2 < kk.klocki[i].x + kk.klocki[i].dl)
		{
			for(int j = 0; j < p->ile; j++)
			{
				
				p[l].particles[j].x = kk.klocki[i].x+kk.klocki[i].dl/2;
				p[l].particles[j].y = kk.klocki[i].y+kk.klocki[i].sz/2;
				
			}
			l++;
			kolizja = true;
			kk.DeleteKlocek(kk, i);
			cout << kk.ile << endl;
			goy = -goy;
			y += goy;
		}

//*********************************************************************************************//
//                                  ODBICIE OD PRAWEJ STRONY KLOCKA                            //
//*********************************************************************************************//		
	if( x - r  <= kk.klocki[i].x + kk.klocki[i].dl &&
		x + r > kk.klocki[i].x + kk.klocki[i].dl && 
		y + r/2 >= kk.klocki[i].y && y - r/2 <= kk.klocki[i].y + kk.klocki[i].sz)
		{
			for(int j = 0; j < p->ile; j++)
			{
				p[l].particles[j].x = kk.klocki[i].x+kk.klocki[i].dl/2;
				p[l].particles[j].y = kk.klocki[i].y+kk.klocki[i].sz/2;
			}
			l++;
			kolizja = true;
			kk.DeleteKlocek(kk, i);
			gox = -gox;
			x += gox;
		}

//*********************************************************************************************//
//                                  ODBICIE OD LEWEJ STRONY KLOCKA                             //
//*********************************************************************************************//
		if(x - r <= kk.klocki[i].x  && x + r > kk.klocki[i].x && y + r/2 >= kk.klocki[i].y &&
			y- r/2 <= kk.klocki[i].y + kk.klocki[i].sz )
		{
			for(int j = 0; j < p->ile; j++)
			{
				p[l].particles[j].x = kk.klocki[i].x+kk.klocki[i].dl/2;
				p[l].particles[j].y = kk.klocki[i].y+kk.klocki[i].sz/2;
			}
			l++;
			kolizja = true;
			kk.DeleteKlocek(kk, i);
			gox = -gox;
			x += gox;
		}

//*********************************************************************************************//
//                                     ODBICIE OD GORY KLOCKA                                  //
//*********************************************************************************************//
		if( y + r > kk.klocki[i].y && y  < kk.klocki[i].y  &&
			x + r/2 > kk.klocki[i].x && x - r/2 < kk.klocki[i].x + kk.klocki[i].dl)
		{
			for(int j = 0; j < p[l].ile; j++)
			{
				p[l].particles[j].x = kk.klocki[i].x+kk.klocki[i].dl/2;
				p[l].particles[j].y = kk.klocki[i].y+kk.klocki[i].sz/2;
			}
			l++;
			kolizja = true;
			kk.DeleteKlocek(kk, i);
			goy = -goy;
			y += goy;
		}
		
	}
	


//*********************************************************************************************//
//                                             WYBUCHY PIKSELI                                 //
//*********************************************************************************************//
	if(kolizja)
	{
		for(int i = 0; i < l; i++)
		{
			
			for(int j = 0; j < p->ile; j++)
			{
				if(p[i].particles[j].energy <= 0.1)
				{
					//p[i].particles[j].DeleteParticle(p[i].particles[j]);
					
				}
				else
				{
					p[i].particles[j].MoveParticle();
					p[i].particles[j].DrawParticle((unsigned int*)screen->pixels);
				}
			}
			
		}
	}
	return kolizja;
}

//*********************************************************************************************//
//                                   Blendavg - rozmywa kolory                                 //
//*********************************************************************************************//
unsigned int Kulka :: Blendavg(unsigned int source, unsigned int target)
{
	unsigned int sourcer = (source >>  0) & 0xff;
    unsigned int sourceg = (source >>  8) & 0xff;
    unsigned int sourceb = (source >> 16) & 0xff;
    unsigned int targetr = (target >>  0) & 0xff;
    unsigned int targetg = (target >>  8) & 0xff;
    unsigned int targetb = (target >> 16) & 0xff;

    targetr = (sourcer + targetr) / 2;
    targetg = (sourceg + targetg) / 2;
    targetb = (sourceb + targetb) / 2;

	return (targetr <<  0) |
           (targetg <<  8) |
           (targetb << 16);
}

//*********************************************************************************************//
//                                      Scalebit                                               //
//*********************************************************************************************//
void Kulka :: Scalebit()
{
	DrawKulka();
}

//*********************************************************************************************//
//                                    DrawKulka - Rysuje kulke                                 //
//*********************************************************************************************//
void Kulka :: DrawKulka()
{
	int color = c;
	DrawParticles();
	
	if(x - r >= 0 && x + r <= 1024 && y - r >= 0 && y + r <= 768)
	for(int i = 0; i < 2 * r; i++)
	{
		int len = (int)sqrt((float)(r * r - (r - i) * (r - i))) * 2;
		int xofs = (int)x - len / 2;

		int ofs = ((int)y - (int)r + i) * 1024 + xofs;

		/*color = ((int)(sin((tick * 0.01 + i) * 0.234897f) * 127 + 128) << 16) |
                   ((int)(sin((tick * 0.01 + i) * 0.123489f) * 127 + 128) <<  8) |
                   ((int)(sin((tick * 0.01 + i) * 0.312348f) * 127 + 128) <<  0);*/
		

		for (int j = 0; j < len; j++)
		{
			 	memcpy(tempbuf + ofs  + j, ((unsigned int*)screen->pixels) + ofs  + j,
				sizeof(SDL_Surface));
				((unsigned int*)screen->pixels)[(int)ofs + j] = color;
		}
	}
}

//*********************************************************************************************//
//                           DrawParticles - Rysuje piksele przy kulce                         //
//*********************************************************************************************//
void Kulka :: DrawParticles()
{
	for(int i = 0; i < 20; i++)
	{
		if(particles[i]->dead())
		{
			delete particles[i];

			particles[i] = new Particles();
			particles[i]->x = x - 10 + (rand() % 20);
			particles[i]->y = y - 10 + (rand() % 20);
			particles[i]->z = 600;	
		}	
		else
		{
			for(int i = 0; i < 20; i++)
			{
				particles[i]->DrawParticle((unsigned int*)screen->pixels);
			}
		}
	}
}

//*********************************************************************************************//
//                                  MoveKulka - Porusza Kulke                                  //
//*********************************************************************************************//
void Kulka :: MoveKulka()
{
	y += goy;
	x += gox;
}

//*********************************************************************************************//
//                               Koniec pliku kulka.cpp                                        //
//*********************************************************************************************//

