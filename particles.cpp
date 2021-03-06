//*********************************************************************************************//
//                                      Plik particles.cpp                                     //
//*********************************************************************************************//

#include "particles.h"
#include "globals.h"

//*******************************   Konstruktor z parametrami   *******************************//
Particles :: Particles(Particles *p, int ile)
{
	p->particles = new Particle[ile];
	p->ile = ile;
}

//*******************************   Konstruktor z parametrem   ********************************//
Particles :: Particles(int il)
{
	particles = new Particle[il];
	ile = il;
}

//********************************   Konstruktor kopiujacy   **********************************//
Particles :: Particles(const Particles &a)
{
	delete [] particles;
	particles = a.particles;
	ile = a.ile;
}

//*******************************   Przeciazenie operatora =   ********************************//
Particles& Particles::operator=(const Particles& a)
{
	ile = a.ile;
	//particles = new Particle[ile];
	particles = a.particles;
	
}

//*********************************************************************************************//
//                               Koniec pliku particles.cpp                                    //
//*********************************************************************************************//


