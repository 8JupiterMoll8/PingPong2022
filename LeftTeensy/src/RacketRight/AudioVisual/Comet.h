#ifndef COMET_H
#define COMET_H

#include <FastLED.h>
#pragma once

class Comet
{

public:
  Comet(CRGB (&ledStrip)[288]): A_leds(ledStrip){} 

  void loop()
  {
    switch (state)
    {
    case WAIT:
      //Leave State:
      if(m_animationCometStart == true) 
         state = START;
      break;

    case START:
      //Do:
      animationComet();
      //Leave State
      if(animationCometIsEnd())
      {
        state = END; 

      }
      break;

    case END:
      //Do:
       m_animationCometStart = false;
      //Leave State
      state = WAIT;
      break;

    default:
      break;
    }
  }
  // Behaviours
  void start()                   { m_animationCometStart = true; }
  void reverseDirection()        { m_iDirection *= -1;           }
  void setSpeed(float speed)     { m_speed       = speed;        }
  void setFadeSize(int fadeSize) { m_fadeAmt     = fadeSize;     }
  void setSize(int size)         { m_size        = size;         }
  void setMidiVelocity(int v)    { m_midiVelocity = v;           }

  boolean animationCometIsEnd()
  {
    // Check if Comet hits end and reverse Direction
    if (m_iPos >= (NUM_LEDS - m_size) || m_iPos <= 0)
    {
      // reverseDirection();
      m_iPos = 0;
      FastLED.clear();

      return true;
    }
    else
    {
      return false;
    }
  }


  void animationComet()
  {
    if (ms > 10)
    {
      ms = 0;
      m_speed = m_speed +  m_acceleration;
      m_iPos += m_iDirection * m_speed;

      // Move a 5 LedGroup Forward
      for (int i = 0; i < m_size; i++)
      {
        A_leds[(int)m_iPos + i] += CRGB(255, 255, 255);
        
        usbMIDI.sendNoteOn(m_iPos, m_midiVelocity, 2);
        //! Oprator Synth leads
      }

      // Randomly fade the LEDs
      for (int j = 0; j < NUM_LEDS; j++)
      {
        if (random(10) > 5)
          A_leds[j] += A_leds[j].fadeToBlackBy(m_fadeAmt);
      
       usbMIDI.sendNoteOff(j, 75, 2);
      }
    }
  }
private:
  CRGB (&A_leds)[288];
  const int NUM_LEDS = 288;

  byte    m_fadeAmt             = 288;
  int     m_size                = 2;
  float   m_speed               = 7.0;
  float   m_acceleration        = 0.01;
  float   m_iPos                = 0.0;
  float   m_iDirection          = 1.0;
  byte    m_midiVelocity        = 75;
  boolean m_animationCometStart = false;

  elapsedMillis ms;
  enum States { WAIT, START, END};
  States state = WAIT;
};

#endif