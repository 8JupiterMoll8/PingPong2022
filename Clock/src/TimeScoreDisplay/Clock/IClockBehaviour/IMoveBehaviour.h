#ifndef I_CLOCK_MOVE_BEHAVIOUR_H
#define I_CLOCK_MOVE_BEHAVIOUR_H
#pragma once
#include "AccelStepper.h"

class IMoveBehaviour
{
public:
  IMoveBehaviour(AccelStepper &xAxis, AccelStepper &yAxis, AccelStepper &aAxis) : m_stundenZeiger(xAxis),
                                                                                    m_minutenZeiger(yAxis),
                                                                                    m_sekundenZeiger(aAxis)
  {
  }

  void setup()
  {
    m_stundenZeiger.setMaxSpeed(12800);
    m_stundenZeiger.setSpeed(10000); // had to slow for my motor
    m_stundenZeiger.setAcceleration(100.0);

    m_minutenZeiger.setMaxSpeed(12800);
    m_minutenZeiger.setSpeed(10000); // had to slow for my motor
    m_minutenZeiger.setAcceleration(100.0);

    m_sekundenZeiger.setMaxSpeed(12800);
    m_sekundenZeiger.setSpeed(10000); // had to slow for my motor
    m_sekundenZeiger.setAcceleration(100.0);
  }

  virtual void loop() = 0;

protected:
  AccelStepper &m_stundenZeiger;
  AccelStepper &m_minutenZeiger;
  AccelStepper &m_sekundenZeiger;
};

#endif