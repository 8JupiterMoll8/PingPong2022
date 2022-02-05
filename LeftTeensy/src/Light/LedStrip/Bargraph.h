#ifndef BARGRAPH_H
#define BARGRAPH_H

#pragma once
#include "SwingEnergizer.h"
#include <FastLED.h>
#include "Speed.hpp"
class Bargraph : public SwingEnergizer
{
private:
  CRGB (&m_A_ledStrip)[134];
  Speed m_speed;
  int ledCount ;

public:
  Bargraph(CRGB (&ledStrip)[134], Speed & speed)
      : m_A_ledStrip(ledStrip),
        m_speed(speed)
  {
  }

public:
    virtual void loop() override
    {
        m_speed.loop();
        m_speed.getNormal();
        Serial.println( m_speed.getNormal());

        // map the result to a range from 0 to the number of LEDs:
        int ledLevel = map(1023, 0, 1023, 0, ledCount);

        // loop over the LED array:
        for (int thisLed = 0; thisLed < ledCount; thisLed++)
        {
            // if the array element's index is less than ledLevel,
            // turn the pin for this element on:
            if (thisLed < ledLevel)
            {
                m_A_ledStrip[thisLed].setRGB(255,255,255);
                m_A_ledStrip[thisLed].nscale8(255);
            }
            // turn off all pins higher than the ledLevel:
            else
            {
                 m_A_ledStrip[thisLed].setRGB(0,0,0);
                m_A_ledStrip[thisLed].nscale8(0);
            }
        }
    }
};

#endif