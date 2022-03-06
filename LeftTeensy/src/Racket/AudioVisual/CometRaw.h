#ifndef COMETRAW_H
#define COMETRAW_H

#include <FastLED.h>
#pragma once
extern const int NUM_LEDS;
class CometRaw
{

public:
  CometRaw(CRGB (&ledStrip)[360]): 
  A_leds(ledStrip)
  {
     m_iPos = 0;
     m_startPosition = 0;
     
  } 

  CometRaw(CRGB (&ledStrip)[360], int Reversedirection): 
  A_leds(ledStrip)
  {
     m_iPos = NUM_LEDS - m_size;
     m_startPosition = NUM_LEDS - m_size;
     m_iDirection *= -1;
     
  } 

  void loop()
  {
 
     // CHECK FOR HIT WALL

     if (ms > 10)
     {
     

       ms = 0;
      m_speed = m_speed + m_acceleration;
      m_iPos += m_iDirection * m_speed ; 
   

      //Serial.println(m_iPos);
      //  Serial.println(NUM_LEDS - m_size);
      //  Serial.println(m_iDirection);
       if (int(m_iPos) >= (NUM_LEDS - m_size) || m_iPos <= 0)
       {
          Serial.println(m_iPos);
         //m_iDirection *= -1;
         m_iPos = m_startPosition;
         m_acceleration = 0.01;
         m_speed        = 1.25;
        
       }

       // Move Forward
       for (int i = 0; i < m_size; i++)
       {
         A_leds[(int)m_iPos + i] = CRGB(255, 255, 255);
         usbMIDI.sendNoteOn(m_iPos, m_midiVelocity, 2);
       }

       // Randomly fade the LEDs
       for (int j = 0; j < NUM_LEDS; j++)
       {
         if (random(10) > 5)
         {
             A_leds[j] = A_leds[j].fadeToBlackBy(m_fadeAmt);

         }
        
         

         usbMIDI.sendNoteOff(j, 75, 2);
       }
     }

  }// End Loop

  // Behaviours
  void start()                   { m_animationCometStart = true; m_iPos = 0; }
  void reverseDirection()        { m_iDirection *= -1;           }
  void setSpeed(float speed)     { m_speed       = speed;        }
  void setFadeSize(int fadeSize) { m_fadeAmt     = fadeSize;     }
  void setSize(int size)         { m_size        = size;         }
  void setMidiVelocity(int v)    { m_midiVelocity = v;           }

 
    // Check if Comet hits end and reverse Direction
 
  
private:
  CRGB (&A_leds)[360];
  const int NUM_LEDS = 360;
 
  float   m_startPosition       = 0.0;
  byte    m_fadeAmt             = 200;
  int     m_size                = 7;
  float   m_speed               = 10.25;
  float   m_acceleration        = 0.01;
  float   m_iPos                = 0.0;
  float   m_iDirection          = 1.0;
  byte    m_midiVelocity        = 75;
  boolean m_animationCometStart = false;

  elapsedMillis ms;

};

#endif