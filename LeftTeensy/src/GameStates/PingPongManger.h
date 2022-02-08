#ifndef PINGPONGMANGER_H
#define PINGPONGMANGER_H
#pragma once
#include "GameManager.h"

class PingPongManger : public GameManager
{
public:
    PingPongManger(RacketLeft &leftRacket, RacketRight &rightRacket, Table &leftTable, Table &rightTable) :
    GameManager(leftRacket, rightRacket, leftTable, rightTable)
    {
    }

private:
    virtual void lr_hitAufschlag() override
    {
        usbMIDI.sendNoteOn(random(32, 73), 127, 4);
    };

    virtual void lt_hitAufschalg() override
    {
        usbMIDI.sendNoteOn(random(32, 73), 127, 4);
    };

    virtual void rr_hitAufschlag() override
    {
        usbMIDI.sendNoteOn(random(32, 73), 127, 4);
    };

    virtual void rt_hitAufschlag() override
    {
        usbMIDI.sendNoteOn(random(32, 73), 127, 4);
    };


    virtual void lr_hitBallwechsel() override
    {
        usbMIDI.sendNoteOn(random(32, 73), 127, 4);
    };

    virtual void lt_hitBallwechsel() override
    {
        usbMIDI.sendNoteOn(random(32, 73), 127, 4);
    };

    virtual void rr_hitBallwechsel() override
    {
        usbMIDI.sendNoteOn(random(32, 73), 127, 4);
    };

    virtual void rt_hitBallwechsel() override
    {
        usbMIDI.sendNoteOn(random(32, 73), 127, 4);
    };

    virtual void error() override
    {
         usbMIDI.ControlChange(78,127,9);
    }

};

#endif
