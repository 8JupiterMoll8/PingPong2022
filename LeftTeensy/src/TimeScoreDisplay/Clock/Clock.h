#ifndef CLOCK_H
#define CLOCK_H

#pragma once
#include <AccelStepper.h>
class Clock
{
public:
  Clock(AccelStepper &xAxis, AccelStepper &yAxis, AccelStepper &aAxis) : m_stundenZeiger(xAxis),
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

  void loop()
  {
    m_stundenZeiger.setSpeed(3000);
    m_minutenZeiger.setSpeed(5000);
    m_sekundenZeiger.setSpeed(500);

    m_stundenZeiger.runSpeed();
    m_minutenZeiger.runSpeed();
    m_sekundenZeiger.runSpeed();
  }

  

private:
  AccelStepper &m_stundenZeiger;
  AccelStepper &m_minutenZeiger;
  AccelStepper &m_sekundenZeiger;
};

#endif