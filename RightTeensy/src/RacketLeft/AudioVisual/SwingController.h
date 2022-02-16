#ifndef SWINGCONTROLLER_H
#define SWINGCONTROLLER_H
#pragma once
#include "Comet.h"
#include "Bargraph.h"
#include "Racket.hpp"
#include "Arduino.h"

class SwingController
{
public:
    SwingController(Comet &comet, Bargraph &bargraph, Racket &racketRight) :
    m_comet(comet),
    m_bargraph(bargraph),
    m_leftRacket(racketRight)
    {
    }

    void loop()
    {
        //float speed = constrain(m_leftRacket.speed(),0.00, 30.0);
       // m_bargraph.loop();
        m_comet.loop();// empty
   

        float speed = m_leftRacket.speed();
        // Uv Meter
       // m_bargraph.setMapSpeed(speed, 0.0 , 30.0);

        // Comet
        if(m_leftRacket.isHit())
        {
        m_comet.start();
        m_comet.setSpeed       (map( speed, 0.0, 25.0, 0.0, 10.0   ));
        m_comet.setSize        (map( speed, 0.0, 25.0, 0.0, 20.0   ));
        m_comet.setFadeSize    (map( speed, 0.0, 25.0, 223.0, 134.0));
        m_comet.setMidiVelocity(map( speed, 0.0, 25.0, 0.0, 127.0    ));
        }
    }

private:
    Comet       &m_comet;
    Bargraph    &m_bargraph;
    Racket &    m_leftRacket;
};

#endif

     