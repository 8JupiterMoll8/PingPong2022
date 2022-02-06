#ifndef BARGRAPH_H
#define BARGRAPH_H

#pragma once
#include "SwingEnergizer.h"
#include <FastLED.h>
#include "RacketRight.hpp"
class Bargraph : public SwingEnergizer
{
private:
  CRGB (&m_A_ledStrip)[134];
  RacketRight &m_rightRacket;
  float ledCount = 134.0;

public:
  Bargraph(CRGB (&ledStrip)[134], RacketRight &racketRight)
      : m_A_ledStrip(ledStrip),
        m_rightRacket(racketRight)
  {
  }

public:
    virtual void loop() override
    {
         m_rightRacket.loop();
         float speed = m_rightRacket.speed();
         FastLED.show();

        // map the result to a range from 0 to the number of LEDs:
        int ledLevel = map(speed, 0.0, 30.0, 0.0, ledCount);

        //Serial.println(ledLevel);
        //delay(10);

        // loop over the LED array:
        for (int thisLed = 0; thisLed < ledCount; thisLed++)
        {
            // if the array element's index is less than ledLevel,
            // turn the pin for this element on:
            if (thisLed < ledLevel)
            {
                m_A_ledStrip[thisLed].setRGB(255,255,255);
                usbMIDI.sendNoteOn(thisLed,75,2);
                //m_A_ledStrip[thisLed].nscale8(255);
               
            }
            // turn off all pins higher than the ledLevel:
            else
            {
                 m_A_ledStrip[thisLed].setRGB(0,0,0);
                  usbMIDI.sendNoteOff(thisLed,0,2);
               // m_A_ledStrip[thisLed].nscale8(0);
                  
            }
           
        }
    }  
};

#endif