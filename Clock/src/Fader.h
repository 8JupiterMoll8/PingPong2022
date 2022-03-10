#ifndef FADER_H
#define FADER_H

#pragma once

#include <TweenDuino.h>

class Fader
{
public:
    Fader():  m_speed(1000.0),
              m_startValue(100.0),
              m_endValue(0.0)
    {
              m_tween = TweenDuino::Tween::to(m_startValue, m_speed, m_endValue);
    }



    TweenDuino::Tween *m_tween;

    float m_speed;
    float m_startValue;
    float m_endValue;

    void setStartValue(float startValue) { m_startValue = startValue; }
    void setSpeed     (float speed     ) { m_speed      = speed;      }
    void setEndValue  (float endValue  ) { m_endValue   = endValue;   }

    void  loop    ()                     { m_tween->update(millis()); }
    float getValue()                     { return m_startValue;       }

    void restart()
    {
        m_startValue = 100;
        m_tween->restartFrom(millis());
        m_tween = TweenDuino::Tween::to(m_startValue, m_speed, m_endValue);
    }

    boolean isComplete()
    {
        if (m_tween->isComplete())
            return true;
        else
            return false;
    }
};

#endif







