#ifndef RACKET_H
#define RACKET_H
#pragma once
#include "PeaKDetector.hpp"
#include "ReciverData.hpp"
#include "ResponsiveAnalogRead.h"

class Racket
{
private:
	PeakDetector &m_ballDetector; // Composition
	ReciverData &m_racketData;    // Compostion
	ResponsiveAnalogRead  analog;

	// States of Recket
	float m_speed;
	

public:
	Racket(PeakDetector &PeakDetector, ReciverData &ReciverData) : m_ballDetector(PeakDetector),
																   m_racketData(ReciverData),
																   analog(A17,true)
	{
	}

	void setup()
	{
	}

	void loop()
	{
		m_ballDetector.loop();
		//analog.update();
		//m_ballDetector.setInput(analog.getValue());


		if (m_ballDetector.getHit())
		{
             m_speed = getTotalSpeed();
			//Map TotalSpeed Gyro to  Midi  Velocity
			byte velocity = map(m_speed, 0.00, 24.0, 0, 127);
			Serial.print("MidiVelocity :");
			Serial.println(velocity);

			// Toggle Note on Note Off
			static boolean togglePressd = false;
			togglePressd = !togglePressd;
			if (togglePressd)
			{
				usbMIDI.sendNoteOn(54, velocity, 2);
				usbMIDI.sendNoteOff(100, 0, 2);
			}
			else
			{
				usbMIDI.sendNoteOff(54, 0, 2);
				usbMIDI.sendNoteOn(100, velocity, 2);
			}

			// Workarround to leave this state if condition
			// if (racketPiezo.getHit())
			// setting it to False via Pointer
			m_ballDetector.hitReleased();
		}
	}

private:

	float getTotalSpeed()
	{
		// Totalspeed Gyro of Racket during swinging 
		m_speed = sqrtf(powf(m_racketData.gx, 2) + powf(m_racketData.gy, 2) + powf(m_racketData.gz, 2));
		Serial.print("Racket Speed :");
		Serial.println(m_speed);

		return m_speed;
	}
};
#endif