#ifndef RACKET_H
#define RACKET_H
#pragma once
#include "Piezo.hpp"
	
class Racket  
{
	private:
	Piezo &m_piezo;

	public:

		Racket(Piezo piezo):m_piezo(piezo)
		{

		}

		void loop()
		{
			

		}

	
		

};
#endif