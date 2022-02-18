#ifndef CLOCK_CONSTANT_MOVE_H
#define CLOCK_CONSTANT_MOVE_H

#pragma once
#include <AccelStepper.h>
#include "IMoveBehaviour.h"
class MoveConstant : public IMoveBehaviour
{
public:
  MoveConstant(AccelStepper &xAxis, AccelStepper &yAxis, AccelStepper &aAxis) : IMoveBehaviour(xAxis, yAxis, aAxis)
  {
  }

  void loop()
  {
    m_stundenZeiger.setSpeed(100);
    m_minutenZeiger.setSpeed(9000);
    m_sekundenZeiger.setSpeed(100);

    m_stundenZeiger.runSpeed();
    m_minutenZeiger.runSpeed();
    m_sekundenZeiger.runSpeed();

    
   
  }
};

#endif