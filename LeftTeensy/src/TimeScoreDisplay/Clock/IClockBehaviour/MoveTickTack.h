#ifndef MOVETICKTACK_H
#define MOVETICKTACK_H

#pragma once
#include <AccelStepper.h>
#include "IMoveBehaviour.h"

class MoveTickTack :public  IMoveBehaviour
{
public:
  
  MoveTickTack(AccelStepper &xAxis, AccelStepper &yAxis, AccelStepper &aAxis) : IMoveBehaviour(xAxis, yAxis, aAxis)
  {
  }

  virtual void loop()override
  {
    tickTack();

    m_stundenZeiger.setSpeed(incrementSpeed);
    m_minutenZeiger.setSpeed(incrementSpeed);
    m_sekundenZeiger.setSpeed(incrementSpeed);

    m_stundenZeiger.runSpeed();
    m_minutenZeiger.runSpeed();
    m_sekundenZeiger.runSpeed();

    static float in = 4.712;
    float out;

    // do input, etc. here - as long as you don't pause, the LED will keep pulsing

    in = m_stundenZeiger.currentPosition()*0.01;
   
    out = sin(in) * 35.5 + 35.5;
    usbMIDI.sendNoteOn(map(out,0.0,127.0,30.0,75.0),127,11);
    //Serial.println(out);
   
  }



    

private:
    int speed = 1000;
    int incrementSpeed = 0;

    void tickTack()
    {
        static boolean toogle = false;

        if (ms > speed)
        {
            ms = 0;
            toogle = !toogle;

            if (toogle == true)
            {
                incrementSpeed = 1000;
                speed = 500;
                
            }
            else
            {
                incrementSpeed = 0;
                speed = 500;
                
            }
        }
    }
};

#endif