#ifndef particle_h
#define particle_h

//*********************************************************************************************//
//                                      Plik particle.h                                        //
//*********************************************************************************************//

#include <cmath>
#include <iostream>

using namespace std;

//*******************************  definicja klasy Particle   *********************************//
class Particle
{
	public:
		float x, sx;	
		float y, sy;	
		float z, sz;
		float energy, gravity, bounce, ground;
		int frame;

	public:
		Particle()
		{
			x = 0;
 			y = 0;
			z = 300;

			sx = (float)((rand() % 1000) -500) / 500;
			sy = (float)((rand() % 1000) - 500) / 500;
			sz = sqrt(1-sx*sx-sy*sy)+((float)((rand() % 1000)-500)/1000);
			sx *= 5;
			sy *= 5; 
			sz *= 5;
			//if ((rand() % 2)==1) sz =- sz;
	
			energy = 1;
			gravity = -0;
			bounce = -0.5;
			ground = -1000;

			frame = rand() % 10;
		};
		
		void DrawBox(int x, int y, int color, int size, unsigned int *ptr);
		void DrawParticle(unsigned int *ptr);
		void MoveParticle();
		bool dead();
		void DeleteParticle(Particle &t);
	
		virtual ~Particle()
		{
			//cout << "delete" << "  " << sizeof(Particle) << "  " << this << endl;
		};
};

//*********************************************************************************************//
//                              Koniec pliku particle.h                                        //
//*********************************************************************************************//
#endif

