#ifndef KULKA_H
#define KULKA_H

//*********************************************************************************************//
//                                      Plik kulka.h                                           //
//*********************************************************************************************//

#include "paletka.h"
#include "particles.h"
#include "klocki.h"
#include <SDL/SDL.h>
#include <iostream>

using namespace std;



//********************************   Definicja klasy Kulka   **********************************//
class Kulka 
{
		public:
		float x, y, z ,r, angle;
		int c;
		bool kolizja;
		int frame;
		Particle *particles[20];

		public:
		Kulka();
		Kulka(float _x, float _y, float _r, int _c, bool kolizja);
		void handle_input();
		bool handle_collision(Paletka &pl, Particles *p, Klocki &kk);
		void DrawKulka();
		void DrawBall(Kulka *k);
		void DrawParticles();
		void MoveKulka();
		unsigned int Blendavg(unsigned int source, unsigned int target);
		void Scalebit();
		void Kulkarotate_x(float angle);
		void Kulkarotate_y(float angle);
		void Kulkarotate_z(float angle);

		~Kulka(){};
};

//*********************************************************************************************//
//                             Koniec pliku kulka.h                                            //
//*********************************************************************************************//
#endif


