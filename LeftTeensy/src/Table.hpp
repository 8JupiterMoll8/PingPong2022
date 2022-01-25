#ifndef TABLE_H
#define TABLE_H
#pragma once
#include "Counter.hpp"
#include "ResponsiveAnalogRead.h"
#include "PeaKDetector.hpp"
	
class Table  
{
	private:
	PeakDetector &m_peakDetecor;



	public:

		Table(PeakDetector &peakDetector):m_peakDetecor(peakDetector)
		{

		}

		void setup(){}
		void loop(){}
		

};
#endif