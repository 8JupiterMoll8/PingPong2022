#ifndef PIEZO_H
#define PIEZO_H
#pragma once
	
#include "PeaKDetector.hpp"
#include "Counter.hpp"
#include "I_InputSensorBhv.hpp"

class Piezo
{
private:
   PeakDetector         &m_peakDetecor;
   Counter              &m_counter;
   I_InputSensorBhv     *m_inputValue;
   

public:
 
	Piezo(PeakDetector &peakDetector,Counter &counter,I_InputSensorBhv &inputValue):
	m_peakDetecor(peakDetector),
	m_counter(counter),
    m_inputValue(&inputValue) 
	{

	}


	void loop()
	{
		m_smoother.update();
		m_peakDetecor.loop(m_inputValue->);

	    
		m_peakDetecor.setInput(m_inputValue->getValue());

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