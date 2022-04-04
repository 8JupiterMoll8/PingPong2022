#ifndef SWINGCONTROLLER_H
#define SWINGCONTROLLER_H
#pragma once
#include "Comet.h"
#include "Bargraph.h"
#include "Racket.hpp"

class SwingController
{
public:
    SwingController(Comet &comet, Bargraph &bargraph, Racket &racketRight) :
    _comet(comet),
    _bargraph(bargraph),
    _racket(racketRight)
    {
    }

    void loop()
    {
        //_rightRacket.loop();
       // _bargraph.loop();
        _comet.loop();// empty
   

     
        // Uv Meter
        //_bargraph.setMapSpeed(speed, 0.0 , 30.0);

        // Comet
        if(_racket.isHit())
        {
        float minIn = 0.00;
        float maxIn = 127.0;
        //float speed = constrain (_racket.speed() ,minIn, maxIn);
        float speed = constrain (_racket.hitPeak() ,minIn, maxIn);

     
        Serial.println(speed);

        _comet.start();
        // _comet.reverseDirection();
        _comet.setSpeed       (map( speed, minIn, maxIn, 1.0, 10.0    ));
        _comet.setSize        (map( speed, int(minIn), int(maxIn), 1,  25   ));
        _comet.setFadeSize    (map( speed, minIn, maxIn, 223.0, 134.0 ));
        _comet.setMidiVelocity(map( speed, minIn, maxIn, 0.0, 127.0   ));
        }
    }

private:
    Comet       &_comet;
    Bargraph    &_bargraph;
    Racket      &_racket;
};

#endif