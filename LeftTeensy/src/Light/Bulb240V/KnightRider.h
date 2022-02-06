#ifndef KNIGHTRIDER_H
#define KNIGHTRIDER_H

#pragma once

class KnightRider
{
  public:
  unsigned char (&m_AcBulb)[8];
  elapsedMillis sinceTest1;
  int intervall     = 25;
 

  KnightRider(unsigned char (&acBulb)[8]) : m_AcBulb(acBulb)
  {
  }

  void loop()
  {
       
   static int circle_Counter = 0; 
  
   static int toggleOnOff    = 0;   
   

    if (sinceTest1 >= intervall)
    {
      sinceTest1 = sinceTest1 - intervall;
     // Serial.println(  ++intervall*10);
      toggleOnOff++;

      if (toggleOnOff == 1 && circle_Counter <= 8)
      {

        m_AcBulb[circle_Counter] = 10;
        usbMIDI.sendNoteOn(57+circle_Counter,75,3);
      }

      if (toggleOnOff == 2 && circle_Counter <= 8)

      {

        m_AcBulb[circle_Counter] = 75;
         usbMIDI.sendNoteOff(57 + circle_Counter,0,3);

        toggleOnOff = 0;
        circle_Counter++;
      }

      if (circle_Counter == 8)
      {
       
        
        circle_Counter = 0;
        toggleOnOff = 0;
      }
    }

  }

  void setBrightness(int b)
  {
    // Light Bulb
    for (int i = 0; i < 8; i++)
    {
      m_AcBulb[i] = b;
    }
  }
  void setSpeed(int speed)
  {
    intervall = speed;

  }

  

};

#endif


