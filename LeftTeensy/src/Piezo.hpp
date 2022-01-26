#ifndef PIEZO_H
#define PIEZO_H
#pragma once
	
#include "PeaKDetector.hpp"
#include "Counter.hpp"
#include "ResponsiveAnalogRead.h"

class Piezo
{
private:
   PeakDetector         &m_peakDetecor;
   Counter              &m_counter;
   ResponsiveAnalogRead &m_smoother;

public:
	Piezo(PeakDetector &peakDetector,Counter &counter,ResponsiveAnalogRead &smoother):
	m_peakDetecor(peakDetector),
	m_counter(counter),
	m_smoother(smoother)
	{

	}


	void loop()
	{
		m_smoother.update();
		m_peakDetecor.loop();
		m_peakDetecor.setInput(m_smoother.getValue());

		if(m_peakDetecor.getHit())
		{
			m_counter.add();
			Serial.println("Hit");
		   
		}	

	}

	boolean isHit()
	{
		return m_peakDetecor.getHit(); 

	}

	int getHitSum()
	{
		return m_counter.getSum();

	}

	void resetHitSum()
	{
		m_counter.reset();
	}
};
#endif