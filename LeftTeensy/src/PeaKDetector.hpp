#ifndef PEAKDETECTOR_H
#define PEAKDETECTOR_H
#pragma once
#include "Arduino.h"


class PeakDetector
{
private:
	int m_thresholdMin     {5} ; // minimum reading, avoid noise and false starts
    int m_peakTrackMillis  {3} ;
	int m_aftershockMillis {25} ; // aftershocks & vibration reject
	int m_inputSensor     {1} ;

    int           m_state;// 0=idle, 1=looking for peak, 2=ignore aftershocks
    int           m_peak; // remember the highest reading
    elapsedMillis m_msec; // timer to end states 1 and 2


	boolean ball ;
	boolean *ptr = &ball;

public:
    PeakDetector(){};
	PeakDetector(int inputSensor ):m_inputSensor(inputSensor)                                            
	{}


   boolean getHit()
   {
	   return *ptr;

   }

private: void hitReleased() { *ptr = false; }
public:
	void loop()
	{
		//Serial.println(m_inputSensor);
		switch (m_state)
		{

		// IDLE state: wait for any reading is above threshold.  Do not set
		// the threshold too low.  You don't want to be too sensitive to slight
		// vibration.
		case 0:
			if (m_inputSensor > m_thresholdMin)
			{
				Serial.print("begin peak track ");
				Serial.println(m_inputSensor);
				m_peak = m_inputSensor;
				m_msec = 0;
				m_state = 1;
			}
			return;


		// Peak Tracking state: capture largest reading
		case 1:
			if (m_inputSensor > m_peak)
			{
				m_peak = m_inputSensor;
			}
			if (m_msec >= m_peakTrackMillis)
			{
				Serial.print("peak = ");
				Serial.println(m_peak);
			
				*ptr = true;
				
				m_msec = 0;
				m_state = 2;
			}
			return;


		// Ignore Aftershock state: wait for things to be quiet again.
		default:
		    
			*ptr = false;

			if (m_inputSensor > m_thresholdMin)
			{
				
					//*ptr = false;
				m_msec = 0; // keep resetting timer if above threshold
			}
			else if (m_msec > m_aftershockMillis)
			{
				//usbMIDI.sendNoteOff(note, 0, channel);
			    
				//*ptr = false;
				m_state = 0; // go back to idle when
			}
		}
	}

	void setInput(int input)
	{ 
		m_inputSensor = input;

	}

	void setThersholdMin(int thersholdMin)
	{
		m_thresholdMin = thersholdMin;

	}

	void setPeakTrackMillis(int peaktarckMillis)
	{
		m_peakTrackMillis = peaktarckMillis;

	}

	void setAfterSchockMillis(int afterschockMillis)
	{
		m_aftershockMillis = afterschockMillis;

	}

	
};
#endif