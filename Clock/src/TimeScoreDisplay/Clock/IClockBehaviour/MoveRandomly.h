#ifndef MOVERANDOMLY_H
#define MOVERANDOMLY_H

#pragma once
#include <AccelStepper.h>
#include "IMoveBehaviour.h"

class MoveRandomly : public IMoveBehaviour
{
public:
    MoveRandomly(AccelStepper &xAxis, AccelStepper &yAxis, AccelStepper &aAxis) : IMoveBehaviour(xAxis, yAxis, aAxis)
  {
  }

    void loop() 
    {
        m_minutenZeiger.runToNewPosition(0);
        m_minutenZeiger.runToNewPosition(500);

        m_stundenZeiger.runToNewPosition(0);
        m_stundenZeiger.runToNewPosition(500);

        m_sekundenZeiger.runToNewPosition(0);
        m_sekundenZeiger.runToNewPosition(500);

    }


};

#endif