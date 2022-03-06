#ifndef COMET_H
#define COMET_H

#include <FastLED.h>
#pragma once
extern const int NUM_LEDS;
class Comet
{

public:
  Comet(CRGB (&ledStrip)[360]): 
  A_leds(ledStrip)
  {
      //m_iPos = 0.00;
     // m_startPosition = 0;
  
  
  } 

  Comet(CRGB (&ledStrip)[360], int start): 
  A_leds(ledStrip)
  {
     // m_iPos = NUM_LEDS - m_size;
      m_iPos = 360 - 1;
      m_startPosition = 360 -1 ;
      m_iDirection *= -1;
  
  } 

  void loop()
  {
    switch (state)
    {
    case WAIT:
      //Leave State:
      if(m_animationCometStart == true) {
        state = START;
        Serial.print("Start Comet at Position : ");
        Serial.println(m_iPos);
      } 
      break;

    case START:
      //Do:
      animationComet();
       m_animationCometStart = false;
       Serial.print(" Comet at Position : ");
       Serial.println(m_iPos);
  
      //Leave State
      if(animationCometIsEnd()== true)
      {
       state = END; 
       Serial.print("End Comet at Position : ");
       Serial.println(m_iPos);
        
       

      }
      break;

    case END:
      //Do:
       m_animationCometStart = false;
      //Leave State
      state = WAIT;
        m_iPos = m_startPosition;
      Serial.print("Waiting to Start a Position : ");
        Serial.println(m_iPos);
      break;

    default:
      break;
    }
  }
  // Behaviours
  void start()                   { m_animationCometStart = true; m_iPos = m_startPosition;  }
  void reverseDirection()        { m_iDirection *= -1;           }
  void setSpeed(float speed)     { m_speed       = speed;        }
  void setFadeSize(int fadeSize) { m_fadeAmt     = fadeSize;     }
  void setSize(int size)         { m_size        = size;         }
  void setMidiVelocity(int v)    { m_midiVelocity = v;           }

  void animationComet()
  {
    if (ms > 10)
    {
      ms = 0;
      m_speed  = m_speed +  m_acceleration;
      m_iPos  += m_iDirection * m_speed;
     // Serial.println(m_size);
     

      // Move Forward
      for (int i = 0; i < m_size; i++)
      {
        A_leds[(int)m_iPos + i] += CRGB(255, 255, 255);
        int  n = map(m_iPos,0,360,0,127);
        usbMIDI.sendNoteOn(n, m_midiVelocity, 2);
      }

      // Randomly fade the LEDs
      for (int j = 0; j < NUM_LEDS; j++)
      {
        if (random(10) > 5)
        {
          A_leds[j] += A_leds[j].fadeToBlackBy(m_fadeAmt);
          usbMIDI.sendNoteOff(j, 75, 2);

        } 
  
         
      }
    }
  }
  boolean animationCometIsEnd()
  {
      Serial.println(m_size);
   // int(m_iPos) = m_iPos;
    // Check if Comet hits end and reverse Direction
    //!Something with m_size is wrong i have to take look
    //! Right now i change  (NUM_LEDS - m_size) to (NUM_LEDS - 1)
    if (m_iPos > (NUM_LEDS - m_size ) || m_iPos < (float) 0.0)
    {
      m_iPos = 0;
      m_iPos = 360;
      //reverseDirection();
      Serial.print("HIT BORDER at ");
      Serial.print(m_iPos);
     // m_iPos = m_startPosition;
      Serial.print("HIT BORDER at ");
      Serial.print(m_iPos);
      FastLED.clear();

      return true;
    }
    else
    {
      return false;
    }
  }


private:
  CRGB (&A_leds)[360];
  const int NUM_LEDS = 360;
 

  byte    m_fadeAmt             = 124;
  int     m_size                = 5;
  float   m_speed               = 1.0;
  float   m_acceleration        = 0.01;
  float   m_iPos                = 0.0;
  float   m_startPosition       = 0.0;
  float   m_iDirection          = 1.0;
  byte    m_midiVelocity        = 75;
  boolean m_animationCometStart = false;

  elapsedMillis ms;
  enum States { WAIT, START, END};
  States state = WAIT;
};

#endif