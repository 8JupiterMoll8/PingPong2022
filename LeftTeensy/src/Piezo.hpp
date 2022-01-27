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
   int m_piezoInput = 0;
   

public:
 
	Piezo(PeakDetector &peakDetector,Counter &counter,I_InputSensorBhv &inputValue):
	m_peakDetecor(peakDetector),
	m_counter(counter),
    m_inputValue(&inputValue) 
	{

	}


	void loop()
	{
		m_inputValue->loop();
		m_peakDetecor.loop();

	    
        m_piezoInput = m_inputValue->getValue();
		m_peakDetecor.setInput(m_piezoInput);

		if(m_peakDetecor.getHit())
		{
			m_counter.add();
			//Serial.println("Hit");
		   
		}	

	}

	void countHit()
	{
		m_counter.add();

	}

	boolean isHit()
	{
		return m_peakDetecor.getHit(); 

	}

	int hitSum()
	{
		return m_counter.getSum();

	}

	void resetHitSum()
	{
		m_counter.reset();
	}
};
#endif