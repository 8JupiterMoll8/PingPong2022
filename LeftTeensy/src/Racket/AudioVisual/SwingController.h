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
    m_comet(comet),
    m_bargraph(bargraph),
    m_racket(racketRight)
    {
    }

    void loop()
    {
        //m_rightRacket.loop();
       // m_bargraph.loop();
        m_comet.loop();// empty
   

     
        // Uv Meter
        //m_bargraph.setMapSpeed(speed, 0.0 , 30.0);

        // Comet
        if(m_racket.isHit())
        {
        float minIn = 0.00;
        float maxIn = 25.0;
        float speed = constrain (m_racket.speed() ,minIn, maxIn);
     
        Serial.println(speed);

        m_comet.start();
        // m_comet.reverseDirection();
        m_comet.setSpeed       (map( speed, minIn, maxIn, 1.0, 10.0    ));
        m_comet.setSize        (map( speed, int(minIn), int(maxIn), 1,  25   ));
        m_comet.setFadeSize    (map( speed, minIn, maxIn, 223.0, 134.0 ));
        m_comet.setMidiVelocity(map( speed, minIn, maxIn, 0.0, 127.0   ));
        }
    }

private:
    Comet       &m_comet;
    Bargraph    &m_bargraph;
    Racket &m_racket;
};

#endif