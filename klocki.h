#ifndef KLOCKI_H
#define KLOCKI_H

//*********************************************************************************************//
//                                      Plik klocki.h                                          //
//*********************************************************************************************//


#include "klocek.h"
#include <iostream>

using namespace std;

//********************************** definicja klasy Klocki ***********************************//
class Klocki : public Klocek
{
	public:
		int ile;			
		Klocek *klocki;
			
		Klocki(){};
		Klocki(int ile);
		Klocki(Klocki *k, int ile);
		void UstawKlocki(Klocki *k);
		void DrawKlocek(Klocek *k, unsigned int* ptr);
		void DrawKlocki(Klocki *k, unsigned int *ptr);
		void MoveKlocki(Klocki *k);
		void DeleteKlocek(Klocki &k, int i);

		friend void DrawParticle(unsigned int *ptr);
		friend void MoveParticle();
			
		~Klocki(){};
};

//*********************************************************************************************//
//                                   Koniec pliku klocki.h                                     //
//*********************************************************************************************//
#endif



