#ifndef MOVETICKTACK_H
#define MOVETICKTACK_H

#pragma once
#include <AccelStepper.h>
#include "IMoveBehaviour.h"

class MoveTickTack : public IMoveBehaviour
{
private:
    
    int incrementSpeed = 0;
    float in = 4.712;
    float out;

public:
    MoveTickTack(AccelStepper &Axis) : 
    IMoveBehaviour(Axis)
    {
         _speed = 1000;
    }

    virtual void loop() override
    {

        tickTack();

        in = Zeiger.currentPosition() * 0.01;
        out = sin(in) * 61.5 + 61.5;
        usbMIDI.sendNoteOn(map(out, 0.0, 127.0, 30.0, 70.0), map(out, 0.0, 127.0, 0.0, 70.0), 11);
        Serial.println(out);
    }

virtual void setSpeed(int speed) override
  {
    _speed = speed;
  }

private:
    void tickTack()
    {
        static boolean toogle = false;

        if (ms > _speed)
        {
            ms = 0;
            toogle = !toogle;

            if (toogle == true)
            {
                incrementSpeed = 9000;
                _speed = 100;
                usbMIDI.sendNoteOff(120, 127, 11);
            }
            else
            {
                incrementSpeed = 0;
                _speed = 500;
                usbMIDI.sendNoteOn(120, 127, 11);
            }
        }

        Zeiger.setSpeed(incrementSpeed);
        Zeiger.runSpeedNow();
     
    }
};

#endif