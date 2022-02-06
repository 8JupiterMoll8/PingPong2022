#ifndef COMET_H
#define COMET_H
#include "SwingEnergizer.h"
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#pragma once

class Comet : public SwingEnergizer
{
private:
  CRGB (&m_A_ledStrip)
  [134];

public:
  Comet(CRGB (&ledStrip)[134])
      : m_A_ledStrip(ledStrip)
  {
  }

 virtual void loop() override
  {
    for (int i = 0; i < 100; i++)
    {
      m_A_ledStrip[i].setRGB(255, 255, 255);
      m_A_ledStrip[i].nscale8(55);
      FastLED.show();
    }
  }
};

#endif