#ifndef CLOCK_H
#define CLOCK_H

#pragma once
#include "AccelStepper.h"
#include "IMoveBehaviour.h"
#include "MoveConstant.h"
#include "MoveRandomly.h"
#include "MoveTickTack.h"

class Clock
{
public:
    Clock() : stundenZeiger (1, X_STEPPER_STEP_PIN, X_STEPPER_DIR_PIN),
              minutenZeiger (1, Y_STEPPER_STEP_PIN, Y_STEPPER_DIR_PIN),
              sekundenZeiger(1, A_STEPPER_STEP_PIN, A_STEPPER_DIR_PIN )
    {
        moveConstant = new MoveConstant(stundenZeiger, minutenZeiger, sekundenZeiger);
        moveRandomly = new MoveRandomly(stundenZeiger, minutenZeiger, sekundenZeiger);
        moveTickTack = new MoveTickTack(stundenZeiger, minutenZeiger, sekundenZeiger);
    }

    virtual void setup()
    {
        moveConstant->setup();
        moveRandomly->setup();
        moveTickTack->setup();
    }

    void loop()
    {

        setMoveBehaviour(moveConstant);
        executeMoveBehaviour();
    }

private:

//AccelStepper
    const byte X_STEPPER_STEP_PIN  {41};
    const byte X_STEPPER_DIR_PIN   {40};

    const byte Y_STEPPER_STEP_PIN  {39};
    const byte Y_STEPPER_DIR_PIN   {38};

    const byte A_STEPPER_STEP_PIN  {37};
    const byte A_STEPPER_DIR_PIN   {36};

    AccelStepper stundenZeiger;
    AccelStepper minutenZeiger;
    AccelStepper sekundenZeiger;

 //Move Behaviour
    IMoveBehaviour *moveBehaviour;
    IMoveBehaviour *moveConstant;
    IMoveBehaviour *moveRandomly;
    IMoveBehaviour *moveTickTack;
 
 //Set Behaviour on Runtime
    void setMoveBehaviour(IMoveBehaviour *mv)
    {
        this->moveBehaviour = mv;
    }

    void executeMoveBehaviour()
    {
        this->moveBehaviour->loop();
    }
};

#endif